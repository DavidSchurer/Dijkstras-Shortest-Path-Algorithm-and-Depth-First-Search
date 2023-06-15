// ---------------------------- graphl.cpp -----------------------------
// David Schurer
// CSS 343
// Creation Date: 4/27/2023
// Date of Last Modification: 5/5/2023
// ---------------------------------------------------------------------
// Purpose - The graphl.cpp file is the implementation file for the
// GraphL class, which is the implementation of a depth-first search
// traversal of a graph. This implementation file contains the
// implementation for the methods buildGraph, displayGraph, depthFirstSearch,
// and its helper method depthFirstSearchHelper as well as the class
// constructor and destructor.
// ---------------------------------------------------------------------
// Notes - The buildGraph method of the GraphL class reads in a text file
// that contains the data for building the graph, which is constructed
// by using adjacency lists. Additionally, the constructor of the class
// initializes the data members for the nodes in the graph through the use
// of a range-based for loop. The depthFirstSearch method performs a
// depth-first search traversal of the graph using recursion, it keeps
// track of the nodes that it needs to visit and explores the graph
// by going as far along it can through each branch before backtracking
// and exploring another branch.
// ---------------------------------------------------------------------
#include "graphl.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stack>
#include <climits>
using namespace std;

// ----------------------------------[Constructor]--------------------------------------------
// Description: The GraphL constructor initializes all of the graph node's
// data members to their default values. It uses a range-based for loop to iterate
// through all of the elements in the graphNodes array.
// -------------------------------------------------------------------------------------------
GraphL::GraphL() 
{
    // Initializes all of the elements in the graphNodes array to their default values
    for (auto& graphNode : graphNodes)
    {
        // edgeHead is initialized to nullptr
        graphNode.edgeHead = nullptr;

        // Data of the node is initialized to nullptr
        graphNode.data = nullptr;

        // Visited status initialized to false
        graphNode.visited = false;
    }

    // The graph's size is initialized to 0
    graphSize = 0;
}
// -------------------------------------------------------------------------------------------

// -----------------------------------[Destructor]--------------------------------------------
// Description: The GraphL destructor is used to dellocate all of the memory
// that as allocated by the GraphL class. This method iterates through all of
// the nodes in the graph and deletes all of the nodes and their edges in the graph.
// -------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
    // For loop to iterate through all of the nodes in the graph
    for (int nodeIndex = 1; nodeIndex <= graphSize; nodeIndex++)
    {
        // The current node is set to the head of the adjacency list
        // of the node 
        EdgeNode* currentNode = graphNodes[nodeIndex].edgeHead;

        // Node of the data is deleted
        delete graphNodes[nodeIndex].data;
        
        // The node's data is set to nullptr
        graphNodes[nodeIndex].data = nullptr;

        // The head node of that node's adjacency list is set to nullptr
        graphNodes[nodeIndex].edgeHead = nullptr;

        // The node is marked as unvisited
        graphNodes[nodeIndex].visited = false;

        // Iterate through the adjacency list for the current node
        // and delete all of its edges
        while (currentNode != nullptr) 
        {
            // Temporary edge node used to store the current edge node, then
            // move the current edge node to the next edge node
            EdgeNode* temporaryNode = currentNode;
            currentNode = currentNode->nextEdge;
            
            // Delete the temporary edge node and set it to nullptr
            delete temporaryNode;
            temporaryNode = nullptr;
        }
    }
}
// -------------------------------------------------------------------------------------------

// -----------------------------------[buildGraph]--------------------------------------------
// Description: The buildGraph method for the GraphL class reads in the input
// data text file and builds the graph using adjacency lists. The method
// reads in the size of the graph from the input file and then the data for each
// node in the graph and creates a new NodeData object for each node that is read in,
// then the method reads in the data for the edges in the graph.
// -------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& inputfile) 
{
    // Initialize the variables for the source node, destination node, and data of the node
    int sourceNode;
    int destinationNode;
    string nodeData;

    // Reads in the size of the graph from the input file
    inputfile >> graphSize;
    getline(inputfile, nodeData);

    // Reads in the data for each node and creates a new NodeData object for the node
    for (int i = 1; i <= graphSize; i++) 
    {
        getline(inputfile, nodeData);
        graphNodes[i].data = new NodeData(nodeData);
    }

    // Reads in the data for the edges between the nodes
    while (inputfile >> sourceNode >> destinationNode)
    {
        // If the source or destination node are read in as 0, stop reading in input
        if (sourceNode == 0 || destinationNode == 0)
        {
            break;
        }

        // If the source and destination node are not read in as 0, continue
        if (sourceNode != 0 && destinationNode != 0)
        {
            // A new edge node is initialized
            EdgeNode* newNode = new EdgeNode;

            // Sets the destination node for the new edge node
            newNode->adjGraphNode = destinationNode;

            // If the source node has an adjacency list
            if (graphNodes[sourceNode].edgeHead != nullptr)
            {
                // The new edge node is added to the beginning of the adjacency
                // list
                newNode->nextEdge = graphNodes[sourceNode].edgeHead;
                graphNodes[sourceNode].edgeHead = newNode;
            }
            // If the source node does not have an adjacency list, the new edge node
            // will be set as the head of the adjacency list for the source node
            else if (graphNodes[sourceNode].edgeHead == nullptr)
            {
                graphNodes[sourceNode].edgeHead = newNode;
                newNode->nextEdge = nullptr;
            }
        }
    }
}
// -------------------------------------------------------------------------------------------

// ----------------------------------[displayGraph]-------------------------------------------
// Description: The displayGraph method of the GraphL class prints out the graph
// information. It iterates through every node in the graph and prints its index
// out and every edge that is adjacent to that node.
// -------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;

    // For loop used to iterate through all the nodes in the graph
    for (int nodeIndex = 1; nodeIndex <= graphSize; nodeIndex++)
    {   
        // Node and its number are printed followed by the data of the node
        cout << "Node" << nodeIndex << "      " << *(graphNodes[nodeIndex].data) << endl << endl;
    
        // For loop used to iterate through all of the edges of the current node
        for(EdgeNode* currentNode = graphNodes[nodeIndex].edgeHead; currentNode != nullptr; currentNode = currentNode->nextEdge)
        {
            // Each edge adjacent to the current node is printed out
            cout << "  " << "edge" << "  " << nodeIndex << "  " << currentNode->adjGraphNode << endl;
        }
    }
}
// -------------------------------------------------------------------------------------------

// --------------------------------[depthFirstSearch]-----------------------------------------
// Description: The depthFirstSearch method in the GraphL class is used to implement
// the depth-first search graph traversal algorithm by using a helper method.
// This method iterates through all of the nodes in the graph and checks to see
// if the current node has been visited or not and calls the helper method when
// it has found a node that has not been visited.
// -------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    cout << "Depth-first ordering:";
    
    // Iterate through all of the nodes in the graph
    for (int currentNode = 1; currentNode <= graphSize; currentNode++) 
    {
        // Continue to the next node if the current node has been visited
        if (graphNodes[currentNode].visited == true)
        {
            continue;
        }

        // If the current node has not been visited, perform a depth-first search
        // on this node by calling the helper method
        if (graphNodes[currentNode].visited == false)
        {
            depthFirstSearchHelper(currentNode);
        }
    }

    cout << endl;
    cout << endl;
}
// -------------------------------------------------------------------------------------------

// -----------------------------[depthFirstSearchHelper]--------------------------------------
// Description: The depthFirstSearchHelper method in the GraphL class is a 
// recursive helper method for the depthFirstSearch method for performing a 
// depth-first traversal on a graph. It marks the source node as visited and 
// prints its index, then it traverses the adjacency list of the source node
// and checks if each adjacent node has been visited, if a node hasn't been visited,
// it recursively calls itself with the adjacent node as the new source node.
// The depth-first ordering of the nodes are returned.
// -------------------------------------------------------------------------------------------
void GraphL::depthFirstSearchHelper(int sourceNode)
{
    // Current node is set to the first node in the adjacency list
    // of the source node
    EdgeNode* currentNode = graphNodes[sourceNode].edgeHead; 

    graphNodes[sourceNode].visited = true; 

    cout << "  " << sourceNode;

    while (currentNode != nullptr) 
    { 
        // If the node adjacent to the current node has been visited, traverse to the next node
        // in the adjacency list
        if (graphNodes[currentNode->adjGraphNode].visited == true)
        {
            currentNode = currentNode->nextEdge;
        }
        // If the node adjacent to the current node has not been visited, recursively call
        // the method with the source node updated to the adjacent node
        else if (graphNodes[currentNode->adjGraphNode].visited == false)
        {
            depthFirstSearchHelper(currentNode->adjGraphNode);
        }
    }
}
// -------------------------------------------------------------------------------------------
