// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#pragma once

#define DSO_MAX_OBJECTS (128)

struct atexit_func_entry_t final {
  void (*destructor_func)(void*);
  void* obj_ptr;
  void* dso_handle;
};

typedef unsigned uarch_t;

namespace cxxabiv1 {
typedef void* __guard;
}
