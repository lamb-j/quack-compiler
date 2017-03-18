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

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder;
extern std::map<std::string, llvm::Value *> NamedValues;
extern std::unique_ptr<llvm::Module> TheModule;

Function *Int_PLUS_codegen		(vector <f_arg_pair *> *formal_args);
Function *Int_MINUS_codegen		(vector <f_arg_pair *> *formal_args);
Function *Int_TIMES_codegen		(vector <f_arg_pair *> *formal_args);
Function *Int_DIVIDE_codegen	(vector <f_arg_pair *> *formal_args);
Function *Int_ATMOST_codegen	(vector <f_arg_pair *> *formal_args);
//Function *Int_ATLEAST_codegen	(vector <f_arg_pair *> *formal_args);
//Function *Int_LESS_codegen		(vector <f_arg_pair *> *formal_args);
//Function *Int_MORE_codegen		(vector <f_arg_pair *> *formal_args);
//Function *Int_EQUALS_codegen	(vector <f_arg_pair *> *formal_args);

Function *Int_PRINT_codegen(vector <f_arg_pair *> *formal_args);

Function *method_node::builtins()
{
	// Int methods
	if (!strcmp(method_name, "PLUS") )		return Int_PLUS_codegen(formal_args);
	if (!strcmp(method_name, "MINUS") )		return Int_MINUS_codegen(formal_args);
	if (!strcmp(method_name, "TIMES") )		return Int_TIMES_codegen(formal_args);
	if (!strcmp(method_name, "DIVIDE") )	return Int_DIVIDE_codegen(formal_args);
	if (!strcmp(method_name, "ATMOST") )	return Int_ATMOST_codegen(formal_args);
	//if (!strcmp(method_name, "ATLEAST") ) return Int_ATMOST_codegen(formal_args);
	//if (!strcmp(method_name, "LESS") )		return Int_ATMOST_codegen(formal_args);
	//if (!strcmp(method_name, "MORE") )		return Int_ATMOST_codegen(formal_args);
	//if (!strcmp(method_name, "EQUALS") )	return Int_ATMOST_codegen(formal_args);

	if (!strcmp(method_name, "PRINT") ) return Int_PRINT_codegen(formal_args);

	// no default function matched
	printf("ERROR not default function\n");
	return nullptr;
}

Function *Int_PLUS_codegen(vector <f_arg_pair *> *formal_args) 
{
	std::vector<Type *> mTypes(2, Type::getInt32Ty(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, 
			"PLUS", TheModule.get() );

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

  Value *x_ptr = Builder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, "x_ptr");
  Value *y_ptr = Builder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, "y_ptr");

  Builder.CreateStore(x, x_ptr, false);
  Builder.CreateStore(y, y_ptr, false);

  x = Builder.CreateLoad(Type::getInt32Ty(TheContext), x_ptr, "x_load");
  y = Builder.CreateLoad(Type::getInt32Ty(TheContext), y_ptr, "y_load");

	Value *b = Builder.CreateAdd(x, y, "addtmp");
	Builder.CreateRet(b);

	verifyFunction(*F);

	return F;
}

Function *Int_MINUS_codegen(vector <f_arg_pair *> *formal_args) 
{
	std::vector<Type *> mTypes(formal_args->size(), Type::getInt32Ty(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, 
			"MINUS", TheModule.get() );

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

	return F;
}

Function *Int_TIMES_codegen(vector <f_arg_pair *> *formal_args) 
{
	std::vector<Type *> mTypes(2, Type::getInt32Ty(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, 
			"TIMES", TheModule.get() );

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

	Value *b = Builder.CreateMul(x, y, "multmp");
	Builder.CreateRet(b);

	verifyFunction(*F);

	return F;
}

Function *Int_DIVIDE_codegen(vector <f_arg_pair *> *formal_args) 
{
	std::vector<Type *> mTypes(2, Type::getInt32Ty(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getInt32Ty(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, 
			"DIVIDE", TheModule.get() );

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

	Value *b = Builder.CreateSDiv(x, y, "divtmp");
	Builder.CreateRet(b);

	verifyFunction(*F);

	return F;
}

Function *Int_ATMOST_codegen(vector <f_arg_pair *> *formal_args) 
{
	std::vector<Type *> mTypes(2, Type::getInt32Ty(TheContext) );
	FunctionType *FT = FunctionType::get(Type::getInt1Ty(TheContext), mTypes, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, 
			"ATMOST", TheModule.get() );

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

	Value *b = Builder.CreateICmpULE( x, y, "cmptmp");

	Builder.CreateRet(b);

	verifyFunction(*F);

	return F;
}

Function *Int_PRINT_codegen(vector <f_arg_pair *> *formal_args)
{
	std::vector<Type *> mTypes;
	mTypes.push_back( llvm::Type::getInt32Ty(TheContext) );

	FunctionType *FT = FunctionType::get(
			Type::getInt32Ty(TheContext), mTypes, false);

	Function *F = Function::Create(FT, 
			Function::ExternalLinkage, "PRINT",  TheModule.get() );

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

	return F;
}
