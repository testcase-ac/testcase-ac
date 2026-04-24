#include <bits/stdc++.h>
using namespace std;
#define int long long

#define _USE_MATH_DEFINES
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
#define rep(i, n) for(int i=0; i<n; i++)
typedef vector<int> vi;
typedef complex<double> base;
void fft(vector <base> &a, bool invert) {
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    for(int len=2; len<=n; len<<=1) {
        double ang = 2*M_PI/len*(invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for(int i=0; i<n; i+=len) {
            base w(1);
            for(int j=0; j<len/2; j++) {
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if(invert) {
        for(int i=0; i<n; i++) a[i] /= n;
    }
}

void multiply(const vi &a, const vi &b, vi &res) {
    vector<base> fa(all(a)), fb(all(b));
    int n=1;
    while(n < max(sz(a), sz(b))) n <<=1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for(int i=0; i<n; i++) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    for(int i=0; i<n; i++) {
        res[i] = (int)(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
    }

}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, L, M, W;
    cin >> N >> L >> M >> W;
    vector<vector<int>> sky(M, vector<int>(N)), tel(M, vector<int>(L));
    rep(i, M) rep(j, N) cin >> sky[i][j];
    rep(i, M) rep(j, L) cin >> tel[i][j];
    vector<int> res, fin(N);
    for(int i=0; i<M; i++) {
        reverse(tel[i].begin(), tel[i].end());
        multiply(sky[i], tel[i], res);
        for(int j=0; j<=N-L; j++) {
            fin[j] += res[L-1+j];
        }
    }
    cout << count_if(fin.begin(), fin.end(), [&](int t) {return t > W;});
}
