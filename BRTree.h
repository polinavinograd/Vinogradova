#pragma once
#include<iostream>
using namespace std;         /*BLACK = true*/
                             /*RED = false*/
struct Node {
	int key;
	bool color;
	Node* left;
	Node* right;
	Node* parent;
};

class BRTree
{
private:
	Node* root = NULL;
	Node* grandparent(Node* n);
	Node* uncle(Node* n);
	Node* sibling(Node* n);


	void
		rotate_left(Node* n);

	void
		rotate_right(Node* n);

	void
		replace_node(Node* n, Node* child);

	bool
		is_leaf(Node* n);

	void
		insert_case1(Node* n);

	void
		insert_case2(Node* n);

	void
		insert_case3(Node* n);

	void
		insert_case4(Node* n);

	void
		insert_case5(Node* n);

	void
		delete_case1(Node* n);

	void
		delete_case2(Node* n);

	void
		delete_case3(Node* n);

	void
		delete_case4(Node* n);

	void
		delete_case5(Node* n);

	void
		delete_case6(Node* n);

	Node* search1(int key);

	Node* search_min(Node* n);

	Node* search_max(Node* n);

	Node* searchNearMin(Node* n);

	Node* searchNearMax(Node* n);

public:
	void
		insert(int key);
	void
		Delete(int key);
	bool
		search(int key);
	int
		searchGlobMax();
	int
		searchGlobMin();
	int
		searchNearestLess(int key);
	int
		searchNearestMore(int key);
};

