#include<stdio.h>

int main2(void) {
    long s = 8245928625469605920l;
    long p = 32183114504l;

    while(p) {
        putchar((s >> (((p >>= 3) & 7 ) << 3)) & 127 );
    }
    putchar('\n');

    return 0;
}

int main3() {
    char str[20] = "Hello, World!";
    printf("%s\n", str);
    printf("Hello, World!\n");

    return 0;
}

int main() {
    main2();
    main3();
}

