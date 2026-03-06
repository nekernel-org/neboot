// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#include <include/boot.h>

/// @brief Restarts the computer.
/// @param none.
void nb_restart_machine(void) {
#ifdef __COMPILE_RISCV__
  volatile uint32_t* brd_pwr = (volatile uint32_t*) 0x100000;
  *brd_pwr                   = 0x7777;  // send reboot signal from DMA.

  while (1) {
    asm volatile("wfi");
  }
#else
  /// @todo add your reset vector here.
  while (1);
#endif
}
