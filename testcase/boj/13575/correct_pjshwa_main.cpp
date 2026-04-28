#include <bits/stdc++.h>
typedef long long ll;
#define vl vector<ll>
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

vl operator * (const vl &a, const vl &b) {
  vector <complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max((int)a.size(),(int)b.size())) n <<= 1;
  vl c(n);
  fa.resize(n); fb.resize(n);
  fft(fa,false); fft(fb,false);
  for (int i=0;i<n;i++) fa[i] *= fb[i];
  fft(fa,true);
  for (int i = 0; i < n; i++) {
    if (round(fa[i].real()) > 0) c[i] = 1;
  }
  return c;
}

int main() {
  fast_io();

  ll k, n, s;
  cin >> n >> k;

  ll m = 1e6 + 1;

  vl a = vl(m);
  for (int i = 0; i < n; i++) {
    cin >> s;
    a[s] = 1;
  }

  // Identity
  vl ans = vl(m);
  ans[0] = 1;

  // Exponentiation by squaring
  while (k) {
    if (k & 1) ans = ans * a;
    a = a * a;
    k /= 2;
  }

  for (int i = 0; i < m; i++) {
    if (ans[i]) cout << i << ' ';
  }
  cout << '\n';
}
