/*
-----------------------------------------
Paola Reyes
CS 251, Wed 4pm Lab
4-27-23
Prof. Adam Koehler
-----------------------------------------
Program 6: Open Street Maps

References:
TinyXML: https://github.com/leethomason/tinyxml2
OpenStreetMap: https://www.openstreetmap.org
OpenStreetMap docs:
  https://wiki.openstreetmap.org/wiki/Main_Page
  https://wiki.openstreetmap.org/wiki/Map_Features
  https://wiki.openstreetmap.org/wiki/Node
  https://wiki.openstreetmap.org/wiki/Way
  https://wiki.openstreetmap.org/wiki/Relation

This is the header file for the graph application. We take an .osm file from
an address we choose on openstreetmap.org. This file contains nodes of coordinate
pairs surrounding significant markers, like buildings or sidewalks. 

This file makes a an adjacency list using the graph class in graph.h. We will
keep track of all the edges in the area. The goal is to select 2 nodes and find
the shortest edge between them. We read in the .osm file and add it's data to the 
graph object.

There are a couple other structures we use to organize all the data. File osm.h
creates more classes for specific nodes, like buiding nodes or sidewalk nodes.
We store the class objects into vectors or maps. Then, we cross reference to get
the data we need. For example, one structure will give us a node's name while 
another will give us it's coordinates. This is all to minimize time searching
for a specific node.

We use Dijsktra's algorithm to find the shortest path between 2 buildings the user
specifies. The process goes:
  1. We find their coordinates
  2. We find the midpoint
  3. Find the building closest to that midpoint
  4. Find the shortest path to that midpoint for each person  

Adam T Koehler, PhD
University of Illinois Chicago
CS 251, Spring 2023

Project Original Variartion By:
Joe Hummel, PhD
University of Illinois at Chicago
*/

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>    // For sqrt()

#include "tinyxml2.h"
#include "dist.h"
#include "graph.h"
#include "osm.h"


using namespace std;
using namespace tinyxml2;

const double INF = numeric_limits<double>::max();   // Infinity


/// @brief Condition for sort() Sort by Building vector by the abbreviations
/// @param b1 
/// @param b2 
/// @return Boolean of < comparison of 2 BuildingInfo objects
bool compareAbbrev(const BuildingInfo &b1, const BuildingInfo &b2) {
  return b1.Abbrev < b2.Abbrev;
}


/// @brief Condition for sort(). Sort by Building vector by the Coordinates
/// @param b1 
/// @param b2 
/// @return Boolean of < comparison of 2 BuildingInfo objects
bool compareBuildings(const BuildingInfo &b1, const BuildingInfo &b2) {
  Coordinates c1 = b1.Coords;
  Coordinates c2 = b2.Coords;
  
  // Find the next closest coordinate by comparing x values first, then y values if necessary
  return c1.Lat < c2.Lat || (c1.Lat == c2.Lat && c1.Lon < c2.Lon);
}


/// @brief Condition for sort(). Sort the Coordinates vector by the Lat and Lon 
/// @param c1 
/// @param c2 
/// @return Boolean of < comparison of 2 Coordinates objects
bool compareCoordinates(const Coordinates &c1, const Coordinates &c2) {
  // Find the next closest coordinate by comparing x values first, then y values if necessary
  return c1.Lat < c2.Lat || (c1.Lat == c2.Lat && c1.Lon < c2.Lon);
}


/// @brief Makes a string all lower case so user input isn't case sentitive
string lowerCase(string &s) {
  string copy = "";

  for (long unsigned i = 0; i <  s.size(); i++) {
    copy.push_back( tolower(s[i]));
  }

  return copy;
}


/// @brief Find the building's index given its name. Use binary search
/// @param input The user's input. We will return the building's full name by reference via this variable
/// @param Buildings A copy of the Buildings vector. We want to alter the order
/// @return The building's Coordinates
Coordinates findBuilding(string &input, vector<BuildingInfo> Buildings) 
{
  // Sort copy of vector by building abbreviation, which will also sort by full name
  sort( Buildings.begin(), Buildings.end(), compareAbbrev );

  int low = 0;
  int high = Buildings.size() - 1;

  while (low <= high) {
    int mid = (high + low) / 2;

    // Make all the string lowercase for easier comparing
    input = lowerCase(input);
    string abbreviation = lowerCase(Buildings.at(mid).Abbrev);
    string name = lowerCase(Buildings.at(mid).Fullname);

    // Check if the input matches a Building's abbreviation 
    if (input == abbreviation) {
      input = Buildings.at(mid).Fullname;
      return Buildings.at(mid).Coords;
    }
    // Check if the input is part of the full name
    else if (name.find(input) != string::npos) {
      input = Buildings.at(mid).Fullname;
      return Buildings.at(mid).Coords;
    }
    else if (input < abbreviation) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }

  // The building does not exist. Return a Coordinate with ID -1
  Coordinates null(-1, -1, -1);
  return null;
}


/// @brief Find the building nearest to a set of coordinates. Return the index of that building
/// @param x Location's latitude
/// @param y Location's longitude
/// @param name Return the building's name by reference 
/// @param Buildings A copy of the Buildings vector. We want to alter the order
/// @return The building's Coordinates
Coordinates nearestBuilding(double x, double y, string &name, vector<BuildingInfo> Buildings) 
{
  sort(Buildings.begin(), Buildings.end(), compareBuildings);   // Sort by coordinates
  map<double, int> distances;     // To sort the distances and keep track of their index #

  // Calculate the distance of between each the midpoint and each Building
  for (long long unsigned int i = 0; i < Buildings.size(); i++) {
    distances.emplace( distBetween2Points(x, y, Buildings.at(i).Coords.Lat, Buildings.at(i).Coords.Lon), i);
  }

  int min = distances.begin()->second;
  name = Buildings.at(min).Fullname;   // Update the name
  return Buildings.at(min).Coords;     // Return that buildings coordinates
}


/// @brief Finds the node nearest to the given node. Use binary search
/// @param x Person's or destination's latitude
/// @param y Person's or destination's longitude
/// @param coordinates A copy of the Coordinates vector. We want to alter the order
/// @return The coordinates
Coordinates nearestNode(double x, double y, long long &ID, vector<Coordinates> coordinates) 
{
  sort(coordinates.begin(), coordinates.end(), compareCoordinates);
  map<double, int> distances;     // To sort the distances and keep track of their index #

  // Calculate the distance of between each the midpoint and each Node coordinate
  for (long long unsigned int i = 0; i < coordinates.size(); i++) {
    distances.emplace( distBetween2Points(x, y, coordinates.at(i).Lat, coordinates.at(i).Lon), i);
  }

  int min = distances.begin()->second;
  ID = coordinates.at(min).ID;  // Pass the ID
  return coordinates.at(min);    // Return the coordinates
}


void DijkstraShortestPath(long long startV, graph<long long, double> g, vector<int> distance, vector<long long> &predecessor) 
{
  // Add the starting vertex to the queue
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> unvisitedQ;
  vector<long long> vertices;

  for (int i = 0; i < vertices.size(); i++) {
    distance.at(i) = INF;
    predecessor.at(i) = -1;

    // Push each vertex w/ it's initial distance of infinity
    unvisitedQ.push(make_pair(vertices.at(i), INF));  
  }

  // Push the starting vertex
  unvisitedQ.push(make_pair(startV, 0));  

  while (!unvisitedQ.empty()) 
  {
    pair<int, int> currentV = unvisitedQ.top();

    set<long long> neighbors = g.neighbors(currentV.first);

    for (long long adjV : neighbors) {
      double weight = 0;
      g.getWeight(startV, currentV.first, weight);
      double altPathWeight = currentV.second + weight;

      if (altPathWeight < a)
    }


   
  }
}


//
// Implement your standard application here
//
void application( map<long long, Coordinates> &Nodes, 
                  vector<FootwayInfo> &Footways, 
                  vector<BuildingInfo> &Buildings, 
                  graph<long long, double> &G ) 
{
  string person1Building, person2Building;

  cout << endl;
  cout << "Enter person 1's building (partial name or abbreviation), or #> ";
  getline(cin, person1Building);

  while (person1Building != "#") {
    cout << "Enter person 2's building (partial name or abbreviation)> ";
    getline(cin, person2Building);
    
    // Find the index of the given buildings + update personXBuildinghg variables
    Coordinates person1Coords = findBuilding(person1Building, Buildings);
    Coordinates person2Coords = findBuilding(person2Building, Buildings);

    // Check for the terminating value again
    if (person2Building == "#") {
      cout << "Person 2's building not found" << endl;
    }
    // Print out error messages
    else if (person1Coords.ID == -1) {
     cout << "Person 1's building not found" << endl;
    }
    else if (person2Coords.ID == -1) {
     cout << "Person 2's building not found" << endl;
    }
    // If the given buildings exist, get their coordinates
    else {

      // Find the midpoint of the 2 building coordinates
      Coordinates midpoint = centerBetween2Points(person1Coords.Lat, person1Coords.Lon, person2Coords.Lat, person2Coords.Lon);
      cout << "\t midpoint: " << midpoint.Lat << ", " << midpoint.Lon << endl; 

      // Get the data of the building nearest to the midpoint. This is where they'll meet
      string destinationBuilding = "";
      Coordinates destinationCoords = nearestBuilding(midpoint.Lat, midpoint.Lon, destinationBuilding, Buildings);

      // For finding a building's nearest node
      vector<Coordinates> coordinates;
      
      // Go through to Footways vector and access its Nodes vector
      for (const auto &footway : Footways) 
      {
        // Go through the Nodes vector, which is a list of ID's
        for (const auto &node : footway.Nodes) {
          coordinates.push_back(Nodes.at(node));  // Given the ID, add the node's coordinates
        }
      }

      // Find the nodes closest to each person's building  
      long long p1NodeID, p2NodeID, destNodeID;
      Coordinates person1Node = nearestNode(person1Coords.Lat, person1Coords.Lon, p1NodeID, coordinates);
      Coordinates person2Node = nearestNode(person2Coords.Lat, person2Coords.Lon, p2NodeID, coordinates);
      Coordinates destinationNode = nearestNode(destinationCoords.Lat, destinationCoords.Lon, destNodeID, coordinates);
      
      // Print out the data we found
      cout << "Person 1's point: " << endl
           << " " << person1Building << endl 
           << " " << "(" << person1Coords.Lat << ", " << person1Coords.Lon << ")" << endl;
      cout << "Person 2's point: " << endl
           << " " << person2Building << endl 
           << " " << "(" << person2Coords.Lat << ", " << person2Coords.Lon << ")" << endl;
      cout << "Destination Building: " << endl
           << " " << destinationBuilding<< endl 
           << " " << "(" << destinationCoords.Lat << ", " << destinationCoords.Lon << ")" << endl << endl;
         
      cout << "Nearest P1 node: " << endl 
           << " " << p1NodeID << endl 
           << " " << "(" << person1Node.Lat << ", " << person1Node.Lon << ")" << endl;
      cout << "Nearest P2 node: " << endl 
           << " " << p2NodeID << endl 
           << " " << "(" << person2Node.Lat << ", " << person2Node.Lon << ")" << endl;
      cout << "Nearest destination node: " << endl 
           << " " << destNodeID << endl 
           << " " << "(" << destinationNode.Lat << ", " << destinationNode.Lon << ")" << endl << endl;
         
      cout << "Person 1's distance to dest: "
           << distBetween2Points(person1Node.Lat, person1Node.Lon, destinationNode.Lat, destinationNode.Lon) 
           << " miles" << endl
           << "Path: " << endl;
      cout << "Person 2's distance to dest: " 
           << distBetween2Points(person2Node.Lat, person2Node.Lon, destinationNode.Lat, destinationNode.Lon)
           << " miles" << endl
           << "Path: " << endl << endl;
    } 

    //
    // Get user input again
    //
    cout << endl;
    cout << "Enter person 1's building (partial name or abbreviation), or #> ";
    getline(cin, person1Building);
  }    
}

int main() {
  graph<long long, double> G;
  map<long long, Coordinates>  Nodes;       // maps a Node ID to it's coordinates (lat, lon)
  vector<FootwayInfo>          Footways;    // info about each footway, in no particular order
  vector<BuildingInfo>         Buildings;   // info about each building, in no particular order
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << setprecision(8);

  string def_filename = "map.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;

    //
  // Add the Node ID's as vertices in the graph
  //
  for (const auto &node : Nodes) {
    G.addVertex(node.first);
  }

  //
  // Add the Footway's nodes as edges
  // 
  // Go through every FootwayInfo object in the Footways vector
  for (const auto &footway : Footways) 
  {    
     // Go through every ID in footway's Nodes vector
     for (long long unsigned int i = 0; i < footway.Nodes.size() - 1; i++) 
     {
        // Get both vertices' ID from the Nodes vector 
        long long startID = footway.Nodes.at(i);
        long long endID = footway.Nodes.at(i+1);
        
        // Use the ID to get the coordinates from the Nodes map
        Coordinates start = Nodes.at(startID);
        Coordinates end = Nodes.at(endID);
        
        // Find the weight and add the bidirectionaledge
        double weight = distBetween2Points(start.Lat, start.Lon, end.Lat, end.Lon);
        G.addEdge(startID, endID, weight);
        G.addEdge(endID, startID, weight);
     }
  }  

  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  cout << endl;

  // Execute Application
  application(Nodes, Footways, Buildings, G);

  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
