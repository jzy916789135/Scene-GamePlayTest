#include "World.h"

World::World()
	: mActors()
	, mActorMapNameToindex()
	, mActorsStateFlags()
	, mName("DefaultWorld")
{
	pRootNode = new BasicNode("DefaultWorld");
}

World::World(std::string name)
	: mActors()
	, mActorMapNameToindex()
	, mActorsStateFlags()
	, mName(name)
{
	pRootNode = new BasicNode(name);
}

World::~World()
{

}

void World::DestroyActor(Actor* actor)
{
	auto iter = find(mActors.begin(), mActors.end(), actor);
	if (mActorsStateFlags[iter - mActors.begin()] == PointerCanBeUse)
	{
		cout << "Destroying failed, actor you want to destroy has not existed" << endl;
		return;
	}

	if (!actor->GetWorld())
	{
		cout << "Destroying failed" + actor->GetName() + " has not a valid world pointer" << endl;
		return;
	}

	if (actor->GetRootComponent()->CheckChildActorComponent())
	{
		for (auto child : actor->GetChildrenActors())
		{
			DestroyActor(child);
		}
	}
	auto RootComponent = actor->GetRootComponent();
	DestroyComponent(RootComponent);

	/* Get Actor index from map by actor's name , then find itself by the index from mActors and delete itself */
	int index = mActorMapNameToindex[actor->GetName()];
	if (index > mActorsStateFlags.size() || index < 0)
	{
		std::cout<< " can't find actor index form world Actor's list  " << endl;
	}
	if (mActorsStateFlags[index] == PointerCanBeUse)
	{
		std::cout << "the actor pointer is already reset" << endl;
	}

	/* delete the map actor's name to index, Destructor the actor  and set the pointer state */
	if (actor->GetParentActor())
	{
		actor->GetParentActor()->PreDetroy(actor);
	}
	actor->SceneNode()->Parent()->DestoryChildNode(actor->SceneNode());
	mActorMapNameToindex.erase(actor->GetName());
	delete mActors[index];
	mActorsStateFlags[index] = PointerCanBeUse;



}

void World::DestroyComponent(TransformComponent* &thiscomponent)
{
	if (!thiscomponent)
	{
		cout << "Destroying failed" + thiscomponent->GetName() + " has not existed" << endl;;
		return;
	}
	else
	{
		auto chidlcomponents = thiscomponent->GetChildrenComponents();
		if (chidlcomponents.size() != 0)
		{
			/* Traverse the component children list and delete it one by one */
			for (auto component : thiscomponent->GetChildrenComponents())
			{
				DestroyComponent(component);
			}
		}
		/* if this component has not child component, delete itself, but not delete RootComponent */
		auto parent = thiscomponent->GetParentComponent();
		if(chidlcomponents.size() == 0 && parent)
		{
			thiscomponent->PreDestroy();
			auto name = thiscomponent->GetName();
			delete thiscomponent;
			thiscomponent = NULL;
			std::cout << "compontnt" + name + " has been delete" << endl;
		}


		return;
	}
}

std::vector<Actor*> World::GetActors()
{
	vector<Actor*> returnactors;
	for (auto map: mActorMapNameToindex)
	{
		returnactors.push_back(mActors[map.second]);
	}
	return returnactors;
}

void World::AddActorToWorld(Actor* actor)
{
	if (!actor)
	{
		cout << " actor is not exist " << endl;
	}



	mActors.push_back(actor);
	mActorsStateFlags.push_back(PointerIsUsed);
	if (!CheckName(actor->GetName()))
	{
		for (int i = 0; i < mActors.size(); i++)
		{
			if (mActors[i] == actor)
			{
				actor->SetName("Actor" + to_string(i));
				break;
			}
		}
		
	}
	mActorMapNameToindex[actor->GetName()] = int(mActors.size())-1;
	Update(actor);
}
/*
Actor* World::SpwanActor(const ActorSpawnParametres& parameters)
{
	Actor* Template = parameters.pTemplate;
	std::string name = parameters.mName;
	if (!Template)
	{
		Template = GetDefaultObject<Actor>();
	}
	if (!CheckName(name))
	{
		name += std::to_string(GetActors().size());
	}
	Template->SetName(name);
	Template->SetWorld(this);

	mExitsActors.push_back(Template);
	return Template;
}
*/

void World::Update(Actor* actor)
{
	actor->SetWorld(this);
	actor->Update();
}

void World::Update()
{
	for (auto actor : mActors)
	{
		Update(actor);
	}
}

bool World::CheckName(std::string name)
{
	auto actors = this->GetActors();
	for (auto actor : actors)
	{
		if (actor->GetName() == name)
		{
			return false;
		}
	}
	return true;
}
/* -------------------------------------------- */

Actor* World::CreateDefaultActor()
{
	for (int i = 0; i < mActorsStateFlags.size(); i++)
	{
		if (mActorsStateFlags[i] == PointerCanBeUse)
		{
			mActorsStateFlags[i] = PointerIsUsed;
			mActors[i] = new Actor();
			mActorMapNameToindex[mActors[i]->GetName()] = i;
			Update(mActors[i]);

			return mActors[i];
		}
	}

	/* Create Default Actor */
	Actor* newactor = new Actor();
	AddActorToWorld(newactor);
}

BasicNode* World::GetRootNode()
{
	return pRootNode;
}

/* ----------------------------------------------- */
ActorSpawnParametres::ActorSpawnParametres()
	: mName("DefaultActor")
	, pWorld(0)
	, pTemplate(0)
	, mTransform()
{
}