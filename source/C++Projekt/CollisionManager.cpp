#include  "CollisionManager.h"
#include "objects.h"
#include <iostream>
#include "RunGame.h"

CollisionManager::~CollisionManager()
{
	this->game = nullptr;
	std::cout << "Del mgr" << std::endl;
}

void CollisionManager::manage(object* obj_1, object* obj_2) const
{
	const sf::Vector2f obj_1Position = obj_1->getPosition();
	const sf::Vector2f obj_1HalfSize = obj_1->get_halfsize();
	const sf::Vector2f obj_2Position = obj_2->getPosition();
	const sf::Vector2f obj_2HalfSize = obj_2->get_halfsize();

	const float delta_x = obj_2Position.x - obj_1Position.x;
	const float delta_y = obj_2Position.y - obj_1Position.y;

	const float intersect_x = abs(delta_x) - (obj_1HalfSize.x + obj_2HalfSize.x);
	const float intersect_y = abs(delta_y) - (obj_1HalfSize.y + obj_2HalfSize.y);

	const bool collides = intersect_x < 0.0f && intersect_y < 0.0f;

	if (collides)
	{
		if (obj_1->get_type() == object_type::player && obj_2->get_type() == object_type::powerup)
		{
			static_cast<powerup*>(obj_2)->execute();
		} 
		else
		{
			move_object(obj_1, delta_x, delta_y, intersect_x, intersect_y, obj_2->get_type());
		}
	}
}

void CollisionManager::move_object(object* obj, const float delta_x, const float delta_y, const float intersect_x, const float intersect_y, const object_type other_objType) const
{
	if (abs(intersect_x) < abs(intersect_y))
	{
		if (delta_x > 0.0f)
		{
			obj->move_x(intersect_x);
		}
		else
		{
			obj->move_x(-intersect_x);
		}
	}
	else
	{
		if (delta_y > 0.0f)
		{
			obj->move_y(intersect_y);
		}
		else
		{
			obj->move_y(-intersect_y);
		}
	}

	if (obj->get_type() == object_type::player && other_objType == object_type::platform_deadly)
		this->game->game_over();
}
