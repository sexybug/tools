#include "cc_bn.h"

void cc_u8_to_bn(const uint8_t *src, size_t byte_len, size_t bn_word_len, cc_bn_digit_t *bn)
{
    int i, j;
    int zero_pad_len = bn_word_len * CC_BN_DIGIT_BYTES - byte_len;

    for (i = 0; i < zero_pad_len / CC_BN_DIGIT_BYTES; i++)
    {
        bn[bn_word_len - 1 - i] = 0;
    }

    uint32_t src_index = 0;
    if (zero_pad_len % CC_BN_DIGIT_BYTES != 0)
    {
        src_index = CC_BN_DIGIT_BYTES - zero_pad_len % CC_BN_DIGIT_BYTES;

        cc_bn_digit_t tmp = 0;
        for (i = 0; i < src_index; i++)
        {
            tmp = (tmp << 8) | src[i];
        }
        bn[bn_word_len - 1 - zero_pad_len / CC_BN_DIGIT_BYTES] = tmp;
    }

    for (i = (zero_pad_len + 3) / CC_BN_DIGIT_BYTES; i < bn_word_len; i++)
    {
        cc_bn_digit_t tmp = 0;
        for (j = 0; j < CC_BN_DIGIT_BYTES; j++)
        {
            tmp = (tmp << 8) | src[src_index];
            src_index++;
        }
        bn[bn_word_len - 1 - i] = tmp;
    }
}

void cc_bn_to_u8(const cc_bn_digit_t *bn, size_t bn_word_len, uint8_t *dst)
{
    int i;
    int byte_len = bn_word_len * CC_BN_DIGIT_BYTES;

    for (i = 0; i < byte_len; i++)
    {
        dst[i] = (bn[bn_word_len - 1 - i / CC_BN_DIGIT_BYTES] >> (CC_BN_DIGIT_BITS - 8 - (i % CC_BN_DIGIT_BYTES) * 8)) & 0xFF;
    }
}

// set bn=0
void cc_bn_set_zero(cc_bn_digit_t *bn, size_t bn_word_len)
{
    int i;
    for (i = 0; i < bn_word_len; i++)
    {
        bn[i] = 0;
    }
}
// set bn=1
void cc_bn_set_one(cc_bn_digit_t *bn, size_t bn_word_len)
{
    int i;
    bn[0] = 1;
    for (i = 1; i < bn_word_len; i++)
    {
        bn[i] = 0;
    }
}

bool cc_bn_is_zero(const cc_bn_digit_t *bn, size_t bn_word_len)
{
    int i;
    for (i = 0; i < bn_word_len; i++)
    {
        if (bn[i] != 0)
        {
            return false;
        }
    }
    return true;
}

int cc_bn_cmp(const cc_bn_digit_t *bn1, const cc_bn_digit_t *bn2, size_t bn_word_len)
{
    int i;
    for (i = bn_word_len - 1; i >= 0; i -= 1)
    {
        if (bn1[i] > bn2[i])
        {
            return 1;
        }
        else if (bn1[i] < bn2[i])
        {
            return -1;
        }
    }
    return 0;
}

void cc_bn_copy(cc_bn_digit_t *dst, const cc_bn_digit_t *src, size_t bn_word_len)
{
    int i;
    for (i = 0; i < bn_word_len; i++)
    {
        dst[i] = src[i];
    }
}

void cc_bn_xor(const cc_bn_digit_t *src1, const cc_bn_digit_t *src2, size_t bn_word_len, cc_bn_digit_t *dst)
{
    int i;
    for (i = 0; i < bn_word_len; i++)
    {
        dst[i] = src1[i] ^ src2[i];
    }
}

cc_bn_digit_t cc_bn_get_bit(const cc_bn_digit_t *bn, size_t bit_index)
{
    int digit_index = bit_index / CC_BN_DIGIT_BITS;
    int bit_index_in_digit = bit_index % CC_BN_DIGIT_BITS;
    return (bn[digit_index] >> bit_index_in_digit) & 0x01;
}
size_t cc_bn_bit_len(const cc_bn_digit_t *bn, size_t bn_word_len)
{
    int i, j;
    cc_bn_digit_t tmp;
    for (i = bn_word_len - 1; i >= 0; i--)
    {
        if (bn[i] != 0)
        {
            j = 0;
            tmp = bn[i];
            while (tmp != 0)
            {
                tmp >>= 1;
                j++;
            }
            return i * CC_BN_DIGIT_BITS + j;
        }
    }
    return 0; // If all digits are zero, return 0 bits
}

// rigth move 1 bit, bn_out = bn_in / 2
void cc_bn_right_move1(const cc_bn_digit_t *bn_in, size_t bn_word_len, cc_bn_digit_t *bn_out)
{
    int i;
    for (i = 0; i < bn_word_len - 1; i += 1)
    {
        bn_out[i] = (bn_in[i + 1] << (CC_BN_DIGIT_BITS - 1)) | (bn_in[i] >> 1);
    }
    bn_out[bn_word_len - 1] = bn_in[bn_word_len - 1] >> 1;
}

cc_bn_digit_t cc_bn_add_uint(const cc_bn_digit_t *bn_in, size_t bn_word_len, cc_bn_digit_t d, cc_bn_digit_t *bn_out)
{
    int i;
    cc_bn_digit_t s, t;
    for (i = 0; i < bn_word_len; i++)
    {
        s = bn_in[i];
        t = s + d;
        d = (t < s);
        bn_out[i] = t;
    }
    return d; // return carry
}

cc_bn_digit_t cc_bn_sub_uint(const cc_bn_digit_t *bn_in, size_t bn_word_len, cc_bn_digit_t d, cc_bn_digit_t *bn_out)
{
    int i;
    cc_bn_digit_t s, t;
    for (i = 0; i < bn_word_len; i++)
    {
        s = bn_in[i];
        t = s - d;
        d = (t > s);
        bn_out[i] = t;
    }
    return d; // return borrow
}

// return naf_ki = k % w
static inline int cc_naf_mod(cc_bn_digit_t k, int w)
{
    k = k & (((cc_bn_digit_t)1 << w) - 1);

    cc_bn_digit_t modulus = ((cc_bn_digit_t)1 << (w - 1));
    int ki = (k > modulus) ? -(k - modulus) : k;
    return ki;
}

// note: K is changed
void nafwk(cc_bn_digit_t *K, int K_word_len, int w, int *naf, int *naf_len)
{
    size_t i = 0;

    int ki;
    while (cc_bn_is_zero(K, K_word_len) == false)
    {
        if (K[0] & 1)
        {
            ki = cc_naf_mod(K[0], w);
            naf[i] = ki;
            if (ki > 0)
            {
                cc_bn_sub_uint(K, K_word_len, ki, K);
            }
            else
            {
                cc_bn_add_uint(K, K_word_len, -ki, K);
            }
        }
        else
        {
            naf[i] = 0;
        }
        cc_bn_right_move1(K, K_word_len, K);
        i++;
    }
    *naf_len = i;
}