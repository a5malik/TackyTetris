#ifndef SPECIAL_PIECES_INCLUDED
#define SPECIAL_PIECES_INCLUDED
#include "Piece.h"
class PieceVapor:public Piece
{
public:
	PieceVapor()
	{
		orientation[0][0][1] = orientation[0][0][2]="#";
		for(int i = 1;i<4;i++)
			orientation[i]=orientation[0];
		bbox = orientation[current];
	}

	void isspecial(char& s) const
    {
	s = 'v';
    }
};
class PieceFoam: public Piece
{
public:
	PieceFoam() 
	{
	orientation[0][1][1] = "#";
	for(int i = 1;i<4;i++)
		orientation[i] = orientation[0];
	bbox = orientation[current];
	}
	void isspecial(char& s) const
	{
		s = 'f';
	}
};
class PieceCrazy:public Piece
{
public:
	PieceCrazy()
	{
		orientation[0][0][0] = orientation[0][1][1] = orientation[0][1][2] = orientation[0][0][3] ="#";
		orientation[1][0][3] = orientation[1][1][2] = orientation[1][2][2] = orientation[1][3][3] ="#";
		orientation[2][3][0] = orientation[2][2][1] = orientation[2][2][2] = orientation[2][3][3] ="#";
		orientation[3][0][0] = orientation[3][1][1] = orientation[3][2][1] = orientation[3][3][0] ="#";
		bbox = orientation[current];
	}
	void isspecial(char& s) const
	{
		s = 'c';
	}
};
#endif