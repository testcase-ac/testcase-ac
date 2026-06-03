#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> starts;
    vector<int> ends;
    int pos = 1;
    for (int value = 1; pos <= 1000; ++value) {
        starts.push_back(pos);
        int end = min(1000, pos + value - 1);
        ends.push_back(end);
        pos = end + 1;
    }

    int mode = rnd.next(0, 5);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = rnd.next(1, 1000);
        b = a;
    } else if (mode == 1) {
        int idx = rnd.next((int)starts.size());
        int center = rnd.any(vector<int>{starts[idx], ends[idx]});
        a = max(1, center - rnd.next(0, 3));
        b = min(1000, center + rnd.next(0, 3));
    } else if (mode == 2) {
        a = rnd.next(1, 950);
        b = min(1000, a + rnd.next(1, 50));
    } else if (mode == 3) {
        a = rnd.next(1, 1000);
        b = rnd.next(a, 1000);
    } else if (mode == 4) {
        a = rnd.next(900, 1000);
        b = rnd.next(a, 1000);
    } else {
        int leftIdx = rnd.next((int)starts.size());
        int rightIdx = rnd.next(leftIdx, (int)starts.size() - 1);
        a = starts[leftIdx];
        b = ends[rightIdx];
    }

    println(a, b);
    return 0;
}
