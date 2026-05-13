// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-app-ci/next-boot

#pragma once

/// @file pci-tree.h
/// @brief PCI Tree layout.
/// @author Amlal El Mahrouss

#include <include/boot.h>

#define PCI_INVALID_DATA_U8 ((uint8_t) ~0)
#define PCI_INVALID_DATA_U16 ((uint16_t) ~0)
#define PCI_INVALID_DATA_U32 ((uint32_t) ~0)

#define NB_BASE_ADDRESS (0x20008000) /* PCI base mapped in virtual memory. */
#define NB_PCI_TREE_BASE (0x802000)  /* The PCI tree base address. */

/* version 1.0 */
#define NB_PCI_VERSION (0x0100)

#define NB_PCI_DEV_MAGIC (0xfeedd00d)
#define NB_PCI_INT_SZ sizeof(nb_pci_num_t)

#define NB_PCI_NAME_LEN (255U)

#define PCI_CONFIG_SPACE (4096U)

#define PCI_BUS_MAX (256U)
#define PCI_DEV_MAX (32U)
#define PCI_FN_MAX (8U

typedef char      nb_pci_char_t;
typedef uintptr_t nb_pci_num_t;

typedef uint8_t nb_pci_fn_t;
typedef uint8_t nb_pci_bus_t;
typedef uint8_t nb_pci_device_t;

/// @brief hardware tree header
/// used by guest to resolve hardware peripherals.
struct hw_nb_pci_tree {
  nb_pci_num_t d_magic;
  nb_pci_num_t d_version;
  nb_pci_num_t d_off_props;
  nb_pci_num_t d_off_struct;
  nb_pci_num_t d_sz_props;
  nb_pci_num_t d_sz_struct;

  nb_pci_num_t d_first_node;
  nb_pci_num_t d_next_sibling;

  nb_pci_char_t d_name[NB_PCI_NAME_LEN];
};

/// @brief Init PCI tree.
/// @param void
/// @return if it's successful or not.
boolean nb_pci_init_tree(void);

/// @brief Adds a new tree into the internal data structure.
/// @param name device name
/// @param struct_ptr device structure
/// @param struct_sz the structure size of the device.
/// @return if it was successful or not.
boolean nb_pci_append_tree(const caddr_t name, nb_pci_num_t struct_ptr, nb_pci_num_t struct_sz);
