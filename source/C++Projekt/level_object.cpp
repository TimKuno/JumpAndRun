#include "objects.h"
#include <iostream>

level_object::level_object(const sf::Vector2f size, const sf::Vector2f position, const std::shared_ptr<FileManager>& file_manager, const object_type type) 
{
	this->set_type(type);
	this->texture = file_manager->get_texture(this->get_type());

	this->setSize(size);
	this->setPosition(position);
	this->setTexture(&texture);
	this->setOrigin(size / 2.0f);
}

level_object::~level_object()
{
	std::cout << "Object deleted." << std::endl;
}
