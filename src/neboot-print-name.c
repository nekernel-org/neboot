/* -------------------------------------------

  Copyright (C) 2024, Amlal El Mahrouss, licensed under Apache 2.0.

------------------------------------------- */

#include <lib/boot.h>

/// @brief Print firmware name.
/// @param
void cb_print_name(void) {
#ifdef __COMPILE_POWERPC__
  cb_put_string(">> NeBoot for POWERPC.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_ARM64__
  cb_put_string(">> NeBoot for ARM64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
  cb_put_string(">> NeBoot for AMD64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
  cb_put_string(">> NeBoot for RISC-V.\r\n");
#endif  // __COMPILE_POWERPC__
}
