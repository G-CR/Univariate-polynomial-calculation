#ifndef Univariate_polynomial_calculation_h
#define Univariate_polynomial_calculation_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>

#endif /* Univariate_polynomial_calculation_h */

struct element {
    int constant; // 元素中的系数部分
    int index; // 元素中的指数部分
    struct element *next; // 指向下一个元素的指针
};

struct Univariate_polynomial {
    int length; //多项式的元素个数
    struct element *base; // 多项式的元素
};

void start(void); // 初始界面
void printResult(struct Univariate_polynomial *up, struct element *pos); // 输出计算后的结果
int checkNull(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2); // 检测是否已经输入过多项式
int assignment(struct Univariate_polynomial *up, struct element *pos); // x = 1时的赋值运算

struct Univariate_polynomial* Univariate_polynomial_init(int num); // 初始化多项式

void Univariate_polynomial_add(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2); // 多项式加法
void Univariate_polynomial_del(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2); // 多项式减法
void Univariate_polynomial_mul(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2); // 多项式乘法
