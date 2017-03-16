#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <cstdio>
#include "quack.h"
using namespace llvm;

// external data structures
extern std::vector < tree_node *> *tree_vector;
extern int error_flag;

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::map<std::string, llvm::Value *> NamedValues;
std::unique_ptr<llvm::Module> TheModule;

Value *if_node::codegen()
{

	Value *if_cond_v = if_condition->codegen();

	if( !if_cond_v ) {
		return nullptr;
	}

	if_cond_v = Builder.CreateICmpEQ( if_cond_v, ConstantInt::get(TheContext, APInt( 1, 1, false )), "if_cond" );

	Function *F = Builder.GetInsertBlock()->getParent();

	// Setting up the bulding blocks for if and else
	BasicBlock *ifBB = BasicBlock::Create(TheContext, "if_body", F);
	BasicBlock *elseBB = BasicBlock::Create(TheContext, "else_body");

	vector <BasicBlock *> elif_body_BB;
	vector <BasicBlock *> elif_inter_BB;
	for (int i = 0; i < elif_pairs->size; i++) {
		elif_body_BB.push_back ( BasicBlock::Create(TheContext, "elif_body") );
		elif_inter_BB.push_back ( BasicBlock::Create(TheContext, "elif_inter") ); 
	}

	BasicBlock *mergeBB = BasicBlock::Create(TheContext, "if_cont");

	BasicBlock *next;

	if (elif_pairs->size) 
		next = elif_inter_BB[0];
	else
		next = elseBB;

	// if condition
	Builder.CreateCondBr(if_cond_v, ifBB, next);

	// Emit the if_body
	Builder.SetInsertPoint(ifBB);
	Value *if_body_v = if_body->codegen();

	Builder.CreateBr(mergeBB);
	Builder.GetInsertBlock();
	
	// Emit the else_if body(s)
	for (int i = 0; i < elif_pairs->size; i++) {

		if (elif_pairs->size - 1 == i) 
			next = elseBB;
		else
			next = elif_inter_BB[i + 1];

		// Emit intermediate node code
		F->getBasicBlockList().push_back(elif_inter_BB[i] );
		Builder.SetInsertPoint(elif_inter_BB[i] );

		Value *elif_cond_v = (*elif_pairs->elif_conditions)[i]->codegen();

		elif_cond_v = Builder.CreateICmpEQ( elif_cond_v, ConstantInt::get(TheContext, APInt( 32, 0, false )), "elif_cond" );
		Builder.CreateCondBr(elif_cond_v, elif_body_BB[i], next);
		
		// Emit elif body code
		F->getBasicBlockList().push_back(elif_body_BB[i]);
		Builder.SetInsertPoint(elif_body_BB[i]);
		Value *elif_body_v = (*elif_pairs->elif_bodies)[i]->codegen();

		Builder.CreateBr(mergeBB);
		Builder.GetInsertBlock();
	}

	// Emit the else_body
	F->getBasicBlockList().push_back(elseBB);
	Builder.SetInsertPoint(elseBB);

	if (else_body != NULL) else_body->codegen();

	Builder.CreateBr(mergeBB);
	Builder.GetInsertBlock();
	
	// Emit the merge block
	F->getBasicBlockList().push_back(mergeBB);
	Builder.SetInsertPoint(mergeBB);

	verifyFunction(*F);
	return nullptr;
	//return PN;
}

Value *while_node::codegen()
{
	Function *F = Builder.GetInsertBlock()->getParent();
	BasicBlock *loop_inter_BB = BasicBlock::Create(TheContext, "loop_inter", F);
	BasicBlock *loopBB = BasicBlock::Create(TheContext, "loop", F);
	BasicBlock *afterBB = BasicBlock::Create(TheContext, "afterloop", F);

	Builder.CreateBr(loop_inter_BB);

	// inter
	Builder.SetInsertPoint(loop_inter_BB);

	Value *loop_cond_v = condition->codegen();

	loop_cond_v = Builder.CreateICmpEQ( loop_cond_v, 
			ConstantInt::get(TheContext, APInt( 1, 1, false )), "loop_cond" );
	Builder.CreateCondBr(loop_cond_v, loopBB, afterBB);

	// loop body
	Builder.SetInsertPoint( loopBB );
	body->codegen();

	Builder.CreateBr(loop_inter_BB);

	//after loop block
	Builder.SetInsertPoint(afterBB);

	return nullptr;
}

Value *statement_block_node::codegen()
{
	printf("in SBN\n");
	Value *v;
	for (int i = 0; i < statements->size(); i++) { 
		v = (*statements)[i]->codegen();
	}
	return v;
}

Value *class_sig_node::codegen()
{

	return nullptr;
}
//local and field map are NULL. Maps are generated here
Value *class_node::codegen()
{

	sig->codegen();
	body->codegen();
	return nullptr;
}

Value *program_node::codegen(tree_node *root)
{
	printf("In pgm node\n");

	// Generate C functions
  // printf
	std::vector<Type*> printf_arg_types;
	printf_arg_types.push_back(Type::getInt8PtrTy(TheContext));

	FunctionType* printf_type =
		FunctionType::get(
				Type::getInt32Ty(TheContext), printf_arg_types, true);

	Function *func = Function::Create(
			printf_type, Function::ExternalLinkage,
			Twine("printf"),
			TheModule.get()
			);
	func->setCallingConv(CallingConv::C);

	//codegen_class(root);
	get_tree_node(tree_vector, "Int")->AST_node->codegen();
	get_tree_node(tree_vector, "A")->AST_node->codegen();

	// Main Function 
  NamedValues.clear();

	FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, "main",  TheModule.get() );

  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
	Builder.SetInsertPoint(BB);

	// Generate Code for statements
	for (int i = 0; i < statement_vector->size(); i++) {
		(*statement_vector)[i]->codegen();
	}

	verifyFunction(*F);

	Builder.CreateRet( ConstantInt::get(TheContext, APInt( 32, 0, false )  ) );
	return F;

	//F->eraseFromParent();
	//return nullptr;
}

Value *method_node::codegen()
{
	Function *F;

	// check if method is a built-in method
  F = builtins();

	if ( F ) {
		return F;
	}
	else {
		std::vector<Type *> mTypes( formal_args->size() , Type::getInt32Ty(TheContext) );
		FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
		Function *F = Function::Create(FT, Function::ExternalLinkage,
				string(method_name), TheModule.get() );

		unsigned Idx = 0;
		for (auto &Arg : F->args()) {
			string name = string( (* formal_args)[Idx++]->name );
			Arg.setName( name );
		}

		NamedValues.clear();
		for (auto &Arg : F->args()) {
		  printf("Arg: %s\n", Arg.getName().str().c_str()) ;
			NamedValues[Arg.getName()] = &Arg;
    }

		if (NamedValues.find("x") == NamedValues.end()) {
			printf("VAL NOT IN MAP\n");
		}
    else
      printf("VAL IN MAP!\n");

		// Function Body
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
		Builder.SetInsertPoint(BB);

		Value *RetVal = body->codegen(); 
		Builder.CreateRet(RetVal);

 	  verifyFunction(*F);

		return F;
	}

	printf("ERROR, NO FUNCTION BUILT\n");

	F->eraseFromParent();
	return nullptr;
}

Value *class_body_node::codegen()
{
	for (int i = 0;  i < statement_vector->size(); ++i) {
		(*statement_vector)[i]->codegen();
	}

	for (int i = 0;  i < method_vector->size(); ++i) {
		(*method_vector)[i]->codegen();
	}

	return nullptr;
}

Value *return_node::codegen()
{
	printf("in RET node\n");

	if (return_value != NULL ) {
		Builder.CreateRet(return_value->codegen());
	}
	else
		Builder.CreateRetVoid();

	return nullptr;
}

Value *l_expr_node::codegen()
{
	printf("in l_expr_node\n");
printf("---\n");
for(auto it = NamedValues.cbegin(); it != NamedValues.cend(); ++it)
{
    std::cout << it->first << " " << it->second << "\n";
}
printf("---\n");

  printf("find x\n");
  NamedValues.find("x");
  printf("find end\n");
  NamedValues.end();

  printf("compare\n");

  if ( NamedValues.find("x") == NamedValues.end() ) {
		printf("VAL NOT IN MAP\n");
	}

	Value *v = NamedValues[string(var)] ;

  if ( !v ) printf("BAD VALUE\n");

  Value *b = Builder.CreateLoad(v, "load_var");
	return b; 
}

Value *assign_node::codegen()
{
	printf("in ASS node\n");
  
	Value *lhs_v;
	// Get var name
	if(!NamedValues[var_name])
	{
		lhs_v = Builder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, var_name);
		NamedValues[var_name] = lhs_v;
	}
	else
		lhs_v = NamedValues[var_name];
		
	Value *rhs_v = rhs->codegen();

  Value *v = 	Builder.CreateStore(rhs_v, lhs_v, false);

	// add lhs to map

	return v; 
}

Value *constructor_call_node::codegen()
{
	printf("in CCall node\n");

	for (int i = 0; i < arg_vector->size(); ++i) {
		(*arg_vector)[i]->codegen();
	}

	return nullptr;
}

//call_expr
Value *method_call_node::codegen()
{

	//instance->codegen();
	printf("in method_call_node: %s\n", modifier);

	Function *CalleeF = TheModule->getFunction( string(modifier) );

	printf("created CALEEF\n");
	if (!CalleeF) {
		fprintf(stderr, "error:%d: Unknown function %s referenced\n", lineno, modifier);
		error();
	}

	if (CalleeF->arg_size() != arg_vector->size() ) {
		fprintf(stderr, "error:%d: Arg sizes in codegen don't match\n", lineno);
		error();
	}

	std::vector<Value *> ArgsV;
	printf("arg vec size:%lu\n",arg_vector->size());
	for (int i = 0; i < arg_vector->size(); ++i) {
		printf("looping over args\n");
		(*arg_vector)[i]->print(0);
		ArgsV.push_back( (*arg_vector)[i]->codegen() );
		printf("hereee\n");
		if (!ArgsV.back()) {
      printf("Bad Args\n");
			return nullptr;
		}
	}


	printf("Creating method call\n");
	return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Value *int_node::codegen()
{
	printf("in INT node\n");
	Value *v = ConstantInt::get(TheContext, APInt(32, num, false));

	return v;
}

Value *str_node::codegen()
{
	printf("in STR node\n");
	return nullptr;
}
