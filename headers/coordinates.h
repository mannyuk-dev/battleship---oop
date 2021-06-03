#pragma once


struct udtboardreference {
	std::string colref;
	int rowref;
};


struct udtcoord {
	int col;
	int row;
};


udtboardreference coordinates_extractcoordinate(std::string coordinate);

int coordinates_getindex(int col, int row, int width);
udtcoord coordinates_getcolrow(int idx, int width);

int coordinates_colreftoindex(std::string colref);
std::string coordinates_indextocolref(int idx);
