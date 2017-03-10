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
	if_body->codegen();

	//elseif
	std::vector<r_expr_node *>::const_iterator c_iter;
	std::vector<statement_block_node *>::const_iterator b_iter;

	c_iter = elif_pairs->elif_conditions->begin();
	b_iter = elif_pairs->elif_bodies->begin();

	for (int i = 0; i < elif_pairs->size; i++, c_iter++, b_iter++) {
		(*c_iter)->codegen();
		(*b_iter)->codegen();
	}

	//else
	if(else_body != NULL)
	{	
		else_body->codegen();
	}
	return nullptr;
}

Value *while_node::codegen()
{
	condition->codegen();
	body->codegen();

	return nullptr;
}

Value *statement_block_node::codegen()
{
	Value *v;
	for (int i = 0; i < statements->size(); i++) { 
		v = (*statements)[i]->codegen();
	}
	return nullptr;
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

	//codegen_class(root);
  tree_node *test_int_node =	get_tree_node(tree_vector, "Int");
	test_int_node->AST_node->codegen();

	for (int i = 0; i < statement_vector->size(); i++) {
		(*statement_vector)[i]->codegen();
	}

	return nullptr;
}

Value *method_node::codegen()
{

	// Prototype
	// Make the function type
	std::vector<Type *> mTypes(formal_args->size(), Type::getDoubleTy(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getDoubleTy(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, string(method_name), TheModule.get() );

	//for (int i = 0; i < formal_args->size(); i++) {
	//	mTypes[i] = (*formal_args)[i]->return_type;
	//}

	unsigned Idx = 0;
	for (auto &Arg : F->args()) {
		string name = string( (* formal_args)[Idx++]->name );
		Arg.setName( name );
	}

	// Function 
  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
	Builder.SetInsertPoint(BB);

	NamedValues.clear();
	for (auto &Arg : F->args())
		NamedValues[Arg.getName()] = &Arg;

	if (!strcmp(method_name, "PLUS") ) {
		Value *x = NamedValues["x"];
		Value *y = NamedValues["y"];

		Value *b = Builder.CreateFAdd(x, y, "addtmp");
		Builder.CreateRet(b);

		verifyFunction(*F);
		printf("Succesfully made function '%s'\n", method_name); 

		F->print(errs());
		return F;
	}


	else if (Value *RetVal = body->codegen() ) {
		Builder.CreateRet(RetVal);
 
		verifyFunction(*F);
		printf("Succesfully made function '%s'\n", method_name); 
	
		return F;
	}

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

	if (return_value != NULL ) {
		return_value->codegen();
	}

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

Value *plus_node::codegen()
{
	Value *L = left->codegen();
	Value *R = right->codegen();

	Value *b = Builder.CreateFAdd(L, R, "addtmp");

	return b;
}

Value *int_node::codegen()
{
	Value *v = ConstantFP::get(TheContext, APFloat((float) num));

	return v;
}

Value *str_node::codegen()
{
	return nullptr;
}
