// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-ci/next-boot

#include <include/boot.h>

/// @brief Print firmware name.
/// @param
void nb_print_name(void) {
#ifdef __COMPILE_POWERPC__
  nb_put_string(">> Ne.app BCSABoot for POWERPC.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_ARM64__
  nb_put_string(">> Ne.app BCSABoot for ARM64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
  nb_put_string(">> Ne.app BCSABoot for AMD64.\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_RISCV__
  nb_put_string(">> Ne.app BCSABoot for RISC-V.\r\n");
#endif  // __COMPILE_POWERPC__
}
