#include <bits/stdc++.h>
using namespace std;

int ipow(int x, int p) {
  if (p == 0) return 1;
	return x * ipow(x, p - 1);
}

int mem[32];
int acc, pc, bit, op, x;
int main() {
  while (1) {
    memset(mem, 0, sizeof(mem));
    acc = 0, pc = 0;

    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 8; j++) {
        if (scanf("%1d", &bit) < 0) return 0;
        mem[i] += bit * ipow(2, 7 - j);
      }
    }

    while (1) {
      op = mem[pc] / 32;
      x = mem[pc] % 32;
      pc = (pc + 1) % 32;

      if (op == 7) break;

      switch (op) {
        case 0:
          mem[x] = acc;
          break;
        case 1:
          acc = mem[x];
          break;
        case 2:
          if (!acc) pc = x;
          break;
        case 4:
          acc = (acc + 255) % 256;
          break;
        case 5:
          acc = (acc + 1) % 256;
          break;
        case 6:
          pc = x;
          break;
      }

    }

    for (int j = 0; j < 8; j++) {
      printf("%1d", acc / ipow(2, 7 - j));
      acc %= ipow(2, 7 - j);
    }
    printf("\n");
  }
}
