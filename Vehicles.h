#ifndef VEHICLES_H
#define VEHICLES_H

#include "Vehicle.h"

class Rail : public Vehicle
{
public:
  static int derivedStopTime;
  Rail() : Vehicle(5) {this->derivedStopTime = derivedStopTime > 0 ? derivedStopTime : 5;}
  Rail(int stopTime) : Vehicle(stopTime) {this->derivedStopTime = stopTime;}
  Rail(const Vehicle &v) : Vehicle(v) {this->derivedStopTime = v.getStopTime();}
  virtual int getStopTime() const { return this->derivedStopTime; }
  void setStopTime(int stopTime) { this->derivedStopTime = stopTime; }
};

class Tram : public Vehicle
{
public:
  static int derivedStopTime;
  Tram() : Vehicle(3) {this->derivedStopTime = derivedStopTime > 0 ? derivedStopTime : 3;}
  Tram(int stopTime) : Vehicle(stopTime) {this->derivedStopTime = stopTime;}
  Tram(const Vehicle &v) : Vehicle(v) {this->derivedStopTime = v.getStopTime();}
  virtual int getStopTime() const { return this->derivedStopTime; }
  void setStopTime(int stopTime) { this->derivedStopTime = stopTime; }
};

class Bus : public Vehicle
{
public:
  static int derivedStopTime;
  Bus() : Vehicle(2) {this->derivedStopTime = derivedStopTime > 0 ? derivedStopTime : 2;}
  Bus(int stopTime) : Vehicle(stopTime) {this->derivedStopTime = stopTime;}
  Bus(const Vehicle &v) : Vehicle(v) {this->derivedStopTime = v.getStopTime();}
  virtual int getStopTime() const { return this->derivedStopTime; }
  void setStopTime(int stopTime) { this->derivedStopTime = stopTime; }
};

class Sprinter : public Vehicle
{
public:
  static int derivedStopTime;
  Sprinter() : Vehicle(4) {this->derivedStopTime = derivedStopTime > 0 ? derivedStopTime : 4;}
  Sprinter(int stopTime) : Vehicle(stopTime) {this->derivedStopTime = stopTime;}
  Sprinter(const Vehicle &v) : Vehicle(v) {this->derivedStopTime = v.getStopTime();}
  virtual int getStopTime() const { return this->derivedStopTime; }
  void setStopTime(int stopTime) { this->derivedStopTime = stopTime; }
};

#endif // VEHICLES_H
