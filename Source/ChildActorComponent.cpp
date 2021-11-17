#include "ChildActorComponent.h"

ChildActorComponent::ChildActorComponent()
	: mActors()
{

}

ChildActorComponent::~ChildActorComponent()
{
}

std::vector<Actor*> ChildActorComponent::GetActors()
{
	return mActors;
}

void ChildActorComponent::AddNewActor(Actor* actor)
{
	mActors.push_back(actor);
}

void ChildActorComponent::PreDestroy(Actor* actor)
{
	auto iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		mActors.erase(iter);
	}
	else
	{
		cout << "Destroy Error: this actor is not child of the actor" << endl;
	}
}
void ChildActorComponent::RemoveActor(Actor* actor)
{
	auto iter = find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		mActors.erase(iter);
	}
	else
		cout<<"Remove Error: this actor is not a child of the actor"<<endl;
}