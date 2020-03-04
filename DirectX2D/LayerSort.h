#pragma once
#include"GameObject.h"

class GameObject;
class LayerSort
{
public:
	LayerSort();
	bool operator()(const GameObject* obj1, const GameObject* obj2)
	{
		if (obj1->GetLayer() < obj2->GetLayer())
			return true;
		return false;
	}
};