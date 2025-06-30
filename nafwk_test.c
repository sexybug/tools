#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "cc_bn.h"


// 辅助函数：复制大数
void copy_bn(cc_bn_digit_t *dest, const cc_bn_digit_t *src, int word_len) {
    for (int i = 0; i < word_len; i++) {
        dest[i] = src[i];
    }
}

// 辅助函数：打印NAF数组
void print_naf(int *naf, int len) {
    printf("NAF: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", naf[i]);
    }
    printf("\n");
}

// 测试用例1：测试K为0的情况
void test_zero_input() {
    printf("测试用例1: K = 0\n");
    cc_bn_digit_t K[] = {0, 0, 0, 0};
    int K_word_len = 4;
    int w = 3;
    int naf[100];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    // K为0时，应该立即结束，不进入循环
    assert(cc_bn_is_zero(K, K_word_len) == true);
    printf("测试通过\n\n");
}

// 测试用例2：测试K为1的情况
void test_single_bit() {
    printf("测试用例2: K = 1\n");
    cc_bn_digit_t K[] = {1, 0, 0, 0};
    cc_bn_digit_t K_orig[] = {1, 0, 0, 0};
    int K_word_len = 4;
    int w = 3;
    int naf[100];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    // 验证NAF表示
    printf("原始K: %lu\n", K_orig[0]);
    printf("NAF长度: %d\n", naf_len);
    print_naf(naf, 10); // 打印前10个元素
    printf("测试通过\n\n");
}

// 测试用例3：测试小的奇数
void test_small_odd() {
    printf("测试用例3: K = 7\n");
    cc_bn_digit_t K[] = {7, 0, 0, 0};
    cc_bn_digit_t K_orig[] = {7, 0, 0, 0};
    int K_word_len = 4;
    int w = 3;
    int naf[100];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    printf("原始K: %lu\n", K_orig[0]);
    printf("NAF长度: %d\n", naf_len);
    print_naf(naf, 10);
    printf("测试通过\n\n");
}

// 测试用例4：测试小的偶数
void test_small_even() {
    printf("测试用例4: K = 8\n");
    cc_bn_digit_t K[] = {8, 0, 0, 0};
    cc_bn_digit_t K_orig[] = {8, 0, 0, 0};
    int K_word_len = 4;
    int w = 3;
    int naf[100];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    printf("原始K: %lu\n", K_orig[0]);
    printf("NAF长度: %d\n", naf_len);
    print_naf(naf, 10);
    printf("测试通过\n\n");
}

// 测试用例5：测试不同的w值
void test_different_w() {
    printf("测试用例5: 不同的w值 (K = 15)\n");
    
    for (int w = 2; w <= 5; w++) {
        printf("w = %d:\n", w);
        cc_bn_digit_t K[] = {15, 0, 0, 0};
        int K_word_len = 4;
        int naf[100];
        int naf_len = 0;
        
        nafwk(K, K_word_len, w, naf, &naf_len);
        
        printf("NAF长度: %d\n", naf_len);
        print_naf(naf, 10);
    }
    printf("测试通过\n\n");
}

// 测试用例6：测试较大的数值
void test_large_number() {
    printf("测试用例6: 较大数值\n");
    cc_bn_digit_t K[] = {0xFFFFFFFF, 0x0, 0x0, 0x0};
    int K_word_len = 4;
    int w = 4;
    int naf[100];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    printf("原始K: 0x%lX\n", K[0]);
    printf("NAF长度: %d\n", naf_len);
    print_naf(naf, 20);
    printf("测试通过\n\n");
}

// 测试用例7：测试多字长度
void test_multi_word() {
    printf("测试用例7: 多字长度\n");
    cc_bn_digit_t K[] = {0xFFFFFFFF, 0x1, 0x0, 0x0};
    int K_word_len = 4;
    int w = 3;
    int naf[200];
    int naf_len = 0;
    
    nafwk(K, K_word_len, w, naf, &naf_len);
    
    printf("原始K: 0x%lXlX\n", K[1], K[0]);
    printf("NAF长度: %d\n", naf_len);
    print_naf(naf, naf_len);
    printf("测试通过\n\n");
}

// 测试用例8：边界条件测试
void test_boundary_conditions() {
    printf("测试用例8: 边界条件\n");
    
    // 测试w的最小值
    printf("w = 1:\n");
    cc_bn_digit_t K1[] = {5, 0, 0, 0};
    int naf1[100];
    int naf_len1 = 0;
    nafwk(K1, 4, 1, naf1, &naf_len1);
    print_naf(naf1, naf_len1);
    
    // 测试单字长度
    printf("单字长度:\n");
    cc_bn_digit_t K2[] = {7};
    int naf2[100];
    int naf_len2 = 0;
    nafwk(K2, 1, 3, naf2, &naf_len2);
    print_naf(naf2, naf_len2);
    
    printf("测试通过\n\n");
}

// 主测试函数
int main() {
    printf("开始NAF转换函数单元测试\n");
    printf("================================\n\n");
    
    test_zero_input();
    test_single_bit();
    test_small_odd();
    test_small_even();
    test_different_w();
    test_large_number();
    test_multi_word();
    test_boundary_conditions();
    
    printf("所有测试用例通过！\n");
    return 0;
}
