
#ifndef NODE_H
#define NODE_H

#include "Vehicles.h"
#include "Stations.h"
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <typeinfo>
#include <climits>
#include <queue>
#include<algorithm>

using namespace std;

class Node
{
private:
    shared_ptr<Station> station;
    map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>> destinations;
    map<shared_ptr<Node>, map<shared_ptr<Vehicle>, int>> weights;
    map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>> sources;

public:
    int djikstra = INT_MAX;
    shared_ptr<Vehicle> lastVehicle;
    shared_ptr<Bus> bus;
    shared_ptr<Tram> tram;
    shared_ptr<Rail> rail;
    shared_ptr<Sprinter> sprinter;
  //  C'tors D'tor

  Node();
  Node(string stationName);
  Node(const Node &n);
  Node(Node &&n);
  virtual ~Node() {}

  //  Operators

  Node &operator=(const Node &n);
  Node &operator=(Node &&n);
  vector<shared_ptr<Node>> &operator[](shared_ptr<Vehicle> v);
  //  Functions
  void connect(shared_ptr<Node> target, int weight, string vehicle);
  void outbound(shared_ptr<Vehicle> vehicle, shared_ptr<vector<shared_ptr<Node>>> nodes);
  void inbound(shared_ptr<Vehicle> vehicle, shared_ptr<vector<shared_ptr<Node>>> nodes);
  void djikstraAlgorithm(shared_ptr<Vehicle> vehicle, queue<shared_ptr<Node>> nodes);
  void mulDjikstraAlgorithm(shared_ptr<Vehicle> vehicle, queue<shared_ptr<Node>> nodes, shared_ptr<Node> source);
  int minWeight(shared_ptr<Vehicle> vehicle, shared_ptr<Node> n, shared_ptr<Node> source);
  //  Get/Set
  shared_ptr<Station> getStation() { return this->station; }
  shared_ptr<Vehicle> getVehicle(string type);
  map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>> getDestinations() { return this->destinations; }
  map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>> getSources() { return this->sources; }
  map<shared_ptr<Node>, map<shared_ptr<Vehicle>, int>> getWeights() { return this->weights; }
};
#endif //NODE_H
