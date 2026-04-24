#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MX = 2e5+2;
struct point {
    int x, y;
};
string name[MX];
point pos[MX];


void solve(vector<int>& v, double xmin, double xmax, double ymin, double ymax, int a, int b, int c, int d, int dep=0) {
    if(v.size() <= 1) {
        for(int t: v) {
            cout << name[t] << '\n';
        }
        return;
    }
    //printf("rec at %lf %f %lf %lf: ", xmin, xmax, ymin, ymax);
    // for(int t: v) {
    //     printf("%s ", name[t].c_str());
    // }
    // printf("\n");
    vector<int> sep[4];
    vector<double> rng[4];
    double xmid = (xmin + xmax) / 2, ymid = (ymin+ymax) / 2;
    rng[0] = {xmin, xmid, ymin, ymid};
    rng[1] = {xmid, xmax, ymin, ymid};
    rng[2] = {xmin, xmid, ymid, ymax};
    rng[3] = {xmid, xmax, ymid, ymax};
    for(auto idx: v) {
        if(pos[idx].y < ymid) {
            if(pos[idx].x < xmid) {
                sep[0].push_back(idx);
            } else {
                sep[1].push_back(idx);
            }
        } else {
            if(pos[idx].x < xmid) {
                sep[2].push_back(idx);
            } else {
                sep[3].push_back(idx);
            }
        }
    }
    // 1537
    solve(sep[a], rng[a][0], rng[a][1], rng[a][2], rng[a][3], a, d, c, b, dep+1);
    solve(sep[b], rng[b][0], rng[b][1], rng[b][2], rng[b][3], a, b, c, d, dep+1);
    solve(sep[c], rng[c][0], rng[c][1], rng[c][2], rng[c][3], a, b, c, d, dep+1);
    solve(sep[d], rng[d][0], rng[d][1], rng[d][2], rng[d][3], c, b, a, d, dep+1);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, S;
    cin >> N >> S;
    for(int i=0; i<N; i++) {
        cin >> pos[i].x >> pos[i].y >> name[i];
    }
    vector<int> v(N);
    iota(v.begin(), v.end(), 0);
    solve(v, 0, S, 0, S, 0, 2, 3, 1);
}
