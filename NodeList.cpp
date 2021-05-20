#include "NodeList.h"
#include <iostream>

NodeList::NodeList()
{

    length = 0;
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = nullptr;
    }
}

NodeList::~NodeList()
{

    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        delete nodes[i];
        nodes[i] = nullptr;
    }
}

NodeList::NodeList(NodeList &other) : length(other.length)
{

    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++)
    {
        nodes[i] = new Node(*other.nodes[i]);
    }
}

int NodeList::getLength()
{

    return length;
}

void NodeList::addElement(Node *newPos)
{
    Node *n = new Node(*newPos);

    if (length < NODE_LIST_ARRAY_MAX_SIZE)
    {
        nodes[length] = n;
        length++;
    }
}

Node *NodeList::getNode(int i)
{
    Node *n;
    n = nullptr;
    if (i >= 0 && i < length)
    {
        n = nodes[i];
    }

    return n;
}

bool NodeList::checkNode(Node *nodeVal)
{

    for (int i = 0; i < length; i++)
    {

        if (nodes[i]->getRow() == nodeVal->getRow() &&
            nodes[i]->getCol() == nodeVal->getCol())

        {
            return true;
        }
    }
    return false;
}
