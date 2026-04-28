#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
using ll = long long;

const int MAXK = 1e9;
 
int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  string S = "";
  for (int i = 0; i < 4997; ++i) S += 'z';
  S += "abb";

  cout << S.size() << '\n' << S << '\n';
}
