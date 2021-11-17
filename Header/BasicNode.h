#pragma once
#include "DataStructLibrary.h"
#include "Geometry.h"
#include "Material.h"
#include <vector>
#include <unordered_map>


class BasicNode
{
public:
	BasicNode();
	BasicNode(std::string name);
	~BasicNode();

public:


	enum NodeType {
		BasicNodeType,
		GeometryNodeType,
		TransformNodeType,
		RootNodeType
	};

	/* Destory the selected node from scenegraph */
	void DestoryChildNode(BasicNode* node);

	/* Destory all nodes from scenegraph */
	void DestoryAllChildNodes();

	/* Append a new node to this children list of this node */
	void AppendChildNode(BasicNode* node);

	/* Remove the child node from parent node and push it under the Root node */
	void RemoveChildNode(BasicNode* node);

	/* Set a new Parent node to this node,*/
	/* and delete the old relation of this node and it's old prenet */
	void ReParentChildNodeTo(BasicNode* newParent);

	BasicNode* GetParentNode() { return pParent; }

	int ChildCount() const;

	void SetName(std::string name);

	void SetParent(BasicNode* node) { pParent = node; }
	BasicNode* Parent() { return pParent; }
	unordered_map<std::string, BasicNode*> Children() { return mChildren; }

	virtual void Update();

	void DeleteNode(BasicNode* node);

	/* for test */
	string GetName() { return mName; }
	
private:
	
	BasicNode* pParent;

	unordered_map<std::string,BasicNode*> mChildren;
	
	std::string mName;

	FTransform mRelativeTransform;

	NodeType mType;
};

//-------------------------------

class TransformNode : public BasicNode
{
public:
	TransformNode();
	~TransformNode();


private:

	/* Every TransformNode has a mComponent, default nullptr */
	/* Contain the node's geometry,material,texture and so on  */
	Geometry* mGeometry;
	Material* mMaterial;

	FTransform* mTransform;
};

