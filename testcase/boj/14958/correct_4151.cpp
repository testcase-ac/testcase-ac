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
string arr = "RPSRPS";
void out(vector<int>& v) {
	for(int t: v)
		printf("%d ", t);
	printf("\n");
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	string s, t;
	cin >> s >> t;
	vector<int> res, ans;
	for(int k=0; k<3; k++) {
		vector<int> a(n), b(m);
		for(int i=0; i<n; i++) {
			if(s[i] == arr[k+2])
				a[i] = 1;				
		}
		for(int i=0; i<m; i++) {
			if(t[i] == arr[k]) {
				b[i] = 1;
			}
		}
		reverse(b.begin(), b.end());
		multiply(a, b, res);
		// printf("a: ");
		// out(a);
		// printf("b: ");
		// out(b);
		// printf("res: ");
		// out(res);
		ans.resize(res.size());
		for(int i=0; i<res.size(); i++) {
			ans[i] += res[i];
		}
	}
	cout << *max_element(ans.begin()+m-1, ans.end());
}
