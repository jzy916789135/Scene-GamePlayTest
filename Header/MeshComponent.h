#pragma once
#include "TransformComponent.h"
#include "DataStruct.h"
class TransformComponent;

class MeshComponent : public TransformComponent
{
public:

	MeshComponent();
	~MeshComponent();

private:

	Bound* pBound;

	Geometry* pGeometry;

public:

	Box GetComponentBoundingBox();

	void SetComponentBound(Geometry* geometry);
};

