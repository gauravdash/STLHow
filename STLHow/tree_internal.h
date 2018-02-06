// Copyright (c) 2014 Gaurav Dasharathe

// part of <map>
//
// http://cprogramminglanguage.net/avl-tree.aspx
// http://www.dreamincode.net/forums/topic/236424-data-structures-avl-tree-tutorial/
// http://plasmasturm.org/log/453/
// http://neil.brown.name/blog/20041124101820

#ifndef _MAP_TREE_INTERNAL_H
#define _MAP_TREE_INTERNAL_H

#include <iostream>

#include "algorithm.h"
#include "utility.h"

namespace STLHow
{
	template <typename T>
	class Node
	{
	public:
		Node(const T &d, Node *l=0, Node *r=0, Node *p=0)
			: data(d), left(l), right(r), parent(p), ht(0) { }

		int height();
		int lheight();
		int rheight();
		void computeHeight();

		Node *left;
		Node *right;
		Node *parent;
		
		T data;

	private:
		int ht;
	};

	template <typename T>
	int Node<T>::height()
	{
		return ht;
	}

	template <typename T>
	int Node<T>::lheight()
	{
		int ret(-1);

		if(left)
			ret = left->height();

		return ret;
	}

	template <typename T>
	int Node<T>::rheight()
	{
		int ret(-1);

		if(right)
			ret = right->height();

		return ret;
	}

	template <typename T>
	void Node<T>::computeHeight()
	{
		ht = max(lheight(), rheight()) + 1;
	}

	template <typename T>
	class Tree
	{
	public:
		Tree(bool a) : root_(0), allowDuplicates(a) { }

		T &insert(const T &d)
		{ Node<T> *r = insertInternal(d);
		  return r->data;
		}

		void printPreOrder()
		{ printPreOrder(root_, 1); }

		void printPostOrder()
		{ printPostOrder(root_); }

		void printInOrder()
		{ printInOrder(root_); }

		void printDot()
		{ 
			std::cout << " digraph graphname {" << std::endl;
			printDot(root_); 
			std::cout << "}" << std::endl;
		}

		Node<T> *find(const T &k)
		{ return findInternal(k); }

		void remove(const T &k)
		{ removeR(k, root_); }

		Node<T> *inorderNext(Node<T> *n);

		Node<T> *minNode();
		Node<T> *maxNode();

	private:
		Node<T> *root_;

		bool allowDuplicates;

		Node<T> *insertInternal(const T &d);
		Node<T> *insertR(const T &d, Node<T> *&n);

		void removeR(const T &k, Node<T> *&n);
		int removeInternal(const T &d);

		Node<T> *findR(const T &k, Node<T> *n);
		Node<T> *findInternal(const T &d);

		void printPreOrder(Node<T> *n, int offset);
		void printPostOrder(Node<T> *n);
		void printInOrder(Node<T> *n);
		void printDot(Node<T> *n);

		T removeMin(Node<T> *&n);

		void balanceTree(Node<T> *n, const T &d);

		Node<T> *singleRotateLeft(Node<T> *n);
		Node<T> *singleRotateRight(Node<T> *n);
		Node<T> *doubleRotateLeft(Node<T> *n);
		Node<T> *doubleRotateRight(Node<T> *n);
	};

	// insert data d, starting at node n, return the inserted node
	// should not be called on an arbitrary n unless in recrusion
	// as it may leave the tree unbalanced
	// if duplicates are not allowed, return the existing node
	template <typename T>
	Node<T> *Tree<T>::insertR(const T &d, Node<T> *&n)
	{
		Node<T> *ret(n);

		if(n == 0)
		{
			n = new Node<T>(d);
			ret = n;
		}
		else
		{
			if(d < n->data)
			{
				ret = insert(d, n->left);

				if(n->lheight() - n->rheight() == 2)
				{
					if(d < n->left->data)
						n = singleRotateLeft(n);
					else
						n = doubleRotateLeft(n);
				}
			}
			else if(d > n->data || (d == n->data && allowDuplicates))
			{
				ret = insert(d, n->right);

				if(n->rheight() - n->lheight() == 2)
				{
					if(d >= n->right->data)
						n = singleRotateRight(n);
					else
						n = doubleRotateRight(n);
				}
			}

			// TODO: it is called even if n is not modified
			n->computeHeight();
		}

		return ret;
	}

	template <typename T>
	Node<T> *Tree<T>::insertInternal(const T &d)
	{
		// microsoft compiler does not understand *&current(n)
		Node<T> *current(root_);
		Node<T> *parent(0);

		if(! root_)
		{
			root_ = new Node<T>(d);
			current = root_;
			current->computeHeight();
		}
		else
		{
			bool doInsert(true);

			while(current)
			{
				if(d < current->data)
				{
					parent = current;
					current = current->left;
				}
				else if(d > current->data || (d == current->data && allowDuplicates))
				{
					parent = current;
					current = current->right;
				}
				else
				{
					parent = current;
					current = 0;
					doInsert = false;
				}
			}

			if(doInsert)
			{
				current = new Node<T>(d);
				current->parent = parent;

				if(d < parent->data)
				{
					parent->left = current;
				}
				else if(d > parent->data || (d == parent->data && allowDuplicates))
				{
					parent->right = current;
				}

				balanceTree(parent, d);
			}
			else
			{
				current = parent;
			}
		}

		return current;
	}

	// traverse up the tree from the current node
	// along the way compute new heights
	// and rebalance the node which is unbalanced
	template <typename T>
	void Tree<T>::balanceTree(Node<T> *n, const T &d)
	{
		Node<T> *next(n);
		Node<T> *newHead(0);
		bool rotated(false);

		while(next)
		{
			Node<T> *parent(next->parent);
			next->computeHeight();

			if(! rotated)
			{
				if(next->lheight() - next->rheight() == 2)
				{
					if(next->left)
					{
						// left has left child
						//if(d < next->left->data)
						std::cout << "dL " << d 
							 << " rh " << next->left->rheight() 
						     << " lh " << next->left->lheight() << std::endl;
						if(next->left->lheight() > next->left->rheight())
						{
							newHead = singleRotateLeft(next);
						}
						// data inserted in right subtree
						else
						{
							newHead = doubleRotateLeft(next);
						}
					}
				}
				else if(next->rheight() - next->lheight() == 2)
				{
					if(next->right)
					{
						// right has right child
						//if(d >= next->right->data)
						std::cout << "dR " << d 
							 << " rh " << next->right->rheight() 
						     << " lh " << next->right->lheight() << std::endl;
						if(next->right->rheight() > next->right->lheight())
						{
							newHead = singleRotateRight(next);
						}
						// data inserted in right subtree
						else
						{
							newHead = doubleRotateRight(next);
						}
					}
				}

				if(newHead)
				{
					// if there is a tree above this
					// adjust it to point to the new head of subtree
					if(parent)
					{
						// next is left child of its parent
						if(parent->left == next)
						{
							newHead->parent = parent;
							parent->left = newHead;
						}
						// next is right child of its parent
						else if(parent->right == next)
						{
							newHead->parent = parent;
							parent->right = newHead;
						}
					}
					else
					{
						// this is root, adjust it
						newHead->parent = 0;
						root_ = newHead;
					}

					newHead = 0;
					rotated = true;
				}
			}

			next = parent;
		}
	}

	template <typename T>
	void Tree<T>::printDot(Node<T> *n)
	{
		if(n)
		{
			if(n->left)
			    std::cout << n->data << " -> " << n->left->data << ";" << std::endl; 
			if(n->right)
				std::cout << n->data << " -> " << n->right->data << ";" << std::endl; 
			if(n->parent)
				std::cout << n->data << " -> " << n->parent->data << ";" << std::endl; 

			printDot(n->left);
			printDot(n->right);
		}
	}

	template <typename T>
	void Tree<T>::printPreOrder(Node<T> *n, int offset)
	{
		if(n)
		{
			std::cout << "val[" << n->data << "]" 
				      << " height[" << n->height() << "]" 
					  << " parent[" << (n->parent?n->parent->data:-1) << "]"
					  << std::endl;
			printPreOrder(n->left, offset+1);
			printPreOrder(n->right, offset+1);
		}
	}

	template <typename T>
	void Tree<T>::printPostOrder(Node<T> *n)
	{
		if(n)
		{
			printPostOrder(n->left);
			printPostOrder(n->right);
			std::cout << n->data
				      << " : " << n->height() << std::endl;
		}
	}

	template <typename T>
	void Tree<T>::printInOrder(Node<T> *n)
	{
		if(n)
		{
			printInOrder(n->left);
			std::cout << n->data
				      << " : " << n->height() << std::endl;
			printInOrder(n->right);
		}
	}

	template <typename T>
	Node<T> *Tree<T>::findR(const T &k, Node<T> *n)
	{
		Node<T> *ret(0);

		if(n)
		{
			if(k < n->data)
				ret = find(k, n->left);
			else if(k > n->data.first)
				ret = find(k, n->right);
			else 
				ret = n;
		}

		return ret;
	}

	template <typename T>
	Node<T> *Tree<T>::findInternal(const T &d)
	{
		bool found(false);
		Node<T> *current(root_);

		while(current && ! found)
		{
			if(d < current->data)
				current = current->left;
			else if(d > current->data)
				current = current->right;
			else
				found = true;
		}

		return current;
	}

	template <typename T>
	Node<T> *Tree<T>::minNode()
	{
		Node<T> *ret(0);
		Node<T> *current( root_ );

		while(current)
		{
			ret = current;
			current = current->left;
		}

		return ret;
	}

	template <typename T>
	Node<T> *Tree<T>::maxNode()
	{
		Node<T> *ret(0);
		Node<T> *current( root_ );

		while(current)
		{
			ret = current;
			current = current->right;
		}

		return ret;
	}

	// TODO : AVL balance the tree
	template <typename T>
	void Tree<T>::removeR(const T &d, Node<T> *&n)
	{
		if(n)
		{
			if(d < n->data)
				removeR(d, n->left);
			else if(d > n->data)
				removeR(d, n->right);
			else if(n->left != 0 && n->right != 0)
			{
				int rightMinVal = removeMin(n->right);
				n->data = rightMinVal;
			}
			else if(n->left == 0 && n->right == 0)
			{
				delete n;
				n = 0;
			}
			else if(n->left == 0 && n->right != 0)
			{
				Node<T> *tmp(n->right);
				delete n;
				n = tmp;
			}
			else if(n->right == 0 && n->left != 0)
			{
				Node<T> *tmp(n->left);
				delete n;
				n = tmp;
			}
		}
	}

	// remove all the 'd's in the tree and return
	// how many were removed
	template <typename T>
	int Tree<T>::removeInternal(const T &d)
	{
		int ret(0);
	}

	template <typename T>
	Node<T> *Tree<T>::inorderNext(Node<T> *n)
	{
		Node<T> *current(n);
		Node<T> *ret(0);

		if(current->right)
		{
			ret = current->right;

			while(ret->left)
				ret = ret->left;
		}
		else
		{
			Node<T> *previous(current);

			// climb up
			while(current && current->left != previous)
			{
				// if root is reached from a right node
				// that is the end
				if(current == root_ && previous == current->right)
				{
					current = 0;
				}
				else
				{
				    previous = current;
				    current = current->parent;
				}
			}

			ret = current;
		}

		return ret;
	}

	template <typename T>
	T Tree<T>::removeMin(Node<T> *&n)
	{
		T ret;

		if(n->left)
		{
			ret = removeMin(n->left);
		}
		else
		{
			ret = n->data;
			Node<T> *tmp(n->right);
			delete n;
			n = tmp;
		}

		return ret;
	}

	template <typename T>
	Node<T> *Tree<T>::singleRotateLeft(Node<T> *n)
	{
		Node<T> *k2(n);
		Node<T> *k1(k2->left);

		k2->left = k1->right;
		if(k1->right) k1->right->parent = k2;
		k1->right = k2;
		k2->parent = k1;

		k1->computeHeight();
		k2->computeHeight();

		return k1;
	}

	template <typename T>
	Node<T> *Tree<T>::singleRotateRight(Node<T> *n)
	{
		Node<T> *k1(n);
		Node<T> *k2(n->right);

		k1->right = k2->left;
		if(k2->left) k2->left->parent = k1;
		k2->left = k1;
		k1->parent = k2;

		k1->computeHeight();
		k2->computeHeight();

		return k2;
	}

	template <typename T>
	Node<T> *Tree<T>::doubleRotateLeft(Node<T> *n)
	{
		Node<T> *k3(n);

		k3->left = singleRotateRight(k3->left);

		return singleRotateLeft(k3);
	}

	template <typename T>
	Node<T> *Tree<T>::doubleRotateRight(Node<T> *n)
	{
		Node<T> *k1(n);

		k1->right = singleRotateLeft(k1->right);

		return singleRotateRight(k1);
	}

} // namespace STLHow

#endif