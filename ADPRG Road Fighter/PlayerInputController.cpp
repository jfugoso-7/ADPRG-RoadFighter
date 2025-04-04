
#include "PlayerInputController.h"
#include "CarPlayer.h"

PlayerInputController::PlayerInputController(string name) : GenericInputController(name)
{

}

PlayerInputController::~PlayerInputController()
{
	GenericInputController::~GenericInputController();
}

void PlayerInputController::perform()
{
	CarPlayer* player = (CarPlayer*)this->getOwner();

	/* do not accept any input if the player:
		- skids
		- crashed
		- finished the course
	*/
	if(player->isSkidding()|| player->crashed || player->winCourse ||player->noFuel)
	{
		// disable all movements
		this->moveUp = false;
		this->moveLeft = false;
		this->moveRight = false;
	}

	//read player input
    if (event.is<sf::Event::KeyPressed>()) //changed
    {
        if (const auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
        {
            switch (keyEvent->code)
            {
            case sf::Keyboard::Key::Space:
                this->moveUp = true;
                break;
            case sf::Keyboard::Key::A:
                this->moveLeft = true;
                break;
            case sf::Keyboard::Key::D:
                this->moveRight = true;
                break;
            }
        }
    }
    else if (event.is<sf::Event::KeyReleased>())
    {
        if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>())
        {
            switch (keyEvent->code)
            {
            case sf::Keyboard::Key::Space:
                this->moveUp = false;
                break;
            case sf::Keyboard::Key::A:
                this->moveLeft = false;
                break;
            case sf::Keyboard::Key::D:
                this->moveRight = false;
                break;
            }
        }
    }
	
}

bool PlayerInputController::isUp()
{
	return this->moveUp;
}
bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}