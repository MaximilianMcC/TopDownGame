#include "sprite.h"

#include <iostream>
#include "utils.h"

Sprite::Sprite(std::string filePath, int sliceSize, float layerSpacing, sf::Vector2f initialPosition)
{
	// Load the actual texture
	if (texture.loadFromFile(filePath) == false)
	{
		std::cerr << "issue loading sprite texture from " << filePath << "\n";
		return;
	}

	// Figure out how many layers we have
	int layerCount = texture.getSize().y / sliceSize;
	layerSize = sf::Vector2f((float)sliceSize, (float)sliceSize);

	// Loop over every layer and load it
	for (int i = 0; i < layerCount; i++)
	{
		// Store the layer in a sprite
		sf::Sprite currentLayer(texture);

		// 'crop' it to just include the layer we want
		currentLayer.setTextureRect(sf::IntRect(
			sf::Vector2i(0, i * (int)layerSize.y),
			static_cast<sf::Vector2i>(layerSize)
		));

		// Set its origin in the centre for rotating
		currentLayer.setOrigin(layerSize / 2.0f);

		// Add it to the list of layers
		layers.push_back(currentLayer);
	}

	// Set the position
	spacing = layerSpacing;
	SetPosition(initialPosition);
}

void Sprite::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;

	// Loop over all sprites
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].setPosition(position - sf::Vector2f(0, i * (layerSize.y + spacing)));
	}
}

void Sprite::SetRotation(sf::Angle newRotation)
{
	rotation = newRotation;

	// Loop over all sprites
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i].setRotation(rotation);
	}
}

void Sprite::Draw()
{
	// Loop over all sprites
	for (size_t i = 0; i < layers.size(); i++)
	{
		Utils::GetWindow()->draw(layers[i]);
	}
}
