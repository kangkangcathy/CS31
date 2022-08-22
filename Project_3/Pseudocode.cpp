# include <iostream>
using namespace std;
# include <string>
# include "grid.h"
# include "grid.cpp"

int main()
{
      if (r,c) is not valid (not empty, or dir is not a dir letter, or maxstep is negative,)
      {
            return 1;
      }
      else
      {
            int countstep = 0;
            for (keep walking in the maze)
            {
                  if(the poitn is not a wall)
                  {
                        countstep ++;
                  }
                  else
                  {
                        break;
                  }
            }
            return countstep;
      }
      
      return 0;
} 

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
      if((sr,sc) or (er,ec) is not valid empty grid position || dir is not a direction letter || plan is not right || )
      {
            return 2;
            nsteps unchanged; 
      }
      else if()
      else if(determineSafeDistance(sr, sc, dir, nsteps) < nsteps)
      {
            & nsteps = determineSafeDistance(sr, sc, dir, nsteps);
            return 3;
      }

      
}