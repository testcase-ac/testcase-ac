#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int N = rnd.next(1, 5000);
  cout << N << '\n';

  for (int i = 0; i < N; ++i) cout << (char)(rnd.next(0, 25) + 'a');
  cout << '\n';
}
