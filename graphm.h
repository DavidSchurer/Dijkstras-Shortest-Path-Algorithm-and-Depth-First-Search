// ----------------------------- graphm.h ------------------------------
// David Schurer
// CSS 343
// Creation Date: 4/27/2023
// Date of Last Modification: 5/5/2023
// ---------------------------------------------------------------------
// Purpose - The graphm.h file is the header file for the GraphM
// class, which is the implementation for Dijkstra's shortest path
// algorithm. This header file provides the class definition for graphM
// including all of its method declarations and data members, as well as
// the private struct TableType, which stores the information for each
// node in the graph.
// ---------------------------------------------------------------------
// Notes - This header file initializes a global constant integer 
// variable named MAXNODES and sets it to 100, this represents the maximum
// number of nodes that can be stored in a given graph. Additionally, the
// buildGraph method passes in an ifstream object inputfile by reference
// as its parameter as this method reads in a data input text file which
// contains the number of nodes in the graph, each node description, and
// the edge weights between the nodes in the graph.
// ---------------------------------------------------------------------
#ifndef GRAPH_M
#define GRAPH_M
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

// Global constant int variable to represent the max number of nodes in the graph
const int GRAPHM_MAXNODES = 100;

class GraphM {

    public:
        // GraphM default constructor initializes the data member T to set all the distances to infinity,
        // all visited to false, all paths to 0
        GraphM(); 

        // buildGraph reads in the input data text file to build the graph                          
        void buildGraph(ifstream &inputfile);

        // Methods for inserting and removing an edge between two nodes
        void insertEdge(int fromNode, int toNode, int edgeWeight);
        void removeEdge(int fromNode, int toNode);
        
        // Implementation of Dijkstra's shortest path algorithm to find the shortest distances
        // between all of the nodes in the graph
        void findShortestPath();

        // displayAll displays the shortest distance and the path 
        // to all of the other nodes from each node
        void displayAll();

        // display displays the shortest path between two given nodes in the graph
        void display(int fromNode, int toNode);

    private:
        // The TableType struct is used to store all of the node information in the graph
        struct TableType 
        {
            bool visited;                 
            int dist;                       
            int path;                       
            NodeData nodeData;
        };
        
        // The NodeData array used to represent the data of each node
        NodeData data[GRAPHM_MAXNODES];     

        // Adjacency matrix for all of the edge weights between each node       
        int C[GRAPHM_MAXNODES][GRAPHM_MAXNODES];      

        // Number of nodes in the graph 
        int size;

        // 2D array used to store all of the node information (visited, shortest distance, path, and node data)
        TableType T[GRAPHM_MAXNODES][GRAPHM_MAXNODES];   

        // Recursive helper methods used to recursively display
        // the data for all of the nodes between two nodes in the graph
        // and the shortest path between those two nodes
        void recursiveNodeDataHelper(int fromNode, int toNode);
        void recursivePathHelper(int fromNode, int toNode);
        
};

#endif
