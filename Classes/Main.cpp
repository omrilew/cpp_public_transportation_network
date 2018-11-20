//
//  Main.cpp
//  hw2
//
//  Created by omri lewkowicz on 29/05/2018.
//  Copyright © 2018 omri lewkowicz. All rights reserved.
//

#include "IOClass.h"

int main(int argc, char *argv[])
{
    vector<string> v = vector<string>();
    IOClass io;
    for (int i = 0; i < argc; i++)
    {
        v.push_back(string(argv[i]));
    }
    try
    {
        io = IOClass(v);
        io.terminal();
    }
    catch (UsageException e)
    {
        cerr << e.message << endl;
        exit(1);
    }
    catch (InputFileException e)
    {
        cerr << e.message << endl;
        exit(1);
    }
    catch (ConfigFileException e)
    {
        cerr << e.message << endl;
        exit(1);
    }
    catch (...)
    {
        cerr << "Wrong File Format." << endl;
        exit(1);
    }
    return 0;
}
