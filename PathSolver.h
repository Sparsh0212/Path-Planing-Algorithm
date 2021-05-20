#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

#define VAL_ONE    1

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
      
      
     
      Node* findMinDistanceNode(Node* nValue);  //gets the minimum estimated distance node to goal
      Node* getMinNodePath(Node* n, Env env);    // gets the node which will make the shortest path to goal
     


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;
    NodeList* OpenList;     // list of positions reachable from from source
    NodeList* tempList;      // temprory list
    NodeList* minPath;      //  get the minimum path possible to reach goal
    int minDistVal;       // minimum estimated distance variable

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER