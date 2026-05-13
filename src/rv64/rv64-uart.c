// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-ci/next-boot

#include <include/boot.h>
#include <include/string.h>

/// BUGS: 0

/* this file handles the UART */

static uint8_t* nb_uart_ptr = (uint8_t*) NB_UART_BASE;

utf_char_t nb_get_char(void) {
  uintptr_t ptr = NB_UART_BASE;

  while (!(*(((volatile uint8_t*) ptr) + 0x05) & 0x01));

  return (utf_char_t) *nb_uart_ptr;
}

// we need that one, to avoid sending mutliple chars to UART.
static boolean nb_locked_put_char = no;

void nb_put_char(utf_char_t ch) {
  int32_t timeout = 0;

  while (nb_locked_put_char) {
    ++timeout;

    if (timeout > 1000000) break;
  }

  nb_locked_put_char = yes;
  *nb_uart_ptr       = ch;
  nb_locked_put_char = no;
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
