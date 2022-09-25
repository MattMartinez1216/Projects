/* ADD IN ERROR HANDLING cin.good and .clear() for incorrect inputs?

  Program allows user to practice the multiplication tables
   from 1-12. The program asks a multiplication 
   problem, accepts an answer as input and tells
   the user whether their answer was correct or not.
   If the answer is incorrect it allows two other 
   attempts and then displays the correct answer.
*/

#include <iostream>
#include <ctime>
#include <limits>

using namespace std;

int main() {
  string exit_Option = "5";

  srand(time(NULL));
    
  cout << "Hello, Welcome to the times tables game. Press Enter to begin." << endl;

  cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

  while(!(exit_Option == "1")) {
    int multiplier_1 = rand()%12 + 1, multiplier_2 = rand()%12 + 1, 
    correct_Answer = multiplier_1 * multiplier_2, user_Answer,
    answer_Attempts = 2; 

    cout << "What is " << multiplier_1 << " x " << multiplier_2 << "?";
    
    cout << " Type your answer and press enter to submit your answer." << endl;

    cin >> user_Answer;

    while (!(answer_Attempts == 0)) {
    if ( user_Answer == correct_Answer) {
      cout << "Correct! Enter 1 to end game. Enter any ";
      cout << "other key to continue" << endl;

      answer_Attempts = 0;
      cin >> exit_Option;
    } else {
        cout << "Incorrect Answer. Try again, you have " << answer_Attempts;
        cout << " attempt(s) remaining." << endl;

        cout << "Type your answer and press enter to submit." << endl;

        cin >> user_Answer;

        if (!(user_Answer == correct_Answer)) {
          answer_Attempts = answer_Attempts - 1;
        }
          switch (answer_Attempts) {
            case 0: cout << "All attempts have been exhausted, ";
                    cout << "try again champ!" << endl;
                    cout << "Press 1 to end the game. Enter any other key to continue." << endl;
                    cin >> exit_Option;
          }
      }
    }
  }

  return 0;
}

