# include <iostream>
using namespace std;
# include <string>

int main()
{
      //initialize all the inputs and data
      int startDate = 0;
      int endDate = 0;
      int rentalDays = 0;
      string customerName = "";
      string car = "";
      int month = 0;

      // sentences show on the screen to allow user's input
      cout << "Odometer at start: " ;
      cin >> startDate;
      cout << "Odometer at end: " ;
      cin >> endDate;
      cout << "Rental days: ";
      cin >> rentalDays;
      cin.ignore(10000, '\n'); 
      cout << "Customer name: ";
      getline(cin, customerName);
      cout << "Luxury car? (y/n): ";
      getline(cin, car);
      cout << "Month (1=Jan, 2=Feb, etc.): ";
      cin >> month;

      //setup basic numbers for calculation
      double baseCharge = 0.0;
      int totalMiles = endDate - startDate;
      double first100 = 0.0;
      double second400 = 0.0;
      double beyond500 = 0.0;
      double result = 0.0;

      //print the three hyphens
      cout << "---" << endl;

      //test if there is any invalide numbers
      if(startDate < 0)
      {
            cout << "The starting odometer reading must not be negative." ;
            return 1;
      }
      else if(endDate < startDate)
      {
            cout << "The ending odometer reading must be at least as large as the starting reading.";
            return 1;
      }
      else if(rentalDays <= 0)
      {
            cout << "The number of rental days must be positive.";
            return 1;
      }
      else if(customerName == "")
      {
            cout << "You must enter a customer name.";
            return 1;
      }
      else if(car != "y" && car != "n")
      {
            cout << "You must enter y or n.";
            return 1;
      }
      else if(month < 1 || month > 12)
      {
            cout << "The month number must be in the range 1 through 12.";
            return 1;
      }
      else
      {
            if(car == "n")  //test if it is normal car or not
            {
                  baseCharge = 43 * rentalDays;

            }
            else
            {
                  baseCharge = 71 * rentalDays;
            }

            if(totalMiles <= 100)  //test if the total miles are equal or smaller than 100
            {
                  first100 = totalMiles * 0.27;
            } 
            else if (totalMiles <= 500)  //test if the totel miles are between 100 and 500
            {
                  first100 = 27;  //the money spend for the first 100 miles 
                  if(month > 3 && month < 12)
                  {
                        second400 = (totalMiles - 100) * 0.21;
                  }
                  else
                  {
                        second400 = (totalMiles - 100) * 0.27;
                  }
            }
            else  //other cases
            {
                  first100 = 27;
                  if(month > 3 && month < 12)
                  {
                        second400 = 400 * 0.21;
                  }
                  else
                  {
                        second400 = 400 * 0.27;
                  }
                  beyond500 = (totalMiles - 500) * 0.17;
            }

            //calculate the ultimate result
            result = baseCharge + first100 + second400 + beyond500;
            cout.setf(ios::fixed);
            cout.precision(2);
            cout << "The rental charge for " << customerName << " is $" << result << endl;
      }
      return 0;
} 