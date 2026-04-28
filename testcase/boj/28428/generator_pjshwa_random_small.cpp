#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = 5;
  int sx = rnd.next(1, nmax);
  int sy = rnd.next(1, nmax);
  int mx = rnd.next(1, nmax);
  int my = rnd.next(1, nmax);
  printf("%d %d %d %d\n", sx, sy, mx, my);
}
