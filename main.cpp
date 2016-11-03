#include <iostream>
#include "Tree.h"
#include <conio.h>

using std::cout;
using std::endl;

int main()
{
	Tree tree;

	TreeNode *root1, *root2;
	root1 = new TreeNode;
	root2 = new TreeNode;

	root1->nodeName = "ROOT1";
	root2->nodeName = "ROOT2";

	TreeNode *subItm1_1, *subItm2_1;
	TreeNode *subItm1_2, *subItm2_2;

	subItm1_1 = new TreeNode;
	subItm1_2 = new TreeNode;
	subItm2_1 = new TreeNode;
	subItm2_2 = new TreeNode;

	subItm1_1->nodeName = "1.1";
	subItm1_2->nodeName = "1.2";
	subItm2_1->nodeName = "2.1";
	subItm2_2->nodeName = "2.2";

	tree.addItem(root1);
	tree.addItem(root2);

	tree.addSubItem(0, subItm1_1);
	tree.addSubItem(0, subItm1_2);
	tree.addSubItem(tree.Items(1)->AbsoluteIndex(), subItm2_1);
	tree.addSubItem(tree.Items(1)->AbsoluteIndex(), subItm2_2);

	string s = tree.ToString();

	Tree tree2;

	tree2.FromString(s);

	cout << tree2.Items(1)->Items(1)->nodeName << endl;

	_getch();
	return 0;
}