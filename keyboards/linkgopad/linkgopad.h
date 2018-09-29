#ifndef FIVEX5_H
#define FIVEX5_H

#include "quantum.h"
#define ___ KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define pad_5x5( \
    K00, K01, K02, K03, K04, \
    K10, K11, K12, K13, K14, \
    K20, K21, K22, K23, K24, \
    K30, K31, K32, K33, K34, \
    K40, K41, K42, K43, K44 \
) \
{ \
    { K00, K01, K02, K03, K04}, \
    { K10, K11, K12, K13, K14}, \
    { K20, K21, K22, K23, K24}, \
    { K30, K31, K32, K33, K34}, \
    { K40, K41, K42, K43, K44} \
}

#endif
