/* -------------------------------------------

	Copyright (C) 2025, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#pragma once

#include <lib/boot.h>

#define BOOTNET_INET_MAGIC	   "NETB"
#define BOOTNET_INET_MAGIC_LEN (4)

#define BOOTNET_NAME_LEN (256)

/// @brief Netboot Internet Header
/// Consists of 4 magic characters, and a set of fields describing the current patch that's being sent (if m_preflight = 0)
/// @note Can be used to patch ROMs too (if m_implies_rom = 1)
typedef struct bootnet_inet_header
{
	ascii_char_t m_nb1; /// magic char 1 'N'
	ascii_char_t m_nb2; /// magic char 2 'E'
	ascii_char_t m_nb3; /// magic char 3 'T'
	ascii_char_t m_nb4; /// magic char 4 'B'

	ascii_char_t	m_patch_name[BOOTNET_NAME_LEN]; /// example: ColdChoco
	int32_t m_length;		   /// The patch's length.
	ascii_char_t	m_target[BOOTNET_NAME_LEN];	   /// The target file.
	uint8_t m_implies_program;	   /// does it imply reprogramming?
	uint8_t m_preflight;	   /// Do we just check if this endpoint exists/is valid?
	uint8_t m_blob[];
} bootnet_inet_header;
