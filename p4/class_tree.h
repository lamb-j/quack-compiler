#include <string>
#include <vector>

using namespace std;

// tree data structure
class tree_node {
	public:
		string name;
		tree_node *parent;
		vector <tree_node *> children;

		vector <string > method_names;
		
		// add methods/arguments

    tree_node(string n) { name = n ; }
};

int print_tree( tree_node *root, int level );

tree_node * append_tree( list <tree_node *> *tree_list, string parent_class, string new_class);

tree_node * get_tree_node(list < tree_node *> *tree_node_list, string cname);

int class_defines_method(tree_node * class_node, string method_name);

string least_common_ancestor(string A, string B);

tree_node * least_common_ancestor(tree_node *A, tree_node *B);

