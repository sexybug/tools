#ifndef _TEST_H
#define _TEST_H

#include <stdint.h>

/**
 * @brief 打印内存数据
 * 
 * @param ptr 
 * @param len 
 */
void dump_mem(const void *ptr, int len);


/**
 * @brief 打印字符串，每行block_len个字符
 * 
 * @param str 
 * @param str_len 
 * @param block_len 
 */
void print_string(const char *str, int str_len, int block_len);

/**
 * @brief 16进制字符串转数组
 * 
 * @param str 16进制字符串
 * @param strLen 字节串长度(in Byte)
 * @param out 输出
 */
void HexString2Hex(const char *str, int len, uint8_t *out);

#endif // _TEST_H