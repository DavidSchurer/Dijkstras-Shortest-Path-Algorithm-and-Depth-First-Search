// ----------------------------- graphl.h ------------------------------
// David Schurer
// CSS 343
// Creation Date: 4/27/2023
// Date of Last Modification: 5/5/2023
// ---------------------------------------------------------------------
// Purpose - The graphl.h file is the header file for the GraphL class
// which represents a graph data structure and is used for the depth-first
// search traversal of a graph. It contains the method declarations
// for the GraphL class and a global constant integer variable
// to represent the maximum number of nodes that can be stored in
// the graph.
// ---------------------------------------------------------------------
// Notes - This method contains a struct EdgeNode to represent an 
// edge in the graph and it contains the nextEdge pointer, which points
// to the next edge in the adjacency list as well as the adjGraphNode
// data member to represent the subscript of the adjacent graph node.
// Additionally, this method contains a struct GraphNode to represent
// each node and has an EdgeNode pointer edgeHead which points to the first
// node in the edge and data memebers for the data of the node and
// the visited status of the node.
// ---------------------------------------------------------------------
#ifndef GRAPH_L
#define GRAPH_L
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

// Global constant int variable to represent the max number of nodes in the graph
const int GRAPHL_MAXNODES = 100;

class GraphL {

    public:
        // GraphL constructor and destructor
        GraphL();
        ~GraphL();

        // Methods for constructing the graph and
        // displaying the contents of the graph
        void buildGraph(ifstream &inputfile);
        void displayGraph();

        // Method for implementing the depth-first search
        // traversal on the graph
        void depthFirstSearch();

    private:
        // The EdgeNode struct represents the edge between nodes in the graph
        struct EdgeNode;

        // The GraphNode struct represents each node in the graph
        struct GraphNode 
        {
            EdgeNode* edgeHead;
            NodeData* data;
            bool visited;
        };

        // The EdgeNode struct represents the edge between nodes in the graph
        struct EdgeNode 
        {
            int adjGraphNode;
            EdgeNode* nextEdge;
        };

        // Integer variable representing the size of the graph
        int graphSize;

        // Array of GraphNode structs to represent the nodes in the graph
        GraphNode graphNodes[GRAPHL_MAXNODES];

        // Recursive helper method for the depth-first search method
        void depthFirstSearchHelper(int source);

};

#endif
