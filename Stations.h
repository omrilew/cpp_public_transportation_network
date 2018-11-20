#ifndef STATIONS_H
#define STATIONS_H

#include "Station.h"

class Intercity : public Station
{
  public:
    static int derivedSwapTime;
    Intercity() : Station("", 15) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 15;}
    Intercity(string name) : Station(name, 15) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 15;}
    Intercity(string name, int vehicleSwapTime) : Station(name, vehicleSwapTime) {}
    Intercity(const Station &s) : Station(s) {}
    virtual int getVehicleSwapTime() const { return this->derivedSwapTime; }
    virtual void setVehicleSwapTime(int vehicleSwapTime) { this->derivedSwapTime = vehicleSwapTime; }
};

class Stad : public Station
{
  public:
    static int derivedSwapTime;
    Stad() : Station("", 10) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 10;}
    Stad(string name) : Station(name, 10) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 10;}
    Stad(string name, int vehicleSwapTime) : Station(name, vehicleSwapTime) {}
    Stad(const Station &s) : Station(s) {}
    virtual int getVehicleSwapTime() const { return this->derivedSwapTime; }
    virtual void setVehicleSwapTime(int vehicleSwapTime) { this->derivedSwapTime = vehicleSwapTime; }
};

class Central : public Station
{
  public:
    static int derivedSwapTime;
    Central() : Station("", 5) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 5;}
    Central(string name) : Station(name, 5) {this->derivedSwapTime = this->derivedSwapTime > 0 ? derivedSwapTime : 15;}
    Central(string name, int vehicleSwapTime) : Station(name, vehicleSwapTime) {}
    Central(const Station &s) : Station(s) {}
    virtual int getVehicleSwapTime() const { return this->derivedSwapTime; }
    virtual void setVehicleSwapTime(int vehicleSwapTime) { this->derivedSwapTime = vehicleSwapTime; }
};

#endif // STATIONS_H