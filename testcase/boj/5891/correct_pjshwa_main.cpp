#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
vector<int> ys[MAX + 1];
int d;

bool do_search(int w) {
  multiset<int> cys;
  int me;
  for (int i = 0; i <= w; i++) {
    for (int el : ys[i]) cys.insert(el);
  }
  me = *cys.lower_bound(-1);
  if (cys.lower_bound(me + d) != cys.end()) return true;

  for (int i = w + 1; i <= MAX; i++) {
    for (int el : ys[i - w - 1]) cys.erase(cys.lower_bound(el));
    for (int el : ys[i]) cys.insert(el);
    me = *cys.lower_bound(-1);
    if (cys.lower_bound(me + d) != cys.end()) return true;
  }
  return false;
}

int main() {
  fast_io();

  int n, xi, yi;
  cin >> n >> d;

  for (int i = 0; i < n; i++) {
    cin >> xi >> yi;
    ys[xi].push_back(yi);
  }

  int left = 0, right = MAX + 1;
  int mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid)) right = mid;
    else left = mid + 1;
 
    mid = (left + right) / 2;
  }
  cout << (mid == MAX + 1 ? -1 : mid);
}
