#include "Actor.h"


Actor::Actor()
	: pNode(0)
	, pParent(0)
	, mName("DefaultActor")
{
	Initalize();
}

Actor::Actor(std::string name)
	: pNode(0)
	, pParent(0)
	, mName(name)
{
	Initalize();
}

void Actor::Initalize()
{
	pRootComponent = new TransformComponent(this);
	pNode = new BasicNode(mName);
}

Actor::~Actor()
{

}

TransformComponent* Actor::GetRootComponent()
{ 
	return pRootComponent; 
}

BasicNode* Actor::SceneNode() 
{ 
	return pNode;
}

std::vector<Actor*> Actor::GetChildrenActors()
{
	if(pRootComponent->CheckChildActorComponent())
		return pRootComponent->GetChildActors();
	
	else
	{
		cout << " actor has not childactor " << endl;
		return vector<Actor*>();
	}
	
}

std::vector<TransformComponent*> Actor::GetChildrenComponents()
{
	return pRootComponent->GetChildrenComponents();
}

Actor* Actor::GetParentActor()
{
	return pParent;
}

std::string Actor::GetName()
{
	return mName;
}

void Actor::SetName(std::string name)
{
	mName = name;
	pNode->SetName(name);
}

void Actor::RemoveComponent(TransformComponent* childcomponent)
{
	if (pRootComponent)
		pRootComponent->RemoveChildComponent(childcomponent);
	else
		cout << "RootComponent is not exist";
}

TransformComponent* Actor::AddComponent()
{
	TransformComponent* NewCom = new TransformComponent();
	if (!pRootComponent)
		pRootComponent = NewCom;
	else
	{
		NewCom->AttachToComponent(pRootComponent);
	}

	return NewCom;
}

TransformComponent* Actor::AddComponent(TransformComponent* child)
{
	if (child)
	{
		if (!pRootComponent)
			pRootComponent = child;
		else
		{
			child->AttachToComponent(pRootComponent);
		}
		return child;
	}
}

void Actor::RemoveActor(Actor* actor)
{

	pRootComponent->RemoveChildActor(actor);
	pNode->RemoveChildNode(actor->pNode);
	actor->pParent = NULL;
}

void Actor::ReParentChildActorTo(Actor* parentactor)
{
	if (this->pParent)
	{
		this->pParent->pRootComponent->RemoveChildActor(this);
		this->AttachToActor(parentactor);

		this->pParent->pNode->RemoveChildNode(this->pNode);
		pNode->ReParentChildNodeTo(parentactor->pNode);
	}
	else
	{
		this->AttachToActor(parentactor);
		pNode->ReParentChildNodeTo(parentactor->pNode);
	}
}

void Actor::AttachToActor(Actor* actor)
{
	if (actor)
	{	/* initialize ChildActorComponent if it is not exist */
		actor->pRootComponent->CheckandCreateChildActorComponent();
		auto childactors = actor->pRootComponent->GetChildActors();
		if(&childactors == NULL)
			cout << "error" << endl;
		/* check if this in actor's children list */
		std::vector<Actor*>::iterator iter = find(childactors.begin(), childactors.end(), this);
		if (iter == childactors.end())
		{
			actor->pRootComponent->AddActor(this);
			this->pParent = actor;
			this->pWorld = actor->pWorld;
			this->GetRootComponent()->UpdateTransform(actor->GetRootComponent());

			actor->pNode->AppendChildNode(this->pNode);
		}
		else
			cout << "the actor is already parent actor  of this actor " << endl;
	}
	else
		cout << "actor is not exist" << endl;
}

void Actor::Update()
{

	/* update RootComponent */
	pRootComponent->UpdateRootComponent();
	/* update child components */
	for (auto childcomponent : pRootComponent->GetChildrenComponents())
	{
		childcomponent->Update(pRootComponent);
	}

	/* update child actors */
	if (pRootComponent->CheckChildActorComponent())
	{
		for (auto childactor : pRootComponent->GetChildActors())
		{
			childactor->Update();
		}
	}
}

World* Actor::GetWorld()
{
	return pWorld;
}

void Actor::SetWorld(World* world)
{
	pWorld = world;
}

void Actor::RegisterRootComponent()
{
	pRootComponent = new TransformComponent();
	World* world = pRootComponent->GetWorld();
	if (pWorld)
	{
		world = pWorld;
	}
	else
	{
		_ASSERT("register rootcomponent failed, because Actor's world which is existed is empty");
	}
	pRootComponent->RegisterComponent();

}



Box Actor::GetAllComponentsBoundingBox()
{
	Box box ;
	for (auto child : pRootComponent->GetChildrenComponents())
	{
		/*  sum GetChildrenComponent box and return */
		
	}
	return box;
}

Box Actor::GetActorBoundingBox()
{
	const Box box = GetAllComponentsBoundingBox();
	return box;
}

void Actor::DeleteActor(Actor* actor)
{
	World* world = GetWorld();
	if (world)
	{
		world->DestroyActor(actor);
	}
}


void Actor::PreDetroy(Actor* actor)
{
	pRootComponent->PreDestroyForActors(actor);
}