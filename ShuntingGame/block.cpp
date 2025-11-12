#include "block.h"

#include "numericalVectors.h"
#include "inputHandler.h"
#include "level.h"
#include "assetManager.h"

// Load all the textures and whatnot
void Block::Load()
{
	AssetManager::LoadTexture("block_2_up", "./assets/blocks/2_up.png");
	AssetManager::LoadTexture("block_3_up", "./assets/blocks/3_up.png");

	AssetManager::LoadTexture("block_2_side", "./assets/blocks/2_side.png");
	AssetManager::LoadTexture("block_3_side", "./assets/blocks/3_side.png");

	AssetManager::LoadTexture("key_2_side", "./assets/blocks/2_side_key.png");
	// AssetManager::LoadTexture("key_2_up", "./assets/blocks/2_up_key.png");
}

Block::Block(sf::Vector2f position, int size, Direction movementDirection, bool key)
{
	isKey = key;
	direction = movementDirection;

	// Create the block
	sf::Vector2f blockShape = (direction == SIDE_TO_SIDE) ? sf::Vector2f((float)size, 1) : sf::Vector2f(1, (float)size);
	shape = sf::RectangleShape(blockShape * (float)Level::BlockSize);

	// Set its initial position on the board
	position *= (float)Level::BlockSize;
	shape.setPosition(position);

	// Make it look nice
	std::string textureKey = isKey ? "key" : "block";
	textureKey += "_" + std::to_string(size) + "_";
	textureKey += (direction == SIDE_TO_SIDE) ? "side" : "up";
	shape.setTexture(AssetManager::GetTexture(textureKey));
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

	// Check for if we're clicking on ourself (begin drag)
	sf::Vector2f mousePosition = InputHandler::GetMousePosition();
	if (blockBeingDragged == nullptr && shape.getGlobalBounds().contains(mousePosition))
	{
		// We are now dragging a block
		blockBeingDragged = this;

		// Get the local position of the mouse relative
		// to the block so we don't drag from (0, 0)
		dragOffset = shape.getPosition() - mousePosition;
	}

	// If we're being dragged then do collision detection
	if (blockBeingDragged == this)
	{
		// Collision detection setup stuff idk
		sf::FloatRect bounds = shape.getGlobalBounds();
		sf::FloatRect targetBounds = bounds;
		sf::Vector2f currentPosition = bounds.position;
		sf::Vector2f targetPosition = currentPosition;

		// Shorthands because we're gonna be using these heaps
		float width = bounds.size.x;
		float height = bounds.size.y;

		// Say where we want to go (based on how much the mouse moves)
		if (direction == SIDE_TO_SIDE) targetPosition.x = mousePosition.x + dragOffset.x;
		else targetPosition.y = mousePosition.y + dragOffset.y;

		// Do border collision
		// TODO: Put this in a method
		{
			// Get the boarder
			const sf::FloatRect& border = Level::Border.getGlobalBounds();

			if (direction == SIDE_TO_SIDE)
			{
				// Get how much we're allowed to move
				float minX = border.position.x;
				float maxX = border.position.x + border.size.x - width;

				// Just kinda don't do right collision for the key
				if ((isKey && targetPosition.x >= maxX) == false)
				{
					// make sure we can't go outside the bounds
					targetPosition.x = std::clamp(targetPosition.x, minX, maxX);
					targetBounds.position.x = targetPosition.x;
				}
			}
			else
			{
				// Get how much we're allowed to move
				float minY = border.position.y;
				float maxY = border.position.y + border.size.y - height;

				// make sure we can't go outside the bounds
				targetPosition.y = std::clamp(targetPosition.y, minY, maxY);
				targetBounds.position.y = targetPosition.y;
			}
		}

		// Do block collision
		// TODO: Put this in a method
		{
			// Check for X collision
			if (direction == SIDE_TO_SIDE)
			{
				bool movingRight = targetPosition.x > currentPosition.x;
				float allowedX = targetPosition.x;
				
				float currentLeft = currentPosition.x;
				float currentRight = currentPosition.x + width;

				// Loop over all blocks
				for (Block* other : Level::Blocks)
				{
					// We cannot collide with ourself
					if (other == this) continue;

					// Check for if we collide
					sf::FloatRect otherBounds = other->shape.getGlobalBounds();
					if (OverlapsOnY(targetBounds, otherBounds) == false) continue;

					// Figure out where we're allowed to go
					float otherLeft = otherBounds.position.x;
					float otherRight = otherBounds.position.x + otherBounds.size.x;

					// If we're 'overflowing' then adjust
					if (movingRight)
					{
						// Left stuff
						float limitX = otherLeft - width;
						if (limitX < allowedX && currentRight <= otherLeft) allowedX = limitX;
					}
					else
					{
						// Right stuff
						float limitX = otherRight;
						if (limitX > allowedX && currentLeft >= otherRight) allowedX = limitX;
					}
				}

				// Set the new adjusted X position
				targetPosition.x = allowedX;
			}
			else
			{
				// Y collision
				bool movingDown = targetPosition.y > currentPosition.y;
				float allowedY = targetPosition.y;

				float currentTop = currentPosition.y;
				float currentBottom = currentPosition.y + height;
				
				// Loop over all blocks
				for (Block* other : Level::Blocks) {

					// We cannot collide with ourself
					if (other == this) continue;
					
					// Check for if we collide
					sf::FloatRect otherBounds = other->shape.getGlobalBounds();
					if (OverlapsOnX(targetBounds, otherBounds) == false) continue;
					
					// Figure out where we're allowed to go
					float otherTop = otherBounds.position.y;
					float otherBottom = otherBounds.position.y + otherBounds.size.y;
					
					// If we're 'overflowing' then adjust
					if (movingDown)
					{
						// Top stuff
						float limitY = otherTop - height;
						if (limitY < allowedY && currentBottom <= otherTop) allowedY = limitY;
					}
					else
					{
						// Bottom stuff
						float limitY = otherBottom;
						if (limitY > allowedY && currentTop >= otherBottom) allowedY = limitY;
					}
				}

				// Set the new adjusted Y position
				targetPosition.y = allowedY;
			}

			// Actually move now that we've changed
			// both the X/Y things
			shape.setPosition(targetPosition);
		}
	}
}

void Block::Draw()
{
	Utils::GetWindow()->draw(shape);
}



bool Block::OverlapsOnY(const sf::FloatRect& a, const sf::FloatRect& b)
{
	// Handle A
	const float aTop = a.position.y;
	const float aBottom = a.position.y + a.size.y;

	// Handle B
	const float bTop = b.position.y;
	const float bBottom = b.position.y + b.size.y;

	// Do the actual check
	return (aTop < bBottom) && (aBottom > bTop);
}

bool Block::OverlapsOnX(const sf::FloatRect& a, const sf::FloatRect& b)
{
	// Handle A
	const float aLeft = a.position.x;
	const float aRight = a.position.x + a.size.x;

	// Handle B
	const float bLeft = b.position.x;
	const float bRight = b.position.x + b.size.x;

	// Do the actual check
	return (aLeft < bRight) && (aRight > bLeft);
}