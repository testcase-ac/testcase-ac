#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int nmax = atoi(argv[1]);
  int n = rnd.next(1, nmax);
  printf("%d\n", n);
  cout << rnd.next("[TGFP]{%d}", n) << endl;
}
