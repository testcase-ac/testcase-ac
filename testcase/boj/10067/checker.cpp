#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;

int n, k;
vector<long long> prefix_sum;

// Convert non-negative __int128 to string
string toString(i128 x) {
    if (x == 0) return "0";
    string s;
    while (x > 0) {
        int d = int(x % 10);
        s.push_back(char('0' + d));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

// Read and validate an answer (jury or participant), compute its score.
i128 readAns(InStream &stream) {
    // Skip the reported score (first token in output)
    stream.readToken(); 

    // Read k split positions
    vector<int> splits;
    splits.reserve(k);
    for (int i = 0; i < k; i++) {
        int x = stream.readInt(1, n-1, format("split[%d]", i+1).c_str());
        splits.push_back(x);
    }
    // Check for duplicate splits
    {
        vector<bool> used(n, false);
        for (int x : splits) {
            if (used[x]) {
                stream.quitf(_wa, "split position %d is used more than once", x);
            }
            used[x] = true;
        }
    }
    // We maintain current segments as [l, r], global indices
    vector<pair<int,int>> segs;
    segs.emplace_back(1, n);
    i128 total = 0;
    // Process splits in order
    for (int idx = 0; idx < k; idx++) {
        int x = splits[idx];
        // Find the segment that contains x
        int si = -1;
        for (int i = 0; i < (int)segs.size(); i++) {
            int l = segs[i].first;
            int r = segs[i].second;
            if (l <= x && x < r) {
                si = i;
                break;
            }
        }
        if (si == -1) {
            stream.quitf(_wa, "split at %d does not lie within any current segment", x);
        }
        int l = segs[si].first;
        int r = segs[si].second;
        // Compute sums
        long long sumL = prefix_sum[x] - prefix_sum[l-1];
        long long sumR = prefix_sum[r] - prefix_sum[x];
        // Both parts must be non-empty: guaranteed by l <= x < r
        // Accumulate score
        total += i128(sumL) * i128(sumR);
        // Replace the segment with the two new ones
        segs[si] = make_pair(l, x);
        segs.emplace_back(x+1, r);
    }
    return total;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input
    n = inf.readInt();
    k = inf.readInt();
    vector<int> a(n+1);
    prefix_sum.assign(n+1, 0);
    for (int i = 1; i <= n; i++) {
        a[i] = inf.readInt();
        prefix_sum[i] = prefix_sum[i-1] + a[i];
    }

    // Read and check jury answer
    i128 juryScore = readAns(ans);
    // Read and check participant answer
    i128 partScore = readAns(ouf);

    // Compare
    if (partScore < juryScore) {
        quitf(_wa, "jury has better answer: jans = %s, pans = %s",
              toString(juryScore).c_str(), toString(partScore).c_str());
    } else if (partScore == juryScore) {
        quitf(_ok, "score = %s", toString(partScore).c_str());
    } else {
        quitf(_fail, "participant has better answer than jury: jans = %s, pans = %s",
              toString(juryScore).c_str(), toString(partScore).c_str());
    }
    return 0;
}
