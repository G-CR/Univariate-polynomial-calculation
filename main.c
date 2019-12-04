//
//  main.c
//  Univariate polynomial calculation
//
//  Created by 龚朝瑞 on 2019/12/2.
//  Copyright © 2019 龚朝瑞. All rights reserved.
//

#include "Univariate polynomial calculation.h"

int main(int argc, const char * argv[]) {
    int choose;
    start();
    struct Univariate_polynomial *up1 = NULL, *up2 = NULL;
    
    while(1) {
        printf("请输入你选择功能的序号： ");
        scanf("%d", &choose);
        if(choose > 6 || choose < 1) {
            printf("输入不正确,请输入对应功能编号（1～6）,谢谢配合！\n");
            system("clear");
            start();
        }
        if(choose == 1) {
            up1 = Univariate_polynomial_init(1);
            up2 = Univariate_polynomial_init(2);
        }
        else if(choose == 2) {
            if(checkNull(up1, up2)) continue;
            Univariate_polynomial_add(up1, up2);
        }
        else if(choose == 3) {
            if(checkNull(up1, up2)) continue;
            Univariate_polynomial_del(up1, up2);
        }
        else if(choose == 4) {
            if(checkNull(up1, up2)) continue;
            Univariate_polynomial_mul(up1, up2);
        }
        else if(choose == 5) {
            printf("谢谢您使用本程序，即将退出～\n");
            break;
        }
    }
}
