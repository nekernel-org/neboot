// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#pragma once

#include <include/boot.h>

#define BOOTNET_INET_MAGIC "ONET"
#define BOOTNET_INET_MAGIC_LEN (4)

#define BOOTNET_NAME_LEN (256)

struct _bootnet_inet_header;

/// @brief Netboot Internet Header
/// Consists of 4 magic characters, and a set of fields describing the current patch that's being
/// sent (if m_preflight = 0)
/// @note Can be used to patch ROMs too (if m_implies_rom = 1)
typedef struct _bootnet_inet_header {
  ascii_char_t m_nb1;  /// magic char 1 'N'
  ascii_char_t m_nb2;  /// magic char 2 'E'
  ascii_char_t m_nb3;  /// magic char 3 'T'
  ascii_char_t m_nb4;  /// magic char 4 'B'

  ascii_char_t m_patch_name[BOOTNET_NAME_LEN];  /// example: ColdChoco
  int32_t      m_length;                        /// The patch's length.
  ascii_char_t m_target[BOOTNET_NAME_LEN];      /// The target file.
  uint8_t      m_implies_rom;                   /// does it imply reprogramming?
  uint8_t      m_preflight;  /// Do we just check if this endpoint exists/is valid?
  uint8_t      m_blob[];
} __attribute__((packed)) bootnet_inet_header_t;

/// @brief Alias for the BootNet pointer.
typedef bootnet_inet_header_t* bootnet_inet_header_ptr_t;
