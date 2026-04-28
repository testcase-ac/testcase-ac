#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

void solve() {
  string s, t;
  cin >> s >> t;
  reverse(s.begin(), s.end()); reverse(t.begin(), t.end());

  if (s == "0" || t == "0") return cout << "0\n", void();

  int n = s.size(), m = t.size();
  vector<int> a(n + m + 10, 0), b(n + m + 10, 0);
  for (int i = 0; i < max(n, m); i++) {
    if (i < s.size()) a[i] = s[i] - '0';
    if (i < t.size()) b[i] = t[i] - '0';
  }

  auto ans = multiply(a, b);

  int carry = 0;
  for (int i = 0; i < ans.size(); i++) {
    ans[i] += carry;
    carry = ans[i] / 10;
    ans[i] %= 10;
  }

  bool lz = true;
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    if (lz && ans[i] == 0) continue;
    lz = false;
    cout << ans[i];
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
