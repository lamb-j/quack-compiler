#include <string>
#include <vector>

using namespace std;

// tree data structure
class tree_node {
	public:
		string name;
		tree_node *parent;
		vector <tree_node *> children;

    tree_node(string n) { name = n ; }
};

int print_tree( tree_node *root, int level );

void append_tree( list <tree_node *> *tree_list, string parent_class, string new_class);

