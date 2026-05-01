#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With small probability generate extreme cases
    if (rnd.next() < 0.15) {
        if (rnd.next() < 0.5)
            println(3);
        else
            println(200000);
        return 0;
    }

    // Ensure both parities appear
    bool want_even = rnd.next() < 0.5;
    bool small = rnd.next() < 0.8;

    int low = small ? 3 : 21;
    int high = small ? 20 : 50;
    vector<int> cand;
    for (int x = low; x <= high; ++x) {
        if (x >= 3 && x <= 200000 && ((x % 2 == 0) == want_even))
            cand.push_back(x);
    }

    if (cand.empty()) {
        // fallback to a valid even
        println(4);
    } else {
        println(rnd.any(cand));
    }

    return 0;
}
