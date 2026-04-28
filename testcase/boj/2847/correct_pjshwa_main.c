#include <stdio.h>

int min(int x, int y) {
  if (x < y) return x;
  else return y;
}

int scores[100];
int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) scanf("%d", scores + i);

  int dec = 0;
  int max_v = scores[n - 1];
  int orig_score;
  for (int i = n - 2; i >= 0; i--) {
    orig_score = scores[i];
    scores[i] = min(max_v - 1, orig_score);
    dec += (orig_score - scores[i]);
    max_v = scores[i];
  }

  printf("%d\n", dec);
}
