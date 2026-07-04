#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long l;
    int n;
    vector<pair<long long, long long>> intervals;

    if (mode == 0) {
        l = rnd.next(1LL, 20LL);
        n = rnd.next(1, 8);
        intervals.assign(n, {0, l});
    } else {
        int parts = rnd.next(2, 8);
        l = rnd.next((long long)parts, 60LL);

        vector<long long> cuts = {0, l};
        while ((int)cuts.size() < parts + 1) {
            cuts.push_back(rnd.next(1LL, l - 1));
            sort(cuts.begin(), cuts.end());
            cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
        }
        sort(cuts.begin(), cuts.end());

        for (int i = 0; i + 1 < (int)cuts.size(); ++i) {
            intervals.push_back({cuts[i], cuts[i + 1]});
        }

        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i) {
            int kind = (mode + rnd.next(0, 3)) % 4;
            long long left;
            long long right;

            if (kind == 0) {
                int a = rnd.next(0, (int)cuts.size() - 2);
                int b = rnd.next(a + 1, (int)cuts.size() - 1);
                left = cuts[a];
                right = cuts[b];
            } else if (kind == 1) {
                int a = rnd.next(0, (int)cuts.size() - 2);
                left = cuts[a];
                right = rnd.next(left + 1, cuts[a + 1]);
            } else if (kind == 2) {
                right = rnd.next(1LL, l);
                left = rnd.next(0LL, right - 1);
            } else {
                auto base = rnd.any(intervals);
                left = base.first;
                right = base.second;
            }

            intervals.push_back({left, right});
        }

        if (mode == 5) {
            intervals.push_back({0, l});
        }

        shuffle(intervals.begin(), intervals.end());
        n = (int)intervals.size();
    }

    println(n, l);
    for (auto interval : intervals) {
        println(interval.first, interval.second);
    }

    return 0;
}
