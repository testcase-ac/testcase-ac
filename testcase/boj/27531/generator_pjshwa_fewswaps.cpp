#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = 2e5, pmax = 1000;
  int n = nmax;
  printf("%d\n", n);

  int a[n], b[n];
  iota(a, a + n, 1);// shuffle(a, a + n);
  iota(b, b + n, 1);// shuffle(b, b + n);

  for (int i = 0; i < 100; i++) {
    int x = rnd.next(0, n - 1);
    int y = rnd.next(0, n - 1);
    swap(a[x], a[y]);
  }
  for (int i = 0; i < 100; i++) {
    int x = rnd.next(0, n - 1);
    int y = rnd.next(0, n - 1);
    swap(b[x], b[y]);
  }

  for (int i = 0; i < n; i++) {
    int p = rnd.next(1, pmax);
    printf("%d %d %d\n", a[i], b[i], p);
  }
}
