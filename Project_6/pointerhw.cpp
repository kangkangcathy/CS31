#include <iostream>
using namespace std;
#include <string>
#include <iostream>
using namespace std;
/*
double mean(const double *scores, int numScores)
{
      const double *ptr = scores;
      double tot = 0;
      while (ptr != scores + numScores)
      {
            cout << *ptr<< endl;
            tot += *ptr;
            ptr++;
      }
      return tot / numScores;
}
*/
double mean(const double *scores, int numScores)
{
      double tot = 0;
      for(int i = 0; i < numScores; i ++)
      {
            tot += *(scores +i);
      }
      return tot / numScores;
}

int main()
{
      double a[3] = {1.5, 2.5, 2.0};
      cout << mean(a, 3);

}
