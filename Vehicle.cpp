#include "Vehicle.h"

int Vehicle::stationStopTime = 0;

Vehicle::Vehicle()
{
    this->stationStopTime = 0;
}
Vehicle::Vehicle(int stopTime)
{
    this->stationStopTime = stopTime;
}
Vehicle::Vehicle(const Vehicle &v)
{
    this->stationStopTime = v.stationStopTime;
}

Vehicle &Vehicle::operator=(const Vehicle &v)
{
    if (&v == this)
    {
        return *this;
    }
    this->stationStopTime = v.stationStopTime;
    return *this;
}
