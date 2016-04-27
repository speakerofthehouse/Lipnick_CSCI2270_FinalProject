#ifndef RBTREE_H
#define RBTREE_H

struct node {
    std::string key;
    std::string color;
    node *parent;
    node *left;
    node *right;
    node (){};
    node (std::string _key, std::string _color, node *_parent, node *_left, node *_right) {
        key = _key;
        color = _color;
        parent = _parent;
        left = _left;
        right = _right;
    };
};

class RBTree
{
    public:
        RBTree();
        ~RBTree();
        void insert(std::string key);
        node* insertNode(std::string key);
        void leftRotate(node *x);
        void rightRotate(node *y);
        void printTree();
        void printTree(node* temp);
        void printRedNodes();
        void printRedNodes(node* temp);
        void printBlackNodes();
        void printBlackNodes(node* temp);
        node *search(std::string name);
        void deleteNode(std::string);
        void balance(node *x);
        node *minimum(node *temp);

    protected:
    private:
        node *root;
};

#endif // RBTREE_H