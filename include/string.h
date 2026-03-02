// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#pragma once

#include <include/boot.h>

#define strncpy(DST, SRC, LEN) memncpy(DST, SRC, LEN)

void   strreverse(char* in_out);
size_t strlen(const char* in);
size_t strnlen(const char* in, size_t maxLen);
void*  memset(void* dst, const char val, size_t len);
size_t memcpy(void* dst, const void* src);
size_t memncpy(void* dst, const void* src, size_t len);
void*  memmove(void* dst, const void* src, size_t len);
size_t strncmp(const char* cmp1, const char* cmp2, size_t len);
char*  strchr(char* str, const char chr);

#define zero_memory(dst, sz) memset(dst, 0, sz)
