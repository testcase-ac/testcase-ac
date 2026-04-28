#include <iostream>
#include <algorithm>
using namespace std;

int n;
pair<int, int> arr[1000000];
int ans[1000000];

const int TSIZE = 1000002;
int fwt[TSIZE];

void fwadd(int p, int val) {
    ++p;
    for (; p < TSIZE; p += p & -p) {
        fwt[p] += val;
    }
}

int fwquery(int p) {
    ++p;
    int ret = 0;
    for (; p > 0; p -= p & -p) {
        ret += fwt[p];
    }
    return ret;
}

void proc() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr, arr + n);
    for (int i = 0; i < n; ++i) {
        ans[arr[i].second] = fwquery(arr[i].second);
        fwadd(arr[i].second, 1);
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    proc();
    return 0;
}
