#include <iostream>

#include "Core/Halite.h"

Halite * my_game; //Is a pointer to avoid problems with assignment, dynamic memory, and default constructors.

int main(int argc, char* args[])
{
	srand(time(NULL));

	std::string in, filename = "../Replays/Output_" + std::to_string(time(NULL)) + ".hlt";
	unsigned short mapWidth, mapHeight;

	std::cout << "Please enter the width of the map: ";
	std::getline(std::cin, in);
	while(true)
	{
		try
		{
			mapWidth = std::stoi(in);
			break;
		}
		catch(std::exception e)
		{
			std::cout << "That isn't a valid input. Please enter an integer width of the map: ";
			std::getline(std::cin, in);
		}
	}
	std::cout << "Please enter the height of the map: ";
	std::getline(std::cin, in);
	while(true)
	{
		try
		{
			mapHeight = std::stoi(in);
			break;
		}
		catch(std::exception e)
		{
			std::cout << "That isn't a valid input. Please enter an integer height of the map: ";
			std::getline(std::cin, in);
		}
	}

	
	my_game = new Halite(mapWidth, mapHeight);
	my_game->init();
	
	std::vector< std::pair<std::string, float> >rankings = my_game->runGame();

	try
	{
		my_game->output(filename);
	}
	catch(std::runtime_error e)
	{
		std::cout << e.what() << std::endl << "Failed to output to file. Opening a file at " << filename.substr(11) << std::endl;
		my_game->output(filename.substr(11));
	}

	std::string victoryOut;
	for(unsigned int a = 0; a < rankings.size(); a++) victoryOut += "In ranking " + std::to_string(a + 1) + " is player " + rankings[a].first + " with a relative score of " + std::to_string(rankings[a].second).substr(0, 5) + "\n";
	std::cout << victoryOut;

	system("PAUSE");
	return 0;
}