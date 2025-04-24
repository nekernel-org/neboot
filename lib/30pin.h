/* -------------------------------------------

	Copyright (C) 2024-2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

/// @file 30pin.h
/// @brief 30pin recovery protocol.
/// @details This file contains the definitions and structures used for the 30pin recovery protocol.

#define CB_30PIN_MAG "TP"
#define CP_30PIN_MAG_LEN (2)

#define CB_30PIN_BUFFER_LEN (498)
#define CB_30PIN_EOP_LEN (11)

/// @brief 30pin recovery header.
/// @param mag magic number.
/// @param kind kind of packet we deal with.
/// @param buffer the data of the packet.
/// @param eop end of packet data.
struct _cb_tpin_recovery_packet
{
	uint8_t mag[CP_30PIN_MAG_LEN];
	uint8_t kind;
	uint8_t buffer[CB_30PIN_BUFFER_LEN];
	uint8_t eop[CB_30PIN_EOP_LEN];
};

/// @brief 30pin recovery packet kinds.
enum
{
	TPIN_RECOVERY_PACKET_KIND_UNKNOWN = 0,
	TPIN_RECOVERY_PACKET_KIND_BOOT = 1,
	TPIN_RECOVERY_PACKET_KIND_DATA = 2,
	TPIN_RECOVERY_PACKET_KIND_EOP = 3,
	TPIN_RECOVERY_PACKET_KIND_EOP_ACK = 4,
	TPIN_RECOVERY_PACKET_KIND_EOP_NACK = 5,
};

typedef struct _cb_tpin_recovery_packet cb_tpin_recovery_packet_t;