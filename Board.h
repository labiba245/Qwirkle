//
//  Board.h
//  game
//
//  Created by Labiba Islam on 8/5/19.
//  Copyright © 2019 Labiba Islam. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Tile.h"

#define MAX_BOARD_SIZE 26;

class Board
{
public:
  std::vector<std::vector<Tile *>> board; 
  //board is a vector of vectors holding tile pointers. so we can dymanically allocate the tiles and store them in the grid
  Board(int size, std::ostream *outputStream);
  void display();
  int getSize();
  Tile *getTile(int row, int col);
  void setTile(int row, int col, Tile *tile);
  std::string toString();
  void reSize();
  std::ostream *outputStream = &std::cout;
};
#endif /* Board_h */