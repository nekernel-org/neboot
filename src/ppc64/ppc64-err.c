// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#include <include/boot.h>

/// BUGS: 0

/// @brief Goes into a panic state.
/// @param reason why?
void cb_panic(const char* reason) {
  cb_put_string("Error: ");
  cb_put_string(reason);
  cb_put_char('\n');

  while (yes) {
    (void) 0;
  }
}
