#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = 200000;
  int n = rnd.next(2, nmax);
  int m = rnd.next(2, nmax);
  printf("%d %d\n", n, m);
  // cout << rnd.next("[TGFP]{%d}", n) << endl;
}

