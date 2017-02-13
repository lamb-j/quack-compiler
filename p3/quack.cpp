#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include <cstdio>
#include "quack.h"
using namespace std;

return_node::return_node(exp_node *rv) {
	return_value = rv;
}

void return_node::print() {
	if (return_value == NULL) 
		printf("empty\n");
	else 
		return_value->print();
}

int return_node::evaluate() {
  printf("return_node: return value =\n");
	if (return_value == NULL) 
		printf("empty\n");
	else 
		return_value->evaluate();
}

operator_node::operator_node(exp_node *L, exp_node *R) {
	left  = L;
	right = R;
}


plus_node::plus_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void plus_node::print() {
	printf("(");
	left->print();
	printf(" + ");
	right->print();
	printf(")\n");
}

int plus_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	num = left_num + right_num;

	printf("plus_node: %d + %d = %d\n", left_num, right_num, num);
	return num;
}

minus_node::minus_node(exp_node *L, exp_node *R) : operator_node(L,R) {}

void minus_node::print() {
	printf("(");
	left->print();
	printf(" - ");
	right->print();
	printf(")\n");
}

int minus_node::evaluate() {
	int left_num, right_num;

	left_num = left->evaluate();
	right_num = right->evaluate();

	num = left_num - right_num;

	printf("minus_node: %d - %d = %d\n", left_num, right_num, num);
	return num;
}

int_node::int_node(int value) {
	num = value;
}

void int_node::print() {
	printf("%d\n", num);
}

int int_node::evaluate() {
	printf("int node: operand = %d\n", num);
	return num;
}
