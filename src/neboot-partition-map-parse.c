// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#include <include/partition-map.h>

bool nb_parse_partition_block_data_at(voidptr_t blob, size_t blob_sz, size_t index, size_t* end_lba,
                                      size_t* start_lba, size_t* sector_sz) {
  if (!start_lba || !end_lba || !blob || !blob_sz || !sector_sz ||
      (sizeof(part_block_t) * index) > blob_sz)
    return false;

  part_block_t* block = (part_block_t*) (blob + (sizeof(part_block_t) * index));

  if (block->version != EPM_REVISION || block->num_blocks < 1 || block->num_blocks > EPM_MAX_BLKS ||
      strcmp(block->magic, EPM_MAGIC) > 0 || block->lba_end == 0 || block->lba_start == 0) {
    return false;
  }

  *end_lba   = block->lba_end;
  *start_lba = block->lba_start;
  *sector_sz = block->sector_sz;

  return true;
}

part_block_t* nb_parse_partition_block_at(voidptr_t blob, size_t blob_sz, size_t index) {
  if (!blob || !blob_sz || (sizeof(part_block_t) * index) > blob_sz) return nil;

  part_block_t* block = (part_block_t*) (blob + (sizeof(part_block_t) * index));

  nb_put_string(block->magic);

  if (block->version != EPM_REVISION || block->num_blocks < 1 || block->num_blocks > EPM_MAX_BLKS ||
      strcmp(block->magic, EPM_MAGIC) > 0 || block->lba_end == 0 || block->lba_start == 0) {
    return nil;
  }

  return block;
}