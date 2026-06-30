#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

int chooseN() {
  int mode = rnd.next(0, 2);
  if (mode == 0) return rnd.next(1, 30);
  if (mode == 1) return rnd.next(31, 3000);
  return rnd.next(3001, 100000);
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  int n = chooseN();
  printf("%d\n", n);
  cout << rnd.next("[TGFP]{%d}", n) << endl;
}
