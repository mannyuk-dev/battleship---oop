#pragma once
//#include <std::string> //add suport for - std::std::string, std::stoi


struct boat
{
	std::string name;
	int len;
	std::string color;
};

// struct boats
// {
// 	Boat submarine = {"patrol", 3};
// 	Boat destroyer = {"patrol", 3};
// 	Boat patrol = {"patrol", 2};
// 	Boat battleship = {"patrol", 4};
// 	Boat carrier = {"carrier", 5};
// };

class Boats
{
public:
	Boats(); //constructor
	void initboats(std::string configname);
	void addboat(std::string name, std::string len, std::string color);
	std::vector<boat> getboats();


protected:

private:
	std::vector<boat> _boats;
};
