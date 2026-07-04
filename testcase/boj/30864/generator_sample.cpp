#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        candidates = {1, 2};
    } else if (mode == 1) {
        for (int n = 1; n <= 12; ++n) candidates.push_back(n);
    } else if (mode == 2) {
        for (int n = 10; n <= 80; n += 10) candidates.push_back(n);
        for (int n = 15; n <= 75; n += 15) candidates.push_back(n);
    } else if (mode == 3) {
        for (int n = 1; n <= 400; n *= 2) {
            candidates.push_back(n);
            if (n + 1 <= 400) candidates.push_back(n + 1);
            if (n > 1) candidates.push_back(n - 1);
        }
    } else if (mode == 4) {
        int center = rnd.next(180, 260);
        int width = rnd.next(5, 40);
        for (int n = max(1, center - width); n <= min(400, center + width); ++n) {
            candidates.push_back(n);
        }
    } else {
        for (int n = 360; n <= 400; ++n) candidates.push_back(n);
    }

    println(rnd.any(candidates));
    return 0;
}
