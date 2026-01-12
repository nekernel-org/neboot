// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#pragma once

#include <include/boot.h>

struct _nb_file_descriptor;

/// @brief NeBoot file/device descriptor.
/// @version 1
typedef struct _nb_file_descriptor {
  int32_t f_kind;
  int32_t f_filesystem;

  size_t (*f_write)(void* ptr, size_t size, size_t nitems, struct _nb_file_descriptor* self);
  size_t (*f_read)(void* ptr, size_t size, size_t nitems, struct _nb_file_descriptor* self);
  int (*f_seek)(struct _nb_file_descriptor* self, size_t off, int whence);
  int (*f_tell)(struct _nb_file_descriptor* self);
  int (*f_rewind)(struct _nb_file_descriptor* self);
  int (*f_eof)(struct _nb_file_descriptor* self);
  int (*f_close)(struct _nb_file_descriptor* self);
} nb_file_descriptor_t;

/// @brief Grabs a new device reference.
/// @param path the device path.
/// @return
nb_file_descriptor_t* nb_grab_fd(const char* path);
