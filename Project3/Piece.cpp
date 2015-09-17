#include "Piece.h"
#include "UserInterface.h"
Piece::Piece()
	:cordx(PIECE_X),cordy(PIECE_Y),current(0),bbox(4,std::vector<std::string>(4)),
	 orientation(4,std::vector<std::vector<std::string>>(4,std::vector<std::string>(4)))
{}

bool Piece::move(char ch)
{
	switch(ch)
	{
	   case '!' : cordy++;break;
	   case ARROW_LEFT : cordx--;break;
	   case ARROW_RIGHT: cordx++;break;
	   case ARROW_DOWN : cordy++;break;
	   case ARROW_UP :  rotate();break;
	}
	return true;
}

bool Piece::rotate()
{
	current = (current+1)%4;
	bbox = orientation[current];
	return true;
}

char Piece::bboxij(int i, int j) const
{
	return bbox[i][j][0];
}
char Piece::rotbboxij(int i, int j) const
{
	return orientation[(current+1)%4][i][j][0];
}

void Piece::isspecial(char& s) const
{
	s = 'n';
}

void Piece::coord( int &i, int &j) const
{
	i = cordx;
	j = cordy;
}