#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int N_MAX = 40;
    vector<int> a;

    int type = rnd.next(0, 7);

    if (type == 0) {
        // Very small random
        int N = rnd.next(1, 5);
        a.resize(N);
        for (int i = 0; i < N; ++i) a[i] = rnd.next(1, 2);
    } else if (type == 1) {
        // All 1s
        int N = rnd.next(1, 15);
        a.assign(N, 1);
    } else if (type == 2) {
        // All 2s
        int N = rnd.next(1, 15);
        a.assign(N, 2);
    } else if (type == 3) {
        // Blocky pattern of 1s and 2s
        int Ntarget = rnd.next(5, N_MAX);
        a.clear();
        while ((int)a.size() < Ntarget) {
            int rem = Ntarget - (int)a.size();
            int len = rnd.next(1, min(5, rem));
            int val = rnd.next(1, 2);
            for (int i = 0; i < len; ++i) a.push_back(val);
        }
    } else if (type == 4) {
        // Alternating 1,2 or 2,1
        int N = rnd.next(5, N_MAX);
        a.resize(N);
        int start = rnd.next(0, 1); // 0 => start with 1, 1 => start with 2
        for (int i = 0; i < N; ++i) {
            if (start == 0)
                a[i] = (i % 2 == 0 ? 1 : 2);
            else
                a[i] = (i % 2 == 0 ? 2 : 1);
        }
    } else if (type == 5) {
        // Guaranteed "Yes": concatenation of segments summing to 3 (12, 21, 111)
        a.clear();
        int numGroups = rnd.next(1, 10);
        int groups = 0;
        while (groups < numGroups) {
            int curN = (int)a.size();
            // Minimum length for one more group is 2
            if (curN >= N_MAX - 2) break;
            int pat = rnd.next(0, 2); // 0: 1 2, 1: 2 1, 2: 1 1 1
            vector<int> seg;
            if (pat == 0) seg = {1, 2};
            else if (pat == 1) seg = {2, 1};
            else seg = {1, 1, 1};
            if ((int)seg.size() + curN > N_MAX) break;
            a.insert(a.end(), seg.begin(), seg.end());
            ++groups;
        }
        if (a.empty()) {
            // Fallback: single group
            a = {1, 2};
        }
    } else if (type == 6) {
        // Guaranteed "No": total sum not divisible by 3
        int N = rnd.next(5, N_MAX);
        a.resize(N);
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            a[i] = rnd.next(1, 2);
            sum += a[i];
        }
        if (sum % 3 == 0) {
            int pos = rnd.next(0, N - 1);
            a[pos] = 3 - a[pos]; // flip 1<->2, changes sum by +/-1
        }
    } else if (type == 7) {
        // Start from a guaranteed "Yes" pattern and insert some extra lemons
        vector<int> base;
        // Build base as in type 5
        int numGroups = rnd.next(2, 8);
        int groups = 0;
        while (groups < numGroups) {
            int curN = (int)base.size();
            if (curN >= N_MAX - 2) break;
            int pat = rnd.next(0, 2);
            vector<int> seg;
            if (pat == 0) seg = {1, 2};
            else if (pat == 1) seg = {2, 1};
            else seg = {1, 1, 1};
            if ((int)seg.size() + curN > N_MAX) break;
            base.insert(base.end(), seg.begin(), seg.end());
            ++groups;
        }
        if (base.empty()) base = {1, 2};
        a = base;
        int remaining = N_MAX - (int)a.size();
        if (remaining > 0) {
            int K = rnd.next(1, min(5, remaining));
            for (int t = 0; t < K; ++t) {
                int pos = rnd.next(0, (int)a.size());
                int val = rnd.next(1, 2);
                a.insert(a.begin() + pos, val);
            }
        }
    }

    int N = (int)a.size();
    println(N);
    println(a);

    return 0;
}
