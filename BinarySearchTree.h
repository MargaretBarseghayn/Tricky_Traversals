#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "stdafx.h"

class SearchTree {
	struct Node {
		int 	key_;
		Node* 	llink_;
		Node* 	rlink_;
		Node* 	parent_;
		Node(int key = 0, Node* llink = 0, Node* rlink = 0, Node* parent = 0) :
			key_(key), llink_(llink), rlink_(rlink), parent_(parent) {}
		~Node() {
			if (parent_)
				if (parent_->llink_ == this)
					parent_->llink_ = NULL;
				else if (parent_->rlink_ == this)
					parent_->rlink_ = NULL;
		}
	};

	static  void	clear(Node* tree);
	static	void	print(Node* tree, int indent = 0);

public:
	SearchTree() :tree_(0) {}
	~SearchTree() { clear(tree_); }

	Node*	search(int key) const;
	void	insert(int key);
	void	remove(int key);

	void	print()const {
		cout << "- - - - - - - - - -" << endl;
		print(tree_);
		cout << "- - - - - - - - - -" << endl;
	}

	int		min() const;

	int		max() const;

	Node*	successor(const Node* node) const;

	Node*	predecessor(const Node* node) const;

private:
	Node*	tree_;
};

void
SearchTree::clear(Node* tree)
{
	if (tree)
	{
		clear(tree->llink_);
		clear(tree->rlink_);
		delete tree;
	}
}

void
SearchTree::print(Node* tree, int indent)
{
	if (tree == 0) return;

	print(tree->rlink_, indent + 5);
	cout << string(indent, ' ') << tree->key_ << endl;
	print(tree->llink_, indent + 5);
}

SearchTree::Node*
SearchTree::search(int key) const
{
	Node * current = tree_;
	while (current && current->key_ != key)
		current = (current->key_ < key ? current->rlink_ : current->llink_);
	return current;
}

void
SearchTree::insert(int key)
{
	if (!tree_) {
		tree_ = new Node(key);
		return;
	}

	Node * parent = NULL, *current = tree_;
	while (current && current->key_ != key) {
		parent = current;
		current = (current->key_ < key ? current->rlink_ : current->llink_);
	}

	if (current)	return;
	if (parent->key_ > key)	parent->llink_ = new Node(key, 0, 0, parent);
	else					parent->rlink_ = new Node(key, 0, 0, parent);
}

void
SearchTree::remove(int key)
{
	Node * parent, *current = tree_;
	while (current && current->key_ != key) {
		parent = current;
		current = (current->key_ < key ? current->rlink_ : current->llink_);
	}
	if (!current)	return;
	if (!current->llink_ && !current->rlink_) {
		if (current == tree_)
			tree_ = NULL;
		delete current;
	}
	else if (current->llink_ && current->rlink_) {
		Node *crnt = current->rlink_;
		while (crnt->llink_)
			crnt = crnt->llink_;

		current->key_ = crnt->key_;
		if (current == crnt->parent_)
			current->rlink_ = crnt->rlink_;
		else
			crnt->parent_->llink_ = crnt->rlink_;
		if (crnt->rlink_)	crnt->rlink_->parent_ = crnt->parent_;
		delete crnt;
	}
	else {
		Node * ptr = (current->llink_ ? current->llink_ : current->rlink_);
		if (current == tree_) {
			delete tree_;
			tree_ = ptr;
			ptr->parent_ = NULL;
		}
		else {
			if (current == current->parent_->llink_) {
				current->parent_->llink_ = ptr;
			}
			else {
				current->parent_->rlink_ = ptr;
			}
			ptr->parent_ = current->parent_;
			delete current;
		}
	}
}

int
SearchTree::min() const
{
	Node * current = tree_;
	while (current->llink_)
		current = current->llink_;
	return current->key_;
}

int
SearchTree::max() const
{
	Node * current = tree_;
	while (current->rlink_)
		current = current->rlink_;
	return current->key_;
}

SearchTree::Node*
SearchTree::successor(const Node* node) const
{
	Node * current = (Node *)node;
	if (current->rlink_) {
		current = current->rlink_;
		while (current->llink_)
			current = current->llink_;
	}
	else {
		while (current != tree_ && current == current->parent_->rlink_)
			current = current->parent_;
		current = current->parent_;
	}
	return current;
}

SearchTree::Node*
SearchTree::predecessor(const Node* node) const
{
	Node * current = (Node *)node;
	if (current->llink_) {
		current = current->llink_;
		while (current->rlink_)
			current = current->rlink_;
	}
	else {
		while (current != tree_ && current == current->parent_->llink_)
			current = current->parent_;
		current = current->parent_;
	}
	return current;
}


#endif // !BINARYSEARCHTREE_H