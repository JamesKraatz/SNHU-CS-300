/*
 * AVLTree.cpp
 *
 * Implementations of the AVL Self-balancing tree
 * invented by Adelson-Velsky and Landis in 1962
 *
 *  Created on: Apr 14, 2021
 *      Author: James Kraatz
 */

#include "AVLTree.h"

AVLTree::AVLTree() {
	m_root = nullptr;
}

AVLTree::~AVLTree() {
	while(m_root != nullptr) {
		this->DeleteTree(m_root);
	}
}

void AVLTree::DeleteTree(Node* t_node) {
	Node* next = t_node->right();

	if(t_node == nullptr) {
		return;
	}

	this->DeleteTree(t_node->left());
	delete(t_node);
	this->DeleteTree(next);
}

Node* AVLTree::DeleteNode(Node* t_root, std::string t_key) {
	if(t_root == nullptr) {
		return t_root;
	}

	// If t_key is lest than t_root key go to the left side of t_root
	if(t_key.compare(t_root->key()) < 0) {
		t_root->setLeft(this->DeleteNode(t_root->left(), t_key));
	// Else if t_key is greater than t_root key go to right side of t+root
	} else if(t_key.compare(t_root->key()) > 0) {
		t_root->setRight(this->DeleteNode(t_root->right(), t_key));
	// A match is found.
	} else {
		// if at least one child is blank
		if((t_root->left() == nullptr) ||
			(t_root->right() == nullptr)) {

			// assign left child to temporary node
			Node* temp = t_root->left();

			// if node is null then get the right
			if( temp == nullptr) {
				temp = t_root->right();
			}

			// if temp is still blank then both children are null
			if (temp == nullptr) {
				// no children so save t_root to temp node
				temp = t_root;
				// and assign t_root nullptr
				t_root = nullptr;
			// t_root has one child so
			} else {
				// copy data from temp node to t_root node
				*t_root = *temp;
			}
			// delete the temp node from memory
			delete(temp);
		// otherwise t_root has two children
		} else {
			// get the lowest key node from the right side of t_root
			Node* temp = this->MinValNode(t_root->right());
			// assign the lowest right side lowest key and ocurese to t_root
			t_root->setCourse(temp->course());
			// now call delete to remove the external leaf the coruse was in
			t_root->setRight(this->DeleteNode(t_root->right(), temp->key()));
		}
	}

	// Nothign to do.
	if(t_root == nullptr) {
		return t_root;
	}

	// set t_roots height
	t_root->setHeight(this->maxHeight(t_root) + 1);
	// get balance factor
	int balance = this->getBalance(t_root);
	// balance is too high on the left
	if(balance > 1) {
		// check for left right rotation
		if(getBalance(t_root->left()) < 0) {
			t_root->setLeft(this->RotateLeft(t_root->left()));
		}
		return this->RotateRight(t_root);
	}
	// balance is too low on the right
	if(balance < -1) {
		// check for right rotation need
		if(getBalance(t_root->right()) > 0) {
			t_root->setRight(this->RotateRight(t_root->right()));
		}
		// rotate left
		return this->RotateLeft(t_root);
	}
	return t_root;
}

Node* AVLTree::InsertNode(Node* t_root, Course* t_course) {
	// if tree is new, initialize new node and assign to root
	if(this->m_root == nullptr) {
		this->m_root = new Node(t_course);
		return m_root;
	// if t_root is nullptr, initialize new node and assign to leaf
	} else if(t_root == nullptr) {
		t_root = new Node(t_course);
		return t_root;
	}
	// course is less than t_root key go the left side of t_root
	if(t_course->Number().compare(t_root->key()) < 0) {
		t_root->setLeft(this->InsertNode(t_root->left(), t_course));
	}
	// course is greater than t_root key go the right side of t_root
	else if(t_course->Number().compare(t_root->key()) > 0) {
		t_root->setRight(this->InsertNode(t_root->right(), t_course));
	// a match is found so return this t_root
	} else {
		return t_root;
	}
	// set t_roots height
	t_root->setHeight(this->maxHeight(t_root) + 1);
	// get balance factor
	int balance = this->getBalance(t_root);
	// if balance is too high
	if(balance > 1) {
		// if t_course > t_root left child
		if(t_course->Number().compare(t_root->left()->key()) > 0) {
			// rotate t_root's left child left
			t_root->setLeft(this->RotateLeft(t_root->left()));
		}
		// rotate t_root right
		t_root = this->RotateRight(t_root);
	}
	// if balance is too low
	if(balance < -1) {
		// if t_course < t_root right child
		if(t_course->Number().compare(t_root->right()->key()) < 0) {
			// rotate t_root's right child right
			t_root->setRight(this->RotateRight(t_root->right()));
		}
		// rotate t_root left
		t_root = this->RotateLeft(t_root);
	}
	return t_root;
}

Node* AVLTree::SearchNode(Node* t_root, std::string t_key) {
	// no key found return nullptr
	if(t_root == nullptr) {
		return t_root;
	}
	// if key is less than t_root search to t_root's left
	if(t_key.compare(t_root->key()) < 0) {
		t_root = this->SearchNode(t_root->left(), t_key);
	// if key is greater tahn t_root searchto t_root's right
	} else if(t_key.compare(t_root->key()) > 0) {
		t_root = this->SearchNode(t_root->right(),t_key);
	}
	return t_root;
}

Node* AVLTree::RotateLeft(Node* t_node) {
	// rotates t_node,"root" to left child of t_node's right child "pivot"
	// moves pivot's left child to root's right child and root to pivot's left
	Node* root = t_node;
	Node* pivot = root->right();
	root->setRight(pivot->left());
	pivot->setLeft(root);
	if(root == m_root) { m_root = pivot; }
	root = pivot;
	pivot = root->left();

	// reset each node height
	if(pivot->left() != nullptr) {
		pivot->left()->setHeight(this->maxHeight(pivot->left()) + 1);
	}

	if(pivot->right() != nullptr) {
		pivot->right()->setHeight(this->maxHeight(pivot->right()) + 1);
	}

	pivot->setHeight(this->maxHeight(pivot) + 1);

	if(root->left() != nullptr) {
		root->left()->setHeight(this->maxHeight(root->left()) + 1);
	}

	root->setHeight(this->maxHeight(root) + 1);

	return root;
}

Node* AVLTree::RotateRight(Node* t_node) {
	// rotates t_node,"root" to right child of t_node's left child "pivot"
	// moves pivot's right child to root's left child and root to pivot's right
	Node* root = t_node;
	Node* pivot = root->left();

	root->setLeft(pivot->right());
	pivot->setRight(root);
	if(root == m_root) { m_root = pivot; }
	root = pivot;
	pivot = root->right();

	// reset each node height
	if(pivot->left() != nullptr) {
		pivot->left()->setHeight(this->maxHeight(pivot->left()) + 1);
	}

	if(pivot->right() != nullptr) {
		pivot->right()->setHeight(this->maxHeight(pivot->right()) + 1);
	}

	pivot->setHeight(this->maxHeight(root) + 1);

	if(root->right() != nullptr) {
		root->right()->setHeight(this->maxHeight(root->right()) + 1);
	}

	root->setHeight(this->maxHeight(root));

	return root;
}

Node* AVLTree::MinValNode(Node* t_node) {
	// find minimum value leaf in t_node tree
	if(t_node == nullptr) {
		return t_node;
	}

	while (t_node->left() != nullptr) {
		t_node = t_node->left();
	}

	return t_node;
}

int AVLTree::maxHeight(Node* t_node) {
	// maximum tree height from children tree's
	Node* t_nodeA = t_node->left();
	Node* t_nodeB = t_node->right();
	int heightA = 0;
	int heightB = 0;

	if(t_nodeA != nullptr) {
		heightA = t_nodeA->height();
	} else {
		heightA = 0;
	}

	if(t_nodeB != nullptr) {
		heightB = t_nodeB->height();
	} else {
		heightB = 0;
	}

	if(heightA > heightB) {
		return heightA;
	}
	return heightB;
}

int AVLTree::getBalance(Node* t_node) {
	// calculates balance factor from children trees.
	// Factor greater than 0 represent left heavy
	// Factor less than 0 represent right heavy
	// Factor equals 0 represent left height == right height
	int balance = 0;
	if(t_node != nullptr) {
		if(!(t_node->left() == nullptr || t_node->right() == nullptr)) {
			balance = (t_node->left()->height() - t_node->right()->height());
		} else if(t_node->right() != nullptr) {
			balance -= t_node->right()->height();
		} else if(t_node->left() != nullptr) {
			balance =  t_node->left()->height();
		}
	}
	return balance;
}

Node* AVLTree::AddNode(Course* t_course) {
	Node* newNode;
	newNode = this->InsertNode(this->m_root, t_course);
	return newNode;
}

Node* AVLTree::RemoveNode(std::string t_key) {
	return this->DeleteNode(m_root, t_key);
}

Node* AVLTree::FindNode(std::string t_key) {
	return this->SearchNode(m_root, t_key);
}

Node* AVLTree::MinNode() {
	return this->MinValNode(m_root);
}

void AVLTree::PrintList() {
	this->PrintList(m_root);
}

void AVLTree::PrintList(Node* t_node) {
	if(t_node == nullptr) {
		return;
	}

	this->PrintList(t_node->left());
	std::cout << t_node->listing() << std::endl;
	this->PrintList(t_node->right());
}

Node* AVLTree::root() {
	return m_root;
}

void AVLTree::ShowTree(Node* t_node) {
	// Used for diagnosis, shows three tree levels starting from t_node as root
	Node* root = t_node;
	Node* rootLeft;
	Node* rootRight;

	std::string rll = "NULL";
	std::string rl = "NULL";
	std::string rlr = "NULL";
	std::string r = "NULL";
	std::string rrl= "NULL";
	std::string rr = "NULL";
	std::string rrr= "NULL";

	if(root != nullptr) {
		rootLeft = root->left();
		if (rootLeft != nullptr) {
			if (rootLeft->left() != nullptr) {
				rll = rootLeft->left()->course()->Number();
			}
			rl = rootLeft->course()->Number();
			if (rootLeft->right() != nullptr) {
				rlr = rootLeft->right()->course()->Number();
			}
		}
		r = root->course()->Number();
		rootRight = root->right();
		if (rootRight != nullptr) {
			if (rootRight->left() != nullptr) {
				rrl = rootLeft->left()->course()->Number();
			}
			rr = rootRight->course()->Number();
			if (rootRight->right() != nullptr) {
				rrr = rootLeft->right()->course()->Number();
			}
		}
	}
	std::cout << std::endl << std::endl << "3 level map from root: " << r << std::endl;
	std::cout << "rll: " << rll << " rl: " << rl << " rlr: " << rlr << " r: " << r << " rrl: " << rrl << " rr: " << rr << " rrl: " << rrl << std::endl << std::endl;

}
