// Neutral reference for BOJ 28085. It keeps one smallest and one
// second-smallest boat as shuttles, then optimally pairs the remaining boats
// when doing so is cheaper than moving them one by one.
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> boats(n);
    for (int &boat : boats) cin >> boat;
    sort(boats.begin(), boats.end());

    if (n == 1) {
        cout << boats[0] << '\n';
        return 0;
    }
    if (boats.front() == boats.back()) {
        cout << -1 << '\n';
        return 0;
    }

    int smallest = boats[0];
    int secondSmallest = 0;
    for (int boat : boats) {
        if (boat > smallest) {
            secondSmallest = boat;
            break;
        }
    }

    map<int, int> countBySize;
    for (int boat : boats) ++countBySize[boat];

    ll answer = 0;
    answer += 2LL * (countBySize[smallest] - 1) * secondSmallest;
    countBySize[smallest] = 1;

    --countBySize[secondSmallest];
    if (countBySize[secondSmallest] == 0) {
        countBySize.erase(secondSmallest);
    }

    vector<int> remaining;
    for (auto [size, count] : countBySize) {
        if (size == smallest) continue;
        for (int i = 0; i < count; ++i) {
            remaining.push_back(size);
            answer += smallest + size;
        }
    }
    answer += secondSmallest;

    map<int, int, greater<int>> groups;
    for (int boat : remaining) ++groups[boat];

    const ll NEG = numeric_limits<ll>::min() / 4;
    vector<ll> dp(n + 1, NEG), nextDp(n + 1, NEG);
    dp[0] = 0;

    for (auto [size, count] : groups) {
        fill(nextDp.begin(), nextDp.end(), NEG);
        ll savedByPair = max(0, size + smallest - 2 * secondSmallest);

        for (int availableLarger = 0; availableLarger <= n; ++availableLarger) {
            if (dp[availableLarger] == NEG) continue;

            int maxPairs = min(count, availableLarger);
            for (int pairs = 0; pairs <= maxPairs; ++pairs) {
                int nextAvailable = availableLarger + count - 2 * pairs;
                ll saved = dp[availableLarger] + savedByPair * pairs;
                nextDp[nextAvailable] = max(nextDp[nextAvailable], saved);
            }
        }
        dp.swap(nextDp);
    }

    ll bestSaved = 0;
    for (ll saved : dp) bestSaved = max(bestSaved, saved);

    cout << answer - bestSaved << '\n';
    return 0;
}
