#include <bits/stdc++.h>
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
  int n, k;
  cin >> n;

  vector <complex<double>> fa;
  int sz = 1 << 19;
  fa.resize(sz);
  fa[0] = complex<double>(1, 0);
  for (int i = 0; i < n; i++) {
    cin >> k;
    fa[k] = complex<double>(1, 0);
  }
  fft(fa, false);
  for (int i = 0; i < sz; i++) fa[i] *= fa[i];
  fft(fa, true);

  int m, cnt = 0;
  cin >> m;
  while (m--) {
    cin >> k;
    if (round(fa[k].real()) > 0) cnt++;
  }

  cout << cnt << '\n';
}
