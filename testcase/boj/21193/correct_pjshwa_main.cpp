#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  vector<int> ws;
  ws.resize(n);
  for (int i = 0; i < n; i++) cin >> ws[i];

  unordered_map<int, int> lv;
  vector<int> ans = {0};

  for (int w : ws) {
    int sz = ans.size();

    for (int j = 0; j < sz; j++) {
      ans.push_back(ans[j] + w);
      lv.emplace(ans[j] + w, w);
    }

    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    if (ans.size() > k) ans.erase(ans.begin() + k, ans.end());
  }

  for (int p : ans) {
    cout << p << ": ";
    k = p;
    while (k) {
      cout << lv[k] << ' ';
      k -= lv[k];
    }
    cout << '\n';
  }

}
