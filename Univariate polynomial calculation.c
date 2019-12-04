#include "Univariate polynomial calculation.h"

struct Univariate_polynomial * Univariate_polynomial_init(int num) { // 初始化多项式
    int n;
    struct Univariate_polynomial * up = NULL;
    struct element *t = NULL, *pos = NULL;
    
    up = (struct Univariate_polynomial *)malloc(sizeof(struct Univariate_polynomial)); // 给新的多项式分配空间
    up->length = 0; // 初始化元素个数为0
    t = (struct element *)malloc(sizeof(struct element)); // 给元素分配空间
    t->constant = -1; t->index = -1; t->next = NULL;
    up->base = t; //将base后的一个节点初始化，便于之后真正节点的插入
    printf("告诉我第%d个式子有多少项: ", num);
    scanf("%d", &n);
    up->length = n; // 将这个多项式的长度更新为n
    for(int i = 1;i <= n; i++) {
        t = (struct element *)malloc(sizeof(struct element));
        t->next = NULL; // 初始化节点信息
        printf("请输入第%d个节点系数: ", i);
        scanf("%d", &t->constant);
        printf("请输入第%d个节点未知数的指数: ", i);
        scanf("%d", &t->index);
        if(t->constant == 0) {
            up->length--;
            continue;
        }
        if(up->base->next == NULL) up->base->next = t; // 如果base后没有其他节点，那么直接加入base之后
        else { // 否则将找到下一个刚好大于即将插入节点指数部分节点的位置，将这个节点插入到这个节点之前
            pos = up->base;
            while(pos->next != NULL && t->index > pos->next->index) pos = pos->next;
            if(pos->next == NULL) {
                pos->next = t;
            }
            else {
                t->next = pos->next;
                pos->next = t;
            }
        }
    }
    
    // 输出用户输入的多项式
    printResult(up, pos);
    return up;
}


void Univariate_polynomial_add(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2) { //多项式加法
    int ans;
    struct Univariate_polynomial *up3 = NULL; // 定义第三个多项式，将结果存储在这里
    struct element *pos1, *pos2, *pos3, *t;
    up3 = (struct Univariate_polynomial *)malloc(sizeof(struct Univariate_polynomial));
    up3->length = 0; // 初始化长度为0
    t = (struct element *)malloc(sizeof(struct element));
    t->constant = -1; t->index = -1; t->next = NULL; // 将base的第一个节点初始化为无用的节点，便于之后节点的插入
    up3->base = t;
    pos1 = up1->base->next;
    pos2 = up2->base->next;
    pos3 = t;
    
    while(pos1 != NULL || pos2 != NULL) { // 直到第一个和第二个的所有节点都遍历完时加法才结束
        up3->length++; // 结果长度加一
        t = (struct element *)malloc(sizeof(struct element));
        t->next = NULL;
        
        if(pos1 != NULL && pos2 != NULL) { // 当第一个与第二个节点都还没有到结尾时
            if(pos1->index == pos2->index) { // 如果节点的指数相等，就可以相加再存入新节点
                t->constant = pos1->constant+pos2->constant;
                t->index = pos1->index;
                
                pos1 = pos1->next;
                pos2 = pos2->next;
            }
            else { // 如果不相等的话，遵循将指数部分小的节点加入结果多项式中
                if(pos1->index < pos2->index) {
                    t->constant = pos1->constant;
                    t->index = pos1->index;
                    pos1 = pos1->next;
                }
                else if(pos1->index > pos2->index) {
                    t->constant = pos2->constant;
                    t->index = pos2->index;
                    pos2 = pos2->next;
                }
            }
        }
        else { // 如果有一项多项式已经便遍历完成，那么将剩下的节点按指数从小到大的顺序加入结果多项式中
            if(pos1 == NULL) {
                t->constant = pos2->constant;
                t->index = pos2->index;
                pos2 = pos2->next;
            }
            else if(pos2 == NULL) {
                t->constant = pos1->constant;
                t->index = pos1->index;
                pos1 = pos1->next;
            }
        }
        
        if(t->constant != 0) { // 如果相加的结果等于0的话，这个t节点将不加入结果多项式中
            pos3->next = t;
            pos3 = t;
        }
        else up3->length--;
    }
    printf("你选择的是多项式相加, 结果如下\n");
    printResult(up3, pos3);
    ans = assignment(up3, pos3);
    if(ans == -1) {
        printf("all right~\n");
    }
    else {
        printf("\n当x = 1时，该式子的值为: %d\n\n", ans);
    }
}

void Univariate_polynomial_del(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2) { // 多项式减法
    int ans;
    struct Univariate_polynomial *up3 = NULL; // 定义第三个多项式，将结果存储在这里
    struct element *pos1, *pos2, *pos3, *t;
    up3 = (struct Univariate_polynomial *)malloc(sizeof(struct Univariate_polynomial));
    t = (struct element *)malloc(sizeof(struct element));
    t->constant = -1; t->index = -1; t->next = NULL; // 将base的第一个节点初始化为无用的节点，便于之后节点的插入
    up3->base = t;up3->length = 0;
    pos1 = up1->base->next;
    pos2 = up2->base->next;
    pos3 = t;
    
    while(pos1 != NULL || pos2 != NULL) { // 直到第一个和第二个的所有节点都遍历完时加法才结束
        up3->length++;
        t = (struct element *)malloc(sizeof(struct element));
        t->next = NULL;
        if(pos1 != NULL && pos2 != NULL) { // 当第一个与第二个节点都还没有到结尾时
            if(pos1->index == pos2->index) { // 如果节点的指数相等，就可以相减再存入新节点
                t->constant = pos1->constant-pos2->constant;
                t->index = pos1->index;
                
                pos1 = pos1->next;
                pos2 = pos2->next;
            }
            else { // 如果不相等的话，遵循将指数部分小的节点加入结果多项式中
                if(pos1->index < pos2->index) {
                    t->constant = pos1->constant;
                    t->index = pos1->index;
                    
                    pos1 = pos1->next;
                }
                else if(pos1->index > pos2->index) {
                    t->constant = -1*pos2->constant;
                    t->index = pos2->index;
                    
                    pos2 = pos2->next;
                }
            }
        }
        else { // 如果有一项多项式已经便遍历完成，那么将剩下的节点按指数从小到大的顺序加入结果多项式中
            if(pos1 == NULL) {
                t->constant = -1*pos2->constant;
                t->index = pos2->index;
                
                pos2 = pos2->next;
            }
            else if(pos2 == NULL) {
                t->constant = pos1->constant;
                t->index = pos1->index;
                                   
                pos1 = pos1->next;
            }
        }
        
        if(t->constant != 0) { // 如果相减的结果等于0的话，这个t节点将不加入结果多项式中
            pos3->next = t;
            pos3 = t;
        }
        else up3->length--;
    }
    
    printf("你选择的是多项式相减, 结果如下\n");
    printResult(up3, pos3); //输出结果
    ans = assignment(up3, pos3);
    if(ans == -1) {
        printf("all right~\n");
    }
    else {
        printf("\n当x = 1时，该式子的值为: %d\n\n", ans);
    }
}

void Univariate_polynomial_mul(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2) { // 多项式乘法
    int ans;
    struct Univariate_polynomial *up3; // 定义第三个多项式，将结果存储在这里
    struct element *pos1, *pos2, *pos3 = NULL, *t, *q;
    up3 = (struct Univariate_polynomial *)malloc(sizeof(struct Univariate_polynomial));
    t = (struct element *)malloc(sizeof(struct element));
    t->constant = -1; t->index = -1; t->next = NULL; // 将base的第一个节点初始化为无用的节点，便于之后节点的插入
    up3->base = t; up3->length = 0;
    
    pos1 = up1->base->next; // pos1 指向第一个多项式的第一个节点
    while(pos1 != NULL) { // 双重循环，将两个多项式中的元素两两进行相乘再存储
        pos2 = up2->base->next; // 第二层循环结束后都要将pos2指针重新回到开头
        while(pos2 != NULL) {
            // 每个节点相乘的结果都存入t中
            t = (struct element *)malloc(sizeof(struct element));
            t->constant = pos1->constant * pos2->constant;
            t->index = pos1->index + pos2->index;
            t->next = NULL;
            
            // pos3用来找t应该存在结果多项式中的哪个位置（指数从小到大）
            pos3 = up3->base;
            while(pos3->next != NULL && t->index > pos3->next->index) pos3 = pos3->next; // 找到pos3的下一个位置即将大于t，或者没有比t指数更大的节点， 那么找到最后的位置
            if(pos3->next == NULL) {
                pos3->next = t; // 如果后面没有更大的值，那么t就是最大值
                up3->length++;
            }
            else { // t的指数在这里只可能比pos3指向的下一个值的指数 相等 或者 更小
                if(pos3->next->index == t->index) { // 如果找到与t节点指数g相等的节点
                    pos3->next->constant += t->constant; // 将系数的值相加
                    if(pos3->next->constant == 0) { // 如果相加后系数等于0， 那么删除该节点
                        q = pos3->next;
                        pos3->next = q->next;
                        free(q);
                    }
                }
                else { // 如果t节点的指数比pos3下一个节点的指数小，那么t就加入pos3的后面
                    t->next = pos3->next;
                    pos3->next = t;
                    up3->length++;
                }
            }
            pos2 = pos2->next; // pos2向后遍历
        }
        pos1 = pos1->next; // pos1向后遍历
    }
    
    printf("你选择的是多项式相乘, 结果如下\n");
    printResult(up3, pos3); // 输出结果
    ans = assignment(up3, pos3);
    if(ans == -1) {
        printf("all right~\n");
    }
    else {
        printf("\n当x = 1时，该式子的值为: %d\n\n", ans);
    }
}


void start() {
    printf("\t\t\t\t\t\t\t\t----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t####欢迎进入到计算功能程序####        |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t0、请选择以下功能：              |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t~1、输入两个多项式。~            |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t~2、将两多项式相加。~            |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t~3、将两多项式相减。~            |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t~4、将两多项式相乘。~            |\n");
    printf("\t\t\t\t\t\t\t\t|\t\t\t\t~5、退出本次的程序。~            |\n");
    printf("\t\t\t\t\t\t\t\t----------------------------------------------\n");
}

int checkNull(struct Univariate_polynomial *up1, struct Univariate_polynomial *up2) { // 检测是否已经输入过多项式
    if(up1 == NULL || up2 == NULL) {
        printf("您并没有对多项式进行输入,请返回功能选择界面重新输入!\n");
        system("clear");
        start();
        return 1;
    }
    return 0;
}


void printResult(struct Univariate_polynomial *up,struct element *pos) {  // 输出计算后的结果
    pos = up->base->next;
    printf("\n多项式长度为: %d\n", up->length);
    printf("多项式为: ");
    if(pos == NULL) {  // 如果计算结束后多项式中元素全部抵消，则输出0
        printf("0\n\n");
        return;
    }
    if(pos->constant < 0) { // 第一个节点正负号的判断
        if(pos->constant == -1 && pos->index == 0) printf("-1 ");
        else if(pos->constant == -1) printf("-x^%d ", pos->index);
        else if(pos->index == 0) printf("-%d ", pos->constant);
        else printf("-%dx^%d ",abs(pos->constant), pos->index);
    }
    else {
        if(pos->constant == 1 && pos->index == 0) printf("1 ");
        else if(pos->constant == 1) printf("x^%d ", pos->index);
        else if(pos->index == 0) printf("%d ", pos->constant);
        else printf("%dx^%d ",pos->constant, pos->index);
    }
    
    pos = pos->next; // 向后一个节点遍历
    
    while(pos != NULL) { // 一直向后遍历
        if(pos->constant > 0) { // 节点为正的情况
            if(pos->constant == 1 && pos->index == 0) printf("+ 1 ");
            else if(pos->constant == 1) printf("+ x^%d ", pos->index);
            else if(pos->index == 0) printf("+ %d ", pos->constant);
            else printf("+ %dx^%d ",pos->constant, pos->index);
        }
        else { // 节点为负的情况
            if(pos->constant == -1 && pos->index == 0) printf("- 1 ");
            else if(pos->constant == -1) printf("- x^%d ", pos->index);
            else if(pos->index == 0) printf("- %d ", pos->constant);
            else printf("- %dx^%d ",abs(pos->constant), pos->index);
        }
        pos=pos->next;
    }
    printf("\n\n");
}


int assignment(struct Univariate_polynomial *up, struct element *pos) {  // x = 1时的赋值运算
    char ass;
    int ans = 0;
    printf("是否将x = 1代入式中得到答案？(Y或者y代表是，N或者n代表否)\n请输入: ");
    while(1) {
        scanf(" %c", &ass);
        if(ass == 'N' || ass == 'n' || ass == 'Y' || ass == 'y') break;
        else printf("请按要求输入哦~ (Y或者y代表是，N或者n代表否)\n请输入: ");
    }
    
    if(ass == 'N' || ass == 'n') return -1;
    else {
        pos = up->base->next;
        while(pos != NULL) {
            ans += pos->constant;
            pos = pos->next;
        }
    }
    return ans;
}
