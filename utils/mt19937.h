//
// Created by beremaran on 4/14/18.
//

#ifndef FELIX_TTT_MT19937_H
#define FELIX_TTT_MT19937_H

#include <stdint.h>

#define N              (624)                 // length of state vector
#define M              (397)                 // a period parameter
#define K              (0x9908B0DFU)         // a magic constant
#define hiBit(u)       ((u) & 0x80000000U)   // mask all but highest   bit of u
#define loBit(u)       ((u) & 0x00000001U)   // mask all but lowest    bit of u
#define loBits(u)      ((u) & 0x7FFFFFFFU)   // mask     the highest   bit of u
#define mixBits(u, v)  (hiBit(u)|loBits(v))  // move hi bit of u to hi bit of v

/**
 *
 */
void mt_seed(uint32_t);

/**
 *
 * @return
 */
uint32_t mt_reload(void);

/**
 *
 * @return
 */
uint32_t mt_random(void);

#endif //FELIX_TTT_MT19937_H
