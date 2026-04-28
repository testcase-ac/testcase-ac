#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

// FFT by myungwoo - blog.myungwoo.kr/54
void fft(vector <complex<double>> &a, bool invert){
  int n = a.size();
  for (int i=1,j=0;i<n;i++){
    int bit = n >> 1;
    for (;j>=bit;bit>>=1) j -= bit;
    j += bit;
    if (i < j) swap(a[i],a[j]);
  }
  for (int len=2;len<=n;len<<=1){
    double ang = 2*M_PI/len*(invert?-1:1);
    complex<double> wlen(cos(ang),sin(ang));
    for (int i=0;i<n;i+=len){
      complex<double> w(1);
      for (int j=0;j<len/2;j++){
        complex<double> u = a[i+j], v = a[i+j+len/2]*w;
        a[i+j] = u+v;
        a[i+j+len/2] = u-v;
        w *= wlen;
      }
    }
  }
  if (invert){
    for (int i=0;i<n;i++) a[i] /= n;
  }
}

const ll MAX = 1e6;
ll lp[MAX + 1];

int main() {
  fast_io();

  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  vector <complex<double>> fa;
  int sz = 1 << 20;
  fa.resize(sz);
  for (int e : pr) fa[e / 2] = complex<double>(1, 0);

  fft(fa, false);
  for (int i = 0; i < sz; i++) fa[i] *= fa[i];
  fft(fa, true);

  int m, k, ans;
  cin >> m;
  while (m--) {
    cin >> k;
    if (k == 4) cout << "1\n";
    else {
      if (lp[k / 2] == k / 2) ans = 1;
      else ans = 0;

      k = (k - 2) / 2;
      ans += (int)round(fa[k].real()) / 2;
      cout << ans << '\n';
    }
  }
}
