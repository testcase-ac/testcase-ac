#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

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

int main() {
  int n;
  cin >> n;

  vector<ll> r;
  int sz = 1 << 20;
  r.resize(sz);
  for (ll i = 1; i < n; i++) r[(i * i) % n]++;

  vector <complex<double>> fa, fb;
  fa.resize(sz); fb.resize(sz);
  for (int i = 0; i < n; i++) fa[i] = r[i];
  for (int i = n; i < 2 * n; i++) fa[i] = fb[i - n] = r[i - n];
  fft(fa, false); fft(fb, false);
  for (int i = 0; i < sz; i++) fa[i] *= fb[i];
  fft(fa, true);

  ll cnt = 0;
  for (int i = 0; i < n; i++) {
    cnt += ((ll)round(fa[i + n].real()) * r[i]);
    cnt += (r[2 * i % n] * r[i]);
  }
  cout << cnt / 2 << '\n';
}
