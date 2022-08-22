#include <iostream>
using namespace std;
#include <string>
#include <cassert>
#include "grid.h"


bool hasCorrectForm(string plan);

int determineSafeDistance(int r, int c, char dir, int maxSteps);

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int &nsteps);

int main()
{
      
      setSize(12, 15);
      setWall(1, 3);
      setWall(1, 4);
      setWall(1, 7);
      setWall(2, 1);
      setWall(2, 4);
      setWall(2, 11);
      setWall(3, 2);
      setWall(3, 5);
      setWall(3, 8);
      setWall(4, 6);
      setWall(5, 3);
      setWall(5, 6);
      setWall(7, 3);
      setWall(8, 8);
      setWall(9, 15);
      setWall(12, 11);
      setWall(10, 5);
      assert(hasCorrectForm("2R1r"));  //the plan is normal plan
      assert(hasCorrectForm("1r2L3llr23R")); // the plan is a complicated normal plan
      assert(hasCorrectForm(""));  // the plan is empty
      assert(hasCorrectForm("l"));  // the plan has zero digit
      assert(hasCorrectForm("R")); //the plan has upper alpha
      assert(hasCorrectForm("2l"));  // the plan has one digit
      assert(!hasCorrectForm("r2"));  // this is not the plan because it ends without direction
      assert(hasCorrectForm("llrrlrlr"));  // this is a normal plan without numbers
      assert(hasCorrectForm("12l"));  // the plan has two digits
      assert(!hasCorrectForm("l234r"));  // the plan has more than two digits
      assert(!hasCorrectForm("1r2"));  // the plan's last letter is a digit
      assert(!hasCorrectForm("2"));  //the plan is only one digit without direction
      assert(!hasCorrectForm("123"));  // the plan has more than two digits
      assert(!hasCorrectForm(" "));  // not a plan; composed of space
      assert(!hasCorrectForm("1l2R 3r"));  // not a plan; seperated by space
      assert(!hasCorrectForm(" 3rl1 "));  // not a plan; surrounded by space
      assert(!hasCorrectForm(",1l2r!")); // not a plan; surrounded b comma and other things
      assert(!hasCorrectForm("2rd1l"));  // not a plan because of d appeared in the plan
      assert(determineSafeDistance(1,3,'n', 2) == -1);  //the point(1,3) is a wall
      assert(determineSafeDistance(99, 2, 'w', 2) == -1);  // the point (99,2) is not valid in the maze
      assert(determineSafeDistance(2,199, 'w', 2) == -1);  // the point (2, 199) is not valie in the maze
      assert(determineSafeDistance(4, 2, 'd', 4) == -1);  // the dir'd' is not a correct direction
      assert(determineSafeDistance(4, 7, 'e', -2) == -1);  // the maxStep is negative 
      assert(determineSafeDistance(6, 12, 'w', 0) == 0);  //maxStep is 0
      assert(determineSafeDistance(8, 2, 'n', 10) == 4);  //during the moving process, it will meet a wall
      assert(determineSafeDistance(10, 6, 'W', 3) == 0);  // it cannot move to the left because the wall is on the left
      assert(determineSafeDistance(3, 1, 'w', 2) == 0);  // it cannot move to the left because that is out of the maze
      assert(determineSafeDistance(10, 15, 'e', 2) == 0); //it cannot move to the right because that is out of the maze
      assert(determineSafeDistance(4, 1, 'e', 4) == 4);  //go east and the plan is valid
      assert(determineSafeDistance(4, 1, 's', 5) == 5); //go south and the plan is valid
      assert(determineSafeDistance(8, 5, 'W', 3)== 3);  // go west and the plan is valid
      assert(determineSafeDistance(12, 6, 'n', 5) == 5); // go north and the plan is valid
      assert(determineSafeDistance(12, 6, 'N', 4) == 4); // go north with capital dir char
      int len = -999;
      assert(obeyPlan(8,2,8,4,'s',"ll2R2r2l", len) == 0 && len == 6); // it successfully follow all the steps to arrive at the expected point
      len = -999;
      assert(obeyPlan(12,1,1,10,'e', "9l11r",len) == 0 && len == 20); // the plan has two continuous number
      len = -999;
      assert(obeyPlan(12, 1, 1, 10, 'e', "fdfs", len) == 2 && len == -999); //the plan is not valid
      len = -999;
      assert(obeyPlan(8,2,8,4,'s', "ll2R2r3r", len) == 1 && len == 7); // it successfully follow the plan but is not end at the expected end point
      len = -999;
      assert(obeyPlan(99,2,8,2,'s', "ll2rlr", len) == 2 && len == -999); //the initial point is not available
      len = -999;
      assert(obeyPlan(2,3,99,3,'w', "ll2rl2r", len) == 2 && len == -999); //the end point is not available
      len = -999;
      assert(obeyPlan(2,4,8,4,'s', "llr2rl", len) == 2 && len == -999); // the initial point is a wall
      len = -999;
      assert(obeyPlan(2,2,3,2,'s', "lr2rlr1", len) == 2 && len == -999); // the end point is a wall
      len = -999;
      assert(obeyPlan(2,2,4,2,'d', "lllr2lll", len) == 2 && len == -999); // the direction char is not correct
      len = -999;
      assert(obeyPlan(2,2,4,2,'w', "234l", len) == 2 && len == -999); //the plan is not a correct plan
      len = -999;
      assert(obeyPlan(2,2,11,2,'w',"1lrl8r", len) == 3 && len == 0); // the plan will walk into a wall
      len = -999;
      assert(obeyPlan(12,1,1,5,'w', "rr9l11RRR3l", len) == 3 && len == 22); // the plan will walk into a wall
      cerr << "All tests succeeded" << endl;
      
      return 0;
}
bool hasCorrectForm(string plan)
{
      //find plan size
      int plansize = plan.size();
      bool result = true;
      //repeatedly
      for (int i = 0; i != plansize; i++)
      {
            //find if the next letter is R,r,L,or l
            if (plan.at(i) == 'R' || plan.at(i) == 'r' || plan.at(i) == 'L' || plan.at(i) == 'l' || isdigit(plan.at(i)))
            {
                  continue; // switch to the next round
            }
            else
            {
                  result = false;
                  break;
            }
      }
      // check whether there are 3 continuous letter that all of them are actually digits
      if (plansize >= 3)
      {
            for (int a = 0; a != plansize - 2; a++)
            {
                  if (isdigit(plan.at(a)) && isdigit(plan.at(a + 1)) && isdigit(plan.at(a + 2)))
                  {
                        result = false;
                        break;
                  }
            }
      }
      if(!(plan == "") && isdigit(plan.at(plansize-1)))
      {
            result = false;
      }

      return result;
}

int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
      //check if the point(r,c) or dir or maxSteps is not valid
      if (maxSteps < 0 || r > getRows() || r <= 0 || c > getCols() || c <= 0 || isWall(r, c) )
      {
            return -1;
      }
      else if (dir != 'N' && dir != 'n' && dir != 'S' && dir != 's' && dir != 'W' && dir != 'w' && dir != 'E' && dir != 'e')
      {
            return -1;
      }
      // if the point(r,c) or dir or maxSteps is valid
      else
      {
            int countstep = 0;
            // start to check the direction is north, south, west, or east
            //start to check the direction is north
            if (dir == 'N' || dir == 'n')
            {
                  //repeatedly check if (r,c) is valid and the total step is smaller than the maxSteps
                  while ((r > 0) && countstep < maxSteps)
                  {
                        if ((r > 1) && !isWall(r - 1, c)) // if the next point it will go is valid
                        {
                              //increase one step and change it present position
                              countstep++;
                              r--;
                        }
                        else  //if the next point it will go is not valid
                        {
                              break;  //stop moving and record the present steps
                        }
                  }
            }
            // the function is the same with the previous one, except that the direction is different and the change of position method is different
            //start to check the direction is south
            else if (dir == 'S' || dir == 's')
            {
                  while ((r <= getRows()) && countstep < maxSteps)
                  {
                        if ((r < getRows()) && !isWall(r + 1, c))
                        {
                              countstep++;
                              r++;
                        }
                        else
                        {
                              break;
                        }
                  }
            }
            //start to check the direction is west
            else if (dir == 'W' || dir == 'w')
            {
                  while ((c > 0) && countstep < maxSteps)
                  {
                        if (c - 1 >= 1 && !isWall(r, c - 1))
                        {
                              countstep++;
                              c--;
                        }
                        else
                        {
                              break;
                        }
                  }
            }
            //start to check the direction is east
            else
            {
                  while ((c <= getCols()) && countstep < maxSteps)
                  {
                        if ( c + 1 <= getCols()  && !isWall(r, c + 1))
                        {
                              countstep++;
                              c++;
                        }
                        else
                        {
                              break;
                        }
                  }
            }
            return countstep;  //return the recorded steps
      }
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int &nsteps)
{
      dir = tolower(dir);
      //check if the initial position, end position, dir, and plan are not valid
      if ( sr <= 0 || sc <= 0 || er <= 0 || ec <= 0 || 
      sr > getRows() || sc > getCols() || er > getRows() || ec > getCols()
      || isWall(sr, sc) || isWall(er, ec))
      {
            return 2;  //if yes, return 2 and end checking
      }
      else if (hasCorrectForm(plan) == false)
      {
            return 2;  //if yes, return 2 and end checking
      }
      else if (dir != 'N' && dir != 'n' && dir != 'S' && dir != 's' && dir != 'W' && dir != 'w' && dir != 'E' && dir != 'e')
      {
            return 2;  
      }
      else
      {
            string plancopy = "";
            int countstep = 0;
            //lower all the letters in original plan string
            for (int i = 0; i != plan.size(); i++)
            {
                  plancopy += tolower(plan.at(i));
            }
            for (int j = 0; j != plancopy.size(); j++)
            {
                  //repeatedly check the next char in plan is alpha or digit
                  if (isalpha(plancopy.at(j)))  //if the next char is alpha
                  {
                        //change direction according to the alpha
                        if (plancopy.at(j) == 'l')
                        {
                              if (dir == 'n')
                              {
                                    dir = 'w';
                              }
                              else if (dir == 's')
                              {
                                    dir = 'e';
                              }
                              else if (dir == 'w')
                              {
                                    dir = 's';
                              }
                              else if (dir == 'e')
                              {
                                    dir = 'n';
                              }
                        }
                        else
                        {
                              if (dir == 'n')
                              {
                                    dir = 'e';
                              }
                              else if (dir == 's')
                              {
                                    dir = 'w';
                              }
                              else if (dir == 'w')
                              {
                                    dir = 'n';
                              }
                              else
                              {
                                    dir = 's';
                              }
                        }
                  }
                  else
                  {
                        int num = 0;
                        if(isdigit(plancopy.at(j+1)))
                        {
                              num = (plancopy.at(j)-'0')* 10 + (plancopy.at(j+1) - '0');
                              j = j + 1;
                        }
                        else
                        {
                              num = plancopy.at(j) - '0';
                        }
                        //check if the moving with the maxSteps would step into wall or out of maze
                        int step = determineSafeDistance(sr, sc, dir, num);
                        countstep += step;
                        if (step < num)
                        {
                              nsteps = countstep;
                              return 3;  //yes, return 3 and end the loop
                        }
                        if (dir == 'n')
                        {
                              sr -= num;  //change current position according to the maxSteps
                        }
                        else if (dir == 's')
                        {
                              sr += num;  //change current position according to the maxSteps
                        }
                        else if (dir == 'w')
                        {
                              sc -= num;  //change current position according to the maxSteps
                        }
                        else
                        {
                              sc += num;  //change current position according to the maxSteps
                        }
                  }
            }
            if (sr == er && sc == ec)  //if the ultimate position is the same with the expected end position
            {
                  nsteps = countstep;  //record total steps
                  return 0;
            }
            else
            {
                  nsteps = countstep;  //record total steps
                  return 1;
            }
      }
}