#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Point;

int count_in_range(const vector<Point>& v, int left, int right, int n) {
    int l = lower_bound(v.begin(), v.end(), Point(left, 0)) - v.begin();
    int r = upper_bound(v.begin(), v.end(), Point(right, n + 1)) - v.begin();

    return r - l;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, k1, k2;
    cin >> n >> k1 >> k2;

    vector<int> x(n + 1);
    vector<int> group(n + 1);
    vector<vector<Point> > pos(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> group[i];

        pos[0].push_back(Point(x[i], i));
        pos[group[i]].push_back(Point(x[i], i));
    }

    for (int i = 0; i <= n; i++) {
        sort(pos[i].begin(), pos[i].end());
    }

    vector<int> ans(n + 1);

    for (int i = 1; i <= n; i++) {
        int g = group[i];

        int same_k1 = count_in_range(pos[g], x[i] - k1, x[i] + k1, n);
        int same_k2 = count_in_range(pos[g], x[i] - k2, x[i] + k2, n);
        int all_k2 = count_in_range(pos[0], x[i] - k2, x[i] + k2, n);

        ans[i] = same_k1 + all_k2 - same_k2 - 1;
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';

    return 0;
}
