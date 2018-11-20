//
// Created by Admin on 04/05/2018.
//

#include "Station.h"

int Station::vehicleSwapTime = 0;
Station::Station()
{
    this->name = "";
    this->vehicleSwapTime = 0;
}

Station::Station( string name, int vehicleSwapTime)
{
    this->name = string(name);
    this->vehicleSwapTime = vehicleSwapTime;
}

Station::Station(const Station &s)
{
    this->name = string(s.name);
    this->vehicleSwapTime = s.vehicleSwapTime;
}

Station &Station::operator=(const Station &s)
{
    if (&s == this)
    {
        return *this;
    }
    this->name = string(s.name);
    this->vehicleSwapTime = s.vehicleSwapTime;
    return *this;
}