// garks.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Mesa::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;   // max number of rows in the mesa
const int MAXCOLS = 25;   // max number of columns in the mesa
const int MAXGARKS = 150; // max number of garks allowed
const int INITIAL_GARK_HEALTH = 2;

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////
class Game
{
public:
      // Constructor/destructor
      Game(int rows, int cols, int nGarks);
      ~Game();

      // Mutators
      void play();

private:
      Mesa *m_mesa;
};
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nGarks)
{
      if (nGarks < 0)
      {
            cout << "***** Cannot create Game with negative number of garks!" << endl;
            exit(1);
      }
      if (nGarks > MAXGARKS)
      {
            cout << "***** Trying to create Game with " << nGarks
                 << " garks; only " << MAXGARKS << " are allowed!" << endl;
            exit(1);
      }
      if (rows == 1 && cols == 1 && nGarks > 0)
      {
            cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
            exit(1);
      }

      // Create mesa
      m_mesa = new Mesa(rows, cols);

      // Add player
      int rPlayer = randInt(1, rows);
      int cPlayer = randInt(1, cols);
      m_mesa->addPlayer(rPlayer, cPlayer);

      // Populate with garks
      while (nGarks > 0)
      {
            int r = randInt(1, rows);
            int c = randInt(1, cols);
            // Don't put a gark where the player is
            if (r == rPlayer && c == cPlayer)
                  continue;
            m_mesa->addGark(r, c);
            nGarks--;
      }
}

Game::~Game()
{
      delete m_mesa;
}

void Game::play()
{
      m_mesa->display();
      Player *player = m_mesa->player();
      if (player == nullptr)
            return;
      while (!player->isDead() && m_mesa->garkCount() > 0)
      {
            cout << endl;
            cout << "Move (u/d/l/r/q or nothing): ";
            string action;
            getline(cin, action);
            if (action.size() == 0) // player stands
                  player->stand();
            else
            {
                  switch (action[0])
                  {
                  default:                    // if bad move, nobody moves
                        cout << '\a' << endl; // beep
                        continue;
                  case 'q':
                        return;
                  case 'u':
                  case 'd':
                  case 'l':
                  case 'r':
                        player->moveOrAttack(decodeDirection(action[0]));
                        break;
                  }
            }
            m_mesa->moveGarks();
            m_mesa->display();
      }
}