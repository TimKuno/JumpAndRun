#pragma once
#include "object_type.h"
#include "objects.h"
#include "RunGame.h"

class RunGame;

class CollisionManager
{
public:
	explicit CollisionManager(RunGame* game) { this->game = game; }
	~CollisionManager();
	void manage(object* obj_1, object* obj_2) const;
	void move_object(object* obj, float delta_x, float delta_y, float intersect_x, float intersect_y,
	                 object_type other_objType) const;

private:
	RunGame* game;
};
