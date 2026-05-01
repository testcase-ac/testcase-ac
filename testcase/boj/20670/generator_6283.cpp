#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// orientation: >0 if a->b->c is CCW, <0 if CW, 0 if colinear
ll orient(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& c) {
    return (b.first - a.first) * (c.second - a.second)
         - (b.second - a.second) * (c.first - a.first);
}

// check if point p is on segment a-b
bool onSegment(const pair<ll,ll>& a, const pair<ll,ll>& b, const pair<ll,ll>& p) {
    if (orient(a, b, p) != 0) return false;
    return min(a.first, b.first) <= p.first && p.first <= max(a.first, b.first)
        && min(a.second, b.second) <= p.second && p.second <= max(a.second, b.second);
}

// point-in-polygon for a general polygon (may be convex).
// returns 0=outside, 1=inside, 2=on boundary
int pointInPoly(const vector<pair<ll,ll>>& P, const pair<ll,ll>& pt) {
    bool inside = false;
    int n = P.size();
    for (int i = 0, j = n-1; i < n; j = i++) {
        auto &a = P[i], &b = P[j];
        if (onSegment(a, b, pt)) return 2;
        bool yi = (a.second > pt.second);
        bool yj = (b.second > pt.second);
        if (yi != yj) {
            double xint = (double)(b.first - a.first) * (pt.second - a.second)
                        / (double)(b.second - a.second) + a.first;
            if (xint > pt.first) inside = !inside;
        }
    }
    return inside ? 1 : 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // sizes
    int N = rnd.next(3, 10);
    int M = rnd.next(3, 10);
    int Kmax = rnd.next(10, 25);
    int K = rnd.next(2, Kmax);

    // radii
    int R_A = rnd.next(50, 100);
    int r_B = rnd.next(10, max(10, int(floor(R_A * 0.4))));

    // build convex polygon A (regular N-gon)
    vector<pair<ll,ll>> A;
    while (true) {
        A.clear();
        double alpha = rnd.next() * 2 * M_PI;
        for (int i = 0; i < N; i++) {
            double ang = alpha + 2 * M_PI * i / N;
            ll x = llround(R_A * cos(ang));
            ll y = llround(R_A * sin(ang));
            A.emplace_back(x, y);
        }
        set<pair<ll,ll>> sa(A.begin(), A.end());
        if ((int)sa.size() != N) continue;
        bool ok = true;
        for (int i = 0; i < N; i++) {
            if (orient(A[i], A[(i+1)%N], A[(i+2)%N]) <= 0) {
                ok = false; break;
            }
        }
        if (ok) break;
    }

    // build convex polygon B (regular M-gon) strictly inside A
    vector<pair<ll,ll>> B;
    while (true) {
        B.clear();
        double beta = rnd.next() * 2 * M_PI;
        for (int i = 0; i < M; i++) {
            double ang = beta + 2 * M_PI * i / M;
            ll x = llround(r_B * cos(ang));
            ll y = llround(r_B * sin(ang));
            B.emplace_back(x, y);
        }
        set<pair<ll,ll>> sb(B.begin(), B.end());
        if ((int)sb.size() != M) continue;
        bool ok = true;
        for (int i = 0; i < M; i++) {
            if (orient(B[i], B[(i+1)%M], B[(i+2)%M]) <= 0) {
                ok = false; break;
            }
        }
        if (!ok) continue;
        // by radii choice B is strictly inside A
        break;
    }

    // track used points to avoid duplicates
    set<pair<ll,ll>> used;
    for (auto &p : A) used.insert(p);
    for (auto &p : B) used.insert(p);

    // hyper-parameters for signature invalid ratio
    double p_fail = rnd.next();
    double p_inB  = rnd.next();

    // bounds for sampling
    int boundA = R_A + 5;
    int boundB = r_B + 5;

    // generate signature points
    vector<pair<ll,ll>> S;
    S.reserve(K);
    while ((int)S.size() < K) {
        bool make_invalid = (rnd.next() < p_fail);
        pair<ll,ll> pt;
        if (make_invalid) {
            if (rnd.next() < p_inB) {
                // inside B
                do {
                    ll x = rnd.next(-boundB, boundB);
                    ll y = rnd.next(-boundB, boundB);
                    pt = {x, y};
                } while (pointInPoly(B, pt) != 1 || used.count(pt));
            } else {
                // outside A
                do {
                    ll x = rnd.next(-boundA, boundA);
                    ll y = rnd.next(-boundA, boundA);
                    pt = {x, y};
                } while (pointInPoly(A, pt) != 0 || used.count(pt));
            }
        } else {
            // valid: inside A (1) and outside B (0)
            do {
                ll x = rnd.next(-boundA, boundA);
                ll y = rnd.next(-boundA, boundA);
                pt = {x, y};
            } while (pointInPoly(A, pt) != 1 || pointInPoly(B, pt) != 0 || used.count(pt));
        }
        used.insert(pt);
        S.push_back(pt);
    }

    // output
    println(N, M, K);
    {
        vector<ll> tmp;
        tmp.reserve(2*N);
        for (auto &p : A) {
            tmp.push_back(p.first);
            tmp.push_back(p.second);
        }
        println(tmp);
    }
    {
        vector<ll> tmp;
        tmp.reserve(2*M);
        for (auto &p : B) {
            tmp.push_back(p.first);
            tmp.push_back(p.second);
        }
        println(tmp);
    }
    {
        vector<ll> tmp;
        tmp.reserve(2*K);
        for (auto &p : S) {
            tmp.push_back(p.first);
            tmp.push_back(p.second);
        }
        println(tmp);
    }
    return 0;
}
