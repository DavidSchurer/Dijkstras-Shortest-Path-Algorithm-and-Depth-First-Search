// ---------------------------- graphm.cpp -----------------------------
// David Schurer
// CSS 343
// Creation Date: 4/27/2023
// Date of Last Modification: 5/5/2023
// ---------------------------------------------------------------------
// Purpose - The graphm.cpp file is the implementation file for the GraphM
// class. It contains the implementation of all of the methods defined in this
// class, such as insertEdge, removeEdge, findShortestPath, display, displayAll,
// etc. It also utilizes two recursive helper methods: recursivePathHelper
// and recursiveNodeDataHelper.
// ---------------------------------------------------------------------
// Notes - This class implements a graph date structure and also implements
// Dijkstra's shortest path algorithm to find the shortest path between all
// of the pairs of nodes in the graph. It starts at a source node and
// updates the distance and path for all of the neighbor nodes of the
// source node that are unvisited and chooses the neighbor node with
// the shortest distance to visit, the distances and paths are then updated
// for the neighbor nodes that are unvisited and this repeats until all the
// nodes in the graph have been visited. The graph is represented as an adjacency
// matrix in this implementation and recursion is used to help display the
// paths and node data of the graph.
// ---------------------------------------------------------------------
#include "graphm.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stack>
#include <climits>
using namespace std;

// ---------------------------------[Constructor]---------------------------------------------
// Description: The GraphM constructor initializes a new object of the GraphM
// class and initializes the visited, dist, and path data members for the
// nodes in the graph.
// -------------------------------------------------------------------------------------------
GraphM::GraphM() 
{
    // Iterate through the maximum number of nodes in the graph (100x100)
    for (int i = 0; i < GRAPHM_MAXNODES; i++)
    {
        for (int j = 0; j < GRAPHM_MAXNODES; j++)
        {
            // Each node's visited status is set to false
            T[i][j].visited = false;

            // Each node's distance is set to infinity
            T[i][j].dist = INT_MAX;

            // Each path between the nodes is set to 0
            T[i][j].path = 0;
        }
    }
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[buildGraph]----------------------------------------------
// Description: The buildGraph method for the GraphM class initialzes the graph
// by reading in the input data text file and storing the read in source and
// destination nodes, distances between nodes, and node data.
// -------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream &inputfile)
{
    // Initialize the variables for the data of each node, source node, destination node, and distance
    // between nodes
    string nodeData;
    int fromNode;
    int toNode;
    int distance;

    // Graph size is initialized to 0
    size = 0;

    // The adjacency matrix representation of the graph is initialized with all
    // the edge weights initialized to infinity
    for (int i = 0; i < GRAPHM_MAXNODES; i++)
    {
        for (int j = 0; j < GRAPHM_MAXNODES; j++)
        {
            C[i][j] = INT_MAX;
        }
    }

    // Graph size is read in from the input data file
    inputfile >> size;

    // If the size of the graph is 0, return
    if (size == 0) 
    {
        return;
    }

    // The data for each node in the graph is read in through the
    // input data text file and then stored in the NodeData array
    getline(inputfile, nodeData);

    for (int i = 1; i <= size; i++)
    {
        getline(inputfile, nodeData);
        data[i] = NodeData(nodeData);
    }

    // Infinite loop until source or destination node are read in as 0
    while (true)
    {
        // Input data text file reads in the source node, destination node, and distance between the nodes
        inputfile >> fromNode >> toNode >> distance;

        // If both nodes are not 0, store the distance read in as
        // the distance between the two nodes
        if (fromNode != 0 && toNode != 0)
        {
            C[fromNode][toNode] = distance;
        }
        
        // If either one of the nodes are 0, stop reading in input
        if (fromNode == 0 || toNode == 0)
        {
            break;
        }
    }
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[insertEdge]----------------------------------------------
// Description: The insertEdge method for the GraphM class is used to 
// insert an edge between two given nodes in the graph.
// -------------------------------------------------------------------------------------------
void GraphM::insertEdge(int fromNode, int toNode, int edgeWeight)
{
    // If the source node or destination node are not within the bounds of the graph, return
    if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
    {
        return;
    }
   
    // If the source node and destination node are within the bounds of the graph
    if ((fromNode <= size && fromNode >= 1) && (toNode <= size && toNode >= 1))
    {
        // Initialize the edge weight for the edge between the souce node and destination node
        C[fromNode][toNode] = edgeWeight;

        // Initialize the distance, path, and visited status of source node to destination node
        T[fromNode][toNode].dist = INT_MAX;
        T[fromNode][toNode].path = 0;
        T[fromNode][toNode].visited = false;
    }
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[removeEdge]----------------------------------------------
// Description: The removeEdge method for the GraphM class removes an edge
// between two given nodes by setting the edge weight between these nodes
// to infinity.
// -------------------------------------------------------------------------------------------
void GraphM::removeEdge(int fromNode, int toNode)
{
    // If the source node and destination node are within the bounds of the graph, set the edge weight from the source node
    // to the destination node as infinity
    if ((fromNode <= size && fromNode >= 1) && (toNode <= size && toNode >= 1))
    {
        C[fromNode][toNode] = INT_MAX;
    }

    // If the source node or destination node are outside of the bounds of the graph, return
    if (fromNode > size || fromNode < 1 || toNode > size || toNode < 1)
    {
        return;
    }
}
// -------------------------------------------------------------------------------------------


// ------------------------------[findShortestPath]-------------------------------------------
// Description: The findShortestPath method for the GraphM class finds the
// shortest path between all of the nodes in the graph using Dijkstra's
// shortest path algorithm. The algorithm works by starting from a source node
// and updating the distance and path for all the neighbor nodes before choosing
// the unvisited node with the shortest distance from the source node, then the distances
// and paths are updated for the neighbor nodes and the process repeats until all nodes
// are visited.
// -------------------------------------------------------------------------------------------
void GraphM::findShortestPath()
{
    for (int sourceNode = 1; sourceNode <= size; sourceNode++)
    {
        // The source node is set to visited and it's distance from itself is 0
        T[sourceNode][sourceNode].visited = true;
        T[sourceNode][sourceNode].dist = 0;

        // The distances and paths for the neighbor nodes of the source node are updated
        for (int neighborNode = 1; neighborNode <= size; neighborNode++)
        {
            // If there is not an edge from the source node to the neighbor node, skip that node
            if (C[sourceNode][neighborNode] == INT_MAX)
            {
                continue;
            }

            // If there is an edge from the source node to the neighbor node, update its distance and path
            if (C[sourceNode][neighborNode] != INT_MAX)
            {
                T[sourceNode][neighborNode].dist = C[sourceNode][neighborNode];
                T[sourceNode][neighborNode].path = sourceNode;
            }
        }

        // Iterate through all of the nodes that are unvisited in the graph
        for (int visitedNodesCount = 1; visitedNodesCount < size; visitedNodesCount++)
        {

            // Initialize the shortest distance to infinity and current node to 0
            int shortestDistance = INT_MAX;
            int currentNode = 0;

            // Find the unvisited node in the graph that has the shortest distance from the source node
            for (int unvisitedNode = 1; unvisitedNode <= size; unvisitedNode++)
            {
                // If the current shortest distance is larger than the distance from
                // the source node to the unvisited node
                if (shortestDistance > T[sourceNode][unvisitedNode].dist)
                {
                    if (T[sourceNode][unvisitedNode].visited == false)
                    {
                        // Set the new shortest distance and set unvisited node
                        // to current node
                        shortestDistance = T[sourceNode][unvisitedNode].dist;
                        currentNode = unvisitedNode;
                    }
                }
            }

            // The new current node is marked as visited
            T[sourceNode][currentNode].visited = true;

            // The distances and paths of the nodes adjacent to the current node will be updated
            for (int adjacentNode = 1; adjacentNode <= size; adjacentNode++)
            {
                // Check if there is an edge between the current and adjacent node
                if (C[currentNode][adjacentNode] != INT_MAX)
                {
                    // Check if the adjacent node has not been visited yet
                    if (T[sourceNode][adjacentNode].visited == false)
                    {
                        // If the distance from the source to current node + the edge weight between the current and adjacent node
                        // is less than the current shortest distance from the source to adjacent node, then update the current
                        // shortest distance to the adjacent node with this new shortest distance found and
                        // set the current node as the new previous node to the adjacent node
                        if ((T[sourceNode][currentNode].dist + C[currentNode][adjacentNode]) < T[sourceNode][adjacentNode].dist)
                        {
                            T[sourceNode][adjacentNode].dist = (T[sourceNode][currentNode].dist + C[currentNode][adjacentNode]);
                            T[sourceNode][adjacentNode].path = currentNode;
                        }
                    }
                }
            }
        }
    }
}
// -------------------------------------------------------------------------------------------

// ---------------------------------[displayAll]----------------------------------------------
// Description: The displayAll method for the GraphM class is used to print out the
// shortest path between all of the nodes of a graph in the form of a table with the
// columns "Description", "From node", "To node", "Dijkstra's", and "Path" to
// display the node description, the source and destination nodes, the shortest path
// to every destination node and the path it took to get from the source to destination
// node.
// -------------------------------------------------------------------------------------------
void GraphM::displayAll()
{
    // The header row is printed to display the description, from node, to node, Dijkstra's, and path
    cout << "Description" << "             ";
    cout << "From node" << "   ";
    cout << "To node" << "   ";
    cout << "Dijkstra's" << "     ";
    cout << "Path";
    cout << endl;
    
    // Iterate through all the source nodes in the graph
    for (int sourceNode = 1; sourceNode <= size; sourceNode++)
    {
        // The data of the source node is printed out
        cout << data[sourceNode];
        cout << endl;
        cout << endl;

        // Iterate through all the destination nodes in the graph
        for (int destinationNode = 1; destinationNode <= size; destinationNode++)
        {
            // Check if there is a path from the source node to the destination node
            if (T[sourceNode][destinationNode].dist != 0)
            {
                cout << "                           ";
                cout << sourceNode;
                cout << "          ";
                cout << destinationNode;

               // If the path from the source node to the destination node is not infinity (path exists)
               if (T[sourceNode][destinationNode].dist != INT_MAX)
               {
                    // The shortest path from the source node to the destination node is printed
                    cout << "            ";
                    cout << T[sourceNode][destinationNode].dist;
                    cout << "          ";

                    // The path taken to get from the source node to the destination node is printed
                    // by calling the recursivePathHelper method
                    recursivePathHelper(sourceNode, destinationNode);
                    cout << endl;
               }
               // If the path from the source node to the destination node is infinity (no path),
               // "----" is printed
               else if (T[sourceNode][destinationNode].dist == INT_MAX)
               {
                    cout << "            ";
                    cout << "----";
                    cout << endl;
               }
            }
        }
    }
}
// -------------------------------------------------------------------------------------------

// -----------------------------[recursivePathHelper]-----------------------------------------
// Description: The recursivePathHelper method for the GraphM class is a recursive
// helper method for the displayAll and display methods that finds the path between
// the source node and destination node in the graph.
// -------------------------------------------------------------------------------------------
void GraphM::recursivePathHelper(int fromNode, int toNode)
{
    // If the source node and the destination node are equal, print the destination
    // node as it is the only node in the path
    if (toNode == fromNode || fromNode == toNode)
    {
        cout << toNode << " ";
    }

    // If a path exists between the source node and destination node
    else if (T[fromNode][toNode].dist != INT_MAX)
    {
        // Store the current destination node in path
        int path = toNode;

        // Set the destination node to the previous node in the path
        toNode = T[fromNode][toNode].path;

        // Recursively call the helper method with the updated destination node
        recursivePathHelper(fromNode, toNode);

        // Print out the current node
        cout << path << " ";
    }

    // If the path from the source node to the destination node is infinity (no path), return
    else
    {
        return;
    }
}
// -------------------------------------------------------------------------------------------

// -----------------------------------[display]-----------------------------------------------
// Description: The display method for the GraphM class prints out the shortest path between 
// the source node and the destination node in the graph, it additionally prints
// out the cost of the path from the nodes and the data of the nodes.
// -------------------------------------------------------------------------------------------
void GraphM::display(int fromNode, int toNode)
{
    // First check to make sure that the source node and destination node are within the size of the graph
    if ((fromNode <= size && fromNode >= 0) && (toNode <= size && toNode >= 0))
    {
        // Source node and destination node are printed
        cout << "       " << fromNode << "       " << toNode;
   
        // If there is no path from the source node to the destination node,
        // "----" is printed
        if (T[fromNode][toNode].dist == INT_MAX)
        {
            cout << "            " << "----" << endl;
        }
        // If there is a path between the two nodes
        else
        {   
            // The shortest path between the source and destination node is printed 
            cout << "            " << T[fromNode][toNode].dist << "            ";

            // Recursive helper method prints out the path taken from the source node to the destination node
            recursivePathHelper(fromNode, toNode); 
            cout << endl;

            // Recursive helper method prints out the data of the nodes in the path
            recursiveNodeDataHelper(fromNode, toNode);
        }
        cout << endl;
    }
    // If either the source node or destination node are not within the bounds of the graph,
    // print "----" to indicate there is no path between the nodes
    else 
    {
        cout << "       " << fromNode << "       " << toNode << "            " << "----" << endl;
    }
}
// -------------------------------------------------------------------------------------------

// ---------------------------[recursiveNodeDataHelper]---------------------------------------
// Description: The recursiveNodeDataHelper for the GraphM class is the recursive helper
// method for the display method that is used to find the data of the node of a given
// edge in the graph from the source node to the destination node.
// -------------------------------------------------------------------------------------------
void GraphM::recursiveNodeDataHelper(int fromNode, int toNode)
{
    // If the source node and destination node are equal, there is only
    // one node in the path
    if (toNode == fromNode || fromNode == toNode)
    {
        cout << data[toNode] << endl;
    }

    // If the path between the source node and destination node
    // is not infinity, recursively find the data for each node in
    // the path
    else if (T[fromNode][toNode].dist != INT_MAX)
    {
        // The current destination node is stored in nodeData
        int nodeData = toNode;

        // Destination node is updated to the next node in the path
        toNode = T[fromNode][toNode].path;

        // Recursive call with updated destination node
        recursiveNodeDataHelper(fromNode, toNode);

        // Print out the node data of the next node in the path
        cout << data[nodeData] << endl;
        cout << endl;
    }

    // If there is not a path from the source node to destination node, return
    else
    {
        return;
    }
}
// -------------------------------------------------------------------------------------------
