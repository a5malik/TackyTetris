#ifndef TANK_INCLUDED
#define TANK_INCLUDED
#include <vector>
#include <string>
#include "Piece.h"
#include "Pieces.h"
#include "specialpiece.h"
#include "randPieceType.h"
class Screen;

//int DEPTH = 19;
//int WIDTH = 12;
const char BORDER = '@';
class Tank
{
  public:
	  Tank(int width, int height);
    void display(Screen& screen, int x, int y);
	void Piecedisplay(Screen& screen) const;
	void endpiecedisplay(Screen& screen) const;
	void move(Screen& Screen);
	int getfull() const;
	bool isclear(int h,int v);
	bool isrotate();
	void burn();
	bool newpiece(PieceType a,Screen& screen);
	void rowfull();
	void vaporize(int j);
	void vaporbomb();
	void foambomb(int ec,int er,int dis1,int dis2);
	void empty();
	void Piececancel(Screen& screen) const;
	void movetime(int);
	int getpoints() const;
	int tfull() const;
  private:
	  int WIDTH,DEPTH;
	std::vector<std::vector<std::string>> t;
	Piece* p;
	int m_full;
	int timepermove;
	int points;
};


#endif // TANK_INCLUDED
