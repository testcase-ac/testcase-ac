#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
 
  int N = 2000, K = MAXK;
  cout << N << ' ' << K << '\n';

  cout << "UD";
  for (int i = 0; i < N - 2; ++i) cout << "R";
  cout << '\n';
}
