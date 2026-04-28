#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  string S = "";
  for (int i = 0; i < 2500; ++i) S += 'a';
  for (int i = 0; i < 2500; ++i) S += 'b';

  cout << S.size() << '\n' << S << '\n';
}
