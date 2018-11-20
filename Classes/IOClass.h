#ifndef IOCLASS_H
#define IOCLASS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Graph.h"
#include "Exceptions.h"
using namespace std;

class IOClass
{
  private:
    vector<string> inFiles;
    string configFile;
    string outputFile;

  public:
    // Ctors
    IOClass(){}
    IOClass(vector<string> argv);
    ~IOClass() {}
    // Functions
    void getGraph(shared_ptr<Graph> graph);
    bool checkInFile(string fname);
    bool checkConfigFile(string fname);
    void checkArguments(vector<string> argv);
    void printGraph(shared_ptr<Graph> graph);
    void terminal();
};

#endif // IOCLASS_H