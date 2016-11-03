#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;

class SubItems;
class TreeNode;
class Tree;

class SubItems
{
	friend class Tree;
private:
	vector<TreeNode*> _v;
public:
	int Count();
	TreeNode* at(int id);
	~SubItems();
};

class TreeNode
{
	friend class SubItems;
	friend class Tree;
private:
	SubItems* _subItems;
	int _absoluteIndex;
	int _level;
	int _id;
	TreeNode* _parent;
public:
	TreeNode(int abID = 0) : _subItems(0), nodeName(""), nodeData(""), _absoluteIndex(abID), _level(0), _id(0), _parent(0) 
	{
		_subItems = new SubItems;
	}

	string nodeName;
	string nodeData;

	TreeNode* Parent();

	int NodeLevel();
	int AbsoluteIndex();
	int Index();

	SubItems* Items();
	TreeNode* Items(int i);

	~TreeNode();
};

class Tree
{
private:
	vector<TreeNode*> _v;
	SubItems* _subItems;
protected:
	int CalculateOffset(int parentID);
public:
	enum Result { Success, InvalidIndex, OtherError };

	Tree();

	TreeNode* addItem(TreeNode* node);
	TreeNode* addSubItem(int parentID, TreeNode* node);

	void Clear();

	Result deleteItem(int id);
	Result deleteItem(int id1, int id2);

	void FromString(string s);
	string ToString();

	int TotalCount();
	int Count();

	SubItems* Items();
	TreeNode* Items(int i);

	TreeNode* at(int id);


	~Tree();
};
