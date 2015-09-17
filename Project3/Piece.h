#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED
#include "UserInterface.h"
#include "string"
#include <vector>
const int PIECE_X = 3;
const int PIECE_Y = 0;
class Tank;
class Piece
{
public:
	Piece();
	virtual bool move(char ch = '!');
	virtual bool rotate();
	void coord(int &i,int &j) const;
	char bboxij(int i, int j) const;
	char rotbboxij(int i, int j) const;
	virtual void isspecial(char& s) const;
protected:
	std::vector<std::vector<std::string>> bbox;
	int cordx,cordy;
	std::vector<std::vector<std::vector<std::string>>> orientation;
	int current;
};
		
#endif