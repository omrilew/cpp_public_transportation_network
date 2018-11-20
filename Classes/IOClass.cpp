#include "IOClass.h"

// not default Ctor in purpose.
IOClass::IOClass(vector<string> argv)
{
    this->configFile = "";
    this->outputFile = "";
    checkArguments(argv);
}

//  returns the graph after reading from the input files and creating all the intersections and vehicles to move between.
void IOClass::getGraph(shared_ptr<Graph> graph)
{
    string line;
    string type;
    int setTo;
    //auto graph = make_shared<Graph>();
    if (inFiles.size() == 0)
    {
        graph = nullptr;
        return;
    }
    if (configFile.size() > 0)
    {
        ifstream confFile(this->configFile);
        while (getline(confFile, line))
        {
            istringstream sStream(line);
            sStream >> type;
            sStream >> setTo;
            if (type.compare("intercity") == 0)
            {
                Intercity::derivedSwapTime = setTo;
            }
            else if (type.compare("central") == 0)
            {
                Central::derivedSwapTime = setTo;
            }
            else if (type.compare("stad") == 0)
            {
                Stad::derivedSwapTime = setTo;
            }
            else if (type.compare("bus") == 0)
            {
                Bus::derivedStopTime = setTo;
            }
            else if (type.compare("tram") == 0)
            {
                Tram::derivedStopTime = setTo;
            }
            else if (type.compare("sprinter") == 0)
            {
                Sprinter::derivedStopTime = setTo;
            }
            else if (type.compare("rail") == 0)
            {
                Rail::derivedStopTime = setTo;
            }
        }
        confFile.close();
    }
    for (auto fName = this->inFiles.begin(); fName != this->inFiles.end(); fName++)
    {
        ifstream file(fName->c_str(), fstream::in);
        while (getline(file, line))
        {
            string source_node, target_node;
            int duration;
            istringstream stream(line);
            getline(stream, source_node, '\t');
            getline(stream, target_node, '\t');
            if(source_node.size() > 16 || source_node.find(' ') != string::npos)
            {
                throw(InputFileException("ERROR: node name " + source_node + " is illegal."));
            }
            if(target_node.size() > 16 || target_node.find(' ') != string::npos)
            {
                throw(InputFileException("ERROR: node name " + target_node + " is illegal."));
            }
            stream >> duration;
            graph->addConnection(source_node, target_node, duration, *fName);
        }
        file.close();
    }
    return;
}
//  this function checks if given config file is in the correct format
bool IOClass::checkConfigFile(string fname)
{
    string line, type;
    int setTo, spaceCnt = 0;
    ifstream confFile;
    confFile.exceptions(ifstream::failbit | ifstream::badbit);
    try
    {
        confFile.open(fname.c_str(), fstream::in);
    }
    catch (ifstream::failure e)
    {
        throw(ConfigFileException("Can't open configuration file '" + fname + "'"));
    }
    while (!confFile.eof())
    {
        getline(confFile, line);
        for (auto c = line.begin(); c != line.end(); c++)
        {
            if (*c == ' ')
            {
                spaceCnt++;
            }
        }
        if (spaceCnt != 1)
        {
            confFile.close();
            return false;
        }
        istringstream sStream(line);
        getline(sStream, type, ' ');
        if (sStream.eof())
        {
            confFile.close();
            return false;
        }
        sStream >> setTo;
        if (setTo < 0 || sStream.fail() || !sStream.eof())
        {
            confFile.close();
            return false;
        }
        spaceCnt = 0;
    }
    confFile.close();
    return true;
}

// this function checks if a given init file is in the correct format.
bool IOClass::checkInFile(string fname)
{
    string line;
    ifstream file;
    int tabCnt = 0;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try
    {
        file.open(fname.c_str(), fstream::in);
    }
    catch (ifstream::failure e)
    {
        throw(InputFileException("Can't open input file '" + fname + "'"));
        return false;
    }
    while (!file.eof())
    {
        getline(file, line);
        for (auto c = line.begin(); c != line.end(); c++)
        {
            if (*c == '\t')
            {
                tabCnt++;
            }
        }
        if (tabCnt != 2)
        {
            file.close();
            return false;
        }
        string source_node, target_node;
        int duration;
        istringstream stream(line);
        getline(stream, source_node, '\t');
        if (stream.eof())
        {
            file.close();
            return false;
        }
        getline(stream, target_node, '\t');
        if (stream.eof())
        {
            file.close();
            return false;
        }
        stream >> duration;
        if (!stream.eof() || stream.fail() || duration < 0)
        {
            file.close();
            return false;
        }
        tabCnt = 0;
    }
    file.close();
    return true;
}

//  checks if the given program arguments are correct.
void IOClass::checkArguments(vector<string> argv)
{
    if (argv.size() < 3 || argv[1].compare("-i") != 0) // check if the is atleast ./<progname> <-i> <inputfile>
    {
        throw(UsageException());
    }
    for (int i = 2; i < argv.size(); i++) // run from the first inputfile to the end of files.
    {
        if (argv[i].compare("-c") == 0 && i < argv.size() - 1 && i > 2) // if there is a '-c' flag after 1 or more input files
        {
            i++;
            if (!checkConfigFile(argv[i]))
            {
                throw(ConfigFileException("Configuration file '" + argv[i] + "' is in wrong format!"));
            }
            this->configFile = argv[i];
            continue;
        }
        if (argv[i].compare("-o") == 0 && i < argv.size() - 1 && i > 2) // if there is a '-o' flag after 1 or more input files
        {
            i++;
            this->outputFile = argv[i];
            if (i != argv.size() - 1)
            {
                throw(UsageException());
            }
            continue;
        }

        // Check if the filename starts with "bus", "tram", "rail", "sprinter"
        if ((argv[i].substr(0, 3).find("bus") != 0 && argv[i].substr(0, 4).find("tram") != 0 && argv[i].substr(0, 4).find("rail") != 0 && argv[i].substr(0, 8).find("sprinter") != 0))
        {
            throw(InputFileException("input file's '" + argv[i] + "' name is in wrong format"));
        }
        if (!checkInFile(argv[i]))
        {
            throw(InputFileException("Input file '" + argv[i] + "' is in wrong format"));
        }
        this->inFiles.push_back(argv[i]);
    }
}

//  prints the whole graph into the given or default output.dat file.
void IOClass::printGraph(shared_ptr<Graph> graph)
{
    if(this->outputFile.compare("") == 0)
    {
        this->outputFile = "output.dat";
    }
    ofstream outFile(this->outputFile, fstream::out);
    for (auto node = graph->getStations().begin(); node != graph->getStations().end(); node++)
    {
        outFile << "From " + (*node)->getStation()->getName() + " -" << endl;
        for (auto n = (**node)[(*node)->bus].begin(); n != (**node)[(*node)->bus].end(); n++)
        {
            if (n == (**node)[(*node)->bus].begin())
            {
                outFile << "Bus : ";
            }
            outFile << (*n)->getStation()->getName() << " " << (*node)->getWeights()[*n][(*node)->bus];
            if (n != (**node)[(*node)->bus].end() - 1)
            {
                outFile << ", ";
            }
            else
            {
                outFile << endl;
            }
        }
        for (auto n = (**node)[(*node)->rail].begin(); n != (**node)[(*node)->rail].end(); n++)
        {
            if (n == (**node)[(*node)->rail].begin())
            {
                outFile << "Rail : ";
            }
            outFile << (*n)->getStation()->getName() << " " << (*node)->getWeights()[*n][(*node)->rail];
            if (n != (**node)[(*node)->rail].end() - 1)
            {
                outFile << ", ";
            }
            else
            {
                outFile << endl;
            }
        }
        for (auto n = (**node)[(*node)->tram].begin(); n != (**node)[(*node)->tram].end(); n++)
        {
            if (n == (**node)[(*node)->tram].begin())
            {
                outFile << "Tram : ";
            }
            outFile << (*n)->getStation()->getName() << " " << (*node)->getWeights()[*n][(*node)->tram];
            if (n != (**node)[(*node)->tram].end() - 1)
            {
                outFile << ", ";
            }
            else
            {
                outFile << endl;
            }
        }
        for (auto n = (**node)[(*node)->sprinter].begin(); n != (**node)[(*node)->sprinter].end(); n++)
        {
            if (n == (**node)[(*node)->sprinter].begin())
            {
                outFile << "Sprinter : ";
            }
            outFile << (*n)->getStation()->getName() << " " << (*node)->getWeights()[*n][(*node)->sprinter];
            if (n != (**node)[(*node)->sprinter].end() - 1)
            {
                outFile << ", ";
            }
            else
            {
                outFile << endl;
            }
        }
    }
}

//  this is the terminal that the client communicate with.
void IOClass::terminal()
{
    shared_ptr<Graph> graph = make_shared<Graph>();
    getGraph(graph);
    string cmd;
    while (true)
    {
        cin >> cmd;
        if (cmd.compare("load") == 0)
        {
            ifstream f;
            string fileName;
            cin >> fileName;
            try
            {
                checkInFile(fileName);
                this->inFiles.push_back(fileName);
                getGraph(graph);
            }
            catch (...)
            {
                cerr << "ERROR opening the specified file." << endl;
                continue;
            }
            cout << "Update was successful." << endl;
        }
        else if (cmd.compare("outbound") == 0)
        {
            string stationName;
            cin >> stationName;
            auto node = graph->getNode(stationName);
            if (node == nullptr)
            {
                cerr << stationName + " does not exist in the current network" << endl;
                continue;
            }
            cout << "bus: ";
            if ((*node)[node->bus].size() == 0)
            {
                cout << "no outbound travel";
            }
            else
            {
                node->outbound(node->bus, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "tram: ";
            if ((*node)[node->tram].size() == 0)
            {
                cout << "no outbound travel";
            }
            else
            {
                node->outbound(node->tram, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "sprinter: ";
            if ((*node)[node->sprinter].size() == 0)
            {
                cout << "no outbound travel";
            }
            else
            {
                node->outbound(node->sprinter, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "rail: ";
            if ((*node)[node->rail].size() == 0)
            {
                cout << "no outbound travel";
            }
            else
            {
                node->outbound(node->rail, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
        }
        else if (cmd.compare("inbound") == 0)
        {
            string stationName;
            cin >> stationName;
            auto node = graph->getNode(stationName);
            if (node == nullptr)
            {
                cerr << stationName + " does not exist in the current network" << endl;
                continue;
            }
            cout << "bus: ";
            if ((*node).getSources()[node->bus].size() == 0)
            {
                cout << "no inbound travel";
            }
            else
            {
                node->inbound(node->bus, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "tram: ";
            if ((*node).getSources()[node->tram].size() == 0)
            {
                cout << "no inbound travel";
            }
            else
            {
                node->inbound(node->tram, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "sprinter: ";
            if ((*node).getSources()[node->sprinter].size() == 0)
            {
                cout << "no inbound travel";
            }
            else
            {
                node->inbound(node->sprinter, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
            cout << "rail: ";
            if ((*node).getSources()[node->rail].size() == 0)
            {
                cout << "no inbound travel";
            }
            else
            {
                node->inbound(node->rail, make_shared<vector<shared_ptr<Node>>>());
            }
            cout << endl;
        }
        else if (cmd.compare("print") == 0)
        {
            printGraph(graph);
        }
        else if (cmd.compare("uniExpress") == 0)
        {
            string src, trg;
            cin >> src >> trg;
            try
            {
                graph->uniExpress(src, trg);
            }
            catch(NodeNotFoundException ex)
            {
                cerr << ex.message << endl;
            }
        }
        else if (cmd.compare("multiExpress") == 0)
        {
            string src, trg;
            cin >> src >> trg;
            try
            {
                graph->multiExpress(src, trg);
            }
            catch(NodeNotFoundException ex)
            {
                cerr << ex.message << endl;
            }
        }
        else if (cmd.compare("QUIT") == 0)
        {
            exit(1);
        }
    }
}

