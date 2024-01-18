/*
-----------------------------------------
Paola Reyes
CS 251, Wed 4pm Lab
4-27-23
Prof. Adam Koehler
-----------------------------------------
Program 6: Open Street Maps

// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation

This is the header file for the graph application. We take an .osm file from
an address we choose on openstreetmap.org. This file contains nodes of coordinate
pairs surrounding significant markers, like buildings or sidewalks. 

This file makes a graph class, which is an adjacency list for the nodes. We will
keep track of all the edges in the area. The goal is to select 2 nodes and find
the shortest edge between them. We read in the .osm file in application.cpp.

This class allows us to:
  - add vertices
  - add edges
  - get edge's cost
  - see a vertex's edges

Adam T Koehler, PhD
University of Illinois Chicago
CS 251, Spring 2023

Project Original Variartion By:
Joe Hummel, PhD
University of Illinois at Chicago
*/

#pragma once

#include <algorithm> // For find_if()
#include <cmath>
#include <iostream>
#include <set>           // For adjacency list value/list of Edges
#include <stdexcept>     // For reporting errors
#include <unordered_map> // For adjacency list
#include <vector>        // For getVertices()

using namespace std;

template <typename VertexT, typename WeightT> class graph {
private:
  // An edge struct that stores the ending vertex and the weight
  // The begining vertex is its own row category in the adjacency list
  struct Edge {
    VertexT vertex;
    WeightT weight;

    Edge(VertexT v, WeightT w) {
      vertex = v;
      weight = w;
    }

    // Overload '<' so we can store Edge in a set
    bool operator<(const Edge &other) const { return vertex < other.vertex; }
  };

  // The adjacency list is an unordered map with a vertex key and a set of Edges
  unordered_map<VertexT, set<Edge>> AdjList;
  vector<VertexT> Vertices;   // A vector because getVertices() returns a vector
  int numEdges;

public:
  //
  // constructor:
  //
  // Constructs an empty graph.
  //
  graph() {
    numEdges = 0;
  }


  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const { 
    return Vertices.size(); 
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    return numEdges;    
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph. If the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
    // If the vertex already exists, return false
    if (AdjList.count(v)) {
      return false;
    }

    // The vertex does not exist so add it to the each list
    set<Edge> s;
    AdjList.emplace(v, s);   // Add the new map pair
    Vertices.push_back(v);
    
    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) 
  {
    // Check if both vertices exist
    if (AdjList.count(from) && AdjList.count(to)) {
      Edge newEdge(to, weight); 

      // The set will not allow duplicate entries. If it does exist, delete it. 
      if (AdjList.at(from).count(newEdge)) {
        AdjList.at(from).erase(newEdge);
        numEdges--;    // Remove this pair from the total count
      }
  
      // Add the new Edge and update the count
      AdjList.at(from).insert(newEdge);
      numEdges++; 
      
      return true;
    }

    // The vertices didn't exist
    return false;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT &weight) const 
  {
    // Check if both vertices exist
    if (AdjList.count(from) && AdjList.count(to)) 
    {      
      // Check if "from" contains "to"
      WeightT w;
      Edge target(to, w); // Make a dummy node we will search for
   
      // If the iterator is found in "from", we can assume the same for "to"
      if (AdjList.at(from).count(target) == 1) {
        weight = (AdjList.at(from).find(target))->weight;
        return true;
      } 
      else {
        // The edge does not exist
        return false;
      }
    }

    // A vertex didn't exist
    return false;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    // Contains the vertices corresponding to a vertex's edges
    set<VertexT> s;

    // If the vector exists, copy all of its edges into the set
    if (AdjList.count(v)) {
      for (auto edge : AdjList.at(v)) {
          s.insert(edge.vertex);
      }
    }

    return s;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    return Vertices; // returns a copy:
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream &output) const {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;
    output << endl;

    for (const auto &vertex : AdjList) {
      output << vertex.first << ": ";

      for (const auto &edge : vertex.second) {
        output << "(" << vertex.first << ", " << edge.vertex << ", "
               << edge.weight << "), ";
      }

      output << endl;
    }

    output << "**************************************************" << endl;
  }
};
