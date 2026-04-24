#include <bits/stdc++.h>
using namespace std;
const int MX = 5000;
int arr[MX], acc[MX];
int N;
bool solve_arr() {
    vector<int> stk;
    for(int i=0; i<N; i++) {
        acc[i] = 0;
    }
    for(int i=2; i<N; i++) {
        acc[arr[i]] = 1;
    }
    for(int i=1; i<N; i++) {
        acc[i] += acc[i-1];
    }
    for(int a=2; a<N-1; a++) {
        for(int i=arr[a]; i<N; i++) {
            acc[i]--;
        }
        stk.clear();
        for(int i=0; i<a; i++) {
            while(stk.size() && stk.back() < arr[i]) {
                stk.pop_back();
            }
            stk.push_back(arr[i]);
        }

        int stidx = 0;
        for(int b=0; b<a-1; b++) {
            if(arr[b] == stk[stidx]) {
                stidx++;
            }
            if(stidx == stk.size()) {
                return false;
            }
            if(stk[stidx] < arr[b]) {
                continue;
            }
            if(arr[b] < arr[a]) {
                continue;
            }
            if(acc[arr[b]] != acc[stk[stidx]]) {
                return true;
            }
        }
    }
    return false;
}
bool solve() {
    cin >> N;
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    vector<int> tmp(arr, arr+N);
    sort(tmp.begin(), tmp.end());
    for(int i = 0; i < N; i++) {
        arr[i] = lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin();
    }
    if(solve_arr())
        return true;
    reverse(arr, arr+N);
    return solve_arr();
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        cout << (solve() ? "Yes\n" : "No\n");
    }
}
