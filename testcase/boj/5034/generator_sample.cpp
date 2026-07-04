#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    vector<int> durations;

    if (mode == 0) {
        int k = rnd.next(1, 4);
        int d = rnd.next(1, 7);
        durations.assign(k, d);
    } else if (mode == 1) {
        int k = rnd.next(8, 20);
        int d = rnd.next(1, 7);
        durations.assign(k, d);
    } else if (mode == 2) {
        int k = rnd.next(2, 20);
        int lowCount = rnd.next(1, k - 1);
        durations.assign(lowCount, 1);
        durations.insert(durations.end(), k - lowCount, 7);
    } else if (mode == 3) {
        int k = rnd.next(5, 20);
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, min(7, lo + 2));
        for (int i = 0; i < k; ++i) durations.push_back(rnd.next(lo, hi));
    } else if (mode == 4) {
        int k = rnd.next(7, 20);
        for (int d = 1; d <= 7; ++d) durations.push_back(d);
        while ((int)durations.size() < k) durations.push_back(rnd.next(1, 7));
    } else if (mode == 5) {
        int k = rnd.next(10, 20);
        vector<int> choices = {2, 3, 4, 5, 6};
        for (int i = 0; i < k; ++i) durations.push_back(rnd.any(choices));
    } else {
        int k = rnd.next(1, 20);
        for (int i = 0; i < k; ++i) durations.push_back(rnd.next(1, 7));
    }

    shuffle(durations.begin(), durations.end());

    println((int)durations.size());
    for (int d : durations) println(d);

    return 0;
}
