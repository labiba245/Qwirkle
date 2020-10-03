//
//  Board.cpp
//  board
//
//  Created by Labiba Islam on 1/5/19.
//  Copyright © 2019 Labiba Islam. All rights reserved.
//

#include "Board.h"

int Board::getSize()
{
    return (int)board.size();
}

Tile *Board::getTile(int row, int col)
{
    Tile *tile = nullptr;
    if (row < getSize() && col < getSize())
    {
        tile = board[row][col];
    }
    return tile;
}
void Board::setTile(int row, int col, Tile *tile)
{
    if (row < getSize() && col < getSize())
    {
        board[row][col] = tile;
    }
}

//to make an empty grid of size nxn. it has initially all nullpointers
//which can be later replaced with pointer to tiles
Board::Board(int size, std::ostream *outputStream)
{
    this->outputStream = outputStream;
    for (int i = 0; i < size; i++)
    {
        std::vector<Tile *> row;
        for (int j = 0; j < size; j++)
        {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

// Makes the board expand diagonally
void Board::reSize()
{
    int bsize = getSize();
    if (bsize < 26)
    {
        for (int i = 0; i < getSize(); i++)
        {
            board[i].push_back(nullptr);
        }
        std::vector<Tile *> row;
        for (int j = 0; j <= getSize(); j++)
        {
            row.push_back(nullptr);
        }
        board.push_back(row);
    }
}

//this is to display the grid
void Board::display()
{
    int n = (int)board.size();
    *outputStream << "   ";
    // shows the top most row conatining integers b0 , 1 2 and so on
    for (int k = 0; k < n; k++)
        if (k < 10)
        {
            *outputStream << k << "  ";
        }
        else
            *outputStream << k << " ";
    *outputStream << "\n  ";
    for (int t = 0; t < n; t++)
        *outputStream << "---";
    *outputStream << std::endl;
    // loops to print the vector of vectors
    for (int i = 0; i < n; i++)
    {
        *outputStream << (char)('A' + i) << " |";
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != nullptr)
            {
                //Behaves differently whether the outstream is to the terminal or a file
                if (this->outputStream != &std::cout)
                {

                    *outputStream << this->getTile(i, j)->getColour() << this->getTile(i, j)->getShape();
                }
                else
                {
                    this->getTile(i, j)->printColoured();
                }
                *outputStream << "|";
            }
            else
                *outputStream << "  |";
        }
        *outputStream << std::endl;
    }
}

std::string Board::toString()
{

    std::string output = "";
    int n = (int)board.size();
    // loops to print the vector of vectors
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != nullptr)
            {
                std::string colour(1, this->getTile(i, j)->getColour());
                output.append(colour);
                output.append(std::to_string(this->getTile(i, j)->getShape()));
                output.append("|");
            }
            else{
                output.append("  |");
            }
        }
        output.append("\n");
    }
    return output;
}