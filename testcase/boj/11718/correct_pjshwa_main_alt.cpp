#include <cstdio>

int main() {
  char s[101];
  while(scanf("%[^\n]\n", s) == 1) {
    printf("%s\n", s);
  }

  return 0;
}
