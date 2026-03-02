// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#include <include/boot.h>
#include <include/string.h>

/// BUGS: 0

#define ARM64_MMIO_REG(addr) (*(volatile uint32_t*) (nb_uart_ptr + addr))

/* this file handles the UART */

static uint32_t* nb_uart_ptr = (uint32_t*) NB_UART_BASE;

/// @brief Retrieve character from nb_uart_ptr
utf_char_t nb_get_char(void) {
  while ((ARM64_MMIO_REG(0x018) & (1 << 4))) {
  }

  return (utf_char_t) ARM64_MMIO_REG(0x0) & 0xFF;
}

void nb_put_char(utf_char_t ch) {
  while ((ARM64_MMIO_REG(0x018) & (1 << 5))) {
  }

  ARM64_MMIO_REG(0x0) = ch;
}

/// @brief UART put string
/// @param text the input text.
size_t nb_put_string(const char* text) {
  if (text == nil) return 0;

  size_t i = 0;

  for (; i < strlen(text); i++) {
    nb_put_char(text[i]);
  }

  return i;
}
