#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = 5000;
  int mx = rnd.next(1, nmax);

  int my;
  if (rnd.next(0, 5) > 2) my = rnd.next(1, nmax);
  else my = mx;

  int sx = rnd.next(1, nmax);
  int sy = sx;
  printf("%d %d %d %d\n", sx, sy, mx, my);
}
