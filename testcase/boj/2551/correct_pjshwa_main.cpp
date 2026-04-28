#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MAX = 5e6;
int arr[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
    sum += arr[i];
  }
  sort(arr, arr + n);

  ll k = sum / n;
  if (2 * sum > n * (2 * k + 1)) k++;
  cout << arr[(n - 1) / 2] << ' ' << k << '\n';
}
