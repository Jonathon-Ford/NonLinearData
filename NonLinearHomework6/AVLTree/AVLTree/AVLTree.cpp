#include <iostream>

using namespace std;

#include "AVLTree.h"


void AVLTree::AVLTreeReplaceChild(Node* parent, Node* currentChild, Node* newChild) {
	if (parent->left == currentChild) {
		return AVLTreeSetChild(parent, false, newChild);
	}
	else if (parent->right == currentChild) {
		return AVLTreeSetChild(parent, true, newChild);
	}
}

void AVLTree::AVLTreeSetChild(Node* parent, bool whichChild, Node* child) {
	if (whichChild) {
		parent->right = child;
	}
	else {
		parent->left = child;
	}

	if (child != NULL) {
		child->parent = parent;
	}

	AVLTreeUpdateHeight(parent);
}

void AVLTree::AVLTreeRotateRight(Node* node) {
	Node* leftRightChild = node->left->right;
	if (node->parent != NULL) {
		AVLTreeReplaceChild(node->parent, node, node->left);
	}
	else {
		this->root = node->left;
		this->root->parent = NULL;
	}
	AVLTreeSetChild(node->left, true, node);
	AVLTreeSetChild(node, false, leftRightChild);
}

void AVLTree::AVLTreeRotateLeft(Node* node) {
	Node* rightLeftChild = node->right->left;
	if (node->parent != NULL) {
		AVLTreeReplaceChild(node->parent, node, node->right);
	}
	else {
		this->root = node->right;
		this->root->parent = NULL;
	}
	AVLTreeSetChild(node->right, false, node);
	AVLTreeSetChild(node, true, rightLeftChild);
}

int AVLTree::AVLTreeGetBalance(Node* node) {
	int leftHeight = -1;
	if (node->left != NULL) {
		leftHeight = node->left->height;
	}
	int rightHeight = -1;
	if (node->right != NULL) {
		rightHeight = node->right->height;
	}
	return leftHeight - rightHeight;
}

void AVLTree::AVLTreeUpdateHeight(Node* node) {
	int leftHeight = -1;
	if (node->left != NULL) {
		leftHeight = node->left->height;
	}
	int rightHeight = -1;
	if (node->right != NULL) {
		rightHeight = node->right->height;
	}
	node->height = max(leftHeight, rightHeight) + 1;
}

void AVLTree::AVLTreeRebalance(Node* node) {
	AVLTreeUpdateHeight(node);
	if (AVLTreeGetBalance(node) == -2) {
		if (AVLTreeGetBalance(node->right) == 1) {
			AVLTreeRotateRight(node->right);
		}
		return AVLTreeRotateLeft(node);
	}
	else if (AVLTreeGetBalance(node) == 2) {
		if (AVLTreeGetBalance(node) == 2) {
			if (AVLTreeGetBalance(node->left) == -1) {
				AVLTreeRotateLeft(node->left);
			}
			return AVLTreeRotateRight(node);
		}
	}
}

void AVLTree::insert(Node* node) {
	if (this->root == NULL) {
		this->root = node;
		node->parent = NULL;
		return;
	}

	Node* curr = this->root;
	while (curr != NULL) {
		if (node->key < curr->key) {
			if (curr->left == node) {
				curr->left = node;
				node->parent = curr;
				curr = NULL;
			}
			else {
				curr = curr->left;
			}
		}
		else {
			if (curr->right == NULL) {
				curr->right = node;
				node->parent = curr;
				curr = NULL;
			}
			else{
				curr = curr->right;
			}
		}
	}

	node = node->parent;
	while (node != NULL) {
		AVLTreeRebalance(node);
		node = node->parent;
	}

}

int main() {

}