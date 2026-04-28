#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
 
  int N = rnd.next(1, 2000), K = rnd.next(1, MAXK);
  cout << N << ' ' << K << '\n';

  string D = "URDL";
  for (int i = 0; i < N; ++i) cout << D[rnd.next(0, 3)];
  cout << '\n';
}
