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
class Gark
{
public:
      // Constructor
      Gark(Mesa *mp, int r, int c);

      // Accessors
      int row() const;
      int col() const;

      // Mutators
      void move();
      bool getAttacked(int dir);

private:
      Mesa *m_mesa;
      int m_row;
      int m_col;
      int m_attack;
      // TODO: You'll probably find that a gark object needs an additional
      // data member to support your implementation of the behavior affected
      // by being attacked.
};



///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////
Gark::Gark(Mesa *mp, int r, int c)
{
      if (mp == nullptr)
      {
            cout << "***** A gark must be created in some Mesa!" << endl;
            exit(1);
      }
      if (r < 1 || r > mp->rows() || c < 1 || c > mp->cols())
      {
            cout << "***** Gark created with invalid coordinates (" << r << ","
                 << c << ")!" << endl;
            exit(1);
      }
      m_mesa = mp;
      m_row = r;
      m_col = c;
      m_attack = 0;
}

int Gark::row() const
{
      return m_row;
}

int Gark::col() const
{
      // TODO: TRIVIAL:  Return the number of the column the gark is at.
      // Delete the following line and replace it with the correct code.
      return m_col; // This implementation compiles, but is incorrect.
}

void Gark::move()
{
      // Attempt to move in a random direction; if it can't move, don't move
      int dir = randInt(0, NUMDIRS - 1); // dir is now UP, DOWN, LEFT, or RIGHT

      // TODO:  Attempt to move in direction dir; if it can't move, don't move.
      m_mesa->determineNewPosition(m_row, m_col, dir);
}

bool Gark::getAttacked(int dir) // return true if dies
{
      if (m_attack == 1)
      {
            return true;
      }
      else
      {
            bool answer = m_mesa->determineNewPosition(m_row, m_col, dir);
            if (answer == false)
            {
                  m_attack++;
                  return true;
            }
            else
            {
                  m_attack++;
                  switch(dir)
                  {
                        case 0:
                              m_row ++;
                              break;
                        case 1:
                              m_row --;
                              break;
                        case 2:
                              m_col ++;
                              break;
                        case 3:
                              m_col --;
                              break;
                  }
                  return false;
            }
      }
      // TODO:  If the gark has been attacked once before, return true
      // (since a second attack kills a gark).  Otherwise, if possible,
      // move the gark one position in direction dir and return false
      // (since it survived the attack).  Otherwise, do not move, but return
      // true (since stepping back causes the gark to die by falling off the
      // mesa).
      // This implementation compiles, but is incorrect.
}

