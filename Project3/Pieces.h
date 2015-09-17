#ifndef PIECE_S_INCLUDED
#define PIECE_S_INCLUDED
#include "Piece.h"
#include <vector>

class PieceI:public Piece
{
public:
	PieceI()
	{
		for(int i = 0;i<4;i++)
			orientation[0][1][i] = "#";
		for(int i = 0;i<4;i++)
			orientation[1][i][1] = "#";
		for(int i = 0;i<4;i++)
			orientation[2][1][i] = "#";
		for(int i = 0;i<4;i++)
			orientation[3][i][1] = "#";
		bbox = orientation[current];
	}
};

class PieceT:public Piece
{
public:
	PieceT()
	{
		for(int i = 0;i<3;i++)
			orientation[0][1][i] = "#";
		orientation[0][0][1] = "#";
		for(int i = 0;i<3;i++)
			orientation[1][i][1] = "#";
		orientation[1][1][2] = "#";
		for(int i = 0;i<3;i++)
			orientation[2][1][i] = "#";
		orientation[2][2][1] = "#";
		for(int i = 0;i<3;i++)
			orientation[3][i][1] = "#";
		orientation[3][1][0] = "#";
		bbox = orientation[current];
	}
};
class PieceL:public Piece
{
public:
	PieceL()
	{
		for(int i = 0;i<3;i++)
			orientation[0][1][i] = "#";
		orientation[0][2][0] = "#";
		for(int i = 0;i<3;i++)
			orientation[1][i][2] = "#";
		orientation[1][0][1] = "#";
		for(int i = 0;i<3;i++)
			orientation[2][2][i] = "#";
		orientation[2][1][2] = "#";
		for(int i = 1;i<4;i++)
			orientation[3][i][1] = "#";
		orientation[3][3][2] = "#";
		bbox = orientation[current];
	}
};
class PieceJ:public Piece
{
public:
	PieceJ()
	{
		for(int i = 1;i<4;i++)
			orientation[0][1][i] = "#";
		orientation[0][2][3] = "#";
		for(int i = 1;i<4;i++)
			orientation[1][i][2] = "#";
		orientation[1][3][1] = "#";
		for(int i = 1;i<4;i++)
			orientation[2][2][i] = "#";
		orientation[2][1][1] = "#";
		for(int i = 0;i<3;i++)
			orientation[3][i][1] = "#";
		orientation[3][0][2] = "#";
		bbox = orientation[current];
	}
};
class PieceO:public Piece
{
public:
	PieceO()
	{
		for(int i = 0;i<2;i++)
			for(int j = 0;j<2;j++)
				orientation[0][i][j] = "#";
		for(int i = 1;i<4;i++)
		orientation[i] = orientation[0];
		bbox = orientation[current];
	}
};
class PieceS:public Piece
{
public:
	PieceS()
	{
		orientation[0][1][1] = orientation[0][1][2] = orientation[0][2][0] = orientation[0][2][1] ="#";
		orientation[1][0][1] = orientation[1][1][1] = orientation[1][1][2] = orientation[1][2][2] ="#";
		orientation[2] = orientation[0];
		orientation[3] = orientation[1];
		bbox = orientation[current];
	}
};
class PieceZ:public Piece
{
public:
	PieceZ()
	{
		orientation[0][1][0] = orientation[0][1][1] = orientation[0][2][1] = orientation[0][2][2] ="#";
		orientation[1][1][1] = orientation[1][2][1] = orientation[1][1][2] = orientation[1][0][2] ="#";
		orientation[2] = orientation[0];
		orientation[3] = orientation[1];
		bbox = orientation[current];
	}
};


#endif