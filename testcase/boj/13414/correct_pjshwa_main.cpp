#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

string sids[(int)5e5];
int main() {
  fast_io();

  int k, l;
  cin >> k >> l;
  for (int i = 0; i < l; i++) cin >> sids[i];

  set<string> sid_cnt;
  for (int i = l - 1; i >= 0; i--) {
    if (sid_cnt.count(sids[i])) sids[i] = "";
    else sid_cnt.insert(sids[i]);
  }

  int out_cnt = 0;
  for (int i = 0; i < l; i++) {
    if (sids[i] != "") {
      cout << sids[i] << '\n';
      out_cnt++;
    }
    if (out_cnt == k) break;
  }
}
