// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#pragma once

///
/// @file boot.h
/// @brief NeBoot types, data structures, and standard library.
///

#ifdef __unix__
#undef __unix__
#define __unix__ 7
#endif  // !__unix__

#define __mpboot__ __unix__

typedef __UINTPTR_TYPE__ uintptr_t;
typedef __UINT32_TYPE__  phys_addr_t;

typedef unsigned long ulong_t;

typedef unsigned long long int uint64_t;
typedef unsigned               uint32_t;
typedef unsigned short         uint16_t;
typedef unsigned char          uint8_t;

typedef __INTPTR_TYPE__ intptr_t;

typedef __INT64_TYPE__ int64_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT16_TYPE__ int16_t;
typedef char           int8_t;

typedef void*       voidptr_t;
typedef char*       addr_t;
typedef const char* caddr_t;

typedef __UINTPTR_TYPE__ ptrtype_t;
typedef ptrtype_t        size_t;

#define array_size(arr) (sizeof(arr[0]) / sizeof(arr))

#ifndef nil
#define nil ((voidptr_t) 0)
#endif  // ifndef nil

#ifndef null
#define null ((voidptr_t) 0)
#endif  // ifndef null

/// C23 introduces `nullptr`: https://en.cppreference.com/w/c/language/nullptr.html
#if __STDC_VERSION__ < 202311L
#define nullptr ((struct nullptr_*) null)

struct nullptr_ {
  char __nullv;
};
typedef struct nullptr_* nullptr_t;
#endif

#define auto_type void*

#define __no 0
#define __yes 1

#define boolean char

#define no __no
#define yes __yes

#ifndef __cplusplus
#define bool boolean
#define false no
#define true yes
#endif  //!_cplusplus

#define NB_RESTART 0
#define NB_SHUTDOWN 1

#ifndef asm
#define asm __asm
#endif  // ifndef asm

#define __COPYRIGHT(s) /* unused */

#ifdef __COMPILE_RISCV__
#define NB_BOOT_ADDR (0x80020000)
#define NB_BOOT_ADDR_STR "0x80020000"
#define NB_FRAMEBUFFER_ADDR 0x40000000L
#define NB_UART_BASE 0x10000000
#define NB_FLASH_BASE_ADDR 0x08000000

#define nb_sync_synchronize() __sync_synchronize()
#elif defined(__COMPILE_POWERPC__)
#define NB_UART_BASE 0x10000000
#define NB_BOOT_ADDR 0x1030000
#define NB_BOOT_ADDR_STR "0x1030000"
#define NB_FRAMEBUFFER_ADDR 0x40000000L
#define NB_FLASH_BASE_ADDR 0x08000000

#define nb_sync_synchronize() __sync_synchronize()
#elif defined(__COMPILE_ARM64__)

#define NB_UART_BASE 0x09000000
#define NB_BOOT_ADDR 0x1030000
#define NB_BOOT_ADDR_STR "0x1030000"
#define NB_FRAMEBUFFER_ADDR 0x40000000L
#define NB_FLASH_BASE_ADDR 0x08000000

static inline void __sync_synchronize(void) {
  /// leave it as is.
}

#define nb_sync_synchronize() __sync_synchronize()
#endif  // ifndef __COMPILE_POWERPC__

#define NB_BAUDRATE_TABLE {300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}

#define NB_STRING(s) #s

#define NB_BOOT_MAG_0 'C'
#define NB_BOOT_MAG_1 'B'

#define NB_BOOT_VER 0x101

#ifndef _Nonnull
#define _Nonnull
#endif  // ifndef _Nonnull

#define NB_BOOT_CALL(struct, offset)                                       \
  volatile nb_proc_t proc_##offset = (volatile nb_proc_t)(struct->offset); \
  proc_##offset();

/// @brief Float point number representation (standard agnostic)
typedef union {
  struct {
    char    __sign;
    int16_t __mantissa;
    int32_t __exponent;
  };
} __attribute__((packed)) binary64_t;

/// @brief Float point number representation (standard agnostic)
typedef union {
  struct {
    char    __sign;
    int8_t __mantissa;
    int16_t __exponent;
  };
} __attribute__((packed)) binary32_t;

/// \brief UTF-32 character
typedef uint32_t utf_char_t;

/// \brief ASCII character
typedef char ascii_char_t;

/// @brief panic the entire system.
/// @param reason why text.
void nb_panic(const char* reason);

/// @brief update the power status of the machine.
void nb_update_power_status(boolean restart);

/// @brief puts a string in serial
/// @param text
/// @return
size_t nb_put_string(const ascii_char_t* _Nonnull text);

/// @brief gets a char from serial
/// @param
/// @return
utf_char_t nb_get_char(void);

/// @brief puts a char in serial
/// @param ch
void nb_put_char(utf_char_t ch);

/// @brief Hangs the firmware.
/// @param void no args.
void nb_restart_machine(void);

/// @brief Flushs the TLB.
/// @param void no args.
void nb_flush_tlb(void);

/// @brief Print current kernel name.
/// @param
void nb_print_name(void);

/// @brief String length getter
/// @param str the string.
/// @return
size_t strlen(_Nonnull caddr_t str);

/// @brief Compare two strings.
/// @param src source string
/// @param cmp string to compare.
/// @return
size_t strcmp(_Nonnull caddr_t src, _Nonnull caddr_t cmp);

typedef void (*nb_proc_t)();

/// \brief ASCII character.
typedef char ascii_char_t;

/// @brief Linear Executable Header
/// @author Amlal El Mahrouss (Amlal El Mahrouss)
struct __attribute__((aligned(4))) nb_boot_header {
  const ascii_char_t h_mag[2];         // magic number
  const ascii_char_t h_name[10];       // operating system name
  const uint32_t     h_revision;       // firmware revision
  const uint64_t     h_start_address;  // start address (master/slave(s) thread)
};

// EOF.
