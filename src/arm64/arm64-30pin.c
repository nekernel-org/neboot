// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/ne-foss-org/neboot

#include <include/30pin.h>
#include <include/partition-map.h>

size_t nb_parse_30pin(voidptr_t blob, size_t* size, size_t* start_lba)
{
    struct _nb_tpin_recovery_packet* pckt = (struct _nb_tpin_recovery_packet*)blob;

    if (pckt == nil) {
        return 0;
    }

    if (pckt->mag[0] != NB_30PIN_MAG[0] || pckt->mag[1] != NB_30PIN_MAG[1]) {
        return 0;
    }

    *size = NB_30PIN_BUFFER_LEN;
    *start_lba = 0;

    return *size;
}