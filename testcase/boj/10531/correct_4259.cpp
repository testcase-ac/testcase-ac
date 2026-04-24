#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
typedef complex<double> base;
// FFT implementation adapted for this solution.
// Reference: http://blog.myungwoo.kr/54
void fft(vector <base> &a, bool invert)
{
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
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
 
void multiply(const vector<int> &a,const vector<int> &b,vector<int> &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < max(sz(a),sz(b))) n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
    for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(200001);
	a[0] = 1;
	for(int i=0; i<n; i++) {
		int t;
		cin >> t;
		a[t] = 1;
	}
	vector<int> res;
	multiply(a, a, res);
	int m, ans = 0;
	cin >> m;
	for(int i=0; i<m; i++) {
		int t;
		cin >> t;
		if(res[t]) ans++;
	}
	cout << ans;
}
