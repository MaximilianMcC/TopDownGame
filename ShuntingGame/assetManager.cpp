#include "assetManager.h"

std::map<std::string, sf::SoundBuffer> AssetManager::sounds;
std::map<std::string, sf::Texture> AssetManager::textures;
std::map<std::string, sf::Cursor> AssetManager::cursors;
std::map<std::string, sf::Image> AssetManager::images;
std::map<std::string, sf::Font> AssetManager::fonts;

// TODO: Like all this is copy pasted (don't)
sf::Texture* AssetManager::LoadTexture(std::string key, std::string path)
{
	// Check for if a key with the same name already exists
	if (textures.find(key) != textures.end())
	{
		// Just return the already loaded one
		return &textures[key];
	}

	// Load it
	sf::Texture texture;
	if (texture.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading texture at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The texture was loaded. Chuck it into
	// the dictionary so it may be used
	textures[key] = texture;

	// Give back the loaded texture
	return &textures[key];
}

sf::Texture* AssetManager::LoadTexture(std::string key, sf::Image& image)
{
	// Check for if a key with the same name already exists
	if (textures.find(key) != textures.end())
	{
		// Just return the already loaded one
		return &textures[key];
	}

	// Create the texture from the image
	sf::Texture texture;
	texture.loadFromImage(image);

	// The texture was created. Chuck it into
	// the dictionary so it may be used
	textures[key] = texture;

	// Give back the loaded texture
	return &textures[key];
}

sf::Texture* AssetManager::GetTexture(std::string key)
{
	// Check for if they key exists or not
	if (textures.find(key) == textures.end())
	{
		std::cerr << "No texture with the key '" << key << "' exists\n";
		return nullptr;
	}

	return &textures[key];
}

sf::Image* AssetManager::LoadImage(std::string key, std::string path)
{
	// Check for if a key with the same name already exists
	if (images.find(key) != images.end())
	{
		// Just return the already loaded one
		return &images[key];
	}

	// Load it
	sf::Image image;
	if (image.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading image at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The image was loaded. Chuck it into
	// the dictionary so it may be used
	images[key] = image;

	// Give back the loaded texture
	return &images[key];
}

sf::Image* AssetManager::GetImage(std::string key)
{
	// Check for if they key exists or not
	if (images.find(key) == images.end())
	{
		std::cerr << "No image with the key '" << key << "' exists\n";
		return nullptr;
	}

	return &images[key];
}


sf::Font* AssetManager::LoadDefaultFont(std::string key, std::string name)
{
	// Check for if they key exists or not
	if (fonts.find(key) != fonts.end())
	{
		// Just return the already loaded one
		return &fonts[key];
	}

	// Get the default windows font path
	// TODO: Don't make this so c-like
	char fontPath[MAX_PATH];
	SHGetFolderPathA(NULL, CSIDL_FONTS, NULL, 0, fontPath);

	// Get the requested font
	std::string path = std::string(fontPath) + "\\" + name + ".ttf";

	// Load it
	sf::Font font;
	if (font.openFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading font at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The font was loaded. Chuck it into
	// the dictionary so it may be used
	fonts[key] = font;

	// Give back the loaded font
	return &fonts[key];
}

sf::Font* AssetManager::GetFont(std::string key)
{
	// Check for if the key exists or not
	if (fonts.find(key) == fonts.end())
	{
		std::cerr << "No font with the key '" << key << "' exists\n";
		return nullptr;
	}

	return &fonts[key];
}


sf::SoundBuffer* AssetManager::LoadSound(std::string key, std::string path)
{
	// Check for if the key exists or not
	if (sounds.find(key) != sounds.end())
	{
		// Just return the already loaded one
		return &sounds[key];
	}

	// Load the buffer
	sf::SoundBuffer buffer;
	if (buffer.loadFromFile(path) == false)
	{
		// If there was an issue then say
		// TODO: exit 1
		std::cerr << "Error loading sound at path '" << path << "' (looked in " << std::filesystem::current_path() << ")";
	}

	// The sound was loaded. Chuck it into
	// the dictionary so it may be used
	sounds[key] = buffer;

	// Give back the loaded sound
	return &sounds[key];
}

sf::Texture* AssetManager::LoadTextureFromRenderTexture(std::string key, sf::RenderTexture &renderTexture)
{
	// Check for if the key exists or not
	if (textures.find(key) != textures.end())
	{
		// Just return the already loaded one
		return &textures[key];
	}

	// Convert the texture to an image to a texture
	// When this happens we make a new 'copy' of the
	// texture that is unrelated to the render texture
	// which means we can delete the render texture
	// once we've generated the final texture thing
	sf::Texture renderTextureTexture = renderTexture.getTexture();
	sf::Image image = renderTextureTexture.copyToImage();
	return LoadTexture(key, image);
}