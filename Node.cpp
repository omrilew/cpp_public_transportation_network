#include "Node.h"

//  Default Ctor
Node::Node()
{
    this->station = nullptr;
    this->destinations = map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>>();
    this->weights = map<shared_ptr<Node>, map<shared_ptr<Vehicle>, int>>();
    this->bus = make_shared<Bus>();
    this->rail = make_shared<Rail>();
    this->sprinter = make_shared<Sprinter>();
    this->tram = make_shared<Tram>();
    this->destinations[this->bus] = vector<shared_ptr<Node>>();
    this->destinations[this->rail] = vector<shared_ptr<Node>>();
    this->destinations[this->tram] = vector<shared_ptr<Node>>();
    this->destinations[this->sprinter] = vector<shared_ptr<Node>>();
    this->sources = map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>>();
    this->sources[this->bus] = vector<shared_ptr<Node>>();
    this->sources[this->rail] = vector<shared_ptr<Node>>();
    this->sources[this->tram] = vector<shared_ptr<Node>>();
    this->sources[this->sprinter] = vector<shared_ptr<Node>>();
}

//Ctor with station name.
Node::Node(string stationName)
{
    if (stationName.substr(0, 2).compare("IC") == 0)
    {
        this->station = make_shared<Intercity>(stationName);
    }
    else if (stationName.substr(0, 2).compare("CS") == 0)
    {
        this->station = make_shared<Central>(stationName);
    }
    else
    {
        this->station = make_shared<Stad>(stationName);
    }
    this->destinations = map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>>();
    this->weights = map<shared_ptr<Node>, map<shared_ptr<Vehicle>, int>>();
    this->bus = make_shared<Bus>();
    this->rail = make_shared<Rail>();
    this->sprinter = make_shared<Sprinter>();
    this->tram = make_shared<Tram>();
    this->destinations[this->bus] = vector<shared_ptr<Node>>();
    this->destinations[this->rail] = vector<shared_ptr<Node>>();
    this->destinations[this->tram] = vector<shared_ptr<Node>>();
    this->destinations[this->sprinter] = vector<shared_ptr<Node>>();
    this->sources = map<shared_ptr<Vehicle>, vector<shared_ptr<Node>>>();
    this->sources[this->bus] = vector<shared_ptr<Node>>();
    this->sources[this->rail] = vector<shared_ptr<Node>>();
    this->sources[this->tram] = vector<shared_ptr<Node>>();
    this->sources[this->sprinter] = vector<shared_ptr<Node>>();
}

//Copy Ctor
Node::Node(const Node &n)
{
    this->bus = n.bus;
    this->tram = n.tram;
    this->rail = n.rail;
    this->sprinter = n.sprinter;
    this->station = n.station;
    this->destinations = n.destinations;
    this->weights = n.weights;
    this->sources = n.sources;
}

//Move Ctor
Node::Node(Node &&n)
{
    this->bus = n.bus;
    this->tram = n.tram;
    this->rail = n.rail;
    this->sprinter = n.sprinter;
    this->station = n.station;
    this->destinations = n.destinations;
    this->weights = n.weights;
    this->sources = n.sources;
}

// Operator=
Node &Node::operator=(const Node &n)
{
    if (this == &n)
    {
        return *this;
    }
    this->bus = n.bus;
    this->tram = n.tram;
    this->rail = n.rail;
    this->sprinter = n.sprinter;
    this->station = n.station;
    this->destinations = n.destinations;
    this->weights = n.weights;
    this->sources = n.sources;
    return *this;
}

//  Move operator=
Node &Node::operator=(Node &&n)
{
    this->bus = n.bus;
    this->tram = n.tram;
    this->rail = n.rail;
    this->sprinter = n.sprinter;
    this->station = n.station;
    this->destinations = n.destinations;
    this->weights = n.weights;
    this->sources = n.sources;
    return *this;
}

// operator[] gets a vehicle and returns the reachabkle destinations with the given vehicle type
vector<shared_ptr<Node>> &Node::operator[](shared_ptr<Vehicle> v)
{
    return this->destinations[v];
}

// returns a vehicle by given name.
shared_ptr<Vehicle> Node::getVehicle(string type)
{
    if (type.find("bus") == 0)
    {
        return this->bus;
    }
    else if (type.find("tram") == 0)
    {
        return this->tram;
    }
    else if (type.find("rail") == 0)
    {
        return this->rail;
    }
    else if (type.find("sprinter") == 0)
    {
        return this->sprinter;
    }
    return nullptr;
}

// Connect this node to the target node, with the given weight and the given vehicle type.
void Node::connect(shared_ptr<Node> target, int weight, string vehicle)
{
    auto v = this->getVehicle(vehicle);
    if (v == nullptr || weight < 0 || target == nullptr)
    {
        //TODO vehicle type error Exception
        return;
    }
    auto nodes = this->destinations[v];
    for (auto node = nodes.begin(); node != nodes.end(); node++)
    {
        if (target->station->getName().compare((*node)->station->getName()) == 0)
        {
            (*node)->weights[target][v] = weight;
            return;
        }
    }
    target->sources[target->getVehicle(vehicle)].push_back(shared_ptr<Node>(this));
    this->destinations[v].push_back(target);
    this->weights[target][v] = weight;
}

//outbound function, recieve the vehicle , and a vector with the nodes that were already printed.
void Node::outbound(shared_ptr<Vehicle> vehicle, shared_ptr<vector<shared_ptr<Node>>> nodes)
{
    vector<shared_ptr<Node>> dest;
    if (dynamic_pointer_cast<Tram>(vehicle) != nullptr)
    {
        dest = this->destinations[this->tram];
    }
    else if (dynamic_pointer_cast<Bus>(vehicle) != nullptr)
    {
        dest = this->destinations[this->bus];
    }
    else if (dynamic_pointer_cast<Rail>(vehicle) != nullptr)
    {
        dest = this->destinations[this->rail];
    }
    else if (dynamic_pointer_cast<Sprinter>(vehicle) != nullptr)
    {
        dest = this->destinations[this->sprinter];
    }
    if ((*nodes).size() != 0)
    {
        for (auto n = (*nodes).begin(); n != (*nodes).end(); n++)
        {
            if ((*n)->getStation()->getName().compare(this->station->getName()) == 0)
            {
                return;
            }
        }
        cout << this->station->getName() + '\t';
    }
    (*nodes).push_back(make_shared<Node>(*this));
    for (auto v = dest.begin(); v != dest.end(); v++)
    {
        (*v)->outbound(vehicle, nodes);
    }
}

//inbound function, recieve the vehicle , and a vector with the nodes that were already printed.
void Node::inbound(shared_ptr<Vehicle> vehicle, shared_ptr<vector<shared_ptr<Node>>> nodes)
{
    vector<shared_ptr<Node>> dest;
    if (dynamic_pointer_cast<Tram>(vehicle) != nullptr)
    {
        dest = this->sources[this->tram];
    }
    else if (dynamic_pointer_cast<Bus>(vehicle) != nullptr)
    {
        dest = this->sources[this->bus];
    }
    else if (dynamic_pointer_cast<Rail>(vehicle) != nullptr)
    {
        dest = this->sources[this->rail];
    }
    else if (dynamic_pointer_cast<Sprinter>(vehicle) != nullptr)
    {
        dest = this->sources[this->sprinter];
    }
    if ((*nodes).size() != 0)
    {
        for (auto n = (*nodes).begin(); n != (*nodes).end(); n++)
        {
            if ((*n)->getStation()->getName().compare(this->station->getName()) == 0)
            {
                return;
            }
        }
        cout << this->station->getName() + '\t';
    }
    (*nodes).push_back(make_shared<Node>(*this));
    for (auto v = dest.begin(); v != dest.end(); v++)
    {
        (*v)->inbound(vehicle, nodes);
    }
}

// djikstraAlgorithm function runs the djiskstra algorithm on 2 nodes to find the shortest path.
void Node::djikstraAlgorithm(shared_ptr<Vehicle> vehicle, queue<shared_ptr<Node>> nodes)
{
    if (nodes.size() == 0)
    {
        return;
    }
    vector<shared_ptr<Node>> dest;
    if (dynamic_pointer_cast<Tram>(vehicle) != nullptr)
    {
        dest = this->destinations[this->tram];
        vehicle = this->tram;
    }
    else if (dynamic_pointer_cast<Bus>(vehicle) != nullptr)
    {
        dest = this->destinations[this->bus];
        vehicle = this->bus;
    }
    else if (dynamic_pointer_cast<Rail>(vehicle) != nullptr)
    {
        dest = this->destinations[this->rail];
        vehicle = this->rail;
    }
    else if (dynamic_pointer_cast<Sprinter>(vehicle) != nullptr)
    {
        dest = this->destinations[this->sprinter];
        vehicle = this->sprinter;
    }
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if ((*n)->djikstra > this->djikstra + this->weights[*n][vehicle] + vehicle->getStopTime())
        {
            (*n)->djikstra = this->djikstra + this->weights[*n][vehicle] + vehicle->getStopTime();
        }
    }
    sort(dest.begin(), dest.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) { return a->djikstra < b->djikstra ? a : b; });
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if (this->djikstra <= (*n)->djikstra)
        {
            nodes.push(*n);
        }
    }
    nodes.pop();
    nodes.front()->djikstraAlgorithm(vehicle, nodes);
}

// mulDjikstraAlgorithm function sets the djisktra numbers in the
void Node::mulDjikstraAlgorithm(shared_ptr<Vehicle> vehicle, queue<shared_ptr<Node>> nodes, shared_ptr<Node> source)
{
    if (nodes.size() == 0)
    {
        return;
    }
    if (dynamic_pointer_cast<Tram>(vehicle) != nullptr)
    {
        vehicle = this->tram;
    }
    else if (dynamic_pointer_cast<Bus>(vehicle) != nullptr)
    {
        vehicle = this->bus;
    }
    else if (dynamic_pointer_cast<Rail>(vehicle) != nullptr)
    {
        vehicle = this->rail;
    }
    else if (dynamic_pointer_cast<Sprinter>(vehicle) != nullptr)
    {
        vehicle = this->sprinter;
    }
    auto dest = this->destinations[this->bus];
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        int newDjikstra = minWeight(this->bus, *n, source);
        if ((*n)->djikstra > newDjikstra)
        {
            (*n)->djikstra = newDjikstra;
        }
    }
    sort(dest.begin(), dest.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) { return a->djikstra < b->djikstra ? a : b; });
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if (this->djikstra <= (*n)->djikstra)
        {
            nodes.push(*n);
        }
    }
    dest = this->destinations[this->rail];
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        int newDjikstra = minWeight(this->rail, *n, source);
        if ((*n)->djikstra > newDjikstra)
        {
            (*n)->djikstra = newDjikstra;
        }
    }
    sort(dest.begin(), dest.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) { return a->djikstra < b->djikstra ? a : b; });
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if (this->djikstra <= (*n)->djikstra)
        {
            nodes.push(*n);
        }
    }
    dest = this->destinations[this->tram];
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        int newDjikstra = minWeight(this->tram, *n, source);
        if ((*n)->djikstra > newDjikstra)
        {
            (*n)->djikstra = newDjikstra;
        }
    }
    sort(dest.begin(), dest.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) { return a->djikstra < b->djikstra ? a : b; });
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if (this->djikstra <= (*n)->djikstra)
        {
            nodes.push(*n);
        }
    }
    dest = this->destinations[this->sprinter];
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        int newDjikstra = minWeight(this->sprinter, *n, source);
        if ((*n)->djikstra > newDjikstra)
        {
            (*n)->djikstra = newDjikstra;
        }
    }
    sort(dest.begin(), dest.end(), [](shared_ptr<Node> a, shared_ptr<Node> b) { return a->djikstra < b->djikstra ? a : b; });
    for (auto n = dest.begin(); n != dest.end(); n++)
    {
        if (this->djikstra <= (*n)->djikstra)
        {
            nodes.push(*n);
        }
    }
    nodes.pop();
    nodes.front()->mulDjikstraAlgorithm(vehicle, nodes, source);
}

// minWeight function returns the new djikstra that will be set as n djikstra if is smaller then n current.
int Node::minWeight(shared_ptr<Vehicle> vehicle, shared_ptr<Node> n, shared_ptr<Node> source)
{
    int newDjisktra, addTime = 0;
    if(source->getStation()->getName().compare(this->getStation()->getName()) != 0)
    {
        if(this->lastVehicle == vehicle)
        {
            addTime = vehicle->getStopTime();
        }
        else
        {
            addTime = source->getStation()->getVehicleSwapTime();
        }
    }
    newDjisktra = this->djikstra + (this->weights[n][vehicle] > 0 ? this->weights[n][vehicle] : INT_MAX - this->djikstra);
    newDjisktra += addTime;
    if(newDjisktra < n->djikstra)
    {
        if (dynamic_pointer_cast<Tram>(vehicle) != nullptr)
        {
            n->lastVehicle = n->tram;
        }
        else if (dynamic_pointer_cast<Bus>(vehicle) != nullptr)
        {
            n->lastVehicle = n->bus;
        }
        else if (dynamic_pointer_cast<Rail>(vehicle) != nullptr)
        {
            n->lastVehicle = n->rail;
        }
        else if (dynamic_pointer_cast<Sprinter>(vehicle) != nullptr)
        {
            n->lastVehicle = n->sprinter;
        }
        return newDjisktra;
    }
    return INT_MAX;
}
