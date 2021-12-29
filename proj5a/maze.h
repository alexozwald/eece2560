//
// Created by Alex Oswald on 12/7/21.
//
#ifndef PROJ5A_MAZE_H
#define PROJ5A_MAZE_H

#include <iostream>
#include <limits.h>
#include "d_except.h"
#include <list>
#include <fstream>
#include <queue>
#include "d_matrix.h"
#include "graph.h"
#include <vector>  
#include <algorithm>

using namespace std;

/********************** MAZE CLASS **********************/

class maze
{
   public:
      maze(ifstream &fin);
      void print(int, int, int, int);
      bool isLegal(int i, int j);

      void setMap(int i, int j, int n);    // i=x, j=y,  n=node id
      int getMap(int i, int j) const;      // i=x, j=y --> get node id
      void mapMazeToGraph(graph &g);

      //Alex functions
      /**** Additions for algo implementation ****/
      void bfs(graph &g, int node1, int node2);
      void dfs(graph &g, int node1, int node2);
      vector<int> do_bfs(graph& g, int, int);
      void        do_dfs(graph& g, vector<int>& ids, int, int);
      void printPath(graph& g, vector<int> ids) const;
      vector<int> getCoord(graph& g, int n) const;
      vector<int> getAdjEdges(graph& g, int n);

   private:
      int rows; // number of rows in the maze
      int cols; // number of columns in the maze

      matrix<bool> value;
      matrix<int> map;      // Mapping from maze (i,j) values to node index values
};

void maze::setMap(int i, int j, int n)
// Set mapping from maze cell (i,j) to graph node n.
{
    map[i][j] = n;
}

int maze::getMap(int i, int j) const
// Return mapping of maze cell (i,j) in the graph.
{
    return map[i][j];
}

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;  //cout << rows << endl;  // DEBUG
   fin >> cols;  //cout << cols << endl;  // DEBUG

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
          fin >> x;
          if (x == 'O')
              value[i][j] = true;
          else
              value[i][j] = false;
      }

   map.resize(rows,cols);
}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows-1 || goalJ < 0 || goalJ > cols-1)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows-1 || currJ < 0 || currJ > cols-1)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze.
{
   if (i < 0 || i > rows-1 || j < 0 || j > cols-1)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

/**************** Start proj5a Additions ****************/

// Create a graph g that represents the legal moves in the maze m.
void maze::mapMazeToGraph(graph &g)
{
    int n;
    // add nodes
    for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
            if (isLegal(i,j))
            {
                n = g.addNode(1);    // get node id
                setMap(i, j, n);        // sets node id on graph
            }
            else  // graph nodes that arent present with 0 NodeWeight
            {
                n = g.addNode(0);
                setMap(i,j,n);
            }
		}
	}

    // add edges  (non-directional)
    for (int i = 0; i < value.rows(); i++) {        // i = current row
		for (int j = 0; j < value.cols(); j++) {    // j = current col
            // look for edge ABOVE
            if (i-1 >= 0   &&  value[i-1][j] && value[i][j] && !g.isEdge(getMap(i, j), getMap(i-1, j)))
            {
                int node1 = getMap(i-1, j);  // alt node
                int node2 = getMap(i, j);  // curr node
                g.addEdge(node1, node2, 1);
                g.addEdge(node2, node1, 1);
            }
            else if (i-1 >= 0  &&  !g.isEdge(getMap(i, j), getMap(i-1, j))) //make empty edge between value[i-1][j], (while a real node)
            {
                int node1 = getMap(i-1,j);
                int node2 = getMap(i,j);
                g.addEdge(node1, node2, 0);
                g.addEdge(node2, node1, 0);
            }

            // look for edge RIGHT
            if (j+1 < cols  &&  value[i][j+1] && value[i][j] && !g.isEdge(getMap(i, j), getMap(i, j+1)))
            {
                int node1 = getMap(i, j+1);  // alt node
                int node2 = getMap(i, j);  // curr node
                g.addEdge(node1, node2, 1);
                g.addEdge(node2, node1, 1);
            }
            else if (j+1 < cols  &&  !g.isEdge(getMap(i, j), getMap(i, j+1))) //make empty edge between value[i][j+1], (while a real node)
            {
                int node1 = getMap(i,j+1);
                int node2 = getMap(i,j);
                g.addEdge(node1, node2, 0);
                g.addEdge(node2, node1, 0);
            }

            // look for edge BELOW
            if (i+1 < rows  &&  value[i+1][j] && value[i][j] && !g.isEdge(getMap(i, j), getMap(i+1, j)))
            {
                int node1 = getMap(i+1, j);  // alt node
                int node2 = getMap(i, j);  // curr node
                g.addEdge(node1, node2, 1);
                g.addEdge(node2, node1, 1);
            }
            else if (i+1 < rows  &&  !g.isEdge(getMap(i, j), getMap(i+1, j))) //make empty edge between value[i+1][j], (while a real node)
            {
                int node1 = getMap(i+1,j);
                int node2 = getMap(i,j);
                g.addEdge(node1, node2, 0);
                g.addEdge(node2, node1, 0);
            }

            // look for edge LEFT
            if (j-1 >= 0   &&  value[i][j-1] && value[i][j] && !g.isEdge(getMap(i, j), getMap(i, j-1)))
            {
                int node1 = getMap(i, j-1);  // alt node
                int node2 = getMap(i, j);  // curr node
                g.addEdge(node1, node2, 1);
                g.addEdge(node2, node1, 1);
            }
            else if (j-1 >= 0  &&  !g.isEdge(getMap(i, j), getMap(i, j-1))) //make empty edge between value[i][j-1], (while a real node)
            {
                int node1 = getMap(i,j-1);
                int node2 = getMap(i,j);
                g.addEdge(node1, node2, 0);
                g.addEdge(node2, node1, 0);
            }
        }
	}
}

//The get coordinate function retrieves the proper coord for the maze
vector<int> maze::getCoord(graph& g, int n) const
{
    vector<int> coord;
    for (int i=0;  i<rows;  i++)
        for (int j=0;  j<cols;  j++)
            if (getMap(i,j) == n)
            {
                coord.push_back(i);
                coord.push_back(j);
            }

    if (!coord.empty())
        return coord;
    else if (n == 0)
    {
        coord.push_back(0);
        coord.push_back(0);
        return coord;
    }
    else
    {
        cout << "[node " << n << "] node not found while getting coordinates.";
        exit(3);
    }
}

vector<int> maze::getAdjEdges(graph& g, int n)
{
    // get list of all nodes that are adjacent edges  (only track the nodes)
    vector<int> adjEdgeNodes;
    for (int x=0;  x<g.numNodes();  x++)
        if ((x != n)  &&  g.isEdge(x, n)  &&  (1==g.getEdgeWeight(x, n) || 1==g.getEdgeWeight(n,x)))
            adjEdgeNodes.push_back(x);

    return adjEdgeNodes;
}

/*********** Addition for Algo Implementation ***********/

void maze::bfs(graph &g, int node1, int node2)
{
    // formatting
    cout << "Executing Breadth-First-Search (BFS) algorithm between nodes " << node1 << " and node " << node2 << "!" << endl;
    cout << "Map between designated nodes...  (+: start,  *: end)" << endl;
    // gen map between points
    int iGoal, jGoal, iStart, jStart;
    vector<int> ijTemp = getCoord(g, node1);
    iGoal = ijTemp[0];   jGoal = ijTemp[1];
    ijTemp = getCoord(g, node2);
    iStart = ijTemp[0];  jStart = ijTemp[1];
    print(iGoal, jGoal, iStart, jStart);
    cout << "Working ..." << endl;

    // execution
    vector<int> bfsNodeOrder;
    bfsNodeOrder = do_bfs(g, node1, node2);
    printPath(g, bfsNodeOrder);
}
void maze::dfs(graph &g, int node1, int node2)
{
    // clear all prior to recursion
    g.clearMark();
    g.clearVisit();

    // formatting
    cout << "Executing Depth-First-Search (DFS) algorithm between nodes " << node1 << " and node " << node2 << "!"
         << endl;
    cout << "Map between designated nodes...  (+: start,  *: end)" << endl;
    // gen map between points
    int iGoal, jGoal, iStart, jStart;
    vector<int> ijTemp = getCoord(g, node1);
    iGoal = ijTemp[0];   jGoal = ijTemp[1];
    ijTemp = getCoord(g, node2);
    iStart = ijTemp[0];  jStart = ijTemp[1];
    print(iGoal, jGoal, iStart, jStart);
    cout << "Working ..." << endl;

    // execution
    vector<int> dfsNodeOrder;
    do_dfs(g, dfsNodeOrder, node1, node2);
    printPath(g, dfsNodeOrder);
}
void maze::printPath(graph& g, vector<int> ids) const
{
    vector<vector<int>> id_coords;
    for (int x = 0; x < ids.size() - 1; x++)
    {
        id_coords.push_back(getCoord(g, ids[x]));
    }
    // Start tracking the values along path ++ print info
    vector <int> curr_loc = id_coords[0], prev_loc;
    for (int y=0;  y<id_coords.size(); y++)
    {
        prev_loc = curr_loc;
        curr_loc = id_coords[y];

        // is first
        if (y == 0)
            cout << "Starting position at (" << curr_loc[0] << "," << curr_loc[1] << ") via node " << ids[y] << endl;
        // is last
        else if (y+1 == id_coords.size())
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << "." << endl
                 << "The maze has been traversed in " << ids.size() << " moves!" << endl;
        // is UP
        else if ( prev_loc[0] == (curr_loc[0]+1)  &&  prev_loc[1] ==  curr_loc[1]    )
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << ".  Move Up a node" << endl;
        // is RIGHT
        else if ( prev_loc[0] ==  curr_loc[0]     &&  prev_loc[1] == (curr_loc[1]-1) )
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << ".  Move Right a node" << endl;
        // is DOWN
        else if ( prev_loc[0] == (curr_loc[0]-1)  &&  prev_loc[1] ==  curr_loc[1]    )
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << ".  Move Down a node" << endl;
        // is LEFT
        else if ( prev_loc[0] ==  curr_loc[0]     &&  prev_loc[1] == (curr_loc[1]+1) )
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << ".  Move Left a node" << endl;
        //else
        else
            cout << "(" << prev_loc[0] << "," << prev_loc[1] << ") --> (" << curr_loc[0] << "," << curr_loc[1] << ")"
                 << " from node " << ids[y-1] << " to " << ids[y] << ".  \n";
        //     << ;
    }

    cout << "Node transit list:  ";
    for (int x=0;  x<ids.size()-1;  x++)
        cout << ids[x] << ", ";
    cout << ids[ids.size()-1] << "." << endl;
}


// NOT-Recursive Implementation of BFS (breadth-first search)
vector<int> maze::do_bfs(graph& g, int v1, int v2)
{
    // ordered list of nodes visited
    vector<int> nodeIDList;
    //mark all vertices as unvisited
    g.clearMark();

    // push the starting vertex into the queue
    queue<int> q;
    q.push(v1);

    //while the queue is not empty
    int v = q.front();
    while (!q.empty())
    {
        //set v = ____front of queue____;
        v = q.front();
        q.pop();
        g.mark(v);   // marks node as marked
        g.visit(v);  // marks node as visited
                        // g.visit(i, j) marks edge as visited
        nodeIDList.push_back(v);

        if (v == v2)
            return nodeIDList;

        // get list of all nodes that are adjacent via an edges
        vector<int>adjEdgeNodes;
        adjEdgeNodes = getAdjEdges(g, v);

        // for each unvisited neighbor w of v
        for (int w=0;  w<adjEdgeNodes.size();  w++)
        {
            if (g.getEdgeWeight(v, adjEdgeNodes[w])  &&  !g.isMarked(adjEdgeNodes[w]))
            {
                g.mark(adjEdgeNodes[w]);
                q.push(adjEdgeNodes[w]);
            }
        }
    }
    return nodeIDList;
}

// Recursive Implementation of DFS (depth-first search)
void maze::do_dfs(graph& g, vector<int>& ids, int v1, int v2)
{
    g.mark(v1);
    g.visit(v1);
    ids.push_back(v1);

    vector<int> adjEdges;
    adjEdges = getAdjEdges(g, v1);

    // for all directed edges from v to w that are in G.adjacentEdges(v) do
    for (int x=0;  x<adjEdges.size(); x++)
        // if vertex w is not labeled as discovered then
        if (g.getEdgeWeight(v1, adjEdges[x])  &&  !g.isMarked(adjEdges[x]))
            //recursively call DFS(G, w)
            do_dfs(g, ids, adjEdges[x], v2);

}

/*
// Recursive Implementation of DFS (depth-first search)
void maze::do_dfs(graph& g, vector<int>& ids, int sourceID, int destID)
{
    //g.numNodes(); = destination ID
    //Marks the current source ID in the graph
    g.mark(sourceID);
    g.visit(sourceID);
    //If it has reached the dest ID it prints that a path is found
    if (g.isVisited(sourceID) && destID == sourceID)
    {
        cout << "A path to complete the maze exists" << endl;
        abort();
    }
    else
    {
        //Moves to the next best possible adjacent node through recursion
        //Goes in left right up down depending on edge weight
        //Also will only change source ID if it has not been there before
        //This is to avoid rerouting to bad routes
        //If right node is on the path
        int nextSourceID;
        //To the right
        if (g.getNodeWeight(sourceID + 1) == 1 && !g.isMarked(sourceID + 1))
        {
            nextSourceID = sourceID + 1;
        }
        //To the left
        else if(g.getNodeWeight(sourceID - 1) == 1 && !g.isMarked(sourceID - 1))
        {
            nextSourceID = sourceID - 1;
        }
        //Upwards
        else if (g.getNodeWeight(sourceID - rows) == 1 && !g.isMarked(sourceID - rows))
        {
            nextSourceID = sourceID + rows;
        }
        //Downwards
        else if (g.getNodeWeight(sourceID + rows) == 1 && !g.isMarked(sourceID + rows))
        {
            nextSourceID = sourceID + rows;
        }
        //DestID remains the same
        //returns true if the next node isn't visited and the recursive call is true
        if (!g.isVisited(nextSourceID))
        {
            ids.push_back(sourceID);
            do_dfs(g, ids, nextSourceID, destID);
        }
    }
}
*/

#endif //PROJ5A_MAZE_H
