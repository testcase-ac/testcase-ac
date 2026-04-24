#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of calls
    int N = rnd.next(1, 10);
    // Hyper-parameters for diversity
    double boundaryProb = rnd.next(0.0, 1.0);
    double shortProb    = rnd.next(0.0, 1.0);
    double midProb      = rnd.next(0.0, 1.0);
    
    vector<pair<int,int>> calls; // (start_minute, duration)

    for (int i = 0; i < N; i++) {
        // Decide call type: 0 = random, 1 = cross 07:00, 2 = cross 19:00, 3 = cross midnight
        int type = 0;
        if (rnd.next() < boundaryProb) {
            type = rnd.next(1, 3);
        }

        // Duration selection: short, mid, or long
        double r = rnd.next();
        int dur;
        if (r < shortProb) {
            dur = rnd.next(1, 10);
        } else if (r < shortProb + (1 - shortProb) * midProb) {
            dur = rnd.next(11, 30);
        } else {
            dur = rnd.next(31, 60);
        }

        // Determine start time in minutes [0..1439]
        int start_min;
        if (type == 1) {
            // Cross 07:00 boundary (420)
            int B = 7 * 60;
            int lo = max(0, B - dur + 1), hi = B - 1;
            if (lo <= hi) start_min = rnd.next(lo, hi);
            else           start_min = rnd.next(0, 1439);
        } else if (type == 2) {
            // Cross 19:00 boundary (1140)
            int B = 19 * 60;
            int lo = max(0, B - dur + 1), hi = B - 1;
            if (lo <= hi) start_min = rnd.next(lo, hi);
            else           start_min = rnd.next(0, 1439);
        } else if (type == 3) {
            // Cross midnight (1440)
            int B = 24 * 60;
            int lo = max(0, B - dur + 1), hi = 1439;
            if (lo <= hi) start_min = rnd.next(lo, hi);
            else           start_min = rnd.next(0, 1439);
        } else {
            // Totally random
            start_min = rnd.next(0, 1439);
        }

        calls.emplace_back(start_min, dur);
    }

    // Shuffle to mix different types
    shuffle(calls.begin(), calls.end());

    // Output
    println(N);
    for (auto &c : calls) {
        int hh = c.first / 60;
        int mm = c.first % 60;
        int dur = c.second;
        // HH:MM and duration DD both two digits
        printf("%02d:%02d %02d\n", hh, mm, dur);
    }
    return 0;
}
