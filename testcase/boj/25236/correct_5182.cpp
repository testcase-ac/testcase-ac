#include <bits/stdc++.h>
using namespace std;
#define n_l '\n'
// #define //dbg(...) cout << "[" << #__VA_ARGS__ << "]: "; cout << to_string(__VA_ARGS__) << endl
// template <typename T, size_t N> int SIZE(const T (&t)[N]){ return N; } template<typename T> int SIZE(const T &t){ return t.size(); } string to_string(const string s, int x1=0, int x2=1e9){ return '"' + ((x1 < s.size()) ? s.substr(x1, x2-x1+1) : "") + '"'; } string to_string(const char* s) { return to_string((string) s); } string to_string(const bool b) { return (b ? "true" : "false"); } string to_string(const char c){ return string({c}); } template<size_t N> string to_string(const bitset<N> &b, int x1=0, int x2=1e9){ string t = ""; for(int __iii__ = min(x1,SIZE(b)),  __jjj__ = min(x2, SIZE(b)-1); __iii__ <= __jjj__; ++__iii__){ t += b[__iii__] + '0'; } return '"' + t + '"'; } template <typename A, typename... C> string to_string(const A (&v), int x1=0, int x2=1e9, C... coords); int l_v_l_v_l = 0, t_a_b_s = 0; template <typename A, typename B> string to_string(const pair<A, B> &p) { l_v_l_v_l++; string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; l_v_l_v_l--; return res; } template <typename A, typename... C> string to_string(const A (&v), int x1, int x2, C... coords) { int rnk = rank<A>::value; string tab(t_a_b_s, ' '); string res = ""; bool first = true; if(l_v_l_v_l == 0) res += n_l; res += tab + "["; x1 = min(x1, SIZE(v)), x2 = min(x2, SIZE(v)); auto l = begin(v); advance(l, x1); auto r = l; advance(r, (x2-x1) + (x2 < SIZE(v))); for (auto e = l; e != r; e = next(e)) { if (!first) { res += ", "; } first = false; l_v_l_v_l++; if(e != l){ if(rnk > 1) { res += n_l; t_a_b_s = l_v_l_v_l; }; } else{ t_a_b_s = 0; } res += to_string(*e, coords...); l_v_l_v_l--; } res += "]"; if(l_v_l_v_l == 0) res += n_l; return res; } void //dbgm(){;} template<typename Heads, typename... Tails> void //dbgm(Heads H, Tails... T){ cout << to_string(H) << " | "; //dbgm(T...); } 
// #define //dbgm(...) cout << "[" << #__VA_ARGS__ << "]: "; //dbgm(__VA_ARGS__); cout << endl

#define all(x) x.begin(), x.end()
#define int long long

struct point {
    int x, y, h;
};
struct query {
    int xl, yl, xh, yh;
};
struct info {
    int y, h;
    info(): y(0), h(0) {}
    info(int _y, int _h): y(_y), h(_h) {}
    bool operator<(const info& d) const {
        return y < d.y;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<point> v(N);
    vector<query> queries(Q);
    vector<int> xs, ys;
    for(auto &t: v) {
        cin >> t.x >> t.y >> t.h;
        xs.push_back(t.x);
        ys.push_back(t.y);
    }
    for(auto &q: queries) {
        cin >> q.xl >> q.yl >> q.xh >> q.yh;
        xs.push_back(q.xl);
        ys.push_back(q.yl);
        xs.push_back(q.xh);
        ys.push_back(q.yh);
    }
    sort(all(xs));
    sort(all(ys));
    xs.erase(unique(all(xs)), xs.end());
    ys.erase(unique(all(ys)), ys.end());
    for(auto &t: v) {
        t.x = lower_bound(all(xs), t.x) - xs.begin();
        t.y = lower_bound(all(ys), t.y) - ys.begin();
    }
    for(auto &q: queries) {
        q.xl = lower_bound(all(xs), q.xl) - xs.begin();
        q.yl = lower_bound(all(ys), q.yl) - ys.begin();
        q.xh = lower_bound(all(xs), q.xh) - xs.begin();
        q.yh = lower_bound(all(ys), q.yh) - ys.begin();
    }
    vector<vector<info>> seg(xs.size() * 2);
    auto query_cnt = [&](int l, int r, int yl, int yh) {
        l += xs.size(), r += xs.size();
        int cnt = 0;
        while(l < r) {
            //dbg(l);
            //dbg(r);
            if(l&1) {
                //dbg(l);
                cnt += upper_bound(all(seg[l]), info(yh, 0)) - lower_bound(all(seg[l]), info(yl, 0));
                l++;
            }
            if(r&1) {
                r--;
                //dbg(r);
                cnt += upper_bound(all(seg[r]), info(yh, 0)) - lower_bound(all(seg[r]), info(yl, 0));
            }
            l /= 2, r /= 2;
        }
        return cnt;
    };
    auto query_vec = [&](int l, int r, int yl, int yh) {
        l += xs.size(), r += xs.size();
        vector<int> res;
        while(l < r) {
            if(l&1) {
                auto it = lower_bound(all(seg[l]), info(yl, 0));
                auto itend = upper_bound(all(seg[l]), info(yh, 0));
                while(it != itend) {
                    res.push_back(it->h);
                    it++;
                }
                l++;
            }
            if(r&1) {
                r--;
                auto it = lower_bound(all(seg[r]), info(yl, 0));
                auto itend = upper_bound(all(seg[r]), info(yh, 0));
                while(it != itend) {
                    res.push_back(it->h);
                    it++;
                }
            }
            l /= 2, r /= 2;
        }
        return res;
    };
    for(auto &t: v) {
        seg[xs.size() + t.x].push_back({t.y, t.h});
    }
    for(int i=xs.size(); i<(int)xs.size()*2; i++) {
        sort(all(seg[i]));
    }
    for(int i=xs.size() - 1; i; i--) {
        seg[i].resize(seg[2*i].size() + seg[2*i+1].size());
        merge(all(seg[2*i]), all(seg[2*i+1]), seg[i].begin());
    }
    //dbg(seg.size());
    for(auto &q: queries) {
        //dbg(q.xl);
        //dbg(q.xh+1);
        int cnt = query_cnt(q.xl, q.xh+1, q.yl, q.yh);
        //dbg(cnt);
        if(cnt > 45) {
            cout << "1\n";
            continue;
        }
        bool ok = 0;
        vector<int> res = query_vec(q.xl, q.xh+1, q.yl, q.yh);
        //dbg(res);
        sort(all(res));
        for(int i=0; i<(int)res.size()-2; i++) {
            if(res[i] + res[i+1] > res[i+2]) {
                ok = 1;
            }
        }
        cout << ok << '\n';
    }

}
