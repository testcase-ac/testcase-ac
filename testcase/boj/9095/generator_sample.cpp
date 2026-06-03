#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        values.push_back(rnd.any(vector<int>{1, 2, 3, 8, 9, 10}));
    } else if (mode == 1) {
        int t = rnd.next(2, 12);
        for (int i = 0; i < t; ++i)
            values.push_back(rnd.next(1, 10));
    } else if (mode == 2) {
        int t = rnd.next(4, 20);
        int repeated = rnd.next(1, 10);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 2) == 0)
                values.push_back(repeated);
            else
                values.push_back(rnd.any(vector<int>{1, 2, 3, 8, 9, 10}));
        }
    } else {
        values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        shuffle(values.begin(), values.end());
        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i)
            values.push_back(rnd.next(1, 10));
        shuffle(values.begin(), values.end());
    }

    println(static_cast<int>(values.size()));
    for (int n : values)
        println(n);

    return 0;
}
