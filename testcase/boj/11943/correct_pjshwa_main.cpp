#include <stdio.h>

int main() {
  int a, b, c, d;
  scanf("%d %d\n%d %d", &a, &b, &c, &d);
  printf("%d\n", b + c < a + d ? b + c : a + d);
}
