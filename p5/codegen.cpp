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

	if_cond_v = Builder.CreateICmpEQ( if_cond_v, ConstantInt::get(TheContext, APInt( 32, 0, false )), "if_cond" );

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

	loop_cond_v = Builder.CreateICmpEQ( loop_cond_v, ConstantInt::get(TheContext, APInt( 32, 0, false )), "loop_cond" );
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
  tree_node *test_int_node =	get_tree_node(tree_vector, "Int");
	test_int_node->AST_node->codegen();

	// Main Function 
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
	if (!strcmp(method_name, "PLUS") ) {

		// Prototype
		std::vector<Type *> mTypes(formal_args->size(), Type::getInt32Ty(TheContext) );
		FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
		Function *F = Function::Create(FT, Function::ExternalLinkage, string(method_name), TheModule.get() );

		unsigned Idx = 0;
		for (auto &Arg : F->args()) {
			string name = string( (* formal_args)[Idx++]->name );
			Arg.setName( name );
		}

		NamedValues.clear();
		for (auto &Arg : F->args())
			NamedValues[Arg.getName()] = &Arg;


		// Function Body
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
		Builder.SetInsertPoint(BB);

		Value *x = NamedValues["x"];
		Value *y = NamedValues["y"];

		Value *b = Builder.CreateAdd(x, y, "addtmp");
		Builder.CreateRet(b);

		verifyFunction(*F);

		//F->print(errs());
		return F;
	}

	if (!strcmp(method_name, "MINUS") ) {

		// Prototype
		std::vector<Type *> mTypes(formal_args->size(), Type::getInt32Ty(TheContext) );
		FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
		Function *F = Function::Create(FT, Function::ExternalLinkage, string(method_name), TheModule.get() );

		unsigned Idx = 0;
		for (auto &Arg : F->args()) {
			string name = string( (* formal_args)[Idx++]->name );
			Arg.setName( name );
		}

		NamedValues.clear();
		for (auto &Arg : F->args())
			NamedValues[Arg.getName()] = &Arg;


		// Function Body
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
		Builder.SetInsertPoint(BB);

		Value *x = NamedValues["x"];
		Value *y = NamedValues["y"];

		Value *b = Builder.CreateSub(x, y, "minus_tmp");
		Builder.CreateRet(b);

		verifyFunction(*F);

		//F->print(errs());
		return F;
	}
	if (!strcmp(method_name, "PRINT") ) {

		// Prototype
		std::vector<Type *> mTypes;
		mTypes.push_back( llvm::Type::getInt32Ty(TheContext) );

		FunctionType *FT = FunctionType::get(
				Type::getInt32Ty(TheContext), mTypes, false);

		Function *F = Function::Create(FT, Function::ExternalLinkage, "PRINT",  TheModule.get() );

		unsigned Idx = 0;
		for (auto &Arg : F->args()) {
			string name = string( (* formal_args)[Idx++]->name );
			Arg.setName( name );
		}

		NamedValues.clear();
		for (auto &Arg : F->args())
			NamedValues[Arg.getName()] = &Arg;

		// Funciton Body
		BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
		Builder.SetInsertPoint(BB);

		Value* this_val = NamedValues["this"];
		Value *formatStr = Builder.CreateGlobalStringPtr("value = %d\n");

		std::vector<Value *> ArgsV;
		ArgsV.push_back(formatStr);
		ArgsV.push_back(this_val);

		Function *CalleeF = TheModule->getFunction( "printf" );
		
	  Value* b = Builder.CreateCall(CalleeF, ArgsV, "calltemp");
		Builder.CreateRet(b);

		verifyFunction(*F);

		//F->print(errs());
		return F;
	}

//	else if (Value *RetVal = body->codegen() ) {
//		Builder.CreateRet(RetVal);
//
//		verifyFunction(*F);
//
//		return F;
//	}
//
//	F->eraseFromParent();
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

	if (return_value != NULL ) {
		Builder.CreateRet(return_value->codegen());
	}
	else
		Builder.CreateRetVoid();

	return nullptr;
}

Value *l_expr_node::codegen()
{

	return nullptr;
}

Value *assign_node::codegen()
{
	lhs->codegen();
	rhs->codegen();

	return nullptr;
}

Value *constructor_call_node::codegen()
{

	for (int i = 0; i < arg_vector->size(); ++i) {
		(*arg_vector)[i]->codegen();
	}

	return nullptr;
}

//call_expr
Value *method_call_node::codegen()
{
	//instance->codegen();

	Function *CalleeF = TheModule->getFunction( string(modifier) );

	if (!CalleeF) {
		fprintf(stderr, "error:%d: Unknown function %s referenced\n", lineno, modifier);
		error();
	}

	if (CalleeF->arg_size() != arg_vector->size() ) {
		fprintf(stderr, "error:%d: Arg sizes in codegen don't match\n", lineno);
		error();
	}

	std::vector<Value *> ArgsV;
	for (int i = 0; i < arg_vector->size(); ++i) {
		ArgsV.push_back( (*arg_vector)[i]->codegen() );
		if (!ArgsV.back())
			return nullptr;
	}

	return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}
/*
Value *plus_node::codegen()
{
	Value *L = left->codegen();
	Value *R = right->codegen();

	Value *b = Builder.CreateFAdd(L, R, "addtmp");

	return b;
}
*/

Value *int_node::codegen()
{
	Value *v = ConstantInt::get(TheContext, APInt(32, num, false));

	return v;
}

Value *str_node::codegen()
{
	return nullptr;
}
