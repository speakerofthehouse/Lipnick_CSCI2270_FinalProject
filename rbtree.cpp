#include <iostream>
#include <string>
#include "rbtree.h"

/*
Class is created with the root as NULL
*/
RBTree::RBTree() {
	root = NULL;
}

RBTree::~RBTree() {
	
}
/*
Method: insert
Description: This function adds a node to the red-black tree. It handles the balancing required and not the new node creation itself.
Pre-conditions: There are no pre-conditions needed for this method to work
Post-conditions: A node will be added to the tree. The tree will be adjusted to keep the red-black characteristics.
*/
void RBTree::insert(std::string _key) {
	node *x = new node();
	x = insertNode(_key);
	while (x != root && x->parent->color == "red") {
		if (x->parent == x->parent->parent->left) {
			node *uncle = x->parent->parent->right;
			if (uncle->color == "red") {
				x->parent->color = "black";
				uncle->color = "black";
				x->parent->parent->color = "red";
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->right) {
					x = x->parent;
					leftRotate(x);
				}
				x->parent->color = "black";
				x->parent->parent->color = "red";
				rightRotate(x->parent->parent);
			}
		}
		else {
				// x->parent is a right child
			node *uncle = x->parent->parent->left;
			if (uncle->color == "red") {
				x->parent->color = "black";
				uncle->color = "black";
				x->parent->parent->color = "red";
				x = x->parent->parent;
			}
			else {
				if (x == x->parent->left) {
					x = x->parent;
					rightRotate(x);
				}
				x->parent->color = "black";
				x->parent->parent->color = "red";
				leftRotate(x->parent->parent);
			}
		}
	}
	root->color = "black";
}

/*
Method: insertNode
Description: This function creates the new node and adds it to the tree in the correct position. The tree then needs to be balanced which is handled by the insert() function.
Pre-conditions: This method is called from insert()
Post-conditions: A new node will be added to the red-black tree in the correct position.  The tree will still need to be balanced afterwards.
*/
node *RBTree::insertNode(std::string _key) {
		// create new node

	node *nullLeft = new node("nullNode", "black", NULL, NULL, NULL);
	node *nullRight = new node("nullNode", "black", NULL, NULL, NULL);
	node *newNode = new node(_key, "red", NULL, nullLeft, nullRight);

	if (root == NULL) {
		root = newNode;
	}
	else {
		node *temp = new node();
		temp = root;
		node *parent = new node();
		parent = NULL;
		// find place in tree to insert
		while (temp->key != "nullNode") {
			parent = temp;
			if (newNode->key.compare(temp->key) < 0){
				temp = temp->left;
			}
			else {
				temp = temp->right;
			}
		}
		if (newNode->key.compare(parent->key) < 0) {
			parent->left = newNode;
			newNode->parent = parent;
		}
		else {
			parent->right = newNode;
			newNode->parent = parent;
		}
	}

	return newNode;
}

/*
Method: leftRotate
Description: This function rotates the tree to help with tree balancing.
Pre-conditions: The tree needs to be balanced in some way.
Post-conditions: Nodes in the tree will be rotated to keep tree balanced.
*/
void RBTree::leftRotate(node *x) {
	node *y = new node();
	node *b = new node();
	y = x->right;
	b = y->left;
	x->right = b;
	b->parent = x;
	y->parent = x->parent;
	if (x->parent == NULL) {
		root = y;
	} 
	else {
		if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}

/*
Method: rightRotate
Description: This function rotates the tree to help with tree balancing.
Pre-conditions: The tree needs to be balanced in some way.
Post-conditions: Nodes in the tree will be rotated to keep tree balanced.
*/
void RBTree::rightRotate(node *y) {
	node *x = new node();
	node *b = new node();
	x = y->left;
	b = x->right;
	y->left = b;
	b->parent = y;
	x->parent = y->parent;
	if (y->parent == NULL) {
		root = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	x->right = y;
	y->parent = x;
}

/*
Method: printTree
Description: This function prints the whole tree.
Pre-conditions: None
Post-conditions: The tree will be printed.
*/
void RBTree::printTree() {
	if (root != NULL) {
		node* temp = new node();
		temp = root;
		if (temp->left != NULL) {
			printTree(temp->left);
		}
		if (temp->key != "nullNode") {
			std::cout << temp->key << " (" << temp->color << "), ";
			if (temp->parent == NULL) {
				std::cout << "root, ";
			}
			else {
				std::cout << "parent: " << temp->parent->key << ", ";
			}
			std::cout << "left: " << temp->left->key << ", ";
			std::cout << "right: " << temp->right->key;
			std::cout << std::endl;
		} 
		if (temp->right != NULL) {
			printTree(temp->right);
		}
	}
	else {
		std::cout << "No names found." << std::endl;
	}
}

/*
Method: printTree
Description: This function helps print the tree. It takes a node as an argument to recusively traverse the tree.
Pre-conditions: None
Post-conditions: The tree will be printed.
*/
void RBTree::printTree(node* temp) {
	if (temp->left != NULL) {
		printTree(temp->left);
	} 
	if (temp->key != "nullNode") {
		std::cout << temp->key << " (" << temp->color << "), ";
		if (temp->parent == NULL) {
			std::cout << "root, ";
		}
		else {
			std::cout << "parent: " << temp->parent->key << ", ";
		}
		std::cout << "left: " << temp->left->key << ", ";
		std::cout << "right: " << temp->right->key;
		std::cout << std::endl;
	}
	if (temp->right != NULL) {
		printTree(temp->right);
	}
}

/*
Method: printRedNodes
Description: This function prints the only the red nodes of the tree.
Pre-conditions: None
Post-conditions: The red nodes will be printed.
*/
void RBTree::printRedNodes() {
	if (root != NULL) {
		node* temp = new node();
		temp = root;
		if (temp->left != NULL) {
			printRedNodes(temp->left);
		}
		if (temp->key != "nullNode" && temp->color == "red") {
			std::cout << temp->key << " (" << temp->color << "), ";
			if (temp->parent == NULL) {
				std::cout << "root, ";
			}
			else {
				std::cout << "parent: " << temp->parent->key << ", ";
			}
			std::cout << "left: " << temp->left->key << ", ";
			std::cout << "right: " << temp->right->key;
			std::cout << std::endl;
		} 
		if (temp->right != NULL) {
			printRedNodes(temp->right);
		}
	}
	else {
		std::cout << "No names found." << std::endl;
	}
}

/*
Method: printRedNodes
Description: This function helps print the red nodes. It takes a node as an argument to recusively traverse the tree.
Pre-conditions: None
Post-conditions: The red nodes will be printed.
*/
void RBTree::printRedNodes(node* temp) {
	if (temp->left != NULL) {
		printRedNodes(temp->left);
	} 
	if (temp->key != "nullNode" && temp->color == "red") {
		std::cout << temp->key << " (" << temp->color << "), ";
		if (temp->parent == NULL) {
			std::cout << "root, ";
		}
		else {
			std::cout << "parent: " << temp->parent->key << ", ";
		}
		std::cout << "left: " << temp->left->key << ", ";
		std::cout << "right: " << temp->right->key;
		std::cout << std::endl;
	}
	if (temp->right != NULL) {
		printRedNodes(temp->right);
	}
}

/*
Method: printBlackNodes
Description: This function prints the only the black nodes of the tree.
Pre-conditions: None
Post-conditions: The black nodes will be printed.
*/
void RBTree::printBlackNodes() {
	if (root != NULL) {
		node* temp = new node();
		temp = root;
		if (temp->left != NULL) {
			printBlackNodes(temp->left);
		}
		if (temp->key != "nullNode" && temp->color == "black") {
			std::cout << temp->key << " (" << temp->color << "), ";
			if (temp->parent == NULL) {
				std::cout << "root, ";
			}
			else {
				std::cout << "parent: " << temp->parent->key << ", ";
			}
			std::cout << "left: " << temp->left->key << ", ";
			std::cout << "right: " << temp->right->key;
			std::cout << std::endl;
		} 
		if (temp->right != NULL) {
			printBlackNodes(temp->right);
		}
	}
	else {
		std::cout << "No names found." << std::endl;
	}
}

/*
Method: printBlackNodes
Description: This function helps print the black nodes. It takes a node as an argument to recusively traverse the tree.
Pre-conditions: None
Post-conditions: The black nodes will be printed.
*/
void RBTree::printBlackNodes(node* temp) {
	if (temp->left != NULL) {
		printBlackNodes(temp->left);
	} 
	if (temp->key != "nullNode" && temp->color == "black") {
		std::cout << temp->key << " (" << temp->color << "), ";
		if (temp->parent == NULL) {
			std::cout << "root, ";
		}
		else {
			std::cout << "parent: " << temp->parent->key << ", ";
		}
		std::cout << "left: " << temp->left->key << ", ";
		std::cout << "right: " << temp->right->key;
		std::cout << std::endl;
	}
	if (temp->right != NULL) {
		printBlackNodes(temp->right);
	}
}

/*
Method: search
Description: This function searches the tree for a given name.
Pre-conditions: There are nodes in the tree.
Post-conditions: The nodes is returned. If it isn't found a nullNode is returned.
*/
node* RBTree::search(std::string name) {
	node *temp = new node();
	temp = root;
	if (root != NULL) {
		bool found = false;
		while (temp->key != "nullNode" && !found) {
			if (temp->key == name) {
				found = true;
			}
			else {
				if (temp->key.compare(name) < 0){
					temp = temp->right;
				}
				else {
					temp = temp->left;
				}
			}
		}
	}
	return temp;
}

/*
Method: deleteNode
Description: This function deletes a node from the tree. It is still a work in progress as a segmentation fault occurs when more than one node is deleted.
Pre-conditions: There are nodes in the tree.
Post-conditions: The nodes will be deleted.
*/
void RBTree::deleteNode(std::string name) {
	if (root != NULL) {
		node *n = search(name);
		if (n != root) {
			if (n->key != "nullNode") {
			// node has been found
				std::cout << n->key << " found. Deleting..." << std::endl;
				std::string nodeColor = n->color;
				node *x = new node();
				// begin node != root
				if (n != root) {
					// begin no children
					if (n->left->key == "nullNode" && n->right->key == "nullNode") {
						node *nullNode = new node("nullNode", "black", NULL, NULL, NULL);
						std::cout << n->key << " has no children." << std::endl;
						// check if n is left or right child of parent
						if (n == n->parent->left) {
							std::cout << n->key << " is left child of its parent." << std::endl;
							n->parent->left = nullNode;
							nullNode->parent = n->parent;
							x = n->left;
						}
						else {
							std::cout << n->key << " is right child of its parent." << std::endl;
							n->parent->right = nullNode;
							nullNode->parent = n->parent;
							x = n->right;
						}
					}
					// end no children
					// begin two children
					else if (n->left->key != "nullNode" && n->right->key != "nullNode") {
						node *min = new node();
						min = minimum(n->right);
						nodeColor = min->color;
						x = min->right;
						if (min == n->right) {
							if (n == n->parent->left) {
								n->parent->left = min;
							}
							else {
								n->parent->right = min;
							}
							min->parent = n->parent;
							min->left = n->left;
							min->left->parent = min;
						}
						else {
							min->parent->left = min->right;
							min->right->parent = min->parent;
							min->parent = n->parent;
							if (n == n->parent->left) {
								n->parent->left = min;
							}
							else {
								n->parent->right = min;
							}
							min->left = n->left;
							min->right = n->right;
							n->right->parent = min;
							n->left->parent = min;
						}
						min->color = n->color;
					}
					// end two children
					// begin one child
					else {
						// check if single child is left or right child
						if (n->left->key != "nullNode" && n->right->key == "nullNode") {
							x = n->left;
						}
						else if (n->right->key != "nullNode" && n->left->key == "nullNode") {
							x = n->right;
						}
						// check if n is left or right child of parent
						if (n == n->parent->left) {
							n->parent->left = x;
							x->parent = n->parent;
						}
						else {
							n->parent->right = x;
							x->parent = n->parent;
						}
					}
					// end one child
				} // end node != root
				else {
					// node is root
					std::cout << "Cannot delete root." << std::endl;
				}
				if (nodeColor == "black") {
					std::cout << "Node Color is black. Running balance on " << x->key << std::endl;
					balance(x);
				}
				std::cout << "Commencing final deletion." << std::endl;
				if (n->left->key == "nullNode") {
					delete n->left;
				}
				if (n->right->key == "nullNode") {
					delete n->right;
				}
				std::cout << n->key << " deleted." << std::endl;
				delete n;
			}
			else {
				std::cout << "Not found." << std::endl;
			}
		}
		else {
			// node is root
			std::cout << "Cannot currently delete root." << std::endl;
		}
	}
	else {
		std::cout << "No nodes found." << std::endl;
	}
}

/*
Method: balance
Description: This function helps balance the tree. There may be something wrong with the code as a segmentation fault occurs when deleting and this function is called.
Pre-conditions: The function is called from the delete function.
Post-conditions: The tree will be balanced.
*/
void RBTree::balance(node *x) {
	std::cout << "Balance check 1" << std::endl;
	while (x != root && x->color == "black") {
		std::cout << "Balance check 2" << std::endl;
		if (x == x->parent->left) {
			std::cout << "Balance check 3" << std::endl;
			std::cout << "x is left child." << std::endl;
			node *s = new node();
			s = x->parent->right;
			if (s->color == "red") {
				s->color = "black";
				x->parent->color = "red";
				std::cout << "leftrotating..." << std::endl;
				leftRotate(x->parent);
				s = x->parent->right;
			}
			if (s->left->color == "black" && s->right->color == "black") {
				s->color = "red";
				x = x->parent;
			}
			else if (s->left->color == "red" && s->right->color == "black") {
				s->left->color = "black";
				s->color = "red";
				std::cout << "rightrotating" << std::endl;
				rightRotate(s);
				s = x->parent->right;
			}
			else {
				s->color = x->parent->color;
				x->parent->color = "black";
				s->right->color = "black";
				std::cout << "leftrotating..." << std::endl;
				leftRotate(x->parent);
				x = root;
			}
		}
		else {
			std::cout << "x is right child." << std::endl;
			// x is a right child
			std::cout << "Balance check 4" << std::endl;
			node *s = new node();
			s = x->parent->left;
			if (s->color == "red") {
				s->color = "black";
				x->parent->color = "red";
				rightRotate(x->parent);
				s = x->parent->left;
			}
			if (s->right->color == "black" && s->left->color == "black") {
				s->color = "red";
				x = x->parent;
			}
			else if (s->right->color == "red" && s->left->color == "black") {
				s->right->color = "black";
				s->color = "red";
				leftRotate(s);
				s = x->parent->left;
			}
			else {
				s->color = x->parent->color;
				x->parent->color = "black";
				s->left->color = "black";
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = "black";
}

/*
Method: minimum
Description: This function returns the minimum node in a branch of the tree.
Pre-conditions: None
Post-conditions: The minimum value node will be returned.
*/
node* RBTree::minimum(node *temp) {
	while (temp->left != NULL && temp->left->key != "nullNode") {
		temp = temp->left;
	}
	return temp;
}


