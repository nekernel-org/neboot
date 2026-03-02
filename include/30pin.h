// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#pragma once

#include <include/boot.h>

/// @file 30pin.h
/// @brief 30pin recovery protocol.
/// @details This file contains the definitions and structures used for the 30pin recovery protocol.

#define NB_30PIN_MAG "TP"
#define NB_30PIN_MAG_LEN (2)

#define NB_30PIN_BUFFER_LEN (498)
#define NB_30PIN_EOP_LEN (11)

/// @brief 30pin recovery header.
/// @param mag magic number.
/// @param kind kind of packet we deal with.
/// @param buffer the data of the packet.
/// @param eop end of packet data.
struct _nb_tpin_recovery_packet {
  uint8_t mag[NB_30PIN_MAG_LEN];
  uint8_t kind;
  uint8_t buffer[NB_30PIN_BUFFER_LEN];
  uint8_t eop[NB_30PIN_EOP_LEN];
};

/// @brief 30pin recovery packet kinds.
enum {
  TPIN_RECOVERY_PACKET_KIND_UNKNOWN  = 0,
  TPIN_RECOVERY_PACKET_KIND_BOOT     = 1,
  TPIN_RECOVERY_PACKET_KIND_DATA     = 2,
  TPIN_RECOVERY_PACKET_KIND_EOP      = 3,
  TPIN_RECOVERY_PACKET_KIND_EOP_ACK  = 4,
  TPIN_RECOVERY_PACKET_KIND_EOP_NACK = 5,
  TPIN_RECVOERY_PACKET_KIND_RESET    = 6,
  TPIN_RECOVERY_PACKET_KIND_COUNT    = TPIN_RECVOERY_PACKET_KIND_RESET - TPIN_RECOVERY_PACKET_KIND_BOOT + 1
};

/// @brief 30pin CRC type.
typedef uint8_t nb_tpin_crc_t[sizeof(uint32_t)];

typedef struct _nb_tpin_recovery_packet nb_tpin_recovery_packet_t;

size_t nb_parse_30pin(voidptr_t blob, size_t* size, size_t* start_lba);