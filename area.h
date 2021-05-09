#ifndef AREA_H_
#define AREA_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: 984963

  This file contains the Area class declaration. Area objects contain all the
  Measure objects for a given local area, along with names for that area and a
  unique authority code.

  TODO: Read the block comments with TODO in area.cpp to know which 
  functions and member variables you need to declare in this class.
 */

#include <string>
#include <vector>

struct Str_LangValue{
  std::string lang_code;
  std::string lang_value;
};

#include "lib_json.hpp"
using json = nlohmann::json;

#include "measure.h"

/*
  An Area object consists of a unique authority code, a container for names
  for the area in any number of different languages, and a container for the
  Measures objects.

  TODO: Based on your implementation, there may be additional constructors
  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/

class Area {

private:
  std::string autority_code;
  std::vector<Str_LangValue> lang_list;
  std::vector<Measure> meas_list;
public:

  Area(const std::string& localAuthorityCode);

  std::string getLocalAuthorityCode();
  void setName(std::string, std::string);
  std::string getName(std::string);
  void setMeasure(std::string, Measure meas);
  Measure getMeasure(std::string);

  std::vector<Measure> &getMeasures() {return meas_list;}

  json toJSON() {
    json names;
    json meases;

    for(size_t i=0; i<lang_list.size(); i++) {
      names[lang_list[i].lang_code] = lang_list[i].lang_value;
    }

    for(size_t i=0; i<meas_list.size(); i++){
      meases[meas_list[i].getLabel()] = meas_list[i].toJSON();
    }

    json j;
    j["names"] = names;
    j["measures"] = meases;

    return j;
  }

  int size();

  friend std::ostream& operator<<(std::ostream& os, const Area& area){
    for(size_t i=0; i<area.lang_list.size(); i++) {
      os << area.lang_list[i].lang_value << (i != area.lang_list.size()-1 ? " / " : "");
    }
    os << " (" << area.autority_code << ")" << std::endl;

    for(size_t i=0; i<area.meas_list.size(); i++){
      os<<area.meas_list[i]<<std::endl;
    }
    return os;
  }

  friend bool operator==(const Area& lhs, const Area& rhs)
  {
    if(lhs.autority_code != rhs.autority_code) return false;
    if(lhs.lang_list.size() != rhs.lang_list.size()) return false;
    for(size_t i=0; i<lhs.lang_list.size(); i++)
    {
      if(lhs.lang_list[i].lang_code != rhs.lang_list[i].lang_code) return false;
      if(lhs.lang_list[i].lang_value != rhs.lang_list[i].lang_value) return false;
    }

    for(size_t i=0; i<lhs.meas_list.size(); i++){
      if(lhs.meas_list[i] == rhs.meas_list[i]) 
        continue;
      else
        return false;
    }
    //if(lhs.meas_list.size() != rhs.meas_list.size()) return false;
    return true;
  }

};

#endif // AREA_H_