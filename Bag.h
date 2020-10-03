#include <cstdlib>
#include "Tile.h"
#include "LinkedList.h"
class Bag
{
public:
  Bag(std::ostream *outputStream);
  int size();
  Tile *pullTile();
  void print();
  bool isEmpty();
  std::string toString();
  void addTile(Tile *tile);

private:
  LinkedList *tileList;
  Colour colours[6] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  Shape shapes[6] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};
  void getShuffledBag();
  std::ostream *outputStream;
};