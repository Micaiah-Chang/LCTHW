#ifndef _hashmap_algos_h_
#define _hashmap_algos_h_

#undef get16bits
#if (defined(__GNUC__) && defined(__i386__)) || defined(__WATCOMC__) \
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__)
#define get16bits(d) (*((const uint16_t *) (d)))
#endif

#if !defined (get16bits)
#define get16bits(d) ((((uint32_t)(((const uint8_t *)(d))[1])) << 8)\
                       +(uint32_t)(((const uint8_t *)(d))[0]) )
#endif

#include <stdint.h>

uint32_t Hashmap_bad_hash(void *data);

uint32_t Hashmap_fnv1a_hash(void *data);

uint32_t Hashmap_adler32_hash(void *data);

uint32_t Hashmap_djb_hash(void *data);

uint32_t Hashmap_jenkins_hash(void *a);

uint32_t Hashmap_murmur_hash(void *data);

uint32_t Hashmap_hsieh_hash(void *data);
#endif 
