#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// 假设 cc_bn_digit_t 的定义
typedef unsigned int cc_bn_digit_t;

// 原函数声明
int cc_bn_sub_int(const cc_bn_digit_t *bn_in, int bn_word_len, int c, cc_bn_digit_t *bn_out);

// 辅助函数：比较两个大数是否相等
int bn_equal(const cc_bn_digit_t *a, const cc_bn_digit_t *b, int len) {
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

// 辅助函数：打印大数
void print_bn(const cc_bn_digit_t *bn, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%u", bn[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]\n");
}

void test_cc_bn_sub_int() {
    printf("开始测试 cc_bn_sub_int 函数...\n");
    
    // 测试用例1：基本减法，无借位
    {
        cc_bn_digit_t input[] = {10, 20, 30};
        cc_bn_digit_t output[3];
        cc_bn_digit_t expected[] = {5, 20, 30};
        
        int borrow = cc_bn_sub_int(input, 3, 5, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 3));
        printf("测试1通过：基本减法，无借位\n");
    }
    
    // 测试用例2：需要借位的情况
    {
        cc_bn_digit_t input[] = {5, 10, 20};
        cc_bn_digit_t output[3];
        // 5 - 8 需要借位，结果应该是 (2^32 + 5 - 8) = 2^32 - 3
        cc_bn_digit_t expected[] = {(cc_bn_digit_t)(-3), 9, 20};
        
        int borrow = cc_bn_sub_int(input, 3, 8, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 3));
        printf("测试2通过：需要借位的情况\n");
    }
    
    // 测试用例3：连续借位
    {
        cc_bn_digit_t input[] = {0, 0, 1};
        cc_bn_digit_t output[3];
        cc_bn_digit_t expected[] = {(cc_bn_digit_t)(-1), (cc_bn_digit_t)(-1), 0};
        
        int borrow = cc_bn_sub_int(input, 3, 1, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 3));
        printf("测试3通过：连续借位\n");
    }
    
    // 测试用例4：减数为0
    {
        cc_bn_digit_t input[] = {100, 200, 300};
        cc_bn_digit_t output[3];
        cc_bn_digit_t expected[] = {100, 200, 300};
        
        int borrow = cc_bn_sub_int(input, 3, 0, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 3));
        printf("测试4通过：减数为0\n");
    }
    
    // 测试用例5：被减数全为0
    {
        cc_bn_digit_t input[] = {0, 0, 0};
        cc_bn_digit_t output[3];
        cc_bn_digit_t expected[] = {(cc_bn_digit_t)(-5), (cc_bn_digit_t)(-1), (cc_bn_digit_t)(-1)};
        
        int borrow = cc_bn_sub_int(input, 3, 5, output);
        
        assert(borrow == 1);
        assert(bn_equal(output, expected, 3));
        printf("测试5通过：被减数全为0\n");
    }
    
    // 测试用例6：单个字长度
    {
        cc_bn_digit_t input[] = {15};
        cc_bn_digit_t output[1];
        cc_bn_digit_t expected[] = {10};
        
        int borrow = cc_bn_sub_int(input, 1, 5, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 1));
        printf("测试6通过：单个字长度\n");
    }
    
    // 测试用例7：单个字需要借位
    {
        cc_bn_digit_t input[] = {3};
        cc_bn_digit_t output[1];
        cc_bn_digit_t expected[] = {(cc_bn_digit_t)(-2)};
        
        int borrow = cc_bn_sub_int(input, 1, 5, output);
        
        assert(borrow == 1);
        assert(bn_equal(output, expected, 1));
        printf("测试7通过：单个字需要借位\n");
    }
    
    // 测试用例8：最大值减法
    {
        cc_bn_digit_t input[] = {(cc_bn_digit_t)(-1), (cc_bn_digit_t)(-1)};
        cc_bn_digit_t output[2];
        cc_bn_digit_t expected[] = {(cc_bn_digit_t)(-2), (cc_bn_digit_t)(-1)};
        
        int borrow = cc_bn_sub_int(input, 2, 1, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 2));
        printf("测试8通过：最大值减法\n");
    }
    
    // 测试用例9：空长度边界情况
    {
        cc_bn_digit_t input[] = {1};
        cc_bn_digit_t output[1];
        
        int borrow = cc_bn_sub_int(input, 0, 5, output);
        
        assert(borrow == 5);  // 没有处理任何位，返回原始的c值
        printf("测试9通过：空长度边界情况\n");
    }
    
    // 测试用例10：大数值减法
    {
        cc_bn_digit_t input[] = {1000000, 2000000, 3000000};
        cc_bn_digit_t output[3];
        cc_bn_digit_t expected[] = {999999, 2000000, 3000000};
        
        int borrow = cc_bn_sub_int(input, 3, 1, output);
        
        assert(borrow == 0);
        assert(bn_equal(output, expected, 3));
        printf("测试10通过：大数值减法\n");
    }
    
    printf("所有测试通过！\n");
}

int main() {
    test_cc_bn_sub_int();
    return 0;
}
