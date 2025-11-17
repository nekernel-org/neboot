/* -------------------------------------------

  Copyright (C) 2024, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

#include <lib/boot.h>

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
