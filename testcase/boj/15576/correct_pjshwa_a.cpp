#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef complex<double> base;
typedef vector<base> poly;
const double PI = acos(-1);

void fft(poly &f, bool inv = 0){
    int n = f.size(), j = 0;
    vector<base> root(n >> 1);
    for(int i=1; i<n; i++){
        int bit = (n >> 1);
        while(j >= bit){
            j -= bit; bit >>= 1;
        }
        j += bit;
        if(i < j) swap(f[i], f[j]);
    }
    double ang = 2 * PI / n; if(inv) ang *= -1;
    for(int i=0; i<(n >> 1); i++) root[i] = base(cos(ang*i), sin(ang*i));
    for(int i=2; i<=n; i<<=1){
        int step = n / i;
        for(int j=0; j<n; j+=i){
            for(int k=0; k<(i >> 1); k++){
                base u = f[j | k], v = f[j | k | i >> 1] * root[step * k];
                f[j | k] = u + v;
                f[j | k | i >> 1] = u - v;
            }
        }
    }
    if(inv) for(int i=0; i<n; i++) f[i] /= n;
}

vector<ll> multiply(const vector<ll> &_a, const vector<ll> &_b){
    poly a(all(_a)), b(all(_b));
    int n = 2;
    while(n < a.size() + b.size()) n <<= 1;
    a.resize(n); b.resize(n);
    fft(a); fft(b);
    for(int i=0; i<n; i++) a[i] *= b[i];
    fft(a, 1);
    vector<ll> ret(n);
    for(int i=0; i<n; i++) ret[i] = llround(a[i].real());
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    string a, b; cin >> a >> b;
    vector<ll> x, y;
    x.reserve(a.size()); y.reserve(b.size());
    for(int i=a.size()-1; i>=0; i--) x.push_back(a[i] - '0');
    for(int i=b.size()-1; i>=0; i--) y.push_back(b[i] - '0');
    vector<ll> v = multiply(x, y);
    v.push_back(0);
	for(int i=0; i<v.size()-1; i++){
		if(v[i] < 0){
			int b = (abs(v[i]) + 9) / 10;
			v[i+1] -= b;
			v[i] += b * 10;
		}else{
			v[i+1] += v[i] / 10;
			v[i] %= 10;
		}
	}
	while(v.size() > 1 && v.back() == 0) v.pop_back();
    for(int i=v.size()-1; i>=0; i--) cout << v[i];
}
