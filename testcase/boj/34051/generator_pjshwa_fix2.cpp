#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  string S = "";
  for (int i = 0; i < 150; ++i) S += 'a';
  S += 'b';
  for (int i = 0; i < 5000 - 151; ++i) S += 'a';

  cout << S.size() << '\n' << S << '\n';
}
