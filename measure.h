#ifndef MEASURE_H_
#define MEASURE_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 984963

  This file contains the decalaration of the Measure class.

  TODO: Read the block comments with TODO in measure.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include<string>

#include "lib_json.hpp"
using json = nlohmann::json;

struct PAIR {
  int year;
  double value;
};

/*
  The Measure class contains a measure code, label, and a container for readings
  from across a number of years.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/
class Measure {
public:
  std::string codename, label;
  std::vector<PAIR> pair_list;
public:
  Measure(){};
  Measure(std::string codename, const std::string &label);  
 
  std::string getCodename();
  std::string getLabel();
  void setLabel(std::string);

  double getValue(int year);
  void setValue(int, double);
  double getDifference();
  double getDifferencePercentage();
  double getAverage();
  int size();

  friend std::ostream& operator<<(std::ostream& os, const Measure& meas){
    for(auto pair : meas.pair_list) {
      std::cout << pair.year << "\t";
    }
    std::cout << "Average\tDiff.\t% Diff.\n";
    double total = 0;
    for(auto pair : meas.pair_list) {
      total += pair.value;
      std::cout << pair.value << "\t";
    }
    std::cout << total / meas.pair_list.size() << std::endl;
    return os;
  }

  friend bool operator==(const Measure& lhs, const Measure& rhs)
  {
    if(lhs.codename != rhs.codename) return false;
    if(lhs.label != rhs.label) return false;

    if(lhs.pair_list.size() != rhs.pair_list.size()) return false;

    for(size_t i=0; i<lhs.pair_list.size(); i++){
      if(lhs.pair_list[i].year != rhs.pair_list[i].year) return false;
      if(lhs.pair_list[i].value != rhs.pair_list[i].value) return false;
    }
    return true;
  }

  json toJSON() {
    json j;

    for(auto e : pair_list) {
      std::string key = std::to_string(e.year), value = std::to_string(e.value);
      j[key] = value;
    }

    return j;
  }

};

#endif // MEASURE_H_