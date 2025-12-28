// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#ifndef __BITMANIP_H__
#define __BITMANIP_H__

/// Name: NeBoot Bits API.
/// Purpose: Bit manip helpers.

#define cb_set_bit(X, O) X = (1 << O) | X
#define cb_clear_bit(X, O) X = ~(1 << O) & X
#define cb_toogle(X, O) X = (1 << O) ^ X
#define cb_lsb(X) X = X & -X
#define cb_msb(X) X = -(cb_lsb(X)) & X

#endif  // ifndef __BITMANIP_H__
