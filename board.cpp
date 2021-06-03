#include "headers/adaship.h"

Board::Board(){
	//constructor function
};

void ColorPrint(const char *text, int fg_color, int bg_color)
{
	//prints color
	static const char begin_sequence[]{0x1B, '[', '\0'};
	static const char reset[]{0x1B, '[', '0', 'm', '\0'};

	std::cout << begin_sequence << fg_color << ';' << bg_color << 'm' << text << reset;
}

void Board::render(bool hide)
{
	// renders board in console
	system("clear");
	//render the object's Board
	std::string colour = C_CYAN;
	std::string colref;
	int idx = 0;

	std::cout << _title;

	//add column reference lables A, B, C..
	for (int row = 0; row < 2; row++)
	{
		std::cout << "\n";
		std::cout << colour << " " << std::setw(3) << " " << C_RESET;
		for (int col = 0; col < _boardconfig.width; col++)
		{
			if (row == 0)
			{
				colref = coordinates_indextocolref(col);
				std::cout << colour << "\t" << std::setw(2) << colref << C_RESET;
			}
			else
			{
				std::cout << colour << "\t"
						  << "\u2501\u2501\u2501" << C_RESET;
			}
		}
	}

	//add row labels (0, 1, 2..) and Board values
	for (int row = 0; row < _boardconfig.height; row++)
	{
		std::cout << "\n";
		std::cout << colour << " " << std::setw(3) << (row + 1) << "\u2503" << C_RESET;
		for (int col = 0; col < _boardconfig.width; col++)
		{
			idx = coordinates_getindex(col, row, _boardconfig.width);

			if (_tile[idx].state == states::Occupied)
			{
				!hide ? std::cout << "\t" << std::setw(2) << _tile[idx].color << _tile[idx].boatId << C_RESET
					  : std::cout << "\t" << std::setw(2) << "\u00B7";
			}
			else if (_tile[idx].state == states::Missed)
			{
				std::cout << "\t" << std::setw(2) << C_RED << "X" << C_RESET;
			}
			else if (_tile[idx].state == states::Hit)
			{
				std::cout << "\t" << std::setw(2) << C_GREEN << "o" << C_RESET;
			}
			else
			{
				std::cout << "\t" << std::setw(2) << "\u00B7";
			}
		}
	}
	std::cout << "\n\n";
}

void Board::nexttile(std::string coordinate)
{
	//at the moment, this is a bit of a hack to find max space availble on column and row
	//could be used to see if a boat could be positioned ??
	int idx = tileindex(coordinate); //convert the coordinate reference to an index
	int col = _tile[idx].col;		 //get the column value for the indexed tile
	int row = _tile[idx].row;		 //get the row value for the indexed tile
	int max_width = 0;				 //set a count
	int max_length = 0;

	for (int c = (col + 1); c < _boardconfig.width; c++)
	{															  //loop through each column to the end of the Board
		int i = coordinates_getindex(c, row, _boardconfig.width); //find next tile on same column
		if (_tile[i].state == states::Available)
		{				 //is the tile 'available'
			max_width++; //essentially a base 1 value indicating how many available tiles exists to the right of the tile
		}
		else
		{
			break;
		}
	}

	for (int r = (row + 1); r < _boardconfig.height; r++)
	{															   //loop through each row to the end of the Board
		int i = coordinates_getindex(col, r, _boardconfig.height); //find next tile on same row
		if (_tile[i].state == states::Available)
		{				  //is the tile 'available'
			max_length++; //essentially a base 1 value indicating how many available tiles exists below the tile
		}
		else
		{
			break;
		}
	}

	std::cout << "\n"
			  << coordinate << " available to the left: " << max_width;
	std::cout << "\n"
			  << coordinate << " available to the below: " << max_length;
}

int Board::tileindex(std::string coordinate, bool rowtobasezero)
{
	//convert Board coordinate to tile index; used to convert "A1.." to tile index
	udtboardreference boardreference;
	boardreference = coordinates_extractcoordinate(coordinate); //break coordinate (A1 to 'A' and '1')

	int col = coordinates_colreftoindex(boardreference.colref);					 //convert colref (A..Z) to column index
	int row = rowtobasezero ? boardreference.rowref - 1 : boardreference.rowref; //update rowref if base 0
	if (row > _boardconfig.width || row < 0 || col > _boardconfig.height || col < 0)
	{
		return -1;
	}

	int idx = coordinates_getindex(col, row, _boardconfig.width); //convert column and row to index
	// if (_tile[idx].state != states::Available)
	// {
	// 	return -1;
	// }

	//std::cout << "\ncoordinate: " << coordinate << " col: " << col << ", row: " << row << ", idx: " << idx;
	return idx;
}

bool Board::isidxoccupied(int row, int col)
{
	//checks if given row/col is occupied/not empty
	int idx = coordinates_getindex(col, row, _boardconfig.width);
	if (_tile[idx].state != states::Available)
	{
		return true;
	}

	return false;
}

bool Board::setboatonboard(char dir, boat boat, std::string coordinate, bool rowtobasezero)
{
	//Sets tile value after verifying it is available and returns the result from the aforementioned.
	udtboardreference boardreference;
	boardreference = coordinates_extractcoordinate(coordinate);					 //break coordinate (A1 to 'A' and '1')
	int col = coordinates_colreftoindex(boardreference.colref);					 //convert colref (A..Z) to column index
	int row = rowtobasezero ? boardreference.rowref - 1 : boardreference.rowref; //update rowref if base 0

	if (dir == 'l')
	{
		if (col - boat.len >= 1)
		{

			for (int i = 0; i <= boat.len - 1; i++)
			{
				if (isidxoccupied(row, col - i))
				{
					return true;
				}
			}
			for (int x = 0; x <= boat.len - 1; x++)
			{
				int idx = coordinates_getindex(col - x, row, _boardconfig.width);
				setboardtile(idx, boat);
			}
		}
		else
		{
			return true;
		}
	}
	else if (dir == 'r')
	{
		if (col + boat.len <= 10)
		{
			for (int i = 0; i <= boat.len - 1; i++)
			{
				if (isidxoccupied(row, col + i))
				{
					return true;
				}
			}
			for (int x = 0; x <= boat.len - 1; x++)
			{
				int idx = coordinates_getindex(col + x, row, _boardconfig.width);
				setboardtile(idx, boat);
			}
		}
		else
		{
			return true;
		}
	}
	else if (dir == 'u')
	{
		if (row - boat.len >= 1)
		{
			for (int i = 0; i >= boat.len - 1; i++)
			{
				if (isidxoccupied(row - i, col))
				{
					return true;
				}
			}
			for (int x = 0; x <= boat.len - 1; x++)
			{
				int idx = coordinates_getindex(col, row - x, _boardconfig.width);
				setboardtile(idx, boat);
			}
		}
		else
		{
			return true;
		}
	}
	else if (dir == 'd')
	{
		if (row + boat.len <= 10)
		{
			for (int i = 0; i <= boat.len - 1; i++)
			{
				if (isidxoccupied(row + i, col))
				{
					return true;
				}
			}
			for (int x = 0; x <= boat.len - 1; x++)
			{
				int idx = coordinates_getindex(col, row + x, _boardconfig.width);
				setboardtile(idx, boat);
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}

int Board::setboardtile(int idx, boat boat)
{
	//set board's tile for a specic boat
	setboardtile_id(idx, toupper(boat.name.at(0)));
	setboardtile_color(idx, boat.color);
	setboardtile_state(idx, Occupied);

	return 0;
}

udtile Board::getboardtile(int idx)
{
	//return the specified tile

	return _tile[idx];
}

udtile Board::getboardtile(std::string coordinate)
{
	//overloaded wrapper to return the specified tile based on Board coordinate values
	int idx = tileindex(coordinate);
	return getboardtile(idx);
}

int Board::setboardtile_id(int idx, char boatId)
{
	//update Board tile based on base 0 index value
	_tile[idx].boatId = boatId;
	return 0;
}

int Board::setboardtile_color(int idx, std::string color)
{
	//update Board tile based on base 0 index value
	_tile[idx].color = color;
	return 0;
}

int Board::setboardtile_state(int idx, states state)
{
	//update Board tile based on base 0 index value
	_tile[idx].state = state;
	return 0;
}

int Board::setboardtile_state(std::string coordinate, states state, bool isgamemode)
{
	//Sets coordinate state if it is a valid index
	int idx = tileindex(coordinate);

	if (idx == -1)
	{
		return -1;
	}

	if (!isgamemode)
	{
		if (_tile[idx].state != states::Available)
		{
			return -1;
		}
	}

	return setboardtile_state(idx, state);
}

void Board::initboard(int w, int h, std::string title)
{
	//set and initialise a Board based on the width and height

	_boardconfig.width = w; //set the width and height
	_boardconfig.height = h;
	_title = title;

	udtcoord coord;
	for (int idx = 0; idx < (_boardconfig.width * _boardconfig.height); idx++)
	{
		coord = coordinates_getcolrow(idx, _boardconfig.width);
		_tile.push_back({
			coord.col,
			coord.row,
			idx,
			Available,
		});
	}
};

boardconfig Board::getboardconfig()
{
	return _boardconfig;
};
