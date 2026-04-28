#include <iostream>
#include <vector>
#include <algorithm>

#define ll long long

using namespace std;
const int MAX = 4000;
ll arr[4][MAX];
ll arr_m[MAX * MAX];

void FastIO(){cin.tie(NULL); ios_base::sync_with_stdio(false);}
int main(void) {
  FastIO();
  int N;
  cin >> N;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < 4; j++)
      cin >> arr[j][i];

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      arr_m[i * N + j] = arr[2][i] + arr[3][j];

  sort(arr_m, arr_m + N * N);
  ll result = 0;
  ll x;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      x = arr[0][i] + arr[1][j];
      ll low = lower_bound(arr_m, arr_m + N * N, -x) - arr_m;
      ll high = upper_bound(arr_m, arr_m + N * N, -x) - arr_m;

      if (-x == arr_m[low]) result += (high - low);
    }
  }

  cout << result << "\n";
  return 0;
}
