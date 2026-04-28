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

vector<int> multiply(const vector<int> &a,const vector<int> &b){
  vector<int> res;
  vector <complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < max((int)a.size(),(int)b.size())) n <<= 1;
  fa.resize(n); fb.resize(n);
  fft(fa,false); fft(fb,false);
  for (int i=0;i<n;i++) fa[i] *= fb[i];
  fft(fa,true);
  res.resize(n);
  for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
  return res;
}

int main() {
  int n;
  cin >> n;

  vector<int> a, b, ans;
  a.resize(2 * n);
  b.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }
  for (int i = n - 1; i >= 0; i--) cin >> b[i];

  ans = multiply(a, b);
  cout << *max_element(ans.begin(), ans.end()) << '\n';
}
