#ifndef Vehicle_h
#define Vehicle_h

#include <iostream>
using namespace std;

class Vehicle
{
private:
  static int stationStopTime;

public:
  //  C'tors D'tor
  Vehicle();
  Vehicle(int stopTime);
  Vehicle(const Vehicle &v);
  virtual ~Vehicle() {}
  //  Operators
  Vehicle &operator=(const Vehicle &v);
  //  Functions

  //  Get/Set
  virtual int getStopTime() const { return this->stationStopTime; }
  virtual void setStopTime(int stopTime) { this->stationStopTime = stopTime; }
};
#endif /* Vehicle_h */ //