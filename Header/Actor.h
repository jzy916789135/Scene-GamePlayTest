#pragma once
#include "BasicNode.h"
#include "TransformComponent.h"
#include "DataStruct.h"
#include "BaseObject.h"
class World;
class TransformComponent;

class Actor : public BaseObject
{
public:
	Actor();
	Actor(std::string name);
	~Actor();
	
public:

	void Initalize();

	/* create a new component to this actor */
	TransformComponent* AddComponent();

	/* add a existed component to this actor */
	TransformComponent* AddComponent(TransformComponent* child);

	/* only remove selected actor in this actor's children components list, but not destroy
	   if you want to delete this component, don't use it. please use DestroyComponent() in World
	*/
	void RemoveComponent(TransformComponent* child);
	
	/* attach this actor as a child actor to a actor */
	void AttachToActor(Actor* actor);

	/* only remove selected actor in this actor's children actors list, but not destroy ,the actor is already existed in world
	   if you want to delete this actor, don't use it. please use DestroyActor() in World or DeleteActor()	*/
	void RemoveActor(Actor* parentactor);

	void ReParentChildActorTo(Actor* actor);

	/* return RootComponent  */
	TransformComponent* GetRootComponent();

	BasicNode* SceneNode();

	/* return children actors */
	std::vector<Actor*> GetChildrenActors();

	/* return children components */
	std::vector<TransformComponent*> GetChildrenComponents();

	/* return this actor's parent actor */
	Actor* GetParentActor();

	/* return world which the actor exits */
	World* GetWorld();

	/* Set world which this actor in */
	void SetWorld(World* world);

	/* Get Actor's name */
	std::string GetName();

	/* Set Actor's name */
	void SetName(std::string name);

	/* update parameters to it's component and actors */
	void Update();

	/* Register RootComponent */
	void RegisterRootComponent();

	/* return bbox of this actor*/
	Box GetActorBoundingBox();

	/* get sum bbox of this actor's children */
	Box GetAllComponentsBoundingBox();

	/* Delete Actor(really destroy this child actor) */
	void DeleteActor(Actor* actor);

	/* some process before actor/world delete it's child actor */
	void PreDetroy(Actor* actor);

private:
	/* SceneGraph node to serialize and deserialize*/
	BasicNode* pNode;

	//std::vector<TransformComponent*> mChildComponents;

	Actor* pParent;

	World* pWorld;

	std::string mName;


protected:
	TransformComponent* pRootComponent;

public:
};





