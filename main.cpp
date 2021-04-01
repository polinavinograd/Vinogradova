#include<iostream>
#include"BRTree.h"
using namespace std;
int main()
{
	system("chcp 1251");
	BRTree tree; 
	int key;
	int numEl;
	cout << "The number of elements: " ;
	cin >> numEl;
	for (int i = 0; i < numEl; i++)
	{
		cin >> key;
		if (!tree.search(key))
			tree.insert(key);
		else i--;
	}
	int absmin, absmax, key1, key2, key3, key4;
	bool skey1;
	while (true)
	{
		cout << "choose the function" << endl
			<< "(1) delete" << endl
			<< "(2) search" << endl
			<< "(3) maximum" << endl
			<< "(4) minimum" << endl
			<< "(5) search the nearest less" << endl
			<< "(6) search the nearest more" << endl
			<< "(7) close the program" << endl;
		int i;
		cin >> i;
		switch (i)
		{
		case 1:
			cout << "choose the element to delete: ";
			cin >> key1;
			skey1 = tree.search(key1);
			if (skey1 == true)
				tree.Delete(key1);
			else cout << "this element doesn't exist" << endl;
			break;

		case 2:
			cout << "choose the element to search: ";
			cin >> key2;
			skey1 = tree.search(key2);
			if (skey1 == true)
				cout << "exists" << endl;
			else cout << "doesn't exist" << endl;
			break;

		case 3:
			absmax = tree.searchGlobMax();
			cout << "maximum: " << absmax << endl;
			break;

		case 4:
			absmin = tree.searchGlobMin();
			cout << "minimum: " << absmin << endl;
			break;


		case 6:
			cout << "the nearest more from: ";
			cin >> key3;
			skey1 = tree.search(key3);
			if (skey1 == true)
			{
				int nmax = tree.searchNearestMore(key3);
				cout << "the element: " << nmax << endl;
			}
			else cout << "doesn't exist" << endl;
			break;

		case 5:
			cout << "the nearest less from: ";
			cin >> key4;
			skey1 = tree.search(key4);
			if (skey1 == true)
			{
				int nmin = tree.searchNearestLess(key4);
				cout << "the element: " << nmin << endl;
			}
			else cout << "doesn't exist" << endl;


		case 7:
			return 0;
			break;
		}
	}
}