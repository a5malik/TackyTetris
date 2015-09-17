#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Tank.h"
#include "UserInterface.h"
#include <string>
#include "Piece.h"
#include "Pieces.h"
#include "specialpiece.h"
// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
	void displaynext();
	void newpiecer(PieceType a);
	void nextdisplay();
    // [Add other members as necessary.]

  private:
    Tank    m_tank;
    Screen  m_screen;
    int     m_level;
	int m_lines;
	Piece* pnext;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
