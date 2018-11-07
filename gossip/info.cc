#include "info.h"

namespace gossip {

string InfoPrefix(string &key)
{
  size_t index = key.find_last_of('.');
  if (index == string::npos)
    return "";
  else
    return key.substr(0, index);
}

}
