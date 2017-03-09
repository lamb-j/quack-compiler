#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <vector>
#include <cstdio>
#include "quack.h"
using namespace std;

// external data structures
extern vector < tree_node *> *tree_vector;
extern int error_flag;

string if_node::codegen()
{
	if_body->codegen();

	//elseif
	vector<r_expr_node *>::const_iterator c_iter;
	vector<statement_block_node *>::const_iterator b_iter;

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
	return "Nothing";
}

string while_node::codegen()
{
	condition->codegen();
	body->codegen();

	return "Nothing";
}

string statement_block_node::codegen()
{
	vector<statement_node *>::const_iterator iter;
	for (iter = statements->begin(); iter != statements->end(); ++iter) {
		(*iter)->codegen();
	}
	return "Nothing";
}

string class_sig_node::codegen()
{

	return "Nothing";
}
//local and field map are NULL. Maps are generated here
string class_node::codegen()
{

	sig->codegen();
	body->codegen();
	return "Nothing";
}

string program_node::codegen(tree_node *root)
{

	codegen_class(root);

	vector<statement_node *>::const_iterator s_iter;
	for (s_iter = statement_vector->begin(); s_iter != statement_vector->end(); ++s_iter) {
		(*s_iter)->codegen();
	}

	return "Nothing";
}

string method_node::codegen()
{
	
	body->codegen();
	return "Nothing";
}

string class_body_node::codegen()
{
	for (int i = 0;  i < statement_vector->size(); ++i) {
		(*statement_vector)[i]->codegen();
	}

	for (int i = 0;  i < method_vector->size(); ++i) {
		(*method_vector)[i]->codegen();
	}

	return "Nothing";
}

string return_node::codegen()
{

	if (return_value != NULL ) {
		return_value->codegen();
	}

	return "Nothing";
}

string l_expr_node::codegen()
{

return "Nothing";
}

string assign_node::codegen()
{
  lhs->codegen();
  rhs->codegen();

	return "Nothing";
}

string constructor_call_node::codegen()
{

	for (int i = 0; i < arg_vector->size(); ++i) {
		(*arg_vector)[i]->codegen();
	}

	return "Nothing";
}

// may need to push this out to static_checks.cpp to avoid wrong error messages
string method_call_node::codegen()
{

	instance->codegen();

	for (int i = 0; i < arg_vector->size(); ++i) {
		(*arg_vector)[i]->codegen();
	}

	return "Nothing";
}

string plus_node::codegen()
{
	left->codegen();
	right->codegen();

	return "Nothing";
}

string int_node::codegen()
{
	return "Nothing";
}

string str_node::codegen()
{
	return "Nothing";
}
