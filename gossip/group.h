#ifndef GROUP_H
#define GROUP_H

#include "info.h"

namespace gossip {

typedef int GroupType;
const GroupType MIN_GROUP = 0;
const GroupType MAX_GROUP = 1;

// Groups organize a collection of Info objects sharing a common key
// prefix (prefix is defined up to the last period character '.').
// Groups maintain a limited-size set of Info objects with set
// inclusion determined by group type. Two types are implemented here:
//
// MIN_GROUP, MAX_GROUP: maintain only minimum/maximum values added
// to group respectively.

class Group {
public:
  bool shouldInclude(Info *info);
  void updateIncremental(Info *info);
  void update();
  bool compact();
  void addInternal(Info *info);
  void removeInternal(Info *info);
  Group *NewGroup(string &prefix, int limit, GroupType typeOf);
  Info *GetInfo(string &key);
  InfoArray Infos();
  bool AddInfo(Info *info);
  Group *Delta(int32_t seq);

private:
  string prefix;        // Key prefix for Info items in group
  int limit;            // Maximum number of keys in group
  GroupType typeOf;     // Minimums or maximums of all values encountered
  int64_t minTTLStamp;  // Minimum of all infos' TTLs (Unix nanos)
  Info *gatekeeper;     // Minimum or maximum value in infos map, depending on type
  InfoMap infos;        // Map of infos in group
};

// Group map is from group prefix => *Group
typedef unordered_map<string, Group *> GroupMap;

}

#endif
