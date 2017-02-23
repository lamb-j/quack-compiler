#include <string>
#include <vector>

using namespace std;

// tree data structure
class tree_node {
	public:
		string name;
		tree_node *parent;
		vector <tree_node *> children;

		// add methods/arguments

    tree_node(string n) { name = n ; }
};

int print_tree( tree_node *root, int level );

void append_tree( list <tree_node *> *tree_list, string parent_class, string new_class);

// int is_subclass(tree_node *A, tree_node *B)

// int is_superclass(tree_node *A, tree_node *B)

// tree_node * least_common_ancestor(tree_node *A, tree_node *B)

// int valid_method_override(method *sub_method, method *super_method)
