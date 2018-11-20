#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

using namespace std;

class UsageException
{
    public:
        string message = "USAGE : ./<progName> -i <infile1> (1 or more)... (optional) -c <configFile> (optional) -o <outPutFile>";
};

class InputFileException
{
    public:
        string message;
        InputFileException(string error) {this->message = error;}
};

class ConfigFileException
{
    public:
        string message;
        ConfigFileException(string error) {this->message = error;}
};

class NodeNotFoundException
{
    public:
        string message;
        NodeNotFoundException(string error) {this->message = error;}
};
#endif //   EXCEPTIONS_H