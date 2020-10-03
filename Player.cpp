#include <cstdlib>
#include <string>
#include <iostream>
#include "Player.h"

using std::cout;
using std::endl;
using std::string;

Player::Player(string name, std::ostream *outputStream)
{
    this->name = name;
    this->hand = new LinkedList(outputStream);
    points = 0;
}

string Player::getName()
{
    return name;
}

int Player::getPoints()
{
    return points;
}

void Player::addPoints(int i)
{
    points += i;
}

void Player::setPoints(int i)
{
    points = i;
}

bool Player::addTile(Tile *tile)
{
    hand->add(tile);
    return true;
}

bool Player::drawTile(Bag bag)
{
    Tile *t = bag.pullTile();
    return addTile(t);
}

Tile *Player::removeTile(char colour, int shape)
{
    return hand->takeTile(colour, shape);
}

void Player::fillHand(Bag bag)
{
    int i = 0;
    while (i < HAND_LIMIT)
    {
        drawTile(bag);
        i++;
    }
}

bool Player::hasTile(char colour, int shape)
{
    bool result = false;
    if (hand->get(colour, shape) != nullptr)
        result = true;
    return result;
}

void Player::printHand()
{
    hand->printList();
}

string Player::toString()
{
    return hand->toString();
}

bool Player::isEmpty()
{
    return this->hand->isEmpty();
}