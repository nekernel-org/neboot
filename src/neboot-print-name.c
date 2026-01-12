// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#include <include/boot.h>

/// @brief Print firmware name.
/// @param
void nb_print_name(void) {
#ifdef __COMPILE_POWERPC__
  nb_put_string(">> NeBoot for POWERPC.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_ARM64__
  nb_put_string(">> NeBoot for ARM64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
  nb_put_string(">> NeBoot for AMD64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
  nb_put_string(">> NeBoot for RISC-V.\r\n");
#endif  // __COMPILE_POWERPC__
}
