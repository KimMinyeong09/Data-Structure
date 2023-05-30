#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fac(int num) {
    if (num == 0)
        return 1;
    return num * fac(num - 1);
}

int main() {
    int n, k, x, count=0, sum = 0;
    printf("N,K: ");
    scanf("%d %d", &n, &k);
    printf("%d ", n);
    count++;

    while (count<k){
        if (count == k)
            break;
        while (n > 0) {
            x = n % 10;
            sum += fac(x);
            n = n / 10;
        }
        printf("%d ", sum);
        count++;
        n = sum;
        sum = 0;
    }

	return 0;
}