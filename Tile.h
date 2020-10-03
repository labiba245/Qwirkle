
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include "TileCodes.h"
#include <iostream>
// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
  Tile(Colour colour, Shape shape, std::ostream *outputStream);
  Tile();
  void printTile();
  Colour getColour();
  Shape getShape();
  // Prints the color and shape with color in the terminal.
  void printColoured();

private:
  Colour colour;
  Shape shape;
  std::ostream *outputStream = &std::cout;
};

#endif // ASSIGN2_TILE_H
