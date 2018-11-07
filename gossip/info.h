#ifndef INFO_H
#define INFO_H

#include <string>
#include <cstdint>
#include <unordered_map>
#include <vector>
using namespace std;

namespace gossip {

class Value {
public:
  virtual bool Less(Value &v) const;
  virtual float GetVal() const;
};

class Float64Value : Value {
public:
  bool Less(Value &v) const
  {
    return val < v.GetVal(); 
  }

  float GetVal() const { return val; }

private:
  float val;
};

// Info objects are the basic unit of information traded over the
// gossip network.
struct Info {
  string Key; // Info key
  Value Val; // Info value
  int64_t Timestamp;  // Wall time at origination (Unix-nanos)
  int64_t TTLStamp;  // Wall time before info is discarded (Unix-nanos)
  int32_t Seq;  // Sequence number for incremental updates
  string Node; // Originating node name
  uint32_t Hops; // Number of hops from originator
};

typedef unordered_map<string, Info *> InfoMap;

class InfoArray {
public:
  int Len() { return a.size(); }

  void Swap(int i, int j)
  {
    Info *tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
  }

  bool Less(int i, int j)
  {
    return a[i]->Val.Less(a[j]->Val);
  }

private:
  vector<Info *> a;
};

}

#endif
