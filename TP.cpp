// TP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stack>
using namespace std;

enum Mark { YES, NO };
enum Dir { LEFT, RIGHT };
struct Node {
	char info_;
	Node *llink_;
	Node *rlink_;
	Node *parent_;
	Mark mark_;
	Dir dir_;

	Node() {}
	Node(char info, Node *llink = 0, Node *rlink = 0, Node *parent = 0, Mark mark = NO, Dir dir = LEFT)
		: info_(info)
		, llink_(llink)
		, rlink_(rlink)
		, parent_(parent)
		, mark_(mark)
		, dir_(dir)
	{}
	// Node(char info, Node* llink = 0, Node* rlink = 0, Node* parent = 0) :
	// info_(info), llink_(llink), rlink_(rlink), parent_(parent){}
};

void removeMarking(Node *tree)
{
	if (tree) {
		tree->mark_ = NO;
		tree->dir_ = LEFT;
		removeMarking(tree->llink_);
		removeMarking(tree->rlink_);
	}
}

void trickyPreorder(Node *tree)
{
	Node *top = 0;
	Node *current = tree;
	Node *temp;

	while (current) {
		if (current->mark_ == NO) {
			cout << current->info_ << endl;
			current->mark_ = YES;
		}

		if (current->llink_ && current->llink_->mark_ == NO) {
			temp = current->llink_;
			current->llink_ = top;
			top = current;
			current = temp;
			continue;
		}

		if (current->rlink_ && current->rlink_->mark_ == NO) {
			current->dir_ = RIGHT;
			temp = current->rlink_;
			current->rlink_ = top;
			top = current;
			current = temp;
			continue;
		}

		if (top == 0)
			return;

		temp = top;
		if (temp->dir_ == LEFT) {
			top = top->llink_;
			temp->llink_ = current;
		}
		else {
			top = top->rlink_;
			temp->rlink_ = current;
		}
		current = temp;
	}
}

void trickyInorder(Node *tree)
{
	Node *top = 0;
	Node *current = tree;
	Node *temp;

	while (current) {
		if (current->llink_ && current->llink_->mark_ == NO) {
			temp = current->llink_;
			current->llink_ = top;
			top = current;
			current = temp;
			continue;
		}

		if (current->mark_ == NO) {
			cout << current->info_ << endl;
			current->mark_ = YES;
		}

		if (current->rlink_ && current->rlink_->mark_ == NO) {
			current->dir_ = RIGHT;
			temp = current->rlink_;
			current->rlink_ = top;
			top = current;
			current = temp;
			continue;
		}

		if (top == 0)
			return;

		temp = top;
		if (temp->dir_ == LEFT) {
			top = top->llink_;
			temp->llink_ = current;
		}
		else {
			top = top->rlink_;
			temp->rlink_ = current;
		}
		current = temp;
	}
}

void trickyPostorder(Node *tree)
{
	// . . . should be implemented . . .
}

// Task1
void postorderWithStack(Node *tree)
{
	if (tree == nullptr)
		return;
	Node *vertex = tree;
	stack< Node * > s;
	while (true) {
		while (vertex) {
			if (vertex->rlink_) {
				s.push(vertex->rlink_);
			}
			s.push(vertex);
			vertex = vertex->llink_;
		}
		if (s.empty())
			return;
		vertex = s.top();
		s.pop();
		if (vertex->rlink_ && !s.empty() && s.top() == vertex->rlink_) {
			s.pop();
			s.push(vertex);
			vertex = vertex->rlink_;
		}
		else {
			std::cout << vertex->info_ << " ";
			vertex = nullptr;
		}
	}
}

// Task2
void postorderWithParent(Node *tree)
{
	if (tree == 0)
		return;
	Node *vertex = tree;
	Node *parent;
	while (1) {
		if (vertex->llink_) {
			vertex = vertex->llink_;
			continue;
		}
		if (vertex->rlink_) {
			vertex = vertex->rlink_;
			continue;
		}
		cout << vertex->info_ << " ";
		for (parent = vertex->parent_; parent != 0;
			vertex = parent, parent = vertex->parent_)
			if (parent->llink_ == vertex) {
				if (parent->rlink_ == nullptr)
				{
					cout << parent->info_ << " ";
				}
				else {
					vertex = parent->rlink_;
					break;
				}
			}
			else {
				cout << parent->info_ << " ";
			}
			if (parent == 0)
				return;
	}
}


void postorder_I(Node *tree)
{
	Node *last = nullptr;
	stack< Node * > s;
	while (1) {
		while (tree) {
			s.push(tree);
			tree = tree->llink_;
		}
		while (!s.empty()) {
			tree = s.top();
			if (!tree->rlink_ || tree->rlink_ == last) {
				cout << tree->info_ << " ";
				s.pop();
				last = tree;
			}
			else {
				tree = tree->rlink_;
				break;
			}
		}
		if (s.empty())
			return;
	}
}

int main()
{
	Node *D = new Node('D');
	Node *G = new Node('G');
	Node *H = new Node('H');
	Node *I = new Node('I');


	Node *B = new Node('B', D, nullptr);
	Node *E = new Node('E', 0, G);
	Node *F = new Node('F', H, I);

	Node *C = new Node('C', E, F);

	Node *tree = new Node('A', B, C);
	B->parent_ = tree;
	C->parent_ = tree;
	D->parent_ = B;
	E->parent_ = C;
	F->parent_ = C;
	G->parent_ = E;
	H->parent_ = F;
	I->parent_ = F;




	cout << endl << "***** TRICKY PREORDER: *****" << endl;
	trickyPreorder(tree);
	removeMarking(tree);

	cout << endl << "***** TRICKY INORDER: *****" << endl;
	trickyInorder(tree);
	removeMarking(tree);

	cout << endl << "***** TRICKY POSTORDER: *****" << endl;
	trickyPostorder(tree);

	postorderWithStack(tree);
	cout << endl;
	postorder_I(tree);
	cout << endl;


	postorderWithParent(tree);

	cout << endl;

	system("pause");
	return 0;
}