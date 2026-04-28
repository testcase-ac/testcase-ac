#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, c, m_i, p_i;
double m, p;
int calories[5001];
int prices[5001];
int dp[10001];

int main() {
  while (true) {
    cin >> n >> m;
    m_i = (int)(m * 100 + 0.5);
    if (n == 0 && m_i == 0) break;

    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
      cin >> c >> p;
      p_i = (int)(p * 100 + 0.5);
      calories[i] = c;
      prices[i] = p_i;
    }
    
    // dp[0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= m_i; j++) {
        if (j + prices[i] > m_i) break;
 
        dp[j + prices[i]] = max(dp[j + prices[i]], dp[j] + calories[i]);
      }
    }
    cout << dp[m_i] << '\n';
  }
  
  return 0;
}


// #include <cstdio>
// #include <algorithm>
// using namespace std;

// struct CANDY { int kal, cot; }candy[5001],arr[5001];
// #define cSWAP(x,y) {CANDY t=x;x=y;y=t;}
// void qSotr(CANDY *a, int l, int r) {
//   int L = l, R = r, pv1 = a[(l + r) / 2].cot, pv2 = a[(l + r) / 2].kal;
//   while (L <= R) {
//     while (pv1 > a[L].cot || (pv1 == a[L].cot && pv2<a[L].kal)) L++;
//     while (pv1 < a[R].cot || (pv1 == a[R].cot && pv2>a[R].kal)) R--;
//     if (L <= R) {
//       cSWAP(a[L], a[R]);
//       L++, R--;
//     }
//   }
//   if (L < r) qSotr(a, L, r);
//   if (l < R) qSotr(a, l, R);
// }
// int N, M;
// int d[10001];
// int main() {
//   int kal, tIdx, t1, t2;
//   while (scanf("%d %d.%d", &N, &t1, &t2), N | t1 | t2) {
//     M = t1 * 100 + t2;
//     for (int n = 0; n < N; n++) {
//       scanf("%d %d.%d", &kal, &t1, &t2);
//       arr[n].cot = t1 * 100 + t2;
//       arr[n].kal = kal;
//     }
//     qSotr(arr, 0, N - 1);

//     int cSize = 0;
//     candy[0] = arr[0];
//     for (int n = 1; n < N; n++)
//       if (arr[n].cot != arr[n - 1].cot && candy[cSize].kal < arr[n].kal)
//         candy[++cSize] = arr[n];

//     for (int n = 1; n <= M; n++) {
//       for (int m = 0; m <= cSize; m++) {
//         if (n < candy[m].cot) break;
//         if (d[n] < d[n - candy[m].cot] + candy[m].kal)
//           d[n] = d[n - candy[m].cot] + candy[m].kal;
//       }
//     }
//     printf("%d\n", d[M]);
//     for (int n = 1; n <= M; n++) d[n] = 0;
//   }
// }
