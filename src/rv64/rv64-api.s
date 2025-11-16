# ====================================
#
#   Amlal El Mahrouss NeBoot
#   (c) Amlal El Mahrouss all rights reserved.
#
#   Purpose: Assembler API for RISC-V
#
# ====================================

.balign 4
.global cb_flush_tlb

cb_flush_tlb:
    sfence.vma

    ret
