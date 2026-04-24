#include <bits/stdc++.h>

using namespace std;
#define int long long
#define rep(i, N) for(int i=0; i<N; i++)
struct region {
    string s;
    int ru, rt, pu, pt, f, tickets;
    double score;
    void read() {
        cin >> s >> pt >> pu >> rt >> ru >> f;
        tickets = 0;
        score = 0.56 * ru + 0.24 * rt + 0.14 * pu + 0.06 * pt + 0.3 * f;
    }

};
int32_t main() {
    int N;
    cin >> N;
    vector<region> arr(6);
    rep(i, 6) {
        arr[i].read();
    }
    sort(arr.begin(), arr.end(), [](region a, region b) {
        return a.score > b.score;
    });
    int ptr = 0;
    while(N) {
        arr[ptr].tickets++;
        ptr++;
        if(ptr == 6) {
            ptr = 0;
        }
        N--;
    }
    rep(i, 6) {
        if(arr[i].s == "Taiwan") {
            cout << arr[i].tickets << '\n';
            return 0;
        }
    }
}
