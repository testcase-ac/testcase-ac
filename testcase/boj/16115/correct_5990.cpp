#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;
ll len(ll x, ll y) {
    return x*x+y*y;
}
double deg(ll x, ll y) {
    double d = acos((double)x / (double)sqrt(len(x,y)));
    return (y >= 0 ? d : 2*M_PI-d)/M_PI*180;
}

double diff(double l, double s) {
    if(l < s) l += 360;
    double ret = l - s;
    //if(ret < 180) ret = 360 - ret;
    return ret;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    ll maxlen = 0;
    vector<double> degs;
    while(n--) {
        int x, y;
        cin >> x >> y;
        if(len(x,y) > maxlen) {
            maxlen = len(x,y);
            degs = {deg(x,y)};
        } else if(len(x,y) == maxlen) {
            degs.push_back(deg(x,y));
        }
    }
    sort(degs.begin(), degs.end());
    if(sz(degs) == 1) return !(cout << 360);
    double maxd = diff(degs[0], degs.back());
    for(int i=0; i<sz(degs)-1; i++) {
        maxd = max(maxd, diff(degs[i+1], degs[i]));
    }
    cout << fixed << setprecision(10) << maxd;
}
