#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n, m, l;
int posts[102];
bool do_build(int target) {
  int cnt = 0;
  for (int i = 0; i < n + 1; i++) cnt += ((posts[i + 1] - posts[i] - 1) / target);
  return cnt > m;
}

int main() {
  fast_io();

  cin >> n >> m >> l;

  posts[0] = 0;
  for (int i = 1; i <= n; i++) cin >> posts[i];
  posts[n + 1] = l;
  sort(posts, posts + n + 2);

  int left = 1, right = 1e9;
  int mid = (left + right) / 2;

  while (left < right) {
    if (do_build(mid)) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }
  cout << mid << '\n';
}
