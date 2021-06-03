#pragma once

enum states
{
	Available,
	Occupied,
	Hit,
	Missed,
};

struct udtile
{
	int col;
	int row;
	int idx;
	char boatId;
	std::string color;
	states state;
};

struct boardconfig
{
	int width;
	int height;
};

class Board
{
public:
	Board(); //constructor

	void initboard(int w, int h, std::string title);
	void render(bool hideboats = false);
	bool setboatonboard(char dir, boat boat, std::string coordinate, bool rowtobasezero = true);
	bool isidxoccupied(int row, int col);
	int setboardtile_state(std::string coordinate, states state, bool isgamemode = false);
	int setboardtile_id(int idx, char boatId);
	int setboardtile_color(int idx, std::string color);
	int setboardtile(int idx, boat boat);
	udtile getboardtile(std::string coordinate);
	boardconfig getboardconfig();

	void nexttile(std::string coordinate);

protected:
private:
	int tileindex(std::string coordinate, bool rowtobasezero = true);
	int setboardtile_state(int idx, states state);
	udtile getboardtile(int idx);
	std::vector<udtile> _tile;
	boardconfig _boardconfig = {10, 10};
	std::string _title;
};