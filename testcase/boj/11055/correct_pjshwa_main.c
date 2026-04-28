#include <stdio.h>

int a[1000], dp[1000];
int main() {
  int n;
  scanf("%d", &n);

  int el;
  for (int i = 0; i < n; i++) scanf("%d", a + i);

  int max = -2147483648;
  for (int i = 0; i < n; i++) {
    dp[i] = a[i];
    for (int j=0; j<i; j++) {
      if (a[j] < a[i] && dp[i] < dp[j] + a[i]) {
        dp[i] = dp[j] + a[i];
      }
    }
    if (max < dp[i]) max = dp[i];
  }

  printf("%d\n", max);
}
