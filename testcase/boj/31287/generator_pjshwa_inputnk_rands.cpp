#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int N = atoi(argv[1]), K = atoi(argv[2]);
  cout << N << ' ' << K << '\n';

  string D = "URDL";
  for (int i = 0; i < N; ++i) cout << D[rnd.next(0, 3)];
  cout << '\n';
}
