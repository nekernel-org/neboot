// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#include <include/boot.h>
#include <include/string.h>

/// BUGS: 0

#define NB_NS16550_COM1 (NB_UART_BASE + 0x4500)
#define NB_NS16550_COM2 (NB_UART_BASE + 0x4600)

volatile ascii_char_t* const UART0DR = (ascii_char_t*) NB_NS16550_COM1;

/* this file handles the UART */

/// @brief Get character from UART.
/// @param
/// @return
utf_char_t nb_get_char(void) {
  while (!(*(((volatile uint8_t*) UART0DR) + 0x05) & 0x01));
  return (utf_char_t) *UART0DR;
}

/// @brief Put character into UART.
/// @param ch
void nb_put_char(utf_char_t ch) {
  *UART0DR = (ascii_char_t) (ch);
}

/// @brief Put string in UART.
/// @param text the input text.
size_t nb_put_string(const char* text) {
  while (*text != '\0') { /* Loop until end of string */

    nb_put_char(*text); /* Transmit char */

    text++; /* Next char */
  }
  return 0;
}
