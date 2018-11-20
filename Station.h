//
// Created by Admin on 04/05/2018.
//
#ifndef STATION_H
#define STATION_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Station
{
protected:
  string name;
  static int vehicleSwapTime;

public:
  //  C'tors D'tor
  Station();
  Station(string name, int vehicleSwapTime);
  Station(const Station &s);
  virtual ~Station() {}
  //  Operators
  Station &operator=(const Station &s);
  //  Functions

  //  Get/Set

  string getName() const { return this->name; }
  void setName(string &name) { this->name = name; }

  virtual int getVehicleSwapTime() const { return this->vehicleSwapTime; }
  virtual void setVehicleSwapTime(int vehicleSwapTime) { this->vehicleSwapTime = vehicleSwapTime; }
};
#endif //STATION_H
