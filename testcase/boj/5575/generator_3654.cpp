#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate 3 employees
    for (int i = 0; i < 3; i++) {
        // Start hour between 7 and 22 inclusive
        int hs = rnd.next(7, 22);
        int ms = rnd.next(0, 59);
        int ss = rnd.next(0, 59);

        // Maximum possible duration in seconds (must end before 23:00:00)
        int maxd = (23 - hs) * 3600 - ms * 60 - ss;
        // Ensure at least 1 second of work
        if (maxd < 1) maxd = 1;

        // Build duration categories: short (<1h), mid (1h–5h), long (>5h)
        vector<pair<int,int>> ranges;
        // short: 1 to min(3599, maxd)
        int endShort = min(3599, maxd);
        if (endShort >= 1) ranges.emplace_back(1, endShort);
        // mid: 3600 to min(5*3600, maxd)
        if (maxd >= 3600) {
            int endMid = min(5 * 3600, maxd);
            if (endMid >= 3600) ranges.emplace_back(3600, endMid);
        }
        // long: 5*3600+1 to maxd
        if (maxd > 5 * 3600) {
            ranges.emplace_back(5 * 3600 + 1, maxd);
        }

        // Pick a random category, then a random duration in that range
        auto cat = rnd.next(0, int(ranges.size()) - 1);
        int dur = rnd.next(ranges[cat].first, ranges[cat].second);

        // Compute end time
        int total = hs * 3600 + ms * 60 + ss + dur;
        int he = total / 3600;
        int rem = total % 3600;
        int me = rem / 60;
        int se = rem % 60;

        // Output one line: hs ms ss he me se
        println(hs, ms, ss, he, me, se);
    }

    return 0;
}
