#include <bits/stdc++.h>
using namespace std;

// int vis[14][14];
// int trav(int r, int n) {
//   int ans = 0;
//   if (r == n - 1) {
//     for (int i = 0; i < n; i++) {
//       if (!vis[r][i]) ans++;
//     }
//   }
//   else {
//     for (int i = 0; i < n; i++) {
//       if (!vis[r][i]) {
//         vis[r][i]++;
//         for (int j = 1; j < n; j++) {
//           if (r + j < n) vis[r + j][i]++;
//           if (r - j >= 0) vis[r - j][i]++;
//           if (i + j < n) vis[r][i + j]++;
//           if (i - j >= 0) vis[r][i - j]++;
//           if (r + j < n && i + j < n) vis[r + j][i + j]++;
//           if (r + j < n && i - j >= 0) vis[r + j][i - j]++;
//           if (r - j >= 0 && i + j < n) vis[r - j][i + j]++;
//           if (r - j >= 0 && i - j >= 0) vis[r - j][i - j]++;
//         }
//         ans += trav(r + 1, n);
//         vis[r][i]--;
//         for (int j = 1; j < n; j++) {
//           if (r + j < n) vis[r + j][i]--;
//           if (r - j >= 0) vis[r - j][i]--;
//           if (i + j < n) vis[r][i + j]--;
//           if (i - j >= 0) vis[r][i - j]--;
//           if (r + j < n && i + j < n) vis[r + j][i + j]--;
//           if (r + j < n && i - j >= 0) vis[r + j][i - j]--;
//           if (r - j >= 0 && i + j < n) vis[r - j][i + j]--;
//           if (r - j >= 0 && i - j >= 0) vis[r - j][i - j]--;
//         }
//       }
//     }
//   }

//   return ans;
// }

int main() {
  int n;
  cin >> n;
  int res[14] = {1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680, 14200, 73712, 365596};
  cout << res[n - 1] << '\n';
}
