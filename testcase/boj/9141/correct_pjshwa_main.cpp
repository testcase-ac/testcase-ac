#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// ll vis[60][60];

// bool trav(int r, int n) {
//   bool ret = 0;
//   if (r == n - 1) {
//     for (int i = 0; i < n; i++) {
//       if (!vis[r][i]) return true;
//     }
//     return false;
//   }
//   else {
//     for (int i = 0; i < n; i++) {
//       if (!vis[r][i]) {
//         vis[r][i]++;
//         for (int j = 1; j < n; j++) {
//           int C = (i + j) % n;
//           vis[r][C]++;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r + j) % n;
//           vis[R][i]++;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r + j) % n, C = (i + j) % n;
//           vis[R][C]++;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r - j + n) % n, C = (i + j) % n;
//           vis[R][C]++;
//         }
//         ret |= trav(r + 1, n);

//         vis[r][i]--;
//         for (int j = 1; j < n; j++) {
//           int C = (i + j) % n;
//           vis[r][C]--;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r + j) % n;
//           vis[R][i]--;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r + j) % n, C = (i + j) % n;
//           vis[R][C]--;
//         }
//         for (int j = 1; j < n; j++) {
//           int R = (r - j + n) % n, C = (i + j) % n;
//           vis[R][C]--;
//         }
//       }
//     }
//   }

//   return ret;
// }

int N;
void solve() {
  int rem = N % 6;
  if (rem == 1 || rem == 5) cout << "Kralovny lze umistit.\n";
  else cout << "Kralovny se nevejdou.\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
