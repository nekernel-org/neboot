// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-ci/next-boot

#include <include/boot.h>
#include <include/mp-bit.h>
#include <include/partition-map.h>
#include <include/pci-tree.h>

/// BUGS: 0

/////////////////////////////////////////////////////////////////////////////////////////

// @name start.c //

// @brief Start file // This is where the firmware starts it's initialization //
// code. //

// @author Amlal El Mahrouss //

/////////////////////////////////////////////////////////////////////////////////////////

extern void nb_start_context(uintptr_t);
extern void nb_start_rom(void);

extern int nb_boot_processor_ready;

/// @brief hardware thread counter (rv64 only)
#ifdef __COMPILE_RISCV__
uint64_t __nb_hart_counter = 0UL;
#endif

/// @brief Start executing the firmware.
/// @param
void nb_start_exec(void) {
#ifndef __COMPILE_RISCV__
  static uint64_t __nb_hart_counter = 0UL;
#endif

  ++__nb_hart_counter;

  uintptr_t hart = __nb_hart_counter;

  // let the hart 0 init our stuff.
  if (hart == 0) {
    nb_put_string("NB> Welcome to NeBoot, (c) Amlal El Mahrouss. Built the ");
    nb_put_string(__DATE__);
    nb_put_string("\r\r\n");

#ifdef __COMPILE_POWERPC__
    nb_put_string("NB> CPU: PowerPC 64-bit Based SoC.\r\r\n");
#endif  // __COMPILE_POWERPC__

#ifdef __COMPILE_AMD64__
    nb_put_string("NB> CPU: x64 Based SoC.\r\r\n");
#endif  // __COMPILE_AMD64__

#ifdef __COMPILE_ARM64__
    nb_put_string("NB> CPU: AArch64 Based SoC.\r\r\n");
#endif  // __COMPILE_ARM64__

#ifdef __COMPILE_ARM32__
    nb_put_string("NB> CPU: AArch32 Based SoC.\r\r\n");
#endif  // __COMPILE_ARM64__

#ifdef __COMPILE_RISCV__
    nb_put_string("NB> CPU: RV64 Based SoC.\r\r\n");
#endif  // __COMPILE_RISCV__
  }

  /// @brief Boots here if LX header matches what we except.

  volatile struct nb_boot_header* boot_hdr = (volatile struct nb_boot_header*) (NB_FLASH_BASE_ADDR);

  /**
    boot if:
      - ident matches.
      - version matches.
  */

  if (boot_hdr->h_mag[0] == NB_BOOT_MAG_0 && boot_hdr->h_mag[1] == NB_BOOT_MAG_1) {
    uint32_t rev = boot_hdr->h_revision;

#ifdef __aarch64__
    rev = __builtin_bswap32(rev);
#endif

    if (rev != NB_BOOT_VER) {
      if (hart == 0) {
        nb_put_string("NB> Can't Boot the StageTwo, LX invalid signature. (CB0003)\r\n");
      }
    } else {
      if (hart == 0) {
        nb_pci_append_tree("@stage2-lx", (nb_pci_num_t) boot_hdr, sizeof(struct nb_boot_header));

        nb_put_string("NB> Executing StageTwo: ");
        nb_put_string((const char*) boot_hdr->h_name);
        nb_put_char('\r');
        nb_put_char('\n');

        // printf("NB> address: %x\n", boot_hdr->h_start_address);
      }

      if (boot_hdr->h_start_address != 0) {
        nb_boot_processor_ready = 1;
        nb_start_context(boot_hdr->h_start_address);
        nb_boot_processor_ready = 0;
      }

      nb_put_string("NB> StageTwo has returned? (CB0002)\r\n");
    }
  } else {
    nb_put_string("NB> Trying EPM partition...\r\n");

    part_block_t* blk =
        nb_parse_partition_block_at((voidptr_t) NB_FLASH_BASE_ADDR, EPM_PART_BLK_SZ, 0);

    if (blk) {
      nb_pci_append_tree("@stage2-epm", (nb_pci_num_t) blk, sizeof(part_block_t) * blk->num_blocks);

      size_t indx = 0;
      size_t end_lba, start_lba, sector_sz;

      while (indx < blk->num_blocks) {
        if (nb_parse_partition_block_data_at(blk, EPM_PART_BLK_SZ * blk->num_blocks, indx, &end_lba,
                                             &start_lba, &sector_sz) == no) {
          ++indx;
          continue;
        }

        nb_boot_processor_ready = 1;
        nb_start_context((uintptr_t) (voidptr_t) blk + start_lba);
        nb_boot_processor_ready = 0;

        if (hart == 1) {
          nb_put_string("NB> Can't boot to StageTwo. (CB0001)\r\n");
        }
      }
    }

    if (hart == 1) {
      nb_put_string(
          "NB> Can't boot to StageTwo via EPM, no bootable partition blocks found. (CB0001)\r\n");
    }
  }

  /// end of TODO

  while (yes) {
    if (__nb_hart_counter == 0) {
      nb_restart_machine();
    }
  }
}
