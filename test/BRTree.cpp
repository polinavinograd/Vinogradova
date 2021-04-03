#include "BRTree.h"
#pragma once
#include <string>
#include<iostream>
#include<vector>
using namespace std;         /*BLACK = true*/
							 /*RED = false*/

	Node* BRTree::grandparent(Node* n)
	{
		if ((n != NULL) && (n->parent != NULL))
			return n->parent->parent;
		else
			return NULL;
	}
	Node* BRTree::uncle(Node* n)
	{
		Node* g = grandparent(n);
		if (g == NULL)
			return NULL;
		if (g->left == n->parent)
			return g->right;
		if (g->right == n->parent)
			return g->left;
	}
	Node* BRTree::sibling(Node* n)
	{
		if (n->parent != NULL)
		{
			if (n == n->parent->right)
				return n->parent->left;
			else
				return n->parent->right;
		}
		else
			return NULL;
	}


	void
		BRTree::rotate_left(Node* n)
	{
		Node* pivot = n->right;

		pivot->parent = n->parent;
		if (n->parent != NULL) {
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}

		n->right = pivot->left;
		if (pivot->left != NULL)
			pivot->left->parent = n;

		n->parent = pivot;
		pivot->left = n;
	}

	void
		BRTree::rotate_right(Node* n)
	{
		Node* pivot = n->left;

		pivot->parent = n->parent;
		if (n->parent != NULL) {
			if (n->parent->left == n)
				n->parent->left = pivot;
			else
				n->parent->right = pivot;
		}

		n->left = pivot->right;
		if (pivot->right != NULL)
			pivot->right->parent = n;

		n->parent = pivot;
		pivot->right = n;
	}

	void
		BRTree::replace_node(Node* n, Node* child)
	{
		child->parent = n->parent;
		if (n == n->parent->left)
			n->parent->left = child;
		else
			n->parent->right = child;
		n = child;
	}

	bool
		BRTree::is_leaf(Node* n)
	{
		if (n == NULL)
			return true;
		else
			return false;
	}

	void
		BRTree::insert_case1(Node* n)
	{
		if (n->parent == NULL)
			n->color = true;
		else
			insert_case2(n);
	}

	void
		BRTree::insert_case2(Node* n)
	{
		if (n->parent->color == true)
			return;
		else
			insert_case3(n);
	}

	void
		BRTree::insert_case3(Node* n)
	{
		Node* u = uncle(n), * g;

		if ((u != NULL) && (u->color == false))
		{
			n->parent->color = true;
			u->color = true;
			g = grandparent(n);
			g->color = false;
			insert_case1(g);
		}
		else
			insert_case4(n);
	}

	void
		BRTree::insert_case4(Node* n)
	{
		Node* g = grandparent(n);

		if ((n == n->parent->right) && (n->parent == g->left))
		{
			rotate_left(n->parent);
			n = n->left;
		}
		else if ((n == n->parent->left) && (n->parent == g->right))
		{
			rotate_right(n->parent);
			n = n->right;
		}
		insert_case5(n);
	}

	void
		BRTree::insert_case5(Node* n)
	{
		Node* g = grandparent(n);
		n->parent->color = true;
		g->color = false;
		if ((n == n->parent->left) && (n->parent == g->left))
			rotate_right(g);
		else
			rotate_left(g);
	}

	void
		BRTree::delete_case1(Node* n)
	{
		if (n->parent != NULL)
			delete_case2(n);
	}

	void
		BRTree::delete_case2(Node* n)
	{
		Node* s = sibling(n);
		if (s->color == false)
		{
			n->parent->color = false;
			s->color = true;
			if (n == n->parent->left)
				rotate_left(n->parent);
			else
				rotate_right(n->parent);
		}
		delete_case3(n);
	}

	void
		BRTree::delete_case3(Node* n)
	{
		Node* s = sibling(n);
		if ((n->parent->color == true) &&
			(s->color == true) &&
			(s->left == NULL || s->left->color == true) &&
			(s->right == NULL || s->right->color == true))
		{
			s->color = false;
			delete_case1(n->parent);
		}
		else
			delete_case4(n);
	}

	void
		BRTree::delete_case4(Node* n)
	{
		Node* s = sibling(n);
		if ((n->parent->color == false) &&
			(s->color == true) &&
			(s->left == NULL || s->left->color == true) &&
			(s->right == NULL || s->right->color == true))
		{
			s->color = false;
			n->parent->color = true;
		}
		else
			delete_case5(n);
	}

	void
		BRTree::delete_case5(Node* n)
	{
		Node* s = sibling(n);
		if (s->color == true)
		{
			if ((n == n->parent->left) &&
				(s->right->color == true) &&
				(s->left->color == false))
			{
				s->color = false;
				s->left->color = true;
				rotate_right(s);
			}
			else if ((n == n->parent->right) &&
				(s->left->color == true) &&
				(s->right->color == false))
			{
				s->color = false;
				s->right->color = true;
				rotate_left(s);
			}
		}
		delete_case6(n);
	}

	void
		BRTree::delete_case6(Node* n)
	{
		Node* s = sibling(n);
		s->color = n->parent->color;
		n->parent->color = true;
		if (n == n->parent->left)
		{
			s->right->color = true;
			rotate_left(n->parent);
		}
		else
		{
			s->left->color = true;
			rotate_right(n->parent);
		}
	}

	Node* BRTree::search1(int key)
	{
		Node* tmp = root;
		while (tmp != NULL)
		{
			if (key == tmp->key)
			{
				return tmp;
			}
			if (key > tmp->key)
			{
				tmp = tmp->right;
				continue;
			}
			if (key < tmp->key)
			{
				tmp = tmp->left;
				continue;
			}
		}
		return tmp;
	}

	Node* BRTree::search_min(Node* n)
	{
		Node* tmp = n;
		if (tmp->left != NULL)
		{
			return search_min(tmp->left);
		}
		else {
			return tmp;
		}
	}

	Node* BRTree::search_max(Node* n)
	{
		Node* tmp = n;
		if (tmp->right != NULL)
		{
			return search_max(tmp->right);
		}
		else {
			return tmp;
		}
	}

	Node* BRTree::searchNearMin(Node* n)
	{
		Node* tmp = n;
		Node* begin = n;
		if (tmp->left != NULL)
		{
			return tmp->left;
		}
		else if (tmp == tmp->parent->right)
		{
			return tmp->parent;
		}
		else if (tmp == tmp->parent->left)
		{
			while (tmp->parent->key > tmp->key)
			{
				tmp = tmp->parent;
				if (tmp->parent == NULL)
				{
					return NULL;
				}
			}
			tmp = tmp->parent;
			return tmp;
		}
	}

	Node* BRTree::searchNearMax(Node* n)
	{
		Node* tmp = n;
		Node* begin = n;
		if (tmp->right != NULL)
			return tmp->right;
		else if (tmp == tmp->parent->left)
		{
			return tmp->parent;
		}
		else if (tmp == tmp->parent->right)
		{
			while (tmp->parent->key < tmp->key)
			{
				tmp = tmp->parent;
				if (tmp->parent == NULL)
				{
					return NULL;
				}
			}
			tmp = tmp->parent;
			return tmp;
		}

	}

	void BRTree::View_Tree(Node* n, int level)
	{
		string s;
		if (n)
		{
			View_Tree(n->right, level + 1);
			for (int i = 0; i < level; i++)
			{
				s += "  ";
			}
			cout << s << n->key << "\n";
			View_Tree(n->left, level + 1);
		}
	}

	void BRTree::View()
	{
		View_Tree(root, 0);
	}
	void
		BRTree::insert(int key)
	{
		if (search(key))return;
		if (root == NULL)
		{
			Node* r = new Node;
			r->color = true;
			r->parent = NULL;
			r->left = NULL;
			r->right = NULL;
			r->key = key;
			root = r;
		}
		else
		{
			Node* tmp;
			tmp = root;
			Node* p;
			p = NULL;
			while (tmp != NULL)
			{
				if (key < tmp->key)
				{
					p = tmp;
					tmp = tmp->left;
					continue;
				}

				if (key > tmp->key)
				{
					p = tmp;
					tmp = tmp->right;
					continue;
				}
			}
			tmp = new Node;
			tmp->color = false;
			tmp->parent = p;
			tmp->right = NULL;
			tmp->left = NULL;
			tmp->key = key;
			if (tmp->key < p->key)
			{
				p->left = tmp;
			}
			if (tmp->key > p->key)
			{
				p->right = tmp;
			}
			insert_case1(tmp);
			while (tmp->parent != NULL)tmp = tmp->parent;
			root = tmp;
		}
	}
	void
		BRTree::Delete(int key)
	{
		Node* tmp = root;
		while (tmp->key != key)
		{
			if (key > tmp->key)
			{
				tmp = tmp->right;
				continue;
			}
			if (key < tmp->key)
			{
				tmp = tmp->left;
				continue;
			}
		}
		Node* replace = NULL;
		if (tmp->right != NULL)
			replace = search_min(tmp->right);
		else if (tmp->left != NULL)
			replace = search_max(tmp->left);
		if (replace != NULL)
		{
			tmp->key = replace->key;
			tmp = replace;
		}
		if (!is_leaf(tmp->right))
		{
			Node* child = tmp->right;
			replace_node(tmp, child);
		}
		else if (!is_leaf(tmp->left))
		{
			Node* child = tmp->left;
			replace_node(tmp, child);
		}
		if (tmp->color)
			delete_case1(tmp);
		if (tmp->key > tmp->parent->key)
			tmp->parent->right = NULL;
		else
			tmp->parent->left = NULL;
		delete tmp;
	}
	bool
		BRTree::search(int key)
	{
		Node* tmp = root;
		while (tmp != NULL)
		{
			if (key == tmp->key)
			{
				return true;
			}
			if (key > tmp->key)
			{
				tmp = tmp->right;
				continue;
			}
			if (key < tmp->key)
			{
				tmp = tmp->left;
				continue;
			}
		}
		return false;
	}
	int
		BRTree::searchGlobMax()
	{
		return search_max(root)->key;
	}
	int
		BRTree::searchGlobMin()
	{
		return search_min(root)->key;
	}
	int
		BRTree::searchNearestLess(int key)
	{
		bool skey;
		skey = search(key);
		if (skey == true)
		{
			Node* tmp = search1(key);
			Node* tmp1 = searchNearMin(tmp);
			if (tmp1 != NULL)
				return tmp1->key;
			else return tmp->key;
		}
		else return -1;
	}
	int
		BRTree::searchNearestMore(int key)
	{
		bool skey;
		skey = search(key);
		if (skey == true)
		{
			Node* tmp = search1(key);
			Node* tmp1 = searchNearMax(tmp);
			if (tmp1 != NULL)
				return tmp1->key;
			else return tmp->key;
		}
		else return -1;
	}
	void BRTree::Tree_to_Vector(vector<int>& a, Node* n)
	{
		if (!n)return;
		Tree_to_Vector(a, n->left);
		a.push_back(n->key);
		Tree_to_Vector(a, n->right);
	}
	void BRTree::Tree_to_Vector(vector<int>& a)
	{
		Tree_to_Vector(a, root);
	}
