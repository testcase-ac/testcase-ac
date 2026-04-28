#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = 5000;
  int sx = rnd.next(1, nmax);

  int sy;
  if (rnd.next(0, 5) > 2) sy = rnd.next(1, nmax);
  else sy = sx;

  int mx = rnd.next(1, nmax);
  int my = mx;
  printf("%d %d %d %d\n", sx, sy, mx, my);
}
