#include <stdio.h>

int gcd(int x, int y){ return y ? gcd(y, x%y) : x; }
int lcm(int x, int y){ return x / gcd(x, y) * y; }

int main() {
  int n, cnt, j, start; int a[20000]; bool visited[20000];

  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", a + i);
    visited[i] = false;
  }

  int trajectory = 1;
  for(int i = 0; i < n; i++) {
    j = i;
    cnt = 0;
    if (!visited[j]) {
      cnt++;
      start = j;
      visited[j] = true;
      j = a[j] - 1;
      while (j != start) {
        cnt++;
        visited[j] = true;
        j = a[j] - 1;
      }

      trajectory = lcm(cnt, trajectory);
    }
  }

  printf("%d\n", trajectory);
}
