#include "Tile.h"
#include "Bag.h"
#include "LinkedList.h"
#include <iostream>
#include <string>

#define HAND_LIMIT 6

using std::string;
class Player
{
public:
  Player(string name, std::ostream *outputStream);
  string getName();
  int getPoints();
  void setPoints(int i);
  void addPoints(int i);
  bool addTile(Tile *tile);
  bool drawTile(Bag bag); //Removing from bag, adding to hand bag.takeFirst()
  Tile *removeTile(char colour, int shape);
  void fillHand(Bag bag);             
  bool hasTile(char colour, int shape); 
  void printHand();                    
  string toString();
  bool replaceTile();
  bool isEmpty();

private:
  string name;
  int points;
  LinkedList *hand;
};