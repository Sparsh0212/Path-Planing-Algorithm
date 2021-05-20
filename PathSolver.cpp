#include "PathSolver.h"
#include <iostream>
#include <algorithm>

PathSolver::PathSolver()
{

    this->nodesExplored = nullptr;
    this->OpenList = nullptr;
    this->tempList = nullptr;
    minDistVal = 0;

    this->minPath = nullptr;
}

PathSolver::~PathSolver()
{

    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env)
{

    nodesExplored = new NodeList();
    OpenList = new NodeList();
    tempList = new NodeList();

    Node *nodeValue = nullptr;
    Node *goalValue = nullptr;

    for (int i = 0; i < ENV_DIM; i++)
    {

        for (int j = 0; j < ENV_DIM; j++)
        {

            if (env[i][j] == SYMBOL_START)
            {
                nodeValue = new Node(i, j, 0);
            }
            if (env[i][j] == SYMBOL_GOAL)
            {
                goalValue = new Node(i, j, 0);
            }
        }
    }

    OpenList->addElement(nodeValue);

    bool pos = false;

    int posX = nodeValue->getRow();
    int posY = nodeValue->getCol();
    int goalX = goalValue->getRow();
    int goalY = goalValue->getCol();

    Node *newNode = nullptr;
    Node *n1 = nullptr;
    Node *n2 = nullptr;
    Node *n3 = nullptr;

    int minDistance1 = 0;
    int minDistance2 = 0;
    int minDistance3 = 0;
    int minDistance4 = 0;

    while (!pos)
    {

        Node *smallVal = findMinDistanceNode(goalValue);

        posX = smallVal->getRow();
        posY = smallVal->getCol();

        if ((env[goalX + 1][goalY] == SYMBOL_WALL) &&
            (env[goalX - 1][goalY] == SYMBOL_WALL) &&
            (env[goalX][goalY + 1] == SYMBOL_WALL) &&
            (env[goalX][goalY - 1] == SYMBOL_WALL))
        {
            std::cout << " Goal location is surrounded by walls on 4 sides " << std::endl;
            pos = true;
        }

        if ((env[posX][posY + VAL_ONE] == SYMBOL_EMPTY) || (env[posX][posY + 1] == SYMBOL_GOAL))
        {

            int valY = posY + 1;
            int valX = posX;

            n1 = nullptr;

            n1 = new Node(valX, valY, smallVal->getDistanceTraveled() + VAL_ONE);

            if (OpenList->checkNode(n1) == true)
            {
                n1 = nullptr;
            }
            else
            {
                minDistance1 = n1->getEstimatedDist2Goal(goalValue);

                OpenList->addElement(n1);
            }
        }

        if ((env[posX][posY - VAL_ONE] == SYMBOL_EMPTY) || (env[posX][posY - VAL_ONE] == SYMBOL_GOAL))
        {

            int valY = posY - VAL_ONE;
            int valX = posX;

            n2 = nullptr;

            n2 = new Node(valX, valY, smallVal->getDistanceTraveled() + VAL_ONE);
            if (OpenList->checkNode(n2) == true)
            {

                n2 = nullptr;
            }
            else
            {
                minDistance2 = n2->getEstimatedDist2Goal(goalValue);
                OpenList->addElement(n2);
            }
        }

        if ((env[posX + VAL_ONE][posY] == SYMBOL_EMPTY) || (env[posX + VAL_ONE][posY] == SYMBOL_GOAL))
        {
            int valX = posX + VAL_ONE;
            int valY = posY;

            n3 = nullptr;

            n3 = new Node(valX, valY, smallVal->getDistanceTraveled() + VAL_ONE);
            if (OpenList->checkNode(n3) == true)
            {
                n3 = nullptr;
            }
            else
            {
                minDistance3 = n3->getEstimatedDist2Goal(goalValue);
                OpenList->addElement(n3);
            }
        }

        if ((env[posX - 1][posY] == SYMBOL_EMPTY) || (env[posX - VAL_ONE][posY] == SYMBOL_GOAL))
        {

            int valX = posX - VAL_ONE;
            int valY = posY;

            newNode = nullptr;
            newNode = new Node(valX, valY, smallVal->getDistanceTraveled() + 1);

            if (OpenList->checkNode(newNode) == true)
            {
                newNode = nullptr;
            }
            else
            {
                minDistance4 = newNode->getEstimatedDist2Goal(goalValue);
                OpenList->addElement(newNode);
            }
        }

        if ((env[posX + VAL_ONE][posY] == SYMBOL_WALL) &&
            (env[posX - VAL_ONE][posY] == SYMBOL_WALL) &&
            (env[posX][posY + VAL_ONE] == SYMBOL_WALL) &&
            (env[posX][posY - VAL_ONE] == SYMBOL_WALL))
        {
            std::cout << "No path Possible location is surrounded by walls on 4 sides " << std::endl;
            pos = true;
        }

        nodesExplored->addElement(smallVal);

        if (smallVal->getRow() == goalValue->getRow() && smallVal->getCol() == goalValue->getCol())
        {
            pos = true;
        }
    }

  
    delete newNode;
    delete nodeValue;
    delete goalValue;
    delete n1;
    delete n2;
    delete n3;
}

NodeList *PathSolver::getNodesExplored()
{

    return nodesExplored;
}

NodeList *PathSolver::getPath(Env env)
{

    Node *goalValue = nullptr;
    Node *startValue = nullptr;
    minPath = new NodeList();
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            if (env[i][j] == SYMBOL_GOAL)
            {
                goalValue = new Node(i, j, 0);
            }
            if (env[i][j] == SYMBOL_START)
            {
                startValue = new Node(i, j, 0);
            }
        }
    }

    Node *nValue = nodesExplored->getNode(nodesExplored->getLength() - 1);

    Node *b = nullptr;
    int posX = startValue->getRow();
    int posY = startValue->getCol();
    int goalX = goalValue->getRow();
    int goalY = goalValue->getCol();

    bool check = false;

    while (!check)
    {
        if(env[posX + VAL_ONE][posY] == SYMBOL_WALL &&
        (env[posX][posY + VAL_ONE] == SYMBOL_WALL)  &&
        (env[posX - VAL_ONE][posY] == SYMBOL_WALL) &&
        (env[posX][posY - VAL_ONE]  == SYMBOL_WALL)){
            check = true;
        }

        if(env[goalX + VAL_ONE][goalY] == SYMBOL_WALL &&
        (env[goalX][goalY + VAL_ONE] == SYMBOL_WALL)  &&
        (env[goalX - VAL_ONE][goalY] == SYMBOL_WALL) &&
        (env[goalX][goalY - VAL_ONE]  == SYMBOL_WALL)){
            check = true;
        }
       

        b = getMinNodePath(nValue, env);

        if (b->getDistanceTraveled() - startValue->getDistanceTraveled() == VAL_ONE)
        {
            check = true;
        }

        else
        {
            nValue = nullptr;
            nValue = new Node(*b);

            b = nullptr;
        }
    }

    delete goalValue;
    delete startValue;

    return nodesExplored;
}

Node *PathSolver::findMinDistanceNode(Node *nValues)
{
    Node *newValue = new Node(*nValues);
    Node *temp = nullptr;

    for (int i = 0; i < OpenList->getLength(); i++)
    {

        if (!(nodesExplored->checkNode(OpenList->getNode(i))))
        {
            if (!(tempList->checkNode(OpenList->getNode(i))))
            {
                tempList->addElement(OpenList->getNode(i));
            }
        }
    }

    for (int i = 0; i < tempList->getLength(); i++)
    {
        if (!(nodesExplored->checkNode(tempList->getNode(i))))
        {
            if (tempList->getLength() == 1)
            {

                temp = tempList->getNode(0);

                minDistVal = tempList->getNode(0)->getEstimatedDist2Goal(newValue);
                return temp;
            }
            else
            {

                if (tempList->getNode(i)->getEstimatedDist2Goal(newValue) <= minDistVal)
                {

                    minDistVal = tempList->getNode(i)->getEstimatedDist2Goal(newValue);
                    temp = nullptr;
                    temp = tempList->getNode(i);
                    return temp;
                }
            }
        }
    }

    for (int i = 0; i < tempList->getLength(); i++)
    {
        if (!(nodesExplored->checkNode(tempList->getNode(i))))
        {
            if (tempList->getNode(i)->getEstimatedDist2Goal(newValue) >= minDistVal)
            {
                minDistVal = tempList->getNode(i)->getEstimatedDist2Goal(newValue);
                temp = nullptr;
                temp = tempList->getNode(i);
                return temp;
            }
        }
    }

    return temp;
}

Node *PathSolver::getMinNodePath(Node *n, Env env)
{
    Node *c = new Node(*n);
    Node *temp = nullptr;

    for (int i = nodesExplored->getLength() - 1; i > 0; i--)
    {

        if ((c->getDistanceTraveled() - nodesExplored->getNode(i)->getDistanceTraveled()) == VAL_ONE)
        {
            if (nodesExplored->getNode(i)->getRow() == c->getRow())
            {
                if (abs(nodesExplored->getNode(i)->getCol() - c->getCol()) == VAL_ONE)
                {
                    minPath->addElement(nodesExplored->getNode(i));
                }
            }
            else
            {
                if (nodesExplored->getNode(i)->getCol() == c->getCol())
                {
                    if (abs(nodesExplored->getNode(i)->getRow() - c->getRow()) == VAL_ONE)
                    {
                        minPath->addElement(nodesExplored->getNode(i));
                    }
                }
            }
        }
    }

    for (int i = 0; i < minPath->getLength(); i++) // temp path for arrow print
    {

        if ((c->getRow() - minPath->getNode(i)->getRow() == VAL_ONE) &&
            (c->getCol() == minPath->getNode(i)->getCol()) &&
            ((c->getDistanceTraveled() - minPath->getNode(i)->getDistanceTraveled()) == VAL_ONE))
        {
            temp = nullptr;
            temp = minPath->getNode(i);

            env[temp->getRow()][temp->getCol()] = MOVE_DOWN;

            return temp;
        }

        if ((minPath->getNode(i)->getRow() - c->getRow()) == VAL_ONE &&
            (c->getCol() == minPath->getNode(i)->getCol()) &&
            ((c->getDistanceTraveled() - minPath->getNode(i)->getDistanceTraveled()) == VAL_ONE))
        {
            temp = nullptr;
            temp = minPath->getNode(i);

            env[temp->getRow()][temp->getCol()] = MOVE_UP;

            return temp;
        }

        if ((c->getCol() - minPath->getNode(i)->getCol()) == VAL_ONE &&
            (c->getRow() == minPath->getNode(i)->getRow()) &&
            ((c->getDistanceTraveled() - minPath->getNode(i)->getDistanceTraveled()) == VAL_ONE))
        {
            temp = nullptr;
            temp = minPath->getNode(i);
            // Arrow
            env[temp->getRow()][temp->getCol()] = MOVE_RIGHT;

            return temp;
        }

        if (((minPath->getNode(i)->getCol() - c->getCol()) == VAL_ONE) &&
            (c->getRow() == minPath->getNode(i)->getRow()) &&
            ((c->getDistanceTraveled() - minPath->getNode(i)->getDistanceTraveled()) == VAL_ONE))
        {
            temp = nullptr;
            temp = minPath->getNode(i);
            //Arrow
            env[temp->getRow()][temp->getCol()] = MOVE_LEFT;

            return temp;
        }
    }

    return temp;
}

//-----------------------------