#include <iostream>
#include "RBT.h"

using namespace std;

int main()
{
	RBT* rbt = new RBT();

	rbt->PrintRBT();
	cout << endl;

	//기본 insert delete 테스트
	Node* newNode1 = new Node(41);
	Node* newNode2 = new Node(11);
	Node* newNode3 = new Node(21);
	Node* newNode4 = new Node(31);
	Node* newNode5 = new Node(41);

	//기본 isnert 테스트
	rbt->RBInsert(newNode1);
	rbt->RBInsert(newNode2);
	rbt->RBInsert(newNode3);
	rbt->RBInsert(newNode4);
	rbt->RBInsert(newNode5);

	rbt->PrintRBT();
	cout << endl;

	//기본 delete 테스트
	rbt->RBDelete(newNode1);
	rbt->RBDelete(newNode2);
	rbt->RBDelete(newNode3);
	rbt->RBDelete(newNode4);
	rbt->RBDelete(newNode5);

	rbt->PrintRBT();
	cout << endl;

	//같은 값 연속 insert
	Node* newNode6 = new Node(41);
	Node* newNode7 = new Node(41);
	Node* newNode8 = new Node(41);
	Node* newNode9 = new Node(41);
	Node* newNode10 = new Node(41);

	rbt->RBInsert(newNode6);
	rbt->RBInsert(newNode7);
	rbt->RBInsert(newNode8);
	rbt->RBInsert(newNode9);
	rbt->RBInsert(newNode10);

	rbt->PrintRBT();
	cout << endl;

	//오름차순 insert
	Node* newNode11 = new Node(1);
	Node* newNode12 = new Node(2);
	Node* newNode13 = new Node(3);
	Node* newNode14 = new Node(4);
	Node* newNode15 = new Node(5);

	rbt->RBInsert(newNode11);
	rbt->RBInsert(newNode12);

	rbt->PrintRBT();
	cout << endl;

	//min 값 delete
	rbt->RBDelete(newNode11);

	rbt->PrintRBT();
	cout << endl;

	getchar();
}