#include "Node.h"
#include <iostream>
#include <cstdlib>

Node::Node(int row, int col, int dist_traveled)
{

    this->col = col;
    this->dist_traveled = dist_traveled;
    this->row = row;
}

Node::Node(Node &n) : row(n.row), col(n.col), dist_traveled(n.dist_traveled)
{
}

Node::~Node()
{
}

int Node::getRow()
{

    return this->row;
}

int Node::getCol()
{

    return this->col;
}

int Node::getDistanceTraveled()
{

    return this->dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{

    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node *goal)
{

    int Manhatten_Distance = (abs(getCol() - goal->getCol()) + abs(getRow() - goal->getRow()));
    return dist_traveled + Manhatten_Distance;
}

//--------------------------------