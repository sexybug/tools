#ifndef CC_BN_H
#define CC_BN_H

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t cc_bn_digit_t;

#define CC_BN_DIGIT_BYTES sizeof(cc_bn_digit_t)
#define CC_BN_DIGIT_BITS (CC_BN_DIGIT_BYTES * 8)


void cc_u8_to_bn(const uint8_t *src, int byte_len, int bn_word_len, cc_bn_digit_t *bn);
uint8_t cc_bn_get_bit(const cc_bn_digit_t *bn, int bit_index);
uint32_t cc_bn_bit_len(const cc_bn_digit_t *bn, int bn_word_len);


#endif // CC_BN_H