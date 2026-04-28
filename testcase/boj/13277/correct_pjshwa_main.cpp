#include<iostream>
#include<vector>
#include<complex>
#include<cmath>

using namespace std;

typedef complex<double> Complex;
typedef vector<Complex> ComplexVector;
typedef vector<int> Polynomial;

const double PI = 2.0 * acos(0.0);

// Given a n-th polynomial p, return its values at
// w^0, w^1, .., w^(n-1). n is assumed to be a power of 2.
// Since the size of the input and output are the same, the output is stored at
// p.
void dft(ComplexVector& p, Complex w) {
  int n = p.size();
  if(n == 1) return;

  // divide
  ComplexVector even(n / 2), odd(n / 2);
  for(int i = 0; i < n/2; ++i) {
    even[i] = p[i * 2];
    odd[i] = p[i * 2 + 1];
  }

  // conquer
  dft(even, w * w); 
  dft(odd, w * w);

  // merge
  Complex w_power = 1;
  for(int i = 0; i < n/2; ++i) {
    Complex offset = w_power * odd[i];
    p[i      ] = even[i] + offset;
    p[i + n/2] = even[i] - offset;
    w_power *= w;
  }
}

// returns smallest power of 2 s.t. p2 >= n.
int roundUp(int n) {
  int p2 = 1;
  while(p2 < n) p2 *= 2;
  return p2;
}

Polynomial operator * (const Polynomial& a, const Polynomial& b) {
  // last *2 is needed because C can have twice the degree from original polys
  int n = roundUp(max(a.size(), b.size())) * 2;

  // Complex representations of a and b
  ComplexVector ac(a.begin(), a.end()), bc(b.begin(), b.end());
  ac.resize(n); 
  bc.resize(n);

  // FFT 
  Complex w = polar(1.0, 2 * PI / n);
  dft(ac, w);
  dft(bc, w);
  // Pointwise multiplication
  for(int i = 0; i < n; ++i) 
    ac[i] *= bc[i];

  // Inverse FFT
  dft(ac, polar(1.0, -2 * PI / n));
  for(int i = 0; i < n; ++i) 
    ac[i] /= double(n);

  // Trim zero paddings
  while(!ac.empty() && fabs(real(ac.back())) < 1e-9) 
    ac.pop_back();

  // return real
  Polynomial ret(ac.size());
  for(int i = 0; i < ac.size(); ++i) 
    ret[i] = int(round(real(ac[i])));

  return ret;
}

int main() {
  string a, b;
  Polynomial ap, bp;
  cin >> a >> b;

  if (a == "0" || b == "0") {
    cout << "0\n";
    return 0;
  }

  int asz = a.size();
  int bsz = b.size();

  for (int i = asz - 1; i >= 0; i--) ap.push_back(a[i] - 48);
  for (int i = bsz - 1; i >= 0; i--) bp.push_back(b[i] - 48);

  Polynomial res = ap * bp;
  int csz = res.size();

  vector<int> ans;
  int d, curry = 0;
  for (int i = 0; i < csz; i++) {
    d = res[i];
    if (curry) d += curry;
    curry = d / 10;
    ans.push_back(d % 10);
  }
  if (curry) ans.push_back(curry);

  int ans_size = ans.size();
  bool leading_zero = true;

  for (int i = ans_size - 1; i >= 0; i--) {
    if (leading_zero && ans[i] == 0) continue;
    leading_zero = false;
    cout << ans[i];
  }
  cout << '\n';
}

// https://algospot.com/wiki/read/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98_%EB%8C%80%ED%9A%8C%EC%97%90_%ED%95%84%EC%9A%94%ED%95%9C_%EC%88%98%ED%95%99
