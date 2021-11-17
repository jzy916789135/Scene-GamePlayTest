#include "TransformComponent.h"



TransformComponent::TransformComponent()
	: mRelativeTransform()
	, mWorldTransform()
	, pParentComponent()
	, mChildrenComponents()
	, mComponentName("DefaultComponent")
	, bAllowAnyoneToRemoveMe(true)
	, pOwnerActor()
	, pWorld()
{

}


TransformComponent::TransformComponent(Actor* actor)
	: mRelativeTransform()
	, mWorldTransform()
	, pParentComponent()
	, mChildrenComponents()
	, mComponentName("RootComponent")
	, bAllowAnyoneToRemoveMe(true)
	, pOwnerActor(actor)
	, pWorld(actor->GetWorld())
{

}

TransformComponent::~TransformComponent()
{
	Release();
}
void TransformComponent::Release()
{
}

FTransform TransformComponent::RelativeTransform()
{ 
	return mRelativeTransform;
}

FTransform TransformComponent::WorldTransform() 
{ 
	return mWorldTransform; 
}

TransformComponent* TransformComponent::GetParentComponent()
{ 
	return pParentComponent;
}

std::vector<TransformComponent*> TransformComponent::GetChildrenComponents()
{ 
	return mChildrenComponents;
}

FTransform TransformComponent::SetRelativeTransform(FTransform relativeTransform)
{
	return FTransform();
}

FTransform TransformComponent::SetWorldTransform(FTransform relativeTransform)
{
	return FTransform();
}

void TransformComponent::AttachToActor(Actor* actor)
{
	if (actor != nullptr)
	{
		if (GetOwner())
		{
			cout << "component has in a actor's list" << endl;
			return;
		}
		pOwnerActor = actor;
		if (actor->GetRootComponent())
		{
			this->AttachToComponent(actor->GetRootComponent());
		}
	}
}

void TransformComponent::AttachToComponent(TransformComponent* parent)
{
	if (parent != nullptr)
	{
		if (parent == this)
		{
			_ASSERT("component can not attach to itself");
			return;
		}
		if (parent->IsChild(this))
		{
			_ASSERT("component con not attach to a component repeat");
			return;
		}
		if (GetOwner())
		{
			if (GetOwner()->GetRootComponent() == this)
			{
				_ASSERT("root component can not attach to other component in same actor");
				return;
			}

		}
		Update(parent);

		if (!parent->CheckName(this->GetName()))
		{
			this->SetName("Component" + to_string(parent->GetChildrenComponents().size() - 1));
		}
	}

}

void TransformComponent::RemoveChildActor(Actor* actor)
{
	pChildActorComponent->RemoveActor(actor);
}

void TransformComponent::RemoveChildComponent(TransformComponent* child)
{

	std::vector<TransformComponent*>::iterator iter = find(mChildrenComponents.begin(), mChildrenComponents.end(), child);
	if (iter == mChildrenComponents.end())
	{
		cout << "this component is not child of this Component" << endl;
	}
	else
	{
		if (child->bAllowAnyoneToRemoveMe)
		{
			child->pWorld = 0;
			child->pParentComponent = 0;
			child->pOwnerActor = 0;
			child->mRelativeTransform = FTransform();
			child->mWorldTransform = FTransform();
			mChildrenComponents.erase(iter);
		}
		else
		{
			cout << "This component can not be remove , please set bAllowAnyoneToDestroyMe to true" << endl;
		}
	}
}

void TransformComponent::UpdateRootComponent()
{
	this->pWorld = pOwnerActor->GetWorld();
}

void TransformComponent::UpdateTransform(TransformComponent* parent)
{
	auto parentReTrans = parent->RelativeTransform();
	auto parentWrTrans = parent->WorldTransform();
	/*-----此处增加处理Transform的操作--------*/
	//SetRelativeTransform(parentReTrans);
	//SetWorldTransform(parentWrTrans);
}

void TransformComponent::Update(TransformComponent* parent)
{
	this->pParentComponent = parent;
	this->pWorld = parent->pWorld;
	this->pOwnerActor = (parent->pOwnerActor) ? parent->pOwnerActor : NULL;
	parent->mChildrenComponents.push_back(this);
	UpdateTransform(parent);
}

void TransformComponent::OnComponentCreated()
{
	bHasBeenCreated = true;
}

void TransformComponent::OnComponentDestroyed()
{
	bHasBeenCreated = false;
}

void TransformComponent::RegisterComponentWithWorld(World* world)
{
	if (world == nullptr)
	{
		_ASSERT("world is nor exist");
	}
	if (IsRegistered())
	{
		return;
	}
	else
	{
		OnRegister();
	}

	if (!bHasBeenCreated)
	{
		OnComponentCreated();
	}
}


void TransformComponent::RegisterComponent()
{
	World* ownerWorld = GetWorld();
	if (ownerWorld)
	{
		RegisterComponentWithWorld(ownerWorld);
	}
}

void TransformComponent::OnRegister()
{

	bRegistered = true;
	/* other sets' initialization like state of this component */
}

World* TransformComponent::GetWorld()
{
	return pWorld;
}

Actor* TransformComponent::GetOwner()
{
	return pOwnerActor;
}

std::string TransformComponent::GetName()
{
	return mComponentName;
}

void TransformComponent::SetName(std::string name)
{
	mComponentName = name;
}

bool TransformComponent::IsChild(TransformComponent* childComponent)
{
	for (auto child : GetChildrenComponents())
	{
		if (child == childComponent)
		{
			return true;
		}
	}
	return false;
}

std::vector<Actor*> TransformComponent::GetChildActors()
{
	return pChildActorComponent->GetActors();
}

void TransformComponent::AddActor(Actor* actor)
{

	pChildActorComponent->AddNewActor(actor);
}

void TransformComponent::CheckandCreateChildActorComponent()
{
	if (!CheckChildActorComponent())
	{
		pChildActorComponent = new ChildActorComponent();
	}
}

bool TransformComponent::CheckChildActorComponent()
{
	if (pChildActorComponent)
		return true;
	else
		return false;
}

bool TransformComponent::CheckName(std::string name)
{
	auto childcomponents = GetChildrenComponents();
	for (auto child : childcomponents)
	{
		if (name == child->GetName())
			return false;
	}

	return true;
}

void TransformComponent::PreDestroy()
{
	this->pWorld = NULL;
	this->pOwnerActor = NULL;
	auto iter = find(pParentComponent->mChildrenComponents.begin(), pParentComponent->mChildrenComponents.end(), this);
	if (iter != pParentComponent->mChildrenComponents.end())
	{
		pParentComponent->mChildrenComponents.erase(iter);
	}
	this->pParentComponent = NULL;
}

void TransformComponent::PreDestroyForActors(Actor* actor)
{
	pChildActorComponent->PreDestroy(actor);
}

