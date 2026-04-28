#include <bits/stdc++.h>
using namespace std;

int a[100000];
int main(){
  int n, k;
  cin >> n >> k;

  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  reverse(a, a + n);

  int s = 0;
  for (int i = 0; i < k; i++) s += a[i];
  cout << s << '\n';
}
