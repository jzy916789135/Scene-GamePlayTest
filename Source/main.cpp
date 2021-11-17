#include <iostream>
#include "BasicNode.h"
#include "Tree.h"
#include "Actor.h"
using namespace std;

int main()
{
	
	Tree* tree = new Tree();
	std::string name = "Actor";
	World* MyWorld = new World();
	Actor* Actor1 = new Actor(name + "1");
	Actor* Actor2 = new Actor(name + "2");
	Actor* Actor3 = new Actor(name + "3");
	
	TransformComponent* Com1 = new TransformComponent();
	TransformComponent* Com2 = new TransformComponent();

	MyWorld->AddActorToWorld(Actor1);
	MyWorld->AddActorToWorld(Actor2);
	MyWorld->AddActorToWorld(Actor3);
	tree->pWorld = MyWorld;

	auto RootNode = tree->GetRootNode();
	

	RootNode->AppendChildNode(Actor1->SceneNode());
	RootNode->AppendChildNode(Actor2->SceneNode());
	RootNode->AppendChildNode(Actor3->SceneNode());
	
	Actor1->AttachToActor(Actor2);
	Actor2->AddComponent(Com1);
	Actor2->AddComponent(Com2);
	MyWorld->DestroyActor(Actor2);
	
	for (auto actor : MyWorld->GetActors())
	{
		std::cout << "######" << endl;
		
		std::cout << "actor " + actor->GetName() << endl;

		cout << "actor node    " + actor->SceneNode()->GetName() << endl;
		
		for (auto childactor : actor->GetChildrenActors())
		{
			std::cout << "--------childactor " + childactor->GetName() << endl;
			cout << "-----------------childactor node  " + childactor->SceneNode()->GetName() << endl;
		}
		for (auto childCom : actor->GetChildrenComponents())
		{
			std::cout << "childCom " + childCom->GetName() << endl;
		}
		
		cout << "actor node    " + actor->SceneNode()->GetName() << endl;
		if (actor->SceneNode()->ChildCount())
		{
			for(auto childnode : actor->SceneNode()->Children())
			{
				cout << "child actor node    -" + childnode.first << endl;
			}

		}
		std::cout << "###################" << endl;
	}

	for (auto childnode : RootNode->Children())
	{
		std::cout << "child actor node    -" + childnode.first << endl;
	}
	
	std::cout << "-------------" << endl;


	return 0;


}

