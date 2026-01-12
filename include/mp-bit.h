// Copyright 2024-2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Apache Software License, Version 2.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.apache.org/licenses/LICENSE-2.0)
// Official repository: https://github.com/nekernel-org/neboot

#ifndef __BITMANIP_H__
#define __BITMANIP_H__

/// Name: NeBoot Bits API.
/// Purpose: Bit manip helpers.

#define nb_set_bit(X, O) X = (1 << O) | X
#define nb_clear_bit(X, O) X = ~(1 << O) & X
#define nb_toogle(X, O) X = (1 << O) ^ X
#define nb_lsb(X) X = X & -X
#define nb_msb(X) X = -(nb_lsb(X)) & X

#endif  // ifndef __BITMANIP_H__
