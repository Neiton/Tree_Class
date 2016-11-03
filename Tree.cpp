#include "Tree.h"

TreeNode * TreeNode::Parent() { return _parent; }

int TreeNode::NodeLevel() { return _level; }

int TreeNode::AbsoluteIndex() { return _absoluteIndex; }

int TreeNode::Index() { return _id; }

SubItems * TreeNode::Items()
{
	if (!_subItems) _subItems = new SubItems;
	return _subItems;
}

TreeNode * TreeNode::Items(int i) { return _subItems->at(i); }

TreeNode::~TreeNode()
{
	if (_subItems) delete _subItems;
	_subItems = 0;
}


//-------------------------------------------------------------------------------

int Tree::CalculateOffset(int parentID)
{
	int offset = 0;
	if (_v.at(parentID)->Items()->Count())
		offset = _v.at(parentID)->_subItems->_v.back()->_absoluteIndex;
	else
		offset = parentID;
	return offset;
}

Tree::Tree()
{
	_subItems = new SubItems;
}

TreeNode * Tree::addItem(TreeNode * node)
{
	int lastID = 0;

	for (size_t i = 0; i < _v.size(); i++)
	{
		if (_v[i]->_level == 0) lastID++;
	}
	
	node->_absoluteIndex = _v.size();
	node->_id = lastID;

	_v.push_back(node);
	_subItems->_v.push_back(node);

	return node;
}

TreeNode * Tree::addSubItem(int parentID, TreeNode * node)
{ 
	_v.insert(_v.begin() + CalculateOffset(parentID) + 1, node);

	_v[parentID]->_subItems->_v.push_back(node);

	node->_parent = _v.at(parentID);
	node->_level = _v.at(parentID)->_level + 1;

	for (size_t i = 0; i < _v.size(); i++)
	{
		_v[i]->_absoluteIndex = i;
		if (_v[i]->_absoluteIndex == parentID)
		{
			TreeNode* parent = _v[i]->_parent;
			if (parent)
			{
				for (int j = 0; j < parent->_subItems->_v.size(); j++)
				{
					parent->_subItems->at(j)->_id = j;
				}
			}
			else
			{
				for (int j = 0; j < _subItems->_v.size(); j++)
				{
					_subItems->at(j)->_id = j;
				}
			}
		}
	}
	return node;
}

void Tree::Clear()
{
	if (_subItems) delete _subItems;
	_v.clear();
}

Tree::Result Tree::deleteItem(int id)
{
	Result r = Success;
	if (_v.size() <= id) return InvalidIndex;

	
	int parentID = _v[id]->_parent ? _v[id]->_parent->_absoluteIndex : -1;

	_v.erase(_v.begin() + id);

	for (size_t i = 0; i < _v.size(); i++)
	{
		_v[i]->_absoluteIndex = i;
		if (i == parentID)
		{
			TreeNode* parent = _v.at(parentID);
			for (int j = 0; j < parent->Items()->Count(); j++)
			{
				parent->Items()->at(j)->_id = j;
			}
		}
	}

	return r;
}

Tree::Result Tree::deleteItem(int id1, int id2)
{
	Result r = Success;
	if (_v.size() <= id2 || _v.size() <= id1 || id2 < 1 || id1 < 0) return InvalidIndex;


	int parentID = _v[id1]->_parent ? _v[id1]->_parent->_absoluteIndex : -1;

	_v.erase(_v.begin() + id1, _v.begin() + id2);

	for (size_t i = 0; i < _v.size(); i++)
	{
		_v[i]->_absoluteIndex = i;
		if (i == parentID)
		{
			TreeNode* parent = _v.at(parentID);
			for (int j = 0; j < parent->Items()->Count(); j++)
			{
				parent->Items()->at(j)->_id = j;
			}
		}
	}

	return r;
}

void Tree::FromString(string s)
{
	this->Clear();
	while (s.length() > 1)
	{
		size_t p1 = s.find("#");
		size_t p2 = s.find(";");	//1#-;1#0;
		if (!p1 || !p2) break;

		TreeNode* node = new TreeNode;
		node->nodeName = s.substr(0, p1);

		string parentID_s = s.substr(p1 + 1, p2 - p1 - 1);

		if (parentID_s == "-")
		{
			addItem(node);
		}
		else
		{
			int parentID = std::stoi(parentID_s);
			addSubItem(parentID, node);
		}

		s.erase(0, p2+1);
	}
}

string Tree::ToString()
{
	string s;

	size_t n = _v.size();

	for (size_t i = 0; i < n; i++)
	{
		s += _v[i]->nodeName;
		s += "#";
		s += (_v[i]->_level > 0) ? std::to_string(_v[i]->_parent->_absoluteIndex) : "-";
		s += ";";
	}

	return s;
}

int Tree::TotalCount() { return _v.size(); }

int Tree::Count() { return _subItems->Count(); }

SubItems * Tree::Items() { return _subItems; }

TreeNode * Tree::Items(int i) { return _subItems->at(i); }

TreeNode* Tree::at(int id) { return _v.at(id); }

Tree::~Tree()
{
	_v.clear();
	if (_subItems) delete _subItems;
	_subItems = 0;
}

//------------------------------------------------------------------------------------

int SubItems::Count() { return _v.size(); }

TreeNode * SubItems::at(int id) { return _v.at(id); }

SubItems::~SubItems()
{
	_v.clear();
}


