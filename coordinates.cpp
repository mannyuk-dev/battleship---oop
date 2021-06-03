#include "headers/adaship.h"


udtboardreference coordinates_extractcoordinate(std::string coordinate) {
	//extract column and row reference from a board coordinate (e.g., A1..ZZ80)
	std::string colref = "", tmp_rowref = "";
	int rowref = 0;
	udtboardreference boardref;

	for (std::string::iterator it = coordinate.begin(); it != coordinate.end(); ++it) {
		if (std::isalpha(*it)) {
			colref += toupper(*it); //extract and convert to upper case
		} else if (isdigit(*it)) {
			tmp_rowref += *it; //extract and store numeric value
		}
	}
	
	boardref.colref = colref;
	boardref.rowref = std::stoi(tmp_rowref); //convert tmp rowref to int

	return boardref;
}


int coordinates_getindex(int col, int row, int width) {
	//return the based 0 index based on the column, row and width
	if(col == 0 && row == 0) { return 0; } //deal with all zeros
	return (col + width * row);
}


udtcoord coordinates_getcolrow(int idx, int width) {
	//return the column and row based on the base 0 index
	if(idx == 0 ) { return { 0, 0 }; }
	int col = idx % width; //use modulo to get the remainder of idx / width;
	int row = idx / width; //integer division
	return {col, row};
}


int coordinates_colreftoindex(std::string colref) {
	//convert 'column reference' (A[a] = 0, B[b] = 2, .. Z[a] = 25, AA[aa], AB[bb]..ZZ[zz] = 701) to an index (0..701)
	//returns valid index (0..701), any negative values represent invalid column references i.e., not A[a]..ZZ[zz]
	if(colref.length() == 1) {//deal with single letter value (A = 0, B = 2 .. Z = 25)
		return toupper(int(colref[0])) - 65; // 65 represents ASCII 'A' 'A' - 65 = 0
	} else if(colref.length() == 2) {//deal with pair values (AA = 26, BA = 52, CA = 78 .. ZZ = 701)
		return ((toupper(int(colref[1])) - 65) + (toupper(int(colref[0])) - 64) * 26); // -64 to get base 1 thus avoiding 0 * n = 0 issue
	}
	return -1; //no match 
}


std::string coordinates_indextocolref(int idx) {
	//convert index to 'column reference'; valid range 0 to 702 (ZZ)
	//invalid indexes return and empty string 
	std::string labels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string reference = ""; //set default return

	if(idx >= 0 && idx <= ((26*26)+26)) { //check in valid range
		int x = idx/26; //check range; 0 if A..Z
		if(x == 0) {
			reference = labels[idx]; //return reference
		} else {
			idx = idx - (x * 26); //update index
			reference = labels[(x-1)]; //add initial column ref; A..Z
			reference += labels[idx]; //add secondary column ref; AA..ZZ
		}
	}
	return reference;
}
