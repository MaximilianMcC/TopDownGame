#include "railVehicle.h"

#include "track.h"
#include "utils.h"

// TODO: Stop you from going off the edge of tracks
void RailVehicle::FollowTrack(float newPositionOnTrack)
{
	// Check for if we're moving forwards onto the next bit of track
	if ((newPositionOnTrack >= CurrentTrack->Length) && (CurrentTrack->NextTrack != nullptr))
	{
		// Move to the start of the next track
		CurrentTrack = CurrentTrack->NextTrack;
		newPositionOnTrack = 0.0f;

		// TODO: Play fishplate sound effect
	}

	// Check for if we're moving backwards onto the previous bit of track
	if ((newPositionOnTrack < 0.0f) && (CurrentTrack->PreviousTrack != nullptr))
	{;
		// Move to the end of the previous track
		CurrentTrack = CurrentTrack->PreviousTrack;
		newPositionOnTrack = CurrentTrack->Length;

		// TODO: Play fishplate sound effect
	}

	// Update our position
	PositionOnTrack = newPositionOnTrack;
}

void RailVehicle::Draw()
{
	shape->setPosition(CurrentTrack->Position + sf::Vector2f(PositionOnTrack, 0.0f));
	Utils::GetWindow()->draw(*shape);
}

std::vector<RailVehicle*> RailVehicle::GetEntireTrain(bool includeOurself)
{
	std::vector<RailVehicle*> train;

	// Add the left vehicles to the leftside of the train
	RailVehicle* left = this->LeftCouple;
	while (left != nullptr)
	{
		train.insert(train.begin(), left);
		left = left->LeftCouple;
	}

	// If we wanna, then also include outself
	if (includeOurself) train.push_back(this);

	// Add the left vehicles to the rightside of the train
	RailVehicle* right = this->RightCouple;
	while (right != nullptr)
	{
		train.push_back(right);
		right = right->RightCouple;
	}

	return train;
}
