#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

/**
 We compute the set of longitudes visited by Amelia's tour on the sphere,
 and then check the contestant's output against that.
 We represent longitudes in [0,360) by shifting λ→λ+180.
 Each great‐circle shortest arc between two non‐antipodal, non‐pole points
 induces an interval (possibly wrapping) of visited longitudes.
 We merge all intervals and see if they cover [0,360).
**/

static const double EPS = 1e-9;

bool le(double a, double b) { return a < b + EPS; }
bool lt(double a, double b) { return a + EPS < b; }

// parse a token as a double, but enforce it is of the form integer or half-integer:
// i.e. matches /^-?\d+(\.0|\.5)$/.
bool parse_half(const string &s, double &out) {
    // must contain exactly one dot
    size_t p = s.find('.');
    if (p == string::npos) return false;
    // fractional part must be "0" or "5"
    if (s.size() != p + 2) return false;
    if (s[p+1] != '0' && s[p+1] != '5') return false;
    // integer part (may be negative) must be non-empty
    if (p == 0) return false;
    for (size_t i = 0; i < p; i++) {
        if (i==0 && s[i]=='-') {
            if (p==1) return false;
            continue;
        }
        if (!isdigit(s[i])) return false;
    }
    // parse
    char *endp = nullptr;
    out = strtod(s.c_str(), &endp);
    if (endp != s.c_str() + s.size()) return false;
    return true;
}

int main(int argc, char * argv[]) {
    registerTestlibCmd(argc, argv);
    // read input
    int n = inf.readInt();
    vector<double> phi(n), lam(n);
    for (int i = 0; i < n; i++) {
        phi[i] = inf.readInt();    // unused
        lam[i] = inf.readInt();    // in [-180,180)
    }
    // build visited‐longitude intervals in [0,360)
    vector<pair<double,double>> segs;
    auto to360 = [&](double x) {
        // x in [-180,180) → [0,360)
        double y = x + 180.0;
        if (y < 0) y += 360.0;
        if (y >= 360.0) y -= 360.0;
        return y;
    };
    for (int i = 0; i < n; i++) {
        int j = (i+1==n)? 0 : i+1;
        double A = to360(lam[i]);
        double B = to360(lam[j]);
        double d = B - A;
        // normalize to (-180,180]
        if (d > 180.0) d -= 360.0;
        else if (d <= -180.0) d += 360.0;
        double start = A, end = A + d;
        double l, r;
        if (d >= 0) {
            l = start; r = end;
        } else {
            l = end; r = start;
        }
        // bring into [0,360)
        if (l < 0) l += 360.0;
        if (l >= 360.0) l -= 360.0;
        if (r < 0) r += 360.0;
        if (r >= 360.0) r -= 360.0;
        if (le(l, r)) {
            segs.emplace_back(l, r);
        } else {
            // wraps
            segs.emplace_back(l, 360.0);
            segs.emplace_back(0.0, r);
        }
    }
    // merge intervals
    sort(segs.begin(), segs.end());
    vector<pair<double,double>> iv;
    for (auto &p : segs) {
        if (iv.empty() || lt(iv.back().second, p.first)) {
            iv.push_back(p);
        } else {
            iv.back().second = max(iv.back().second, p.second);
        }
    }
    // check coverage
    bool full = false;
    if (!iv.empty() && le(iv.front().first, 0.0) && le(360.0, iv.back().second))
        full = true;
    // find gaps if any
    vector<pair<double,double>> gaps;
    if (!full) {
        // gap before first
        if (lt(0.0, iv.front().first)) {
            gaps.emplace_back(0.0, iv.front().first);
        }
        // between
        for (int i = 0; i + 1 < (int)iv.size(); i++) {
            if (lt(iv[i].second, iv[i+1].first))
                gaps.emplace_back(iv[i].second, iv[i+1].first);
        }
        // after last
        if (lt(iv.back().second, 360.0)) {
            gaps.emplace_back(iv.back().second, 360.0);
        }
    }

    // read contestant output
    string tok = ouf.readWord();
    if (tok == "yes") {
        // must cover all
        if (full) {
            quitf(_ok, "correct circumnavigation");
        } else {
            quitf(_wa, "output 'yes' but not all meridians are visited");
        }
    } else if (tok == "no") {
        // must not be full
        if (full) {
            quitf(_wa, "output 'no' but actually all meridians are visited");
        }
        // read longitude
        string s = ouf.readToken();
        double v;
        if (!parse_half(s, v)) {
            quitf(_wa, "longitude '%s' is not a valid integer or half-integer", s.c_str());
        }
        if (!(v >= -180.0 - EPS && v < 180.0 - EPS)) {
            quitf(_wa, "longitude %.10f is out of range [-180,180)", v);
        }
        // map to [0,360)
        double vp = v + 180.0;
        if (vp < 0) vp += 360.0;
        if (vp >= 360.0) vp -= 360.0;
        // check it's in a gap
        bool in_gap = false;
        for (auto &g : gaps) {
            if (le(g.first, vp) && le(vp, g.second)) {
                in_gap = true; break;
            }
        }
        if (!in_gap) {
            quitf(_wa, "longitude %.3f is actually visited", v);
        }
        // no extra tokens
        ouf.readEof();
        quitf(_ok, "found unvisited meridian %.3f", v);
    } else {
        quitf(_wa, "first token is '%s', expected 'yes' or 'no'", tok.c_str());
    }
    return 0;
}
