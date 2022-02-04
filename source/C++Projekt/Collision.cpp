#include "Collision.h"

Collision::~Collision()
= default;

/**
 * \brief 
 * \param delta_x 
 * \param delta_y 
 * \param intersect_x 
 * \param intersect_y 
 */
void Collision::move_object(const float delta_x, const float delta_y, const float intersect_x, const float intersect_y) const
{
	if (abs(intersect_x) < abs(intersect_y))
	{
		if (delta_x > 0.0f)
		{
			this->obj->move(intersect_x, 0.0f);
		}
		else
		{
			this->obj->move(-intersect_x, 0.0f);
		}
	}
	else
	{
		if (delta_y > 0.0f)
		{
			this->obj->move(0.0f, intersect_y);
		}
		else
		{
			this->obj->move(0.0f, -intersect_y);
		}
	}
}

void Collision::check_collision(const Collision* other_obj) const
{
	const sf::Vector2f other_objPosition = other_obj->get_position();
	const sf::Vector2f other_objHalfSize = other_obj->get_half_size();
	const sf::Vector2f this_objPosition = get_position();
	const sf::Vector2f this_objHalfSize = get_half_size();

	const float delta_x = other_objPosition.x - this_objPosition.x;
	const float delta_y = other_objPosition.y - this_objPosition.y;

	const float intersect_x = abs(delta_x) - (this_objHalfSize.x + other_objHalfSize.x);
	const float intersect_y = abs(delta_y) - (this_objHalfSize.y + other_objHalfSize.y);
	
	const bool collides = intersect_x < 0.0f && intersect_y < 0.0f;

	if (collides)
	{
		move_object(delta_x, delta_y, intersect_x, intersect_y);
	}
}



