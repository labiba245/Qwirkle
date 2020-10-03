
// Sam Hoch, s3721859
// Labiba islam s3694372
// Md Abir Ishtiaque s3677701
/* Duncan Do s3718718 */
#include <iostream>
#include "qwirkle.h"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{

  std::istream *inputStream;
  std::ostream *outputStream;

  std::ofstream outputTest;
  std::ifstream inputTest;

  if (argc == 3)
  {
    outputTest.open(argv[2]);
    inputTest.open(argv[1]);
    inputStream = &inputTest;
    outputStream = &outputTest;
  }
  else
  {
    inputStream = &cin;
    outputStream = &cout;
  }
  // LinkedList* list = new LinkedList();
  // delete list;

  qwirkle game = qwirkle(inputStream, outputStream);

  std::string menuInputs[4] = {"1", "2", "3", "4"};
  std::string menuInput = "";

  while (menuInput != menuInputs[3])
  {
    *outputStream << "Welcome to Qwirkle!" << endl;
    *outputStream << "-------------------" << endl;
    *outputStream << "Menu" << endl;
    *outputStream << "----" << endl;
    *outputStream << "1. New Game" << endl;
    *outputStream << "2. Load Game" << endl;
    *outputStream << "3. Show student information" << endl;
    *outputStream << "4. Quit" << endl;
    *outputStream << "> ";
    getline(*inputStream, menuInput);
    if (inputStream->eof())
    {
      game.quit();
    }
    if (menuInput == menuInputs[0])
      game.newGame();
    else if (menuInput == menuInputs[1])
      game.loadGame();
    else if (menuInput == menuInputs[2])
    {
      game.studentInformation();
    }
    else if (menuInput == menuInputs[3])
      game.quit();
    else
      *outputStream << "Invalid Input" << endl;
  }
  return EXIT_SUCCESS;
}