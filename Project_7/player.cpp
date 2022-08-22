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
class Player
{
public:
      // Constructor
      Player(Mesa *mp, int r, int c);

      // Accessors
      int row() const;
      int col() const;
      int age() const;
      bool isDead() const;

      // Mutators
      void stand();
      void moveOrAttack(int dir);
      void setDead();

private:
      Mesa *m_mesa;
      int m_row;
      int m_col;
      int m_age;
      bool m_dead;
};

Player::Player(Mesa *mp, int r, int c)
{
      if (mp == nullptr)
      {
            cout << "***** The player must be created in some Mesa!" << endl;
            exit(1);
      }
      if (r < 1 || r > mp->rows() || c < 1 || c > mp->cols())
      {
            cout << "**** Player created with invalid coordinates (" << r
                 << "," << c << ")!" << endl;
            exit(1);
      }
      m_mesa = mp;
      m_row = r;
      m_col = c;
      m_age = 0;
      m_dead = false;
}

int Player::row() const
{
      // TODO: TRIVIAL:  Return the number of the  row the player is at.
      // Delete the following line and replace it with the correct code.
      return m_row; // This implementation compiles, but is incorrect.
}

int Player::col() const
{
      // TODO: TRIVIAL:  Return the number of the  column the player is at.
      // Delete the following line and replace it with the correct code.
      return m_col; // This implementation compiles, but is incorrect.
}

int Player::age() const
{
      // TODO:  TRIVIAL:  Return the player's age.
      // Delete the following line and replace it with the correct code.
      return m_age; // This implementation compiles, but is incorrect.
}

void Player::stand()
{
      m_age++;
}

void Player::moveOrAttack(int dir)
{
      m_age++;
      // TODO:  If there is a gark adjacent to the player in the direction
      // dir, attack it.  Otherwise, move the player to that position if
      // possible (i.e., if the move would not be off the edge of the mesa).
      bool answer = m_mesa->determineNewPosition(m_row, m_col, dir);
      if (answer == true && (m_mesa->numGarksAt(m_row, m_col)) >= 1)
      {
            m_mesa->attackGarkAt(m_row, m_col, dir);
            switch (dir)
            {
            case 0:
                  m_row++;
                  break;
            case 1:
                  m_row--;
                  break;
            case 2:
                  m_col++;
                  break;
            case 3:
                  m_col--;
                  break;
            }
      }
}

bool Player::isDead() const
{
      // TODO:  TRIVIAL:  Return whether the player is dead.
      if (m_dead)
      {
            return true;
      }
      else
      {
            return false;
      }
      // This implementation compiles, but is incorrect.
}

void Player::setDead()
{
      m_dead = true;
}