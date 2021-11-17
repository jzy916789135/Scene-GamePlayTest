#pragma once
#include "BasicNode.h"
#include "Actor.h"
class World;

/* only contain a world as scenegraph's brgining */
class Tree
{
public:
	Tree();
	~Tree();

	/*  for scenegraph, get rootnode from created world */
	BasicNode* GetRootNode();

	World* pWorld;

};

