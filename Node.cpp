#include <iostream>
#include "Node.h"
#include "Tile.h"

// Node *next;
// Tile tile;

Node::Node(Tile *tile, Node *next)
{
  this->next = next;

  this->tile = tile;
}

Node::Node(Node &other)
{
  // TODO
}

Node *Node::getNext()
{
  return next;
}

Tile *Node::getValue()
{
  return tile;
}

void Node::setNext(Node *newNext)
{
  next = newNext;
}