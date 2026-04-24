#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
typedef vector<int> vi;
typedef complex<double> base;

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
vector<int> multiply(vector<int>& a, vector<int>& b)
{
    vector<base> fa(all(a)), fb(all(b));
    int n = 1, m = sz(a)+sz(b)-1;
    while (n < m) n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<int> ret(m);
    for (int i=0;i<m;i++) ret[i] = fa[i].real()+(fa[i].real()>0?0.5:-0.5);
    return ret;
}
void read(vector<int> &v) {
    int n;
    cin >> n;
    v.resize(n);
    for (int i=0;i<n;i++) {
        cin >> v[i];
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> a, b, c;
    read(a);
    read(b);
    read(c);
    const int offset = 30005;
    for(auto &t: b) {
        t += offset;
        t *= 2;
    }
    for(auto &t: a) {
        t -= offset;
        t *= -1;
    }
    vector<int> fa(offset * 6), fb(offset * 6), res;
    for(auto &t: a) {
        fa[t]++;
    }
    for(auto &t: b) {
        fb[t]++;
    }
    res = multiply(fa, fb);
    int ans = 0;
    for(auto t: c) {
        t += offset * 3;
        ans += res[t];
    }
    cout << ans << '\n';
}
