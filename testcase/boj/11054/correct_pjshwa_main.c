#include <stdio.h>

int a[1000], b[1000], dpi[1000], dpd[1000];
int main() {
  int n;
  scanf("%d", &n);

  int el;
  for (int i = 0; i < n; i++) {
    scanf("%d", &el);
    a[i] = el;
    b[n - i - 1] = el;
  }

  for (int i = 0; i < n; i++) {
    int mini = 0;
    int mind = 0;
    for (int j = 0; j < i; j++){
      if (a[j] < a[i]) {
        if (mini < dpi[j]) mini = dpi[j];
      }
      if (b[j] < b[i]) {
        if (mind < dpd[j]) mind = dpd[j];
      }
    }
    dpi[i] = mini + 1;
    dpd[i] = mind + 1;
  }

  int max = -2147483648;
  for (int i = 0; i < n; i++) {
    if (max < dpi[i] + dpd[n - i - 1]) max = dpi[i] + dpd[n - i - 1];
  }
  printf("%d\n", max - 1);
}
