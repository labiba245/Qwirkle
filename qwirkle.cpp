
// Sam Hoch, s3721859
// Labiba Islam s3694372
// Md Abir Ishtiaque s3677701
// Duncan Do s3718718

//Input format:
//place <tileCode> at <boardPosition>
//replace <tileCode>
#include "qwirkle.h"
#include <cctype>
#include <stdexcept>
#include <cmath>

#define EXIT_SUCCESS 0

using std::cin;
using std::endl;

qwirkle::qwirkle()
{
  this->outputStream = &std::cout;
  this->inputStream = &std::cin;
}

qwirkle::qwirkle(std::istream *inputStream)
{
  this->inputStream = inputStream;
}

qwirkle::qwirkle(std::istream *inputStream, std::ostream *outputStream)
{
  this->inputStream = inputStream;
  this->outputStream = outputStream;
}

// qwirkle::~qwirkle()
// {
// }

void qwirkle::studentInformation()
{
  *outputStream << "Name: Duncan Do\nStudent Number: s3718718\nEmail: s3718718@student.rmit.edu.au" << endl
                << "\nName: Sam Hoch\nStudent Number: s3721859\nEmail: s3721859@student.rmit.edu.au" << endl
                << "\nName: Labiba Islam\nStudent Number: s3694372\nEmail: s3694372@student.rmit.edu.au" << endl
                << "\nName: Md Abir Ishtiaque\nStudent Number: s3677701\nEmail: s3677701@student.rmit.edu.au" << endl;
}

void qwirkle::newGame()
{
  this->firstMove = true;
  this->firstTurn = true;
  this->gameOver = false;
  numPlayers = 0;
  *outputStream << "Starting a New Game" << endl;
  *outputStream << "How many players? (2-4)" << endl;
  *outputStream << "> ";
  //inputStream->clear();
  //inputStream->ignore();
  *inputStream >> numPlayers;
  if (inputStream->eof())
  {
    quit();
  }
  while (numPlayers < 2 || numPlayers > 4)
  {
    *outputStream << "\nInvalid input. Enter an integer between 2 and 4" << endl;
    *outputStream << "> ";
    *inputStream >> numPlayers;
    if (inputStream->eof())
    {
      quit();
    }
  }

  this->bag = std::make_shared<Bag>(*(new Bag(outputStream)));
  this->board = std::make_shared<Board>(*(new Board(6, outputStream)));

  for (int i = 0; i < numPlayers; ++i)
  {
    bool valid = false;
    std::string name = "invalid";

    while (!valid)
    {
      *outputStream << "Enter a name for player " << i + 1 << " (Only uppercase characters)" << endl
                    << "> ";
      inputStream->ignore();
      *inputStream >> std::noskipws >> name;
      if (inputStream->eof())
      {
        quit();
      }

      if (validUserName(name))
      {
        this->players[i] = std::make_shared<Player>(*(new Player(name, outputStream)));
        this->players[i]->fillHand(*this->bag);
        valid = true;
      }
      else
      {
        *outputStream << "Invalid username, please only enter uppercase characters" << endl;
      }
    }
  }
  *outputStream << "Players for the game are \n";
  for (int i = 0; i < numPlayers; i++)
    *outputStream << "Player " << i + 1 << " : " + this->players[i]->getName() + "\n";

  turn = 0;
  *outputStream << "Starting new game \n";
  while (!this->gameOver)
  {
    this->newTurn(false);
  }
  this->endGame();
}

void qwirkle::endGame()
{
  *outputStream << "Game over" << endl;
  int highestPoints = this->players[0]->getPoints();
  std::string winningPlayerName = this->players[0]->getName();
  for (int i = 0; i < numPlayers; i++)
  {
    if (this->players[i]->getPoints() > highestPoints)
    {
      winningPlayerName = this->players[i]->getName();
    }
    *outputStream << "Score for " << this->players[i]->getName() << ": " 
    << this->players[i]->getPoints() << endl;
  }
  *outputStream << "Player " << winningPlayerName << " won!\n"
                << endl;

  quit();
}

void qwirkle::loadGame()
{
  *outputStream << "Please enter save file name (relative path)" << endl;
  *outputStream << "> ";
  std::string fileName;
  //inputStream->ignore();

  std::getline(*inputStream, fileName);

  if (inputStream->eof())
  {
    quit();
  }
  std::string saveData = "";

  *outputStream << "filename = " << fileName << endl;
  std::ifstream inFile;
  inFile.open(fileName);
  while (!inFile.eof())
  {
    std::string temp = "";
    std::getline(inFile, temp);
    saveData.append(temp);
    saveData.append("\n");
  }
  inFile.close();

  int boardStart = saveData.find("|") - 2;
  std::string playerData = saveData.substr(0, boardStart);
  int boardEnd = saveData.substr(boardStart, saveData.length()).find("$");
  std::string boardData = saveData.substr(boardStart, boardEnd);
  std::string finalData = saveData.substr(playerData.length() + boardEnd + 2, saveData.length());
  int bagEnd = finalData.find("\n");
  std::string bagData = finalData.substr(0, bagEnd);
  std::string currentPlayerName = finalData.substr(bagEnd + 1, finalData.length());

  std::vector<std::string> bagString = splitString(bagData, ", ");

  std::vector<std::string> playersDataString = splitString(playerData, "$\n");

  std::vector<std::string> boardString = splitString(boardData, "|");

  //bag
  std::vector<Tile *> bagContents = getTileVectorFromStringVector(bagString);
  //players
  std::vector<Player *> playersList = getPlayerVectorFromStringVector(playersDataString);

  //                initialization
  //board
  this->setBoardState(boardString);
  //bag
  this->bag = std::make_shared<Bag>(*(new Bag(outputStream)));
  for (unsigned int i = 0; i < bagContents.size(); ++i)
  {
    this->bag->addTile(bagContents[i]);
  }
  this->numPlayers = 0;
  currentPlayerName = currentPlayerName.substr(0, currentPlayerName.find("\n"));
  for (unsigned int i = 0; i < playersList.size(); ++i)
  {
    this->players[i] = std::make_shared<Player>(*playersList[i]);
    if (playersList[i] != nullptr)
    {
      this->numPlayers++;
    }

    if (currentPlayerName == this->players[i]->getName())
    {
      turn = i;
    }
  }
  this->gameOver = false;
  while (!gameOver)
  {
    this->newTurn(true);
  }
  this->endGame();
}
/*
Looping logic referenced: 
  https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
  */

void qwirkle::setBoardState(std::vector<std::string> input)
{
  bool unchanged = true;
  int boardLength = std::sqrt(input.size() - 1);
  this->board = std::make_shared<Board>(*(new Board(boardLength, outputStream)));
  for (unsigned int i = 0; i < input.size(); ++i)
  {

    if (input[i] != "  " && input[i] != "\n  " && input[i] != "\n")
    {
      unchanged = false;
      Tile *tile = makeTileFromString(input[i]);
      int row = i / boardLength;
      int col = i % boardLength;
      this->board->setTile(row, col, tile);
    }
  }
  if (unchanged)
  {
    this->firstTurn = true;
    this->firstMove = true;
  }
  else
  {
    this->firstTurn = false;
    this->firstMove = false;
  }
}

std::vector<std::string> qwirkle::splitString(std::string input, std::string delim)
{
  std::vector<std::string> output;
  unsigned int position = 0;
  std::string datum = "";
  bool endOfInput = false;
  while ((position = input.find(delim)) != std::string::npos && !endOfInput)
  {
    if (input != "")
    {
      datum = input.substr(0, position);
      output.push_back(datum);
      input.erase(0, position + delim.length());
    }
    else
    {
      endOfInput = true;
    }
  }
  return output;
}

std::vector<Tile *> qwirkle::getTileVectorFromStringVector(std::vector<std::string> input)
{
  std::vector<Tile *> output;
  for (std::string tileString : input)
  {
    output.push_back(makeTileFromString(tileString));
  }
  return output;
}

std::vector<Player *> qwirkle::getPlayerVectorFromStringVector(std::vector<std::string> input)
{
  std::vector<Player *> output;
  for (unsigned int i = 0; i < input.size(); ++i)
  {
    output.push_back(makePlayerFromString(input[i]));
  }
  return output;
}

Tile *qwirkle::makeTileFromString(std::string input)
{
  char c = 'a';
  char *tileCol = &c;
  input.substr(0, 1).copy(tileCol, 1);
  int tileShape = std::stoi(input.substr(1, input.length()));
  Tile *tile = new Tile(*tileCol, tileShape, outputStream);

  return tile;
}

Player *qwirkle::makePlayerFromString(std::string input)
{
  std::vector<std::string> playerData = splitString(input, "\n");
  Player *player = new Player(playerData[0], outputStream);
  player->setPoints(std::stoi(playerData[1]));
  std::vector<Tile *> hand = getTileVectorFromStringVector(splitString(playerData[2], ", "));
  for (unsigned int i = 0; i < hand.size(); i++)
  {
    player->addTile(hand[i]);
  }

  return player;
}

void qwirkle::quit()
{
  *outputStream << "Goodbye" << endl;
  exit(0);
}

void qwirkle::loadFile(std::string fileName)
{
  *outputStream << "loading file with filename " << fileName << endl;
}

/*
Code References for newTurn:
    String splitting using delimiter: 
        https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c 
    
    String to int conversion (stoi):
        https://www.systutorials.com/131/convert-string-to-int-and-reverse/

    String to char conversion (copy):
        https://www.techiedelight.com/convert-string-char-array-cpp/
*/


void qwirkle::newTurn(bool loadGame)
{
  *outputStream << "Player " << this->players[turn]->getName() << "\'s turn " << endl;
  for (int i = 0; i < numPlayers; i++)
    *outputStream << this->players[i]->getName() << ": " << this->players[i]->getPoints() << "\n";
  this->board->display();
  *outputStream << "Your hand is" << endl;
  if (this->players[turn] != nullptr)
  {

    if (this->outputStream != &std::cout)
    {
      *outputStream << this->players[turn]->toString() << endl;
    }
    else
    {
      this->players[turn]->printHand();
    }
  }
  std::string input;
  bool validInput = false;
  bool errorPrint = false;
  while (!validInput)
  {
    *outputStream << "> ";
    
    
    /*
    firstTurn checks whether it is the program's first run,
    and provides special functionality to other methods
    
    loadGame is true or false depending on whether newTurn is 
    being run from the loadGame method, only necessary for input validation/capture
    
    firstMove is a special case for when the user replaces 
    on the first turn, only necessary for input validation/capture

    errorPrint notifies whether or not an error message has just been 
    printed, only necessary for input validation/capture
    
    */
    if (this->firstTurn && !loadGame && this->firstMove && !errorPrint)
    {
      inputStream->ignore();
    }

    errorPrint = false;
    std::getline(*inputStream, input);
    if (inputStream->eof())
    {
      quit();
    }
    int commandEnd = input.find(' ');
    std::string command = input.substr(0, commandEnd);
    std::string args = input.substr(commandEnd + 1, input.length());
    if (inputStream->eof())
    {
      quit();
    }
    if (command == "place")
    {
      try
      {
        if (args.length() < 8 || args.length() > 9)
        {
          *outputStream << "Invalid command format, enter 'help' for list of valid commands";
        }
        else
        {
          std::string tileString = args.substr(0, 2);
          std::string positionString = args.substr(6);
          Colour tileCol = tileString[0];
          Shape tileShape = std::stoi(tileString.substr(1));
          int placeRow = getIntFromChar(positionString[0]);
          int placeCol = std::stoi(positionString.substr(1));

          validInput = true;
          
          int moveScore = validateMove(tileCol, tileShape, placeRow, placeCol);

          if (moveScore > 0 && this->players[turn]->hasTile(tileCol, tileShape))
          {
            
            Tile *t = this->players[turn]->removeTile(tileCol, tileShape);  
          
            this->board->setTile(placeRow, placeCol, t);
            this->players[turn]->addPoints(moveScore);
            if (!this->bag->isEmpty())
            {
              this->players[turn]->addTile(this->bag->pullTile());
            }
            else if (this->players[turn]->isEmpty())
            {
              gameOver = true;
            }
            changeTurn();
            firstTurn = false;
            this->firstMove = false;
          }
          else
          {
            *outputStream << "Invalid move\n";
          }
        }
      }
      catch (const std::invalid_argument &e)
      {
        *outputStream << "Invalid arguments! To place a tile you must enter 'place <tile> at <grid location>'" << endl;
      }
      catch (const std::out_of_range &e)
      {
        *outputStream << "Out of range!" << endl;
      }
      validInput = true;
    }
    else if (command == "replace")
    {
      try
      {
        char test3 = 'c';
        char *tileCol = &test3;
        args.substr(0, 1).copy(tileCol, 1);
        Shape tileShape = std::stoi(args.substr(1, 2));

        if (!this->bag->isEmpty())
        {
          Tile *t = this->players[turn]->removeTile(*tileCol, tileShape);
          Tile *pulledTile = this->bag->pullTile();
          this->players[turn]->addTile(pulledTile);
          this->bag->addTile(t);
          changeTurn();
          this->firstMove = false;
        }
        validInput = true;
      }
      catch (const std::invalid_argument &e)
      {
        *outputStream << "Invalid arguments! To place a tile you must enter 'replace <tile>'";
      }
    }

    else if (command == "save")
    {
      this->saveGame(args);
    }
    else if (command == "help")
    {
      *outputStream << " --------List of valid commands------------" << endl;
      *outputStream << "place <tileCode> at <boardPosition> to place a tile in the board" << endl;
      *outputStream << "replace <tileCode> to replace a tile from your hand" << endl;
      *outputStream << "save <filename> to save game" << endl;
      *outputStream << "^D to quit game" << endl;
      errorPrint = true;
    }
    else if (command == "")
    {
      validInput = false;
    }

    else
    {
      *outputStream << "command \"" << command << "\" unknown. Type 'help' to see list of availabe commands." << endl;
      validInput = false;
      errorPrint = true;
    }
  }
}

int qwirkle::validateMove(char colour, int shape, int row, int col)
{
  int moveScore = 0;
  bool allTestsTrue = true;
  //Checks whether the desired board location is within bounds
  if (row >= 0 && row < this->board->getSize() && col >= 0 && col < this->board->getSize())
  {
    //For each direction
    for (int d = 1; d <= 4; d++)
    {

      int colModifier = 0;
      int rowModifier = 0;

      if (d == UP && row - 1 >= 0)
        rowModifier = -1;
      else if (d == DOWN && row + 1 < this->board->getSize()) //down
        rowModifier = 1;
      else if (d == RIGHT && col + 1 < this->board->getSize()) // right
        colModifier = 1;
      else if (d == LEFT && col - 1 >= 0) //left
        colModifier = -1;

      if (colModifier != 0 || rowModifier != 0)
      {
        //If there is a tile next to the desired board location
        if (this->board->getTile(row + rowModifier, col + colModifier) != nullptr)
        {
          //Calculate score for the placement
          int tempScore = validateLine(colour, shape, row, col, rowModifier, colModifier);
          //If score == 0, the placement is invalid
          if (tempScore == 0)
          {
            allTestsTrue = false;
          }
          //Else add the points
          else
          {
            moveScore += tempScore;
          }
        }
      }
    }
  }
  //Edge case if statements
  //Runs if outside board location
  else
  {
    allTestsTrue = false;
  }
  //Runs if a previous test fails
  if (!allTestsTrue)
  {
    moveScore = 0;
  }
  //Runs if it is the first turn
  if (firstTurn)
  {
    moveScore = 1;
  }
  //Runs if the board needs to resize as a result of the placement
  if (moveScore > 0 && (row == this->board->getSize() - 1 ||
   col == this->board->getSize() - 1))
  {
    this->board->reSize();
  }

  return moveScore;
}

int qwirkle::validateLine(char colour, int shape, int row, int col,
 int rowModifier, int colModifier)
{
  bool validPlacement = true;
  int bSize = this->board->getSize();
  Tile *oneStep = this->board->getTile(row + rowModifier, col + colModifier);
  Tile *twoStep = nullptr;
  //Checks whether the 'twoStep' neighbour will be out of bounds
  if (row + (2 * rowModifier) >= 0 && row + (2 * rowModifier) < bSize && col +
   (2 * colModifier) >= 0 && col + (2 * colModifier) < bSize)
  {
    twoStep = this->board->getTile(row + (2 * rowModifier), col + (2 * colModifier));
  }
  //Runs when there is a 'twoStep' neighbour
  if (twoStep != nullptr)
  {
    //Checks whether the line is a shape line
    if (oneStep->getColour() != twoStep->getColour())
    {
      //Check tile based on shape
      if (oneStep->getShape() != shape)
      {
        validPlacement = false;
      }
    }
    //Checks whether the line is a colour line
    else if (oneStep->getShape() != twoStep->getShape())
    {
      //Check tile based on colour
      if (oneStep->getColour() != colour)
      {
        validPlacement = false;
      }
    }
  }
  //Runs when there is no 'twoStep' neighbour
  else
  {
    //Checks whether the tile doesn't match either shape or colour
    if (oneStep->getColour() != colour && oneStep->getShape() != shape)
    {
      validPlacement = false;
    }
  }

  bool keepChecking = true;
  int currentRow = row + rowModifier;
  int currentCol = col + colModifier;
  int numTiles = 1;
  while (keepChecking && currentRow > 0 && currentRow < bSize &&
   currentCol > 0 && currentCol < bSize)
  {

    Tile *currentTile = this->board->getTile(currentRow, currentCol);
    //If line is not over
    if (currentTile != nullptr)
    {
      //Checks if a tile is a duplicate of input tile
      if (currentTile->getColour() == colour && currentTile->getShape() == shape)
      {
        validPlacement = false;
      }
      currentRow += rowModifier;
      currentCol += colModifier;
      numTiles++;
    }
    //If line is over
    else
    {
      keepChecking = false;
    }
  }
  //Sets score to 0, or a fail state if any tests failed
  if (!validPlacement)
  {
    numTiles = 0;
  }
  //Runs when a qwirkle has been performed
  if (numTiles == 6)
  {
    *outputStream << "Qwirkle!" << endl;
    numTiles = 12;
  }
  return numTiles;
}

void qwirkle::saveGame(std::string saveFile)
{
  //Construct huge string of the save file
  std::string saveData = "";
  std::string player1Data = "";
  std::string boardData = "";
  std::string bagData = "";

  for (int i = 0; i < numPlayers; i++)
  {
    player1Data.append(players[i]->getName());
    player1Data.append("\n");
    player1Data.append(std::to_string(players[i]->getPoints()));
    player1Data.append("\n");
    player1Data.append(players[i]->toString());
    player1Data.append("$");

    //*outputStream << player1Data << endl;
    saveData.append(player1Data);
    saveData.append("\n");
    player1Data = "";
  }

  bagData.append(this->bag->toString());
  boardData.append(this->board->toString());
  boardData.append("$");

  saveData.append(boardData);
  saveData.append("\n");
  saveData.append(bagData);
  saveData.append("\n");
  saveData.append(this->players[turn]->getName());

  std::ofstream outFile;
  outFile.open(saveFile);
  outFile << saveData << endl;
  outFile.close();
}

int qwirkle::getIntFromChar(char c)
{
  int retVal = 0;
  if (isalpha(c))
  {
    retVal = c - 'A';
  }
  else
  {
    retVal = -1;
  }
  return retVal;
}

bool qwirkle::validUserName(std::string name)
{
  bool valid = true;
  for (char &c : name)
  {
    if (!isalpha(c))
    {
      valid = false;
    }
    if (c >= 'a' && c <= 'z')
    {
      valid = false;
    }
  }
  return valid;
}

void qwirkle::changeTurn()
{
  //this->firstTurn = false;
  turn++;
  turn = turn % numPlayers;
}