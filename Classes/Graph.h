
#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <forward_list>

using namespace std;

class Graph
{
private:
  vector<shared_ptr<Node>> stations;

public:
  //  C'tors D'tor
  Graph() {this->stations = vector<shared_ptr<Node>>();}
  Graph(vector<shared_ptr<Node>> stations);
  Graph(const Graph &g);
  Graph(Graph &&g);
  virtual ~Graph() {}
  //  Operators
  Graph &operator=(const Graph &g);
  Graph &operator=(Graph &&g);
  //  Functions
  void addNode(shared_ptr<Node> node);
  void addConnection(string sourceName, string targetName, int weight, string vehicle);
  shared_ptr<Node> getNode(string stationName);
  void uniExpress(string sourceName, string targetName);
  void multiExpress(string sourceName, string targetName);
  void resetDjikstra();

  //  Get/Set
  vector<shared_ptr<Node>>& getStations() {return this->stations;}
};
#endif //GRAPH_H
