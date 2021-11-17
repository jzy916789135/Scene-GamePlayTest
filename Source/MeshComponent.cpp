#include "MeshComponent.h"

MeshComponent::MeshComponent()
{
}

MeshComponent::~MeshComponent()
{
}

Box MeshComponent::GetComponentBoundingBox()
{
	if (GetChildrenComponents().empty())
	{
		/* Set component bound with its geometry data */
		SetComponentBound(pGeometry);
		return pBound->GetBox();
	}
	else
	{
		Box box;
		for (auto child : GetChildrenComponents())
		{
			/*  sum children box and return */
		}
		return box;
	}
}

void MeshComponent::SetComponentBound(Geometry* geometry)
{

}