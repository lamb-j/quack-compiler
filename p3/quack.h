#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

class statement_node {
	public:
		virtual void print() = 0;
		virtual int evaluate() = 0;
};


class exp_node : public statement_node {
	public:
		int num;

};

class return_node : public statement_node {
	public:
		return_node(exp_node *rv);
		void print();
		int evaluate();

		exp_node *return_value;
};
		
class operator_node : public exp_node {
	public:
		exp_node *left;
		exp_node *right;

		operator_node(exp_node *L, exp_node *R);
};

class plus_node : public operator_node {
	public:

		plus_node(exp_node *L, exp_node *R);
		void print();
		int evaluate();
};

class minus_node : public operator_node {
	public:

		minus_node(exp_node *L, exp_node *R);
		void print();
		int evaluate();
};

class int_node : public exp_node {
	public:
		int_node(int value);
		void print();
		int evaluate();
};
