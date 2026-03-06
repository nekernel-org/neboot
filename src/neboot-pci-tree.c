// Copyright 2024-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

/**
 * @file neboot-pci-tree.c
 * @author Amlal El Mahrouss (amlal@nekernel.org)
 * @brief PCI tree implementation.
 * @version 0.1
 * @date 2024-01-22
 *
 * @copyright Copyright (c) 2024 Amlal El Mahrouss
 *
 */

#include <include/pci-tree.h>
#include <include/string.h>

/// BUGS: 0

/// Standard Root table (Mahrouss Table)
#define NB_PCI_ROOT_NAME "/pci-tree/@/"

static struct hw_nb_pci_tree* nb_base_tree   = nil;
static struct hw_nb_pci_tree* nb_latest_tree = nil;
static struct hw_nb_pci_tree* nb_last_tree   = nil;

/// \brief Init the PCI device tree structure.
/// \return if it already exists -> false
/// Otherwise true.
boolean nb_pci_init_tree(void) {
  nb_base_tree = (struct hw_nb_pci_tree*) (NB_PCI_TREE_BASE);

  // huh? anyway let's ignore it then.
  if (nb_base_tree->d_magic != NB_PCI_DEV_MAGIC) {
    nb_base_tree->d_magic = NB_PCI_DEV_MAGIC;

    memncpy(nb_base_tree->d_name, NB_PCI_ROOT_NAME, strlen(NB_PCI_ROOT_NAME));

    nb_base_tree->d_next_sibling = 0;
    nb_base_tree->d_off_props    = 0;
    nb_base_tree->d_sz_struct    = 0;
    nb_base_tree->d_sz_props     = 0;
    nb_base_tree->d_off_struct   = 0;
    nb_base_tree->d_version      = NB_PCI_VERSION;

    nb_base_tree->d_next_sibling = (nb_pci_num_t) (nb_base_tree + sizeof(struct hw_nb_pci_tree));
    nb_base_tree->d_first_node   = (nb_pci_num_t) nb_base_tree;

    nb_put_string(">> Append root device: " NB_PCI_ROOT_NAME "\r\n");
  }

  nb_latest_tree = nb_base_tree;

  return yes;
}

/// \brief Adds a new device to the tree.
/// \param name the device name.
/// \param struct_ptr the struct containing the device.
/// \param struct_sz the structure size.
boolean nb_pci_append_tree(const caddr_t name, nb_pci_num_t struct_ptr, nb_pci_num_t struct_sz) {
  if (!name || *name == 0 || nb_latest_tree == nil) return no;

  struct hw_nb_pci_tree* nb_pci_tree = (struct hw_nb_pci_tree*) (nb_latest_tree);

  while (nb_pci_tree->d_magic == NB_PCI_DEV_MAGIC) {
    if (strcmp(nb_pci_tree->d_name, name) == 0) return no;

    nb_pci_tree = (struct hw_nb_pci_tree*) (nb_pci_tree + sizeof(struct hw_nb_pci_tree));
  }

  nb_pci_tree->d_magic = NB_PCI_DEV_MAGIC;

  memncpy(nb_pci_tree->d_name, name, strlen(name));

  nb_pci_tree->d_off_struct = struct_ptr;
  nb_pci_tree->d_sz_struct  = struct_sz;
  nb_pci_tree->d_off_props  = 0;
  nb_pci_tree->d_sz_props   = 0;
  nb_pci_tree->d_version    = NB_PCI_VERSION;

  nb_pci_tree->d_next_sibling = (nb_pci_num_t) (nb_pci_tree + sizeof(struct hw_nb_pci_tree));
  nb_pci_tree->d_first_node   = (nb_pci_num_t) nb_latest_tree;

  nb_latest_tree = nb_pci_tree;
  nb_last_tree   = nb_pci_tree;

  nb_put_string(">> Append device: ");
  nb_put_string(name);
  nb_put_string("\r\n");

  return yes;
}
