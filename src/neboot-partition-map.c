/* -------------------------------------------

  Copyright (C) 2024, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

#include <lib/partition-map.h>
#include <lib/string.h>

// include this for documentation.

#define NB_FILESYSTEM_COUNT (5U)
#define NB_FILESYSTEM_LIST \
  { "NeFS", "HeFS", "FAT32", "ext4", "XeFS" }

/// @brief check if filesystem is supported by NeBoot.
/// @param fs the filesystem magic, as provided by EPM.
boolean cb_filesystem_exists(caddr_t fs, size_t len) {
  if (fs == nil || *fs == 0) return no;

  char* fs_list[] = NB_FILESYSTEM_LIST;

  for (size_t fs_index = 0; fs_index < NB_FILESYSTEM_COUNT; fs_index++) {
    if (strncmp(fs_list[fs_index], fs, strlen(fs_list[fs_index])) == 0) {
      return yes;
    }
  }

  return no;
}
