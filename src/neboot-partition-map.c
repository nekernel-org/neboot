// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#include <include/partition-map.h>
#include <include/string.h>

// include this for documentation.

#define NB_FILESYSTEM_COUNT (5U)
#define NB_FILESYSTEM_LIST {"NeFS", "HeFS", "FAT32", "ext4", "XeFS"}

/// @brief check if filesystem is supported by NeBoot.
/// @param fs the filesystem magic, as provided by EPM.
boolean nb_filesystem_exists(caddr_t fs, size_t len) {
  if (fs == nil || *fs == 0) return no;

  char* fs_list[] = NB_FILESYSTEM_LIST;

  for (size_t fs_index = 0; fs_index < NB_FILESYSTEM_COUNT; fs_index++) {
    if (strncmp(fs_list[fs_index], fs, strlen(fs_list[fs_index])) == 0) {
      return yes;
    }
  }

  return no;
}
