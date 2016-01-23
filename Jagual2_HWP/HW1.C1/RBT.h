#pragma once
#include <limits>

enum COLOR
{
	RED = 0,
	BLACK = 1
};

struct Node
{
	Node(int val)
	{
		key = val;
	}
	Node* parent;
	Node* leftChild;
	Node* rightChild;
	int key;
	COLOR color;
};

struct Tree
{
	Tree()
	{
		nil = new Node(INT_MIN);
		nil->color = BLACK;
		root = nil;
		root->parent = nil;
		nil->leftChild = root;
		nil->rightChild = root;
	}
	~Tree()
	{
		delete(nil);
	}
	Node* root;
	Node* nil;
};

class RBT
{
public:
	void LeftLotate(Node* x);
	void RightLotate(Node* x);
	void RBInsert(Node* newNode);
	void RBInsertFixUp(Node* fixupNode);
	void RBTransplant(Node* oldNode, Node* plantNode);
	void RBDelete(Node* node);
	void RBDeleteFixUp(Node* fixupNode);
	Node* TreeMinimum(Node* node);

	void PrintRBT();

	RBT();
	~RBT();
private:
	Tree* T;
	void PrintNode(Node* node);
};