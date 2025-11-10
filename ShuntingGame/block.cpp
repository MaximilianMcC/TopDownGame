#include "block.h"

#include "numericalVectors.h"

Block::Block(sf::Vector2f position, int size, Direction movementDirection, bool key)
{
	isKey = key;
	direction = movementDirection;

	// Create the block
	const int blockSize = 16;
	sf::Vector2f blockShape = (movementDirection == SIDE_TO_SIDE) ? sf::Vector2f(1, size) : sf::Vector2f(size, 1);
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
}

void Block::Draw()
{
	Utils::GetWindow()->draw(shape);
}
