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

int rsum[200001];
int main() {
  int n, m;
  string s, t;
  cin >> n >> m >> s >> t;

  vector<int> a1, b1, a2, b2, a3, b3;
  a1.resize(n + m - 1, 0); b1.resize(m, 0);
  a2.resize(n + m - 1, 0); b2.resize(m, 0);
  a3.resize(n + m - 1, 0); b3.resize(m, 0);
  for (int i = 0; i < n; i++) {
    if (s[i] == 'R') a1[i] = 1;
    if (s[i] == 'P') a2[i] = 1;
    if (s[i] == 'S') a3[i] = 1;
  }
  for (int i = 0; i < m; i++) {
    if (t[i] == 'R') b3[m - 1 - i] = 1;
    if (t[i] == 'P') b1[m - 1 - i] = 1;
    if (t[i] == 'S') b2[m - 1 - i] = 1;
  }

  int mv = -1;
  vector<int> ans;
  ans = multiply(a1, b1);
  for (int i = 0; i < n + m; i++) rsum[i] += ans[i];
  ans = multiply(a2, b2);
  for (int i = 0; i < n + m; i++) rsum[i] += ans[i];
  ans = multiply(a3, b3);
  for (int i = 0; i < n + m; i++) rsum[i] += ans[i];
  cout << *max_element(rsum + m - 1, rsum + n + m) << '\n';
}
