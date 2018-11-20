
#include "Graph.h"

//Ctors.
Graph::Graph(vector<shared_ptr<Node>> stations)
{
    this->stations = stations;
}

Graph::Graph(const Graph &g)
{
    this->stations = vector<shared_ptr<Node>>(g.stations);
}

Graph::Graph(Graph &&g)
{
    this->stations = g.stations;
}

//Operator=
Graph &Graph::operator=(const Graph &g)
{
    if (this == &g)
    {
        return *this;
    }
    this->stations = vector<shared_ptr<Node>>(g.stations);
    return *this;
}

//Move operator=
Graph &Graph::operator=(Graph &&g)
{
    this->stations = g.stations;
    return *this;
}

//Add a new node to the graph, if the node exists then cancel.
void Graph::addNode(shared_ptr<Node> node)
{
    for (auto n = this->stations.begin(); n != this->stations.end(); n++)
    {
        if ((*n)->getStation()->getName().compare(node->getStation()->getName()) == 0)
        {
            return;
        }
    }
    this->stations.push_back(node);
}

//Add a new connection to the graph, get 2 station names, if the doesn't exist in the graph add them,
//and connect them using the node.connect function.
void Graph::addConnection(string sourceName, string targetName, int weight, string vehicle)
{
    shared_ptr<Node> src = nullptr, trg = nullptr;
    for (auto n = this->stations.begin(); n != this->stations.end(); n++)
    {
        if ((*n)->getStation()->getName().compare(sourceName) == 0)
        {
            src = *n;
        }
        if ((*n)->getStation()->getName().compare(targetName) == 0)
        {
            trg = *n;
        }
    }
    if (src == nullptr)
    {
        src = make_shared<Node>(sourceName);
        this->stations.push_back(src);
    }
    if (trg == nullptr)
    {
        trg = make_shared<Node>(targetName);
        this->stations.push_back(trg);
    }
    src->connect(trg, weight, vehicle);
}

//if the given station exists in the graph return the node that contains it, else return null.
shared_ptr<Node> Graph::getNode(string stationName)
{
    for (auto node = this->stations.begin(); node != this->stations.end(); node++)
    {
        if ((*node)->getStation()->getName().compare(stationName) == 0)
        {
            return *node;
        }
    }
    return nullptr;
}

// uniExpress function run the djikstra algorithm on 2 given nodes if they exist.
void Graph::uniExpress(string sourceName, string targetName)
{
    auto src = getNode(sourceName);
    auto trg = getNode(targetName);
    if (src == nullptr)
    {
        throw(NodeNotFoundException( sourceName + " does not exist in the current network"));
    }
    if (trg == nullptr)
    {
        throw(NodeNotFoundException( targetName + " does not exist in the current network"));
    }
    auto nodes = queue<shared_ptr<Node>>();
    src->djikstra = 0;
    nodes.push(src);
    src->djikstraAlgorithm(src->bus, nodes);
    cout << "bus: ";
    if (trg->djikstra == INT_MAX) // prints the shortest route in bus.
    {
        cout << "route unavailble" << endl;
    }
    else
    {
        cout << trg->djikstra - Bus::derivedStopTime << endl;
    }
    resetDjikstra();
    nodes = queue<shared_ptr<Node>>();
    src->djikstra = 0;
    nodes.push(src);
    src->djikstraAlgorithm(src->tram, nodes);
    cout << "tram: ";
    if (trg->djikstra == INT_MAX) // prints the shortest route in tram.
    {
        cout << "route unavailble" << endl;
    }
    else
    {
        cout << trg->djikstra - Tram::derivedStopTime << endl;
    }
    resetDjikstra();
    nodes = queue<shared_ptr<Node>>();
    src->djikstra = 0;
    nodes.push(src);
    src->djikstraAlgorithm(src->sprinter, nodes);
    cout << "sprinter: ";
    if (trg->djikstra == INT_MAX) // prints the shortest route in sprinter.
    {
        cout << "route unavailble" << endl;
    }
    else
    {
        cout << trg->djikstra - Sprinter::derivedStopTime << endl;
    }
    resetDjikstra();
    nodes = queue<shared_ptr<Node>>();
    src->djikstra = 0;
    nodes.push(src);
    src->djikstraAlgorithm(src->rail, nodes);
    cout << "rail: ";
    if (trg->djikstra == INT_MAX) // prints the shortest route in rail.
    {
        cout << "route unavailble" << endl;
    }
    else
    {
        cout << trg->djikstra - Rail::derivedStopTime << endl;
    }
    resetDjikstra();
}

// multiExpress function calculates the shortest time from source to target in all of the vehicles.
void Graph::multiExpress(string sourceName, string targetName)
{
    auto src = getNode(sourceName);
    auto trg = getNode(targetName);
    if (src == nullptr)
    {
        throw(NodeNotFoundException(sourceName + " does not exist in the current network"));
    }
    if (trg == nullptr)
    {
        throw(NodeNotFoundException(targetName + " does not exist in the current network"));
    }
    auto nodes = queue<shared_ptr<Node>>();
    src->djikstra = 0;
    nodes.push(src);

    src->mulDjikstraAlgorithm(nullptr, nodes, src);
    if (trg->djikstra == INT_MAX) // prints the shortest route.
    {
        cout << "route unavailble" << endl;
    }
    else
    {
        cout << trg->djikstra << endl;
    }
    resetDjikstra();
}

// resets all the djikstra fields at all the nodes to INT_MAX
void Graph::resetDjikstra()
{
    for (auto n = this->stations.begin(); n != this->stations.end(); n++)
    {
        (*n)->djikstra = INT_MAX;
        (*n)->lastVehicle = nullptr;
    }
}


