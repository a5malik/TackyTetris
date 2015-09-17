#include "Game.h"
#include "Tank.h"
#include "UserInterface.h"
#include <string>
#include <algorithm>
#include "randPieceType.h"
#include "Piece.h"
#include "specialpiece.h"
#include "Pieces.h"

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int TANK_X = 0;
const int TANK_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
	: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_tank(width,height),pnext(nullptr)
{
}

void Game::play()
{
    m_tank.display(m_screen, TANK_X, TANK_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Imitris!");
    waitForEnter();  // [in UserInterface.h]

    for(;;)
    {
		displayStatus();
		if (!playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
		m_tank.empty();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)     
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

void Game::displayStatus()
{
	m_screen.gotoXY(SCORE_X,SCORE_Y);
	m_screen.printString( "Score:            ");
	int temp = m_tank.getpoints();
	if(temp == 0)
		{
			m_screen.gotoXY(33,8);
	    m_screen.printChar('0');
	}
	int i = 0;
	while(temp!=0)
	{
		m_screen.gotoXY(33-i,8);
		m_screen.printChar('0'+temp%10);
		i++;;
		temp = temp/10;
	}
	m_screen.gotoXY(ROWS_LEFT_X,ROWS_LEFT_Y);
	m_screen.printString("Rows left:         ");
	int t = 5*m_level - m_tank.tfull();
	if(t <= 0)
		{
			m_screen.gotoXY(33,9);
	    m_screen.printChar('0');
	}
	 i = 0;
	while(t>0)
	{
		m_screen.gotoXY(33-i,9);
		m_screen.printChar('0'+t%10);
		i++;;
		t = t/10;
	}
	m_screen.gotoXY(LEVEL_X,LEVEL_Y);
	m_screen.printString( "Level:            ");
	int h = m_level;
	if(h == 0)
		{
			m_screen.gotoXY(33,10);
	    m_screen.printChar('0');
	}
	i = 0;
	while(h!=0)
	{
		m_screen.gotoXY(33-i,10);
		m_screen.printChar('0'+h%10);
		i++;;
		h = h/10;
	}
}
void Game::displaynext()
{
	m_screen.gotoXY(NEXT_PIECE_TITLE_X,NEXT_PIECE_TITLE_Y);
	m_screen.printString("Next piece:");
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			m_screen.gotoXY(NEXT_PIECE_X+j,NEXT_PIECE_Y+i);
			m_screen.printChar(' ');
		}
	for(int i = 0;i<4;i++)
		for(int j = 0;j<4;j++)
		{
			m_screen.gotoXY(NEXT_PIECE_X+j,NEXT_PIECE_Y+i);
			m_screen.printChar(pnext->bboxij(i,j));
		}
}

void Game::newpiecer(PieceType a)
{
	delete pnext;
	if(a== PIECE_I) pnext= new PieceI;
	else if(a==PIECE_T) pnext= new PieceT;
	else if(a==PIECE_VAPOR) pnext= new PieceVapor;
	else if(a==PIECE_FOAM) pnext= new PieceFoam;
	else if(a==PIECE_L) pnext= new PieceL;
	else if(a==PIECE_J) pnext= new PieceJ;
	else if(a==PIECE_O) pnext= new PieceO;
	else if(a==PIECE_S) pnext= new PieceS;
	else if(a==PIECE_Z) pnext= new PieceZ;
	else if(a==PIECE_CRAZY) pnext= new PieceCrazy;
}

bool Game::playOneLevel()
{
	int lines = 5*m_level;
	m_tank.movetime(std::max(1000-(100*(m_level-1)), 100));
	PieceType pnew = randPieceType();
	while(1)
	{
	    
		if(!m_tank.newpiece(pnew,m_screen))
			{
				pnew = randPieceType();
	            newpiecer(pnew);
	            displaynext();
				break;
		    }
		else
		{
	  pnew = randPieceType();
	  newpiecer(pnew);
	  displaynext();
		}
	   m_tank.move(m_screen);
	   displayStatus();
	  if(m_tank.getfull() >=lines )
		  return true;
	}
    return false;  // [Replace this with the code to play a level.]
}
