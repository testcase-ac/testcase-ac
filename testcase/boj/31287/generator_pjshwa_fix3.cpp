#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);
 
  int N = 1999, K = 997;
  cout << N << ' ' << K << '\n';

  cout << "U";
  for (int i = 0; i < 997; ++i) cout << "L";
  cout << "DU";
  for (int i = 0; i < 998; ++i) cout << "R";
  cout << "D\n";
}
