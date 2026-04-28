#include <bits/stdc++.h>
using namespace std;

string names[300'000];
int main() {
  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) cin >> names[i];

  int sz;
  map<int, int> nlens;
  for (int i = 0; i < k; i++) {
    sz = names[i].size();
    if (!nlens.count(sz)) nlens[sz] = 0;
    nlens[sz]++;
  }

  long long cnt = 0;
  for (int i = 0; i < n; i++) {
    if (i + k < n) {
      sz = names[i + k].size();
      if (!nlens.count(sz)) nlens[sz] = 0;
      nlens[sz]++;
    }

    sz = names[i].size();
    cnt += (--nlens[sz]);
  }
    
  cout << cnt << '\n';
}
