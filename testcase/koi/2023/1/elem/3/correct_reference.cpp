#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <tuple>
using namespace std;
using ll = long long;

int N, Q, X[202020], Y[202020], W[202020];
vector<pair<int,int>> XV[202020], YV[202020];
vector<ll> XP[202020], YP[202020], XS[202020], YS[202020];

void Init(vector<pair<int,int>> &vec, vector<ll> &pos, vector<ll> &sum){
    pos.resize(vec.size());
    sum.resize(vec.size());
    sort(vec.begin(), vec.end());
    for(int i=0; i<vec.size(); i++) tie(pos[i],sum[i]) = vec[i];
    partial_sum(sum.begin(), sum.end(), sum.begin());
}

ll Get(const vector<ll> &pos, const vector<ll> &sum, int l, int r){
    int st = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
    int ed = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;
    return st <= ed ? sum[ed] - (st ? sum[st-1] : 0) : 0;
}

int main(){
    cin >> N >> Q;
    for(int i=1; i<=N; i++) cin >> X[i] >> Y[i] >> W[i];
    for(int i=1; i<=N; i++){
        XV[X[i]].emplace_back(Y[i], W[i]);
        YV[Y[i]].emplace_back(X[i], W[i]);
    }
    for(int i=0; i<202020; i++){
        Init(XV[i], XP[i], XS[i]);
        Init(YV[i], YP[i], YS[i]);
    }

    int x = 1, y = 1;
    long long res = 0;
    for(int q=1; q<=Q; q++){
        int d, v, l=0, r=0; cin >> d >> v;
        if(d == 0) l = x + 1, r = x + v, x += v;
        if(d == 1) l = y + 1, r = y + v, y += v;
        if(d == 2) l = x - v, r = x - 1, x -= v;
        if(d == 3) l = y - v, r = y - 1, y -= v;
        if(d % 2 == 0) res += Get(YP[y], YS[y], l, r);
        else res += Get(XP[x], XS[x], l, r);
    }
    cout << res << "\n";
}