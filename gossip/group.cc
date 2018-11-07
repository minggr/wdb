#include "group.h"
#include "info.h"

namespace gossip {

// Returns true if the specified info should belong in the group
// according to the group type and the value.
bool Group::shouldInclude(Info *info)
{
#if 0
    if group.gatekeeper == nil || len(group.infos) < group.limit {
        return true
    }
    switch group.typeOf {
    case MIN_GROUP:
        return info.Val.Less(group.gatekeeper.Val)
    case MAX_GROUP:
        return !info.Val.Less(group.gatekeeper.Val)
    default:
        panic(fmt.Errorf("unknown group type %d", group.typeOf))
    }
#endif

  switch (typeOf) {
  case MIN_GROUP:
    return info->Val.Less(gatekeeper->Val);
  }

  if (gatekeeper == nullptr || (int)infos.size() < limit) 
    return true;

  return false;
}

}
