
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node
{
public:
  Node(Tile *tile, Node *next);
  Node(Node &other);
  Node *getNext();
  Tile *getValue();
  void setNext(Node *newNext);

  Tile *tile;
  Node *next;
};

#endif // ASSIGN2_NODE_H
