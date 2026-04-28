#include <cstdio>

int main() {
    char a[4];
    scanf("%s", a);
    printf("%d", ((a[0] & 0x0F) << 12) + ((a[1] & 0x3F) << 6) + (a[2] & 0x3F) - 0xABFF);
    return 0;
}
