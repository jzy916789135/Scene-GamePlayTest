#include "BasicNode.h"
#include <assert.h>

BasicNode::BasicNode()
	: pParent(0)
	, mName("DefaultNode")
	, mChildren(0)
	, mRelativeTransform()
{
};

BasicNode::BasicNode(std::string name)
	: pParent(0)
	, mName(name)
	, mChildren(0)
	, mRelativeTransform()
{
};

BasicNode::~BasicNode()
{
}

void BasicNode::DestoryChildNode(BasicNode* node)
{
	/* if node has child, destroy child */
	if (node->ChildCount() != 0)
	{
		auto Children = node->mChildren;
		for (auto child : Children)
		{
			node->DestoryChildNode(child.second);
		}
	}
	/* if node has not any child, destroy the node */
	else
	{
		mChildren.erase(node->mName);
		delete node;
	}

}

void BasicNode::DestoryAllChildNodes()
{
	if (Children().empty())
	{
		cout<< " destroy node error: this node has not any child node " <<endl;
	}
	else
	{
		auto Children = mChildren;
		for (auto child : Children)
		{
			DestoryChildNode(child.second);
		}
	}
	
}

void BasicNode::RemoveChildNode(BasicNode* node)
{
	if (mChildren.count(node->mName))
	{
		mChildren.erase(node->mName);
		/* get rootnode and push this node under root node */
		auto parent = this;
		while (parent->pParent)
		{
			parent = parent->pParent;
		}
		parent->AppendChildNode(node);
	}

	else
		cout << "this node is not child node of this node / this child node maybe remove already" << endl;;

	
}

void BasicNode::AppendChildNode(BasicNode* node)
{
	if (node)
	{
		if (node->pParent)
		{
			node->pParent->DeleteNode(node);
		}

		node->pParent = this;
		pair<std::string, BasicNode*> add{ node->mName, node };
		mChildren.insert(add);
	}
	else
		cout << " node you want to add is not exist " << endl;

}


void BasicNode::ReParentChildNodeTo(BasicNode* newParent)
{	
	if (this->pParent)
	{
		//this->pParent->mChildren.erase(this->mName);
		pParent->DeleteNode(this);
		this->pParent = NULL;
	}
	newParent->AppendChildNode(this);
}
/*  Get the number of children count of this node */
int BasicNode::ChildCount() const
{
	int count = 0;

	for (auto Iter = mChildren.begin(); Iter != mChildren.end(); Iter++)
	{
		count += 1;
	}
	return count;
}

void BasicNode::Update()
{
	
}

void BasicNode::SetName(std::string name)
{
	if (pParent)
	{
		auto copynode = pParent->mChildren[this->mName];
		pParent->mChildren.erase(this->mName);

		mName = name;
		pParent->mChildren.insert({ mName,copynode });
	}


}

void BasicNode::DeleteNode(BasicNode* node)
{
	if (mChildren.find(node->mName) == mChildren.end())
	{
		cout << "delete node error: acn't find node in childnodes list" << endl;
	}
	else 
	{
		mChildren.erase(node->mName);
	}
}


/*--------- TransformNode------*/
TransformNode::TransformNode()
	: mGeometry(0)
{
}

TransformNode::~TransformNode()
{
}

