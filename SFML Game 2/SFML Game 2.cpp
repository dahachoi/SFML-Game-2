#include "Game.h"

int main(){
	srand(static_cast<unsigned>(time(0)));

	//Initialize game object
	Game game;

	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	//End of application
	return 0;
}