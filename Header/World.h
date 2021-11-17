#pragma once
#include "Actor.h"
class TransformComponent;
class Actor;
using namespace std;
class BaseObject;

/* struct of optional parametres to SpwanActor */
struct ActorSpawnParametres 
{
	class World;

	ActorSpawnParametres();

	std::string mName;

	/* An Actor to use as a template when spawning the new Actor.*/
	Actor* pTemplate;

	/* world the actor will be spawned in  */
	World* pWorld;

	FTransform mTransform;

};

enum ActorStateFlags
{
	PointerIsUsed = 0,

	PointerCanBeUse = 1
};
class World
{
public:
	World();
	World(std::string name);
	~World();

public:

	/* Destroy selected actor from this world */
	void DestroyActor(Actor* actor);

	void DestroyComponent(TransformComponent* &thiscomponent);

	/* return all actors in this world */
	std::vector<Actor*> GetActors();

	/* Add created actor to this world*/
	void AddActorToWorld(Actor* actor);

	void SpawnActor();

	/* spawn default actor with parameters
	*  when the actor be spawned, it should in this world and must not attached to any actors
	*/
	Actor* SpwanActor(const ActorSpawnParametres& parameters);

	/* check if the actor's name repeat in this world 
	 * return false if repeat
	 */
	bool CheckName(std::string name);

	/* create default Actor, and add it to this world */
	Actor* CreateDefaultActor();

	/* get scenegraph's rootnode */
	BasicNode* GetRootNode();

public:

	/* Update World paremeters to actor, mainly update Paternity and Transform */
	void Update(Actor* actor);

	/* Update all actors in world */
	void Update();

private:
	/* World's name  */
	std::string mName;

	std::vector<Actor*> mActors;

	std::vector<ActorStateFlags> mActorsStateFlags;

	unordered_map<std::string, int> mActorMapNameToindex;

	/* the begining of scenegraph */
	BasicNode* pRootNode;

private:

};
