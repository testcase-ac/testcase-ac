#include <iostream>

using namespace std;
 
using lint = long long;
 
int N, a[250004], mul[250004];
 
int getmul(int x, int y) {
  lint nowx = x, nowy = y;
  for (int i = 0; i < 20; i++) nowx *= 2;
 
  for (int i = -20; i < 0; i++) {
    if (nowx <= nowy) return i;
    nowx /= 2;
  }
  for (int i = 0; i < 20; i++) {
    if (nowx <= nowy) return i;
    nowy *= 2;
  }
  return 20;
}
 
int main() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
 
  for (int i = 1; i < N; i++) mul[i] = getmul(a[i - 1], a[i]);
 
  lint ans = 0;
 
  for (int i = 1; i < N; i++)
    if (mul[i] > 0) {
      ans += mul[i];
      mul[i + 1] += mul[i];
    }
 
  cout << ans << '\n';
}