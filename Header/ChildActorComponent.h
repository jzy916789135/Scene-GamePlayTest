#pragma once
#include "Actor.h"
#include "TransformComponent.h"
class TransformComponent;
class Actor;

/* this class's only function is contain Actors */
class ChildActorComponent
{
public:
	ChildActorComponent();
	~ChildActorComponent();

public:

	std::vector<Actor*> GetActors();

	void AddNewActor(Actor* actor);

	/* when actor in mActors want to be destroyed, this func is remove actor from mActors */
	void PreDestroy(Actor* actor);

	/*  */
	void RemoveActor(Actor* actor);

private:

	std::vector<Actor*> mActors;
};

