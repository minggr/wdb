#ifndef GOSSIP_H
#define GOSSIP_H

#include <string>
#include <cstdint>
using namespace std;

class Value {

};

struct Group {
  string name;      // Group name
  int32_t limit;        // Maximum number of keys in group
};

struct Info {
  string key;       // Info key
  Value value;      // Info value
  Group *group;     // Group name
  string node;      // Originating node name
  float ts;         // Wall time of origination
  float ttl;        // Time in seconds before info is discarded
  uint32_t hops;    // Number of hops from originator 
};

#endif
