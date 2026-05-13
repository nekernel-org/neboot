# // Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
# // Distributed under the Apache Software License, Version 2.0. (See accompanying
# // file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
# // Official repository: https://github.com/ne-app-ci/next-boot

.balign 4
.global nb_flush_tlb

nb_flush_tlb:
    sfence.vma

    ret
