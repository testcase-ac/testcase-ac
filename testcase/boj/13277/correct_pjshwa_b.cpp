#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

namespace fft{
	typedef complex<double> base;
	void fft(vector<base> &a, bool inv){
		int n = a.size(), j = 0;
		for(int i=1; i<n; i++){
			int bit = (n >> 1);
			while(j >= bit){
				j -= bit;
				bit >>= 1;
			}
			j += bit;
			if(i < j) swap(a[i], a[j]);
		}
		for(int i=2; i<=n; i<<=1){
			double ang = 2 * acos(-1) / i * (inv ? -1 : 1);
			base x(cos(ang), sin(ang));
			for(int j=0; j<n; j+=i){
				base y(1);
				for(int k=0; k<i/2; k++){
					base u = a[j+k], v = a[j+k+i/2] * y;
					a[j+k] = u+v;
					a[j+k+i/2] = u-v;
					y *= x;
				}
			}
		}
		if(inv) for(int i=0; i<n; i++) a[i] /= n;
	}

	vector<lint> multiply(vector<lint> &v, vector<lint> &w){
		vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		fv.resize(n);
		fw.resize(n);
		fft(fv, 0);
		fft(fw, 0);
		for(int i=0; i<n; i++) fv[i] *= fw[i];
		fft(fv, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++) ret[i] = round(fv[i].real());
		return ret;
	}
	vector<lint> multiply(vector<lint> &v, vector<lint> &w, lint mod){
		int n = 1;
		while(n < max(v.size(), w.size())) n <<= 1;
		n <<= 1;
		vector<base> v1(n), v2(n);
		vector<base> r1(n), r2(n);
		for(int i=0; i<v.size(); i++){
			v1[i] = base(v[i] >> 15, v[i] & 32767);
		}
		for(int i=0; i<w.size(); i++){
			v2[i] = base(w[i] >> 15, w[i] & 32767);
		}
		fft(v1, 0);
		fft(v2, 0);
		for(int i=0; i<n; i++){
			int j = (i ? (n - i) : i);
			base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
			base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
			base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
			base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
			r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
			r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
		}
		fft(r1, 1);
		fft(r2, 1);
		vector<lint> ret(n);
		for(int i=0; i<n; i++){
			lint av = (lint)round(r1[i].real());
			lint bv = (lint)round(r1[i].imag()) + (lint)round(r2[i].real());
			lint cv = (lint)round(r2[i].imag());
			av %= mod, bv %= mod, cv %= mod;
			ret[i] = (av << 30) + (bv << 15) + cv;
			ret[i] %= mod;
			ret[i] += mod;
			ret[i] %= mod;
		}
		return ret;
	}
}

char a[1000005], b[1000005];  
lint ans[2000005];

vector<lint> va, vb, ret;  

int main(){  
	scanf("%s %s",a,b);  
	reverse(a, a + strlen(a));
	reverse(b, b + strlen(b));
	for(int i=0; a[i]; i+=3){
		int tmp = 0, pwr = 1;
		for(int j=0; j<3; j++){
			if(!a[i+j]) break;
			tmp = tmp + (a[i+j] - '0') * pwr;
			pwr *= 10;
		}
		va.push_back(tmp);
	}
	for(int i=0; b[i]; i+=3){
		int tmp = 0, pwr = 1;
		for(int j=0; j<3; j++){
			if(!b[i+j]) break;
			tmp = tmp + (b[i+j] - '0') * pwr;
			pwr *= 10;
		}
		vb.push_back(tmp);
	}
	ret = fft::multiply(va, vb);
	int mx = 0;
	for(int i=0; i<ret.size(); i++){
		for(int j=3*i; ret[i]; j++){
			ans[j] += ret[i] % 10;
			ret[i] /= 10;
			mx = max(mx, j);
		}
	}
	for(int i=0; i<mx; i++){
		ans[i+1] += ans[i] / 10;
		ans[i] %= 10;
	}
	while(ans[mx] >= 10){
		ans[mx+1] += ans[mx] / 10;
		ans[mx] %= 10;
		mx++;
	}
	for(int i=mx; i>=0; i--){
		printf("%lld", ans[i]);
	}  
}

// https://www.acmicpc.net/source/6583523
