#ifndef PCOREEXTERN_H
#define PCOREEXTERN_H

#include "pcoreConfig.h"

struct Pcore_Version {
  static constexpr int major = PCORE_VERSION_MAJOR;
  static constexpr int minor = PCORE_VERSION_MINOR;
  static constexpr int patch = PCORE_VERSION_PATCH;
};

const Pcore_Version& coreLibraryVersion();

#endif  // PCOREEXTERN_H
