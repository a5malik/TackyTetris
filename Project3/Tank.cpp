#include "Tank.h"
#include "UserInterface.h"
#include <cmath>
#include <iostream>

Tank::Tank(int width, int height)
	:WIDTH(width+2),DEPTH(height+1),t(width+2,std::vector<std::string>(height+1)),p(nullptr),m_full(0),points(0)
{
	for( int i = 1;i<WIDTH-1;i++)
		t[i][DEPTH-1] += BORDER;
	for( int i = 0;i<DEPTH;i++)
	{t[0][i]=t[WIDTH-1][i] += BORDER;}
}
void Tank::empty()
{
	for(int i = 1;i<t.size()-1;i++)
		for(int j = 0;j<t[i].size()-1;j++)
		{
			t[i][j] = "";
		}
		m_full = 0;
}

void Tank::display(Screen& screen, int x, int y)
{
	for(int i = 0;i<t.size();i++)
		for(int j = 0;j<t[i].size();j++)
		{
			screen.gotoXY(x+i,y+j);
			screen.printChar(t[i][j][0]);
		}
	screen.gotoXY(80, 25);
}
	
void Tank::movetime(int t)
{
	timepermove = t;
}
void Tank::Piecedisplay(Screen& screen) const
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	//screen.gotoXY(c_x,c_y);
	//screen.printChar('P');
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			screen.gotoXY(c_x+j,c_y+i);
			char c = p->bboxij(i,j);
			if(c_x+j<WIDTH && c_y+i<DEPTH && p->bboxij(i,j) == '#' && t[c_x+j][c_y+i] == "" ) 
				screen.printChar('#');
		}
	screen.gotoXY(80, 25);
}
void Tank::endpiecedisplay(Screen& screen) const
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	//screen.gotoXY(c_x,c_y);
	//screen.printChar('P');
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			screen.gotoXY(c_x+j,c_y+i);
			char c = p->bboxij(i,j);
			if(c_x+j<WIDTH && c_y+i<DEPTH && p->bboxij(i,j) == '#') 
				screen.printChar('#');
		}
	screen.gotoXY(80, 25);

}

void Tank::Piececancel(Screen& screen)const
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	//screen.gotoXY(c_x,c_y);
	//screen.printChar('P');
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			screen.gotoXY(c_x+j,c_y+i);
			char c = p->bboxij(i,j);
			if(c_x+j<WIDTH && c_y+i<DEPTH && p->bboxij(i,j) == '#' && t[c_x+j][c_y+i] == "") 
				screen.printChar(' ');
		}
	screen.gotoXY(80, 25);
}
void Tank::burn()
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
			if(p->bboxij(i,j) == '#')
				t[c_x+j][c_y+i] = "$";
}
void Tank::move(Screen& screen)
{
	display(screen,0,0);
	Piecedisplay(screen);
	char s;
	p->isspecial(s);
	bool space = false;
	while(1)
	{
	int endTime = getMsecSinceStart() + timepermove;
	while (getMsecSinceStart() < endTime && !space)
	{
		char ch;
	    if (getCharIfAny(ch))
	    {
		  // There was a character typed; it's now in ch
	        switch (ch)
	        {
			case ARROW_DOWN:
				if(isclear(0,1))
					{
					Piececancel(screen);
					p->move(ARROW_DOWN);
					endTime=getMsecSinceStart()+ timepermove;
				     }
				break;
			case ARROW_LEFT:
				if(s == 'c')
				{
					if(isclear(1,0))
					{
						Piececancel(screen);;
				       p->move(ARROW_RIGHT);
				    }
				}
				else
					if(isclear(-1,0))
				    {
					Piececancel(screen);
					p->move(ARROW_LEFT);
				    }
				break;
			case ARROW_RIGHT:
				if(s == 'c')
				{
					if(isclear(-1,0))
				    {
					Piececancel(screen);
					p->move(ARROW_LEFT);
				    }
				}
			   else
				if(isclear(1,0))
					{
						Piececancel(screen);
				       p->move(ARROW_RIGHT);
				    }
				break;
			case ARROW_UP:
				if(isrotate())
				{
					Piececancel(screen);
					p->rotate();
				}
				break;
			case SPACE_BAR:
				while(isclear(0,1))
				{
					Piececancel(screen);
					p->move();
				}
				space = true;
				break;
			}
	     //	display(screen,0,0);
	        Piecedisplay(screen);
		}

	}
	  if(!isclear(0,1))break;
	  Piececancel(screen);
	   p->move();
	  // display(screen,0,0);
	   Piecedisplay(screen);
	}
	burn();
			if (s == 'v') vaporbomb();
	        else if (s == 'f') 
			{
				int i, j;
				p->coord(i,j);
				foambomb(i+1,j+1,0,0);
			}
	rowfull();
	display(screen,0,0);

}

bool Tank::isclear(int h,int v)
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
			if(p->bboxij(i,j) == '#')
				if(c_x+j+h <=0 || c_x+j+h>WIDTH-1 ||c_y+i+v<0 || c_y+i+v>DEPTH-1 || t[c_x+j+h][c_y+i+v]!="")
					return false;
	return true;
}
bool Tank::isrotate()
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
			if(p->rotbboxij(i,j) == '#')
				if(c_x+j<=0 || c_x+j>WIDTH-1 ||c_y+i<0 || c_y+i>DEPTH-1 || t[c_x+j][c_y+i]!="")
					return false;
	return true;
}

bool Tank::newpiece(PieceType a,Screen& screen)
{
	delete p;
	//a = PIECE_I;
	if(a== PIECE_I) p = new PieceI;
	else if(a==PIECE_T) p = new PieceT;
	else if(a==PIECE_VAPOR) p = new PieceVapor;
	else if(a==PIECE_FOAM) p = new PieceFoam;
	else if(a==PIECE_L) p = new PieceL;
	else if(a==PIECE_J) p = new PieceJ;
	else if(a==PIECE_O) p = new PieceO;
	else if(a==PIECE_S) p = new PieceS;
	else if(a==PIECE_Z) p = new PieceZ;
	else if(a==PIECE_CRAZY) p = new PieceCrazy;
	if(!isclear(0,0))
	{
		endpiecedisplay(screen);
		return false;
	}
	else return true;
}

void Tank::rowfull()
{
	int simultfull = 0;
	for(int j = 0;j<t[0].size();j++)
	{
		bool full = true;
		for(int i = 1;i<t.size()-1;i++)
			if(t[i][j]!="$" && t[i][j]!="*") full = false;
		if(full)
			{
				vaporize(j);
				simultfull++;
		    }
	}
	if(simultfull>0)
	points+=(100*(std::pow(2,simultfull-1)));
}

			
void Tank::vaporize(int j)
{
	for(int i = 0;i<t.size();i++)
		t[i].erase(t[i].begin()+j);
	t[0].insert(t[0].begin(),"@");
	for(int i = 1;i<t.size()-1;i++)
		t[i].insert(t[i].begin(),"");
	t[WIDTH-1].insert(t[WIDTH-1].begin(),"@");
	m_full++;
}

void Tank::vaporbomb()
{
	int c_x,c_y;
	p->coord(c_x,c_y);
	int vpx1 = c_x + 1,vpx2 = c_x+2,vpy = c_y;
	for(int i = 2;i>=-2;i--)
	    if(vpy+i<t[0].size()-1 && vpy+i>=0)
			{
				t[vpx1][vpy+i] = "";
				t[vpx2][vpy+i] = "";
		    }
}

void Tank::foambomb(int ec, int er,int dis1,int dis2)
{
	
	if(abs(dis1)>2 || abs(dis2)>2) return;
	if((dis1!=0 || dis2!=0) && t[ec][er]!="") return;
	t[ec][er] = "*";
	foambomb(ec+1,er,dis1+1,dis2);
	foambomb(ec-1,er,dis1-1,dis2);
	foambomb(ec,er+1,dis1,dis2+1);
	foambomb(ec,er-1,dis1,dis2-1);
}
int Tank::getpoints() const
{
	return points;
}
int Tank::tfull() const
{
	return m_full;
}
int Tank::getfull() const
{
	return m_full;
}
