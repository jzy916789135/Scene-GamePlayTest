#pragma once

struct Box
{
	Box();
	~Box();
};



struct Bound
{
	Bound();
	~Bound();
private:
	Box mBBox;

public:
	/* return component's bbox */
	Box GetBox();
};
