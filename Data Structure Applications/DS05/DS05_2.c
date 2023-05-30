#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)
#define MAX_TERMS 1001

typedef struct {
    int coef;
    int expon;
}polynomial;

polynomial terms[MAX_TERMS];

int startA, finishA, startB, finishB, avail = 0;
int startD, finishD;

void attach(int co, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too may, terms in polynomials");
        exit(1);
    }

    terms[avail].coef = co;
    terms[avail++].expon = expon;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    int co;
    *startD = avail;

    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].expon, terms[startB].expon))
        {
        case -1:
            attach(terms[startB].coef, terms[startB].expon);
            startB++;
            break;
        case 0:
            co = terms[startA].coef + terms[startB].coef;
            if (co)
                attach(co, terms[startA].expon);
            startA++;
            startB++;
            break;
        case 1:
            attach(terms[startA].coef, terms[startA].expon);
            startA++;
            break;
        }
    }

    for (; startA <= finishA; startA++)
        attach(terms[startA].coef, terms[startA].expon);

    for (; startB <= finishB; startB++)
        attach(terms[startB].coef, terms[startB].expon);

    *finishD = avail - 1;
}

int main() {
    int x, num1, num2, i;
    FILE* a = fopen("a.txt", "r");
    FILE* b = fopen("b.txt", "r");

    printf("a.txt\n");
    while (!feof(a)) {
        fscanf(a, "%d", &x);
        printf("%d ", x);
    }printf("\n");
    printf("b.txt\n");
    while (!feof(b)) {
        fscanf(b, "%d", &x);
        printf("%d ", x);
    }printf("\n");

    fseek(a, 0, SEEK_SET);
    fseek(b, 0, SEEK_SET);

    fscanf(a, "%d", &num1);
    fscanf(b, "%d", &num2);

    startA = 0; finishA = num1 - 1; 
    startB = finishA + 1; finishB = startB + num2 - 1;
    avail = finishB + 1;

    for (i = 0; i <= finishA; i++) {
        fscanf(a, "%d", &terms[i].coef);
        fscanf(a, "%d", &terms[i].expon);
    }

    for (; i <= finishB; i++) {
        fscanf(b, "%d", &terms[i].coef);
        fscanf(b, "%d", &terms[i].expon);
    }

    padd(startA, finishA, startB, finishB, &startD, &finishD);

    for (int i = startD; i <= finishD; i++) {
        if (terms[i].expon == 0)
            printf("%d", terms[i].coef);
        else
            printf("%dx^%d", terms[i].coef, terms[i].expon);

        if (i < finishD)
            printf(" + ");
    }

    fclose(a);
    fclose(b);

    return 0;
}
