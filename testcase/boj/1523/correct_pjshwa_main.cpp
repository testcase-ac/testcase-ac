#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lines[10000];
int main() {
  fast_io();

  ll k, n;
  cin >> k >> n;

  for (int i = 0; i < k; i++) cin >> lines[i];

  ll left = 0, right = 4294967294L;
  ll mid = (left + right) / 2;
  ll cur_s = 0;

  while (left < right) {
    for (int i = 0; i < k; i++) cur_s += (lines[i] / mid);

    if (cur_s < n) right = mid;
    else left = mid + 1;

    cur_s = 0;
    mid = (left + right) / 2;
  }

  vector<vector<int>>* scc;
  scc = new vector<vector<int>>;

  cout << mid - 1 << '\n';
}
