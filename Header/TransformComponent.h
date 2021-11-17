#pragma once
#include <iostream>
#include <vector>
#include "World.h"
#include "BaseObject.h"
#include "ChildActorComponent.h"
using namespace std;
class World;
class Actor;
class ChildActorComponent;
class TransformComponent;

class TransformComponent : public BaseObject
{
public:
	TransformComponent();
	/* use when create a actor,to copy parameters to this RootComponent */
	TransformComponent(Actor* actor);
	~TransformComponent();

	void Release();
public:
	std::vector<TransformComponent*> GetChildrenComponents();

	TransformComponent* GetParentComponent();

	/* please ensure that parentcomponent is in a actor's components children list */
	void AttachToComponent(TransformComponent* parent);

	void RemoveChildComponent(TransformComponent* child);

	void RemoveChildActor(Actor* actor);

	void AttachToActor(Actor* actor);
	
	/* only used by when it's owner actor want to add a actor */
	void AddActor(Actor* actor);

	std::vector<Actor*> GetChildActors();

	/* initialize ChildActorComponent if it is not exist */
	void CheckandCreateChildActorComponent();

	/* only check if mChildActorComponent is exist  */
	bool CheckChildActorComponent();

public:

	FTransform RelativeTransform();

	FTransform WorldTransform();

	FTransform SetRelativeTransform(FTransform relativeTransform);

	FTransform SetWorldTransform(FTransform worldTransform);

public:
	/* update it's parameters when attach to component/actor  */
	void Update(TransformComponent* parent);

	/* use it to update RootComponent */
	void UpdateRootComponent();

	void UpdateTransform(TransformComponent* parent);

	World* GetWorld();

	Actor* GetOwner();

	/* Get Component's name */
	std::string GetName();

	/* Set Cimponent's name, please must use it if you want to change this Component's name */
	void SetName(std::string name);

	/* check if component's name has existed in child componens list , if repeat, return flase */
	bool CheckName(std::string name);

	/* some process before actor/world delete this component */
	void PreDestroy();

	/* if this component is a rootcomponent, this function is used to handle some things in pChildActorComponent */
	void PreDestroyForActors(Actor* actor);


private:
	FTransform mRelativeTransform;

	FTransform mWorldTransform;

	TransformComponent* pParentComponent;

	std::vector<TransformComponent*> mChildrenComponents;

	World* pWorld;

	Actor* pOwnerActor;

	ChildActorComponent* pChildActorComponent;

protected:


	/* indiactes if this component is currently registered with a scene */
	bool bRegistered : 1;

	/* if the render state is currently created for this component */
	bool bRenderStateCreated : 1;



public:
	std::string mComponentName;

	/* Can this component be destroyed  */
	bool bAllowAnyoneToRemoveMe ;

	/*  */
	bool bHasBeenCreated : 1;
public:

	/* Set state of bHasBeenCreated, show the creating state of this component before registeration*/
	void OnComponentCreated();

	void OnComponentDestroyed();

	/**/
	void OnRegister();

	/* See if this component is currently registered */
	bool IsRegistered() const { return bRegistered; }

	/* Registers a component with a specific world */
	void RegisterComponentWithWorld(World* world);

	void RegisterComponent();

	/* Check if childComponent is in this component children list */
	bool IsChild(TransformComponent* childComponent);


};
