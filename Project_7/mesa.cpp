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
class Mesa
{
public:
      // Constructor/destructor
      Mesa(int nRows, int nCols);
      ~Mesa();

      // Accessors
      int rows() const;
      int cols() const;
      Player *player() const;
      int garkCount() const;
      int numGarksAt(int r, int c) const;
      bool determineNewPosition(int &r, int &c, int dir) const;
      void display() const;

      // Mutators
      bool addGark(int r, int c);
      bool addPlayer(int r, int c);
      bool attackGarkAt(int r, int c, int dir);
      bool moveGarks();

private:
      int m_rows;
      int m_cols;
      Player *m_player;
      Gark *m_garks[MAXGARKS];
      int m_nGarks;
};

Mesa::Mesa(int nRows, int nCols)
{
      if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
      {
            cout << "***** Mesa created with invalid size " << nRows << " by "
                 << nCols << "!" << endl;
            exit(1);
      }
      m_rows = nRows;
      m_cols = nCols;
      m_player = nullptr;
      m_nGarks = 0;
}

Mesa::~Mesa()
{
      // TODO:  Delete the player and all remaining dynamically allocated garks.
      delete m_player;
      int num = m_nGarks;
      for (int i = 0; i < num; i++)
      {
            delete m_garks[i];
            m_nGarks--;
      }
}

int Mesa::rows() const
{
      // TODO:  TRIVIAL:  Return the number of rows in the mesa.
      // Delete the following line and replace it with the correct code.
      return m_rows; // This implementation compiles, but is incorrect.
}

int Mesa::cols() const
{
      // TODO:  TRIVIAL:  Return the number of columns in the mesa.
      // Delete the following line and replace it with the correct code.
      return m_cols; // This implementation compiles, but is incorrect.
}

Player *Mesa::player() const
{
      return m_player;
}

int Mesa::garkCount() const
{
      return m_nGarks;
}

int Mesa::numGarksAt(int r, int c) const
{
      // TODO:  Return the number of garks at row r, column c.
      int a = 0;
      for (int i = 0; i < m_nGarks; i++)
      {
            int row = m_garks[i]->row();
            int col = m_garks[i]->col();
            if (row == r && col == c)
            {
                  a++;
            }
      }
      return a; // This implementation compiles, but is incorrect.
}

bool Mesa::determineNewPosition(int &r, int &c, int dir) const
{
      // TODO:  If a move from row r, column c, one step in direction dir
      // would go off the edge of the mesa, leave r and c unchanged and
      // return false.  Otherwise, set r or c so that row r, column c, is
      // now the new position resulting from the proposed move, and
      // return true.
      switch (dir)
      {
            // TODO:  Implement the behavior if dir is UP.
      case 0:
            if (r <= 1)
            {
                  return false;
            }
            r--;
            break;
      case 1:
            if (r >= m_rows)
            {
                  return false;
            }
            r++;
            break;
      case 2:
            if (c <= 1)
            {
                  return false;
            }
            c--;
            break;
      case 3:
            if (c >= m_cols)
            {
                  return false;
            }
            c++;
            // TODO:  Implement the other directions.
            break;
      default:
            return true;
      }
      return true;
}

void Mesa::display() const
{
      // Position (row,col) in the mesa coordinate system is represented in
      // the array element grid[row-1][col-1]
      char grid[MAXROWS][MAXCOLS];
      int r, c;

      // Fill the grid with dots
      for (r = 0; r < rows(); r++)
            for (c = 0; c < cols(); c++)
                  grid[r][c] = '.';

      // Indicate each gark's position
      // TODO:  If one gark is at some grid point, set the char to 'G'.
      //        If it's 2 though 8, set it to '2' through '8'.
      //        For 9 or more, set it to '9'.
      int i = 0;
      if (m_garks[i] != nullptr)
      {
            while (i < m_nGarks)
            {
                  char &Char = grid[m_garks[i]->row() - 1][m_garks[i]->col() - 1];
                  if (Char == '.')
                  {
                        Char = 'G';
                  }
                  else if (Char == 'G')
                  {
                        Char = '2';
                  }
                  else if (Char >= '9')
                  {
                        Char = '9';
                  }
                  else
                  {
                        Char++;
                  }
                  i++;
            }
      }

      // Indicate player's position
      if (m_player != nullptr)
      {
            // Set the char to '@', unless there's also a gark there,
            // in which case set it to '*'.
            char &gridChar = grid[m_player->row() - 1][m_player->col() - 1];
            if (gridChar == '.')
                  gridChar = '@';
            else
                  gridChar = '*';
      }

      // Draw the grid
      clearScreen();
      for (r = 0; r < rows(); r++)
      {
            for (c = 0; c < cols(); c++)
                  cout << grid[r][c];
            cout << endl;
      }
      cout << endl;

      // Write message, gark, and player info
      cout << endl;
      cout << "There are " << garkCount() << " garks remaining." << endl;
      if (m_player == nullptr)
            cout << "There is no player." << endl;
      else
      {
            if (m_player->age() > 0)
                  cout << "The player has lasted " << m_player->age() << " steps." << endl;
            if (m_player->isDead())
                  cout << "The player is dead." << endl;
      }
}

bool Mesa::addGark(int r, int c)
{
      // If there are MAXGARKS garks, return false.  Otherwise,
      // dynamically allocate a new Gark at coordinates (r,c).  Save the
      // pointer to the newly allocated Gark and return true.
      if (m_nGarks == MAXGARKS)
      {
            return false;
      }
      else
      {
            m_garks[m_nGarks] = new Gark(this, r, c);
            m_nGarks++;
      }
      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXGARKS
      //!!!!! are added, then some are destroyed, then more are added.
      // TODO:  Implement this.
      return true; // This implementation compiles, but is incorrect.
}

bool Mesa::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
      if (m_player != nullptr)
            return false;

      // Dynamically allocate a new Player and add it to the mesa
      m_player = new Player(this, r, c);
      return true;
}

bool Mesa::attackGarkAt(int r, int c, int dir)
{
      // TODO:  Attack one gark at row r, column c if at least one is at
      // that position.  If the gark does not survive the attack, destroy the
      // gark object, removing it from the mesa, and return true.  Otherwise,
      // return false (no gark at (r,c), or gark didn't die).
      for (int i = 0; i < m_nGarks; i++)
      {
            if (m_garks[i]->row() == r && m_garks[i]->col() == c)
            {
                  bool answer = m_garks[i]->getAttacked(dir);
                  if (answer == true)
                  {
                        delete m_garks[i];
                        m_nGarks--;
                        return true;
                  }
            }
      }
      return false; // This implementation compiles, but is incorrect.
}

bool Mesa::moveGarks()
{
      for (int k = 0; k < m_nGarks; k++)
      {
            m_garks[k]->move();
            if (m_player->col() == m_garks[k]->col() && m_player->row() == m_garks[k]->row())
            {
                  m_player->setDead();
            }
            // TODO:  Have the k-th gark on the mesa make one move.
            //        If that move results in that gark being in the same
            //        position as the player, the player dies.
      }

      // return true if the player is still alive, false otherwise
      return !m_player->isDead();
}
