
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>
#include <iostream>

class LinkedList
{
public:
  LinkedList();
  LinkedList(std::ostream *outputStream);
  ~LinkedList();
  void add(Tile *tile);
  Tile *takeTile(char colour, int shape);
  Tile *get(char colour, int shape);
  Tile *takeFirst();
  void printList();
  void shuffle();
  int getSize();
  void deleteAll();
  std::string toString();
  bool isEmpty();

private:
  Node *head;
  Node *tail;
  std::ostream *outputStream;
};

#endif // ASSIGN2_LINKEDLIST_H
