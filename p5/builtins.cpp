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


Value *method_node::builtins()
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
	return nullptr;
}
