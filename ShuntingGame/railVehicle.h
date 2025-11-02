#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
class Track;

class RailVehicle
{
protected:
	sf::RectangleShape* shape;

	void FollowTrack(float newPositionOnTrack);
	
public:

	Track* CurrentTrack = nullptr;
	float PositionOnTrack = 0.0f;

	RailVehicle* LeftCouple = nullptr;
	RailVehicle* RightCouple = nullptr;

	virtual void Update() { }
	virtual void Draw();

	std::vector<RailVehicle*> GetEntireTrain(bool includeOurself = true);
};