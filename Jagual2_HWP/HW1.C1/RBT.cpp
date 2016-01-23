#include "RBT.h"
#include <iostream>
#include <queue>
using namespace std;

void RBT::LeftLotate(Node* x)
{
	Node* y = x->rightChild; // set y
	x->rightChild = y->leftChild; // subtree Beta ���� ����
	if (y->leftChild != T->nil) // subtree Beta ���� ����
		y->leftChild->parent = x; // subtree Beta ���� ����
	y->parent = x->parent; // y�� parent ���� ����
	if (x->parent == T->nil) // y�� parent ���� ����
		T->root = y;
	else if (x == x->parent->leftChild)
		x->parent->leftChild = y;
	else x->parent->rightChild = y;
	y->leftChild = x; // x�� y�� ���� ����
	x->parent = y; // x�� y�� ���� ����
}

void RBT::RightLotate(Node* y)
{
	Node* x = y->leftChild; // set x

	y->leftChild = x->rightChild; // subtree Beta ���� ����
	if (x->rightChild != T->nil) // subtree Beta ���� ����
		x->rightChild->parent = y; // subtree Beta ���� ����

	x->parent = y->parent; // x�� parent ���� ����
	if (y->parent == T->nil) // x�� parent ���� ����
		T->root = x;
	else if (y == y->parent->leftChild)
		y->parent->leftChild = x;
	else y->parent->rightChild = x;

	x->rightChild = y; // x�� y�� ���� ����
	y->parent = x; // x�� y�� ���� ����
}

void RBT::RBInsert(Node* newNode)
{
	Node* parentNode = T->nil; // sentinel node�� �ʱ�ȭ
	Node* curNode = T->root; // sentinel node ���� Ȯ��

	while (curNode != T->nil) // �˸��� �� ��ġ ã��
	{
		parentNode = curNode;
		if (newNode->key < curNode->key)
			curNode = curNode->leftChild;
		else curNode = curNode->rightChild;
	}

	newNode->parent = parentNode;
	if (parentNode == T->nil)
		T->root = newNode;
	else if (newNode->key < parentNode->key)
		parentNode->leftChild = newNode;
	else parentNode->rightChild = newNode;

	newNode->leftChild = T->nil;
	newNode->rightChild = T->nil;
	newNode->color = RED;

	RBInsertFixUp(newNode);
}

void RBT::RBInsertFixUp(Node* fixupNode)
{
	while (fixupNode->parent->color == RED) // �θ�-�ڽ� ��� RED��
	{
		if (fixupNode->parent == fixupNode->parent->parent->leftChild)
		{
			Node* uncleNode = fixupNode->parent->parent->rightChild;
			if (uncleNode->color == RED)
			{
				fixupNode->parent->color = BLACK; // case1
				uncleNode->color = BLACK; // case1
				fixupNode->parent->parent->color = RED; // case1
				fixupNode = fixupNode->parent->parent;
			}
			else
			{
				if (fixupNode == fixupNode->parent->rightChild)
				{
					fixupNode = fixupNode->parent; // case3
					LeftLotate(fixupNode); // case3
				}
				fixupNode->parent->color = BLACK; // case2
				fixupNode->parent->parent->color = RED; // case2
				RightLotate(fixupNode->parent->parent); // case2
			}
		}
		else
		{
			Node* uncleNode = fixupNode->parent->parent->leftChild;
			if (uncleNode->color == RED)
			{
				fixupNode->parent->color = BLACK; // case1
				uncleNode->color = BLACK; // case1
				fixupNode->parent->parent->color = RED; // case1
				fixupNode = fixupNode->parent->parent;
			}
			else
			{
				if (fixupNode == fixupNode->parent->leftChild)
				{
					fixupNode = fixupNode->parent; // case3
					RightLotate(fixupNode); // case3
				}
				fixupNode->parent->color = BLACK; // case2
				fixupNode->parent->parent->color = RED; // case2
				LeftLotate(fixupNode->parent->parent); // case2
			}
		}
	}
	T->root->color = BLACK; // case1�� parent�� black�� ���
}

void RBT::RBTransplant(Node* oldNode, Node* plantNode)
{
	if (oldNode->parent == T->nil)
		T->root = plantNode;
	else if (oldNode == oldNode->parent->leftChild)
		oldNode->parent->leftChild = plantNode;
	else oldNode->parent->rightChild = plantNode;
	plantNode->parent = oldNode->parent;
}

void RBT::RBDelete(Node* node)
{
	COLOR erasedColor = node->color;
	Node* fixupNode;
	Node* successor;
	if (node->leftChild == T->nil) // left child�� ���� ���
	{
		fixupNode = node->rightChild; // ���� ���� ��� ����
		RBTransplant(node, node->rightChild);
	}
	else if (node->rightChild == T->nil)
	{
		fixupNode = node->leftChild; // ���� ���� ��� ����
		RBTransplant(node, node->leftChild);
	}
	else
	{
		successor = TreeMinimum(node->rightChild);
		erasedColor = successor->color; // �÷� ������
		fixupNode = successor->rightChild; // successor ���� �ڸ����� fixup
		if (successor->parent == node)
			fixupNode->parent = successor; // nil�� ��쿣 parent ������
		else
		{
			RBTransplant(successor, successor->rightChild);
			successor->rightChild = node->rightChild;
			successor->rightChild->parent = successor;
		}
		RBTransplant(node, successor);
		successor->leftChild = node->leftChild;
		successor->leftChild->parent = successor;
		successor->color = node->color;
	}
	if (erasedColor == BLACK)
		RBDeleteFixUp(fixupNode);
}

Node* RBT::TreeMinimum(Node* node)
{
	while (node->leftChild != T->nil)
	{
		node = node->leftChild;
	}
	return node;
}

void RBT::RBDeleteFixUp(Node* fixupNode)
{
	Node* sibling;
	while (fixupNode != T->root && fixupNode->color == BLACK)
	{
		if (fixupNode == fixupNode->parent->leftChild)
		{
			sibling = fixupNode->parent->rightChild;
			if (sibling->color == RED)
			{
				sibling->color = BLACK; // case5
				fixupNode->parent->color = RED; // case5
				LeftLotate(fixupNode->parent); // case5
				sibling = fixupNode->parent->rightChild; // case5
			}
			if (sibling->leftChild->color == BLACK && sibling->rightChild->color == BLACK)
			{
				sibling->color = RED; // case1
				fixupNode = fixupNode->parent; // case1
			}
			else
			{
				if (sibling->rightChild->color == BLACK)
				{
					sibling->leftChild->color = BLACK; // case3
					sibling->color = RED; // case3
					RightLotate(sibling); // case3
					sibling = fixupNode->parent->rightChild; // case3
				}
				sibling->color = fixupNode->parent->color; // case2
				fixupNode->parent->color = BLACK; // case2
				sibling->rightChild->color = BLACK; // case2
				LeftLotate(fixupNode->parent); // case2
				fixupNode = T->root; // ���� // case2
			}
		}
		else // fixupNode == fixupNode->parent->rightChild
		{
			sibling = fixupNode->parent->rightChild;
			if (sibling->color == RED)
			{
				sibling->color = BLACK;
				fixupNode->parent->color = RED;
				RightLotate(fixupNode->parent);
				sibling = fixupNode->parent->leftChild;
			}
			if (sibling->rightChild->color == BLACK && sibling->leftChild->color == BLACK)
			{
				sibling->color = RED;
				fixupNode = fixupNode->parent;
			}
			else
			{
				if (sibling->leftChild->color == BLACK)
				{
					sibling->rightChild->color = BLACK;
					sibling->color = RED;
					LeftLotate(sibling);
					sibling = fixupNode->parent->leftChild;
				}
				sibling->color = fixupNode->parent->color;
				fixupNode->parent->color = BLACK;
				sibling->leftChild->color = BLACK;
				RightLotate(fixupNode->parent);
				fixupNode = T->root;
			}
		}
	}
	fixupNode->color = BLACK;
}

void RBT::PrintRBT()
{
	queue<Node*> Q = queue<Node*>();

	Q.push(T->root);
	while (!Q.empty())
	{
		PrintNode(Q.front());
		if (Q.front()->leftChild != T->nil)
		{
			Q.push(Q.front()->leftChild);
		}
		if (Q.front()->rightChild != T->nil)
		{
			Q.push(Q.front()->rightChild);
		}
		Q.pop();
	}
}

RBT::RBT()
{
	T = new Tree();
}

RBT::~RBT()
{
	delete(T);
}

void RBT::PrintNode(Node* node)
{
	cout << node->key << "(";
	if (node->color == BLACK)
		cout << "B";
	else cout << "R";
	cout << ") ";
}
