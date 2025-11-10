#include "block.h"

#include "numericalVectors.h"
#include "level.h"

Block::Block(sf::Vector2f position, int size, Direction movementDirection, bool key)
{
	isKey = key;
	direction = movementDirection;

	// Create the block
	const int blockSize = 16;
	sf::Vector2f blockShape = (direction == SIDE_TO_SIDE) ? sf::Vector2f((float)size, 1) : sf::Vector2f(1, (float)size);
	shape = sf::RectangleShape(blockShape * (float)blockSize);

	// Set its initial position on the board
	position *= (float)blockSize;
	shape.setPosition(position);

	// Make it look nice
	// TODO: Use textures
	shape.setFillColor(Utils::GetRandomColor());
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(sf::Color::Black);

	// If its the key then give it the special apperance
	if (isKey) shape.setFillColor(sf::Color::Red);
}

void Block::Update()
{
	Move();
}

void Block::Move()
{
	//? cpp is such a crazy language bruh
	// TODO: Move these to the method because this is so crook to have stuff in a method like this
	static Block* blockBeingDragged = nullptr;
	static sf::Vector2f dragOffset;

	// Check for if we're clicking
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false)
	{
		// We are no-longer dragging a block
		blockBeingDragged = nullptr;
		return;
	}

	// Check for if we're clicking on ourself (begin draw)
	sf::Vector2f mousePosition = Utils::GetMousePosition();
	if (blockBeingDragged == nullptr && shape.getGlobalBounds().contains(mousePosition))
	{
		// We are now dragging a block
		blockBeingDragged = this;

		// Get the local position of the mouse relative
		// to the block so we don't drag from (0, 0)
		dragOffset = shape.getPosition() - mousePosition;
	}

	// Check for if we need to drag ourself
	if (blockBeingDragged == this)
	{
		sf::Vector2f newPosition = shape.getPosition();

		// Only let us drag on a single axis
		if (direction == SIDE_TO_SIDE) newPosition.x = mousePosition.x + dragOffset.x;
		else newPosition.y = mousePosition.y + dragOffset.y;

		// Check for collision
		// TODO: Put this in a method
		bool collision = false;
		for (Block* other : Level::Blocks)
		{
			// We cannot collide with ourself
			if (other == this) continue;

			// Get where we will be after moving
			sf::FloatRect newBounds = shape.getGlobalBounds();
        	newBounds.position = newPosition;

			// Check for if we collide with a shape
			if (newBounds.findIntersection(other->shape.getGlobalBounds()))
			{
				// TODO: Solve for collision instead of just stopping
				collision = true;
				break;
			}
		}
		
		// Set our new position if we didn't collide
		if (collision == false) shape.setPosition(newPosition);
	}
}

void Block::Draw()
{
	Utils::GetWindow()->draw(shape);
}
