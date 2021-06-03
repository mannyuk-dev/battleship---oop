#include "headers/adaship.h" //include adaship headers

//https://www.rapidtables.com/code/text/unicode-characters.html

std::vector<std::string> _colors = {C_GREEN, C_MAGENTA, C_YELLOW, C_BLUE, C_PURPLE};
Board player_one;
Board player_two;
Board computer;
Boats boats;
int boatpieces = 0;

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
	//splits a string in two at a specified position
	std::vector<std::string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == std::string::npos)
			pos = str.length();
		std::string token = str.substr(prev, pos - prev);
		if (!token.empty())
			tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

void initgame(std::string config, int gameType)
{
	//Initialises the game using the config file
	std::string line;
	std::ifstream streamer;
	std::vector<std::string> parts;
	int heigth = 10;
	int width = 10;
	int boatcount = 0;

	streamer.open(config);
	if (streamer.is_open())
	{
		while (getline(streamer, line))
		{
			parts = split(line, "=");
			if (parts[0] != "board")
			{
				std::string color = _colors.size() > boatcount ? _colors[boatcount] : C_RESET;
				boats.addboat(parts[0], parts[1], color);
				boatpieces = boatpieces + std::stoi(parts[1]);
				boatcount++;
			}
			else if (parts[0] == "board")
			{
				std::vector<std::string> dimensions = split(parts[1], "X");
				heigth = std::stoi(dimensions[0]);
				width = std::stoi(dimensions[1]);
			}
		}
		streamer.close();
	}

	if (gameType == 1)
	{
		player_one.initboard(width, heigth, "BOARD: PLAYER ONE\n\n");
		computer.initboard(width, heigth, "BOARD: COMPUTER\n\n");
	}
	else if (gameType == 2)
	{
		player_one.initboard(width, heigth, "BOARD: PLAYER ONE\n\n");
		player_two.initboard(width, heigth, "BOARD: PLAYER TWO\n\n");
	}
}

void placeplayerboats(std::vector<boat> boats, Board player)
{
	//Places a player's boats/ships on the board
	std::string coordinate;
	boardconfig boardconfig = player.getboardconfig();
	std::string input = VALID;
	char dir;

	for (auto &boat : boats)
	{
		do
		{
			if (input == INVALID)
			{
				std::cout << "You entered a wrong coordinate. Please enter a cordinate within the range from the board eg. A1\n";
			}

			input = VALID;

			std::cout << "Please enter the co-ordinates to place your " << boat.name << " of length " << boat.len << " on the battlefield:" << std::endl;
			std::cout << "Enter the co-ordinates to place your ship eg. A1: ";
			std::cin >> coordinate;
			int res = player.setboardtile_state(coordinate, Available);
			if (res == -1)
			{
				input = INVALID;
			}
		} while (input == INVALID);

		do
		{
			if (input == INVALID)
			{
				std::cout << "**INVALID DIRECTION**\n Please select a valid direction\n\n";
			}
			input = VALID;
			std::cout << "Choose the Direction to place your ship by selecting one of the following:\nLEFT---> l\nRIGHT---> r\nUP---> u\nDOWN---> d\n";
			std::cin >> dir;

			bool is_set = !player.setboatonboard(dir, boat, coordinate);
			if (is_set)
			{
				input = VALID;
				player.render();
			}
			else
			{
				input = INVALID;
			}

		} while (input == INVALID);
	}

	system("read -p 'Press Enter to continue...' var");
}

std::string randomcoordinate(boardconfig config)
{
	// Gets a random coordinate
	std::string col = coordinates_indextocolref(common_randomselect(1, config.width, true) - 1);
	int row = common_randomselect(1, config.height, true);
	std::string coordinate = col + std::to_string(row);

	return coordinate;
}

void placecomputerboats(std::vector<boat> boats)
{
	//Auto placces computer boats randomly
	std::string coordinate;
	boardconfig boardconfig = computer.getboardconfig();
	std::string input = VALID;

	for (auto &boat : boats)
	{
		do
		{
			coordinate = randomcoordinate(boardconfig);
			int res = computer.setboardtile_state(coordinate, Available);

			if (res == -1)
			{
				input = INVALID;
			}
			else
			{
				input = VALID;
			}
		} while (input == INVALID);

		do
		{
			char directions[4] = {'l', 'r', 'u', 'd'};
			int rand = common_randomselect(0, 3, false);

			bool is_set = !computer.setboatonboard(directions[rand], boat, coordinate);
			if (is_set)
			{
				input = VALID;
			}
			else
			{
				input = INVALID;
			}

		} while (input == INVALID);
	}
}

void startgame_one()
{
	// Starts game one - player one vs computer
	int turn = PLAYER_ONE;
	int playerkills = 0;
	int computerkills = 0;
	boardconfig player_one_config = player_one.getboardconfig();
	std::string coordinate;
	std::string input;
	udtile tile;

	while (playerkills != boatpieces &&
		   computerkills != boatpieces)
	{
		switch (turn)
		{
		case PLAYER_ONE:
			computer.render(true);
			std::cout << "\n"
					  << C_CYAN << "PLAYER ONE:\n"
					  << C_RESET;
			std::cout << "Enter your Target coordinate eg. A1:\n";
			std::cin >> coordinate;
			tile = computer.getboardtile(coordinate);

			if (tile.state == states::Available ||
				tile.state == states::Missed)
			{
				computer.setboardtile_state(coordinate, Missed, true);
				computer.render(true);
				std::cout << "Lol, you missed :/\n\n";
				std::cout << "Press Enter to continue or 0 to quit...\n";
				std::cin >> input;

				if (input == "0")
				{
					playerkills = boatpieces + 3;
					break;
				}

				turn = COMPUTER;
			}
			else if (tile.state == states::Occupied)
			{
				computer.setboardtile_state(coordinate, Hit, true);
				computer.render(true);
				std::cout << "Hmmm, nice hit :)\n";

				if (input == "0")
				{
					playerkills = boatpieces + 3;
					break;
				}

				playerkills++;
				turn = PLAYER_ONE;
			}
			else
			{
				turn = COMPUTER;
			}
			break;
		case COMPUTER:
			coordinate = randomcoordinate(player_one_config);
			tile = player_one.getboardtile(coordinate);

			if (tile.state == states::Available ||
				tile.state == states::Missed)
			{
				player_one.setboardtile_state(coordinate, Missed, true);
				player_one.render();
				turn = PLAYER_ONE;
				std::cout << "Computer missed :/\n\n";
				std::cout << "Press Enter to continue or 0 to quit...\n";
				std::cin >> input;

				if (input == "0")
				{
					playerkills = boatpieces + 3;
					break;
				}
			}
			else if (tile.state == states::Occupied)

			{
				//std::cout << "Hmmm, Ai is taking over :)\n";
				computer.setboardtile_state(coordinate, Hit, true);
				computer.render(true);
				computerkills++;
				turn = COMPUTER;
				std::cout << "Computer hit :/\n\n";
				std::cout << "Press Enter to continue or 0 to quit...\n";
				std::cin >> input;
				if (input == "0")
				{
					playerkills = boatpieces + 3;
					break;
				}
			}
			else
			{
				turn = COMPUTER;
			}
			break;
		default:
			break;
		}
	}

	if (playerkills == boatpieces)
	{
		std::cout << "\nPlayer 1 wins";
	}
	else if (computerkills == boatpieces)
	{
		std::cout << "\nPC wins";
	}
	else if (computerkills >= boatpieces ||
			 playerkills >= boatpieces)
	{
		std::cout << "\nGame successfully ended";
	}
	else
	{
		std::cout << "\nerr";
	}
}

void startgame_two()
{
	//Starts game two - player vs player
	int turn = PLAYER_ONE;
	int player_one_kills = 0;
	int player_two_kills = 0;
	boardconfig player_one_config = player_one.getboardconfig();
	std::string coordinate;
	std::string input;
	udtile tile;

	while (player_one_kills != boatpieces &&
		   player_two_kills != boatpieces)
	{
		switch (turn)
		{
		case PLAYER_ONE:
			player_two.render(true);
			std::cout << "\n"
					  << C_CYAN << "PLAYER ONE:\n"
					  << C_RESET;
			std::cout << "Enter your Target coordinate eg. A1:\n";
			std::cin >> coordinate;
			tile = player_two.getboardtile(coordinate);

			if (tile.state == states::Available ||
				tile.state == states::Missed)
			{
				player_two.setboardtile_state(coordinate, Missed, true);
				player_two.render(true);
				std::cout << "Lol, you missed :/\n\n";
				std::cout << "Press Enter to continue or 0 to quit...\n";
				std::cin >> input;

				if (input == "0")
				{
					player_one_kills = boatpieces + 3;
					break;
				}

				turn = COMPUTER;
			}
			else if (tile.state == states::Occupied)
			{
				player_two.setboardtile_state(coordinate, Hit, true);
				player_two.render(true);
				std::cout << "Hmmm, nice hit :)\n";

				if (input == "0")
				{
					player_one_kills = boatpieces + 3;
					break;
				}

				player_one_kills++;
				turn = PLAYER_ONE;
			}
			else
			{
				turn = COMPUTER;
			}
			break;
		case PLAYER_TWO:
			player_one.render(true);
			std::cout << "\n"
					  << C_CYAN << "PLAYER TWO:\n"
					  << C_RESET;
			std::cout << "Enter your Target coordinate eg. A1:\n";
			std::cin >> coordinate;
			tile = player_one.getboardtile(coordinate);

			if (tile.state == states::Available ||
				tile.state == states::Missed)
			{
				player_one.setboardtile_state(coordinate, Missed, true);
				player_one.render(true);
				std::cout << "Lol, you missed :/\n\n";
				std::cout << "Press Enter to continue or 0 to quit...\n";
				std::cin >> input;

				if (input == "0")
				{
					player_one_kills = boatpieces + 3;
					break;
				}

				turn = COMPUTER;
			}
			else if (tile.state == states::Occupied)
			{
				player_one.setboardtile_state(coordinate, Hit, true);
				player_one.render(true);
				std::cout << "Hmmm, nice hit :)\n";

				if (input == "0")
				{
					player_one_kills = boatpieces + 3;
					break;
				}

				player_one_kills++;
				turn = PLAYER_ONE;
			}
			else
			{
				turn = COMPUTER;
			}
			break;
		default:
			break;
		}
	}

	if (player_one_kills == boatpieces)
	{
		std::cout << "\nPlayer 1 wins";
	}
	else if (player_two_kills == boatpieces)
	{
		std::cout << "\nPlayer 2 wins";
	}
	else if (player_two_kills >= boatpieces ||
			 player_one_kills >= boatpieces)
	{
		std::cout << "\nGame successfully ended";
	}
	else
	{
		std::cout << "\nerr";
	}
}

int main()
{
	//std::string coordinate;
	int i, col, row, input;
	//udtile tile;

	std::cout << "       ****************************************************\n";
	std::cout << "       *                                     				*\n";
	std::cout << "       * 		PLEASE SELECT AN OPTION       				*\n";
	std::cout << "       * 		  1. Player V Computer.     				*\n";
	std::cout << "       * 		  2. Multi Player.     		 				*\n";
	std::cout << "       * 		  3. Player v computer (salvo) game        *\n";
	std::cout << "       * 		  4. Quit the Game.            				*\n";
	//	std::cout << "       *                                      			*\n";
	std::cout << "       *                                      			*\n";
	std::cout << "       ****************************************************\n";

	std::cout << "Please Enter the Number:";
	std::cin >> input;

	switch (input)
	{
	case 1:
		initgame("adaship_config.ini", 1);
		player_one.render();
		placeplayerboats(boats.getboats(), player_one);
		placecomputerboats(boats.getboats());
		startgame_one();
		break;
	case 2:
		initgame("adaship_config.ini", 2);
		player_one.render();
		placeplayerboats(boats.getboats(), player_one);
		player_two.render();
		placeplayerboats(boats.getboats(), player_two);
		startgame_two();
		break;
	case 4:
		std::cout << "Thank you. Game ended";

	default:
		std::cout << "You entered a invalid number\n please enter number between 1 to 3.";
		return 0;
		break;
	}

	return 0;
	//coordinate = "A1";

	//player_one.setboardtile_state(coordinate, Occupied);

	//tile = player_one.getboardtile(coordinate);

	//player_one.nexttile(coordinate);

	//common_randomselect(0, 10, true);
}