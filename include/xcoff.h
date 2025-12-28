// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#ifndef __XCOFF__
#define __XCOFF__

#include <include/boot.h>

#define XCOFF_MAG 0x01F7

#define XCOFF_NAME_LEN 256U

#define XCOFF_REL_FLG 0x0001
#define XCOFF_EXEC_FLG 0x0002
#define XCOFF_LNNO_FLG 0x0004
#define XCOFF_SYMNS_FLG 0x0008

/// @brief XCoff identification header.
typedef struct _xcoff_header {
  uint16_t magic;
  uint16_t target;
  uint16_t num_secs;
  uint32_t timestamp;
  uint64_t symptr;
  uint32_t numsyms;
  uint16_t opthdr;  // ?: Number of bytes in optional header
} xcoff_header_t;

/// @brief This the executable's manifest fork, designed for NeFS.
/// @param prop_xml_fork The XML fork of the executable.
/// @param dyld_fork The DYLD fork metadata.
/// @param code_sign_fork Executable's certificate contained in a fork.
typedef struct _xcoff_fork_header {
  char prop_xml_fork[XCOFF_NAME_LEN];
  char dyld_fork[XCOFF_NAME_LEN];
  char code_sign_fork[XCOFF_NAME_LEN];
} xcoff_fork_header_t;

typedef xcoff_header_t xcoff_header64_t;
typedef xcoff_header_t xcoff_header32_t;

xcoff_header_t*      xcoff_parse_metadata(void);
xcoff_fork_header_t* xcoff_parse_fork_metadata(void);

#endif  // ifndef __XCOFF__
