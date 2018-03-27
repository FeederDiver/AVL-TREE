class Node
{
private:
	int value, height;
	Node *rightChild, *leftChild;
public:  // We can simply just make the variables public and destroy those functions, it's sugar syntax and clear code usage only
	int get_value() { return value; }
	int get_height() { return height; }
	Node* get_right() { return rightChild; }
	Node* get_left() { return leftChild; }
	void set_value(int val) { value = val; }
	void set_height(int h) { height = h; }
	void set_right(Node* right) { rightChild = right; }
	void set_left(Node* left) { leftChild = left; }
};

class AVL_Tree
{
private:
	Node *root;
	int currentNodeHeight(Node* locaNode);
	void makeEmpty(Node* localNode);
	void privInOrder(Node* localNode);
	void privPreOrder(Node* localNode);
	void privPostOrder(Node* localNode);
	Node* checkBalance(Node* localNode);

	Node* getMin(Node* localNode);
	Node* getMax(Node* localNode);
	Node* remove(int value, Node* localNode);
	Node* insert(int value, Node* localNode);
	Node* rightRotate(Node* localNode);
	Node* leftRotate(Node* localNode);
	Node* rightLeftRotate(Node* localNode);
	Node* leftRightRotate(Node* localNode);


public:
	AVL_Tree() { root = NULL; }
	void inOrder() { privInOrder(root); }
	void preOrder() { privPreOrder(root); }
	void postOrder() { privPostOrder(root); }
	void insert(int value) { root = insert(value, root); }
	void remove(int value) { root = remove(value, root); }

};
void checkRemove();
void tenThousands_to_x_element_Tree(int x);

