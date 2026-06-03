#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> perfect = {6, 28, 496, 8128};
    vector<int> deficient = {1, 2, 3, 4, 5, 7, 8, 13, 17, 31, 97, 9973};
    vector<int> abundant = {12, 18, 20, 24, 36, 48, 60, 120, 360, 5040, 7560, 9990};
    vector<int> boundary = {1, 2, 9998, 9999};

    int t = rnd.next(1, 80);
    vector<int> values;
    values.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 7);
        if (mode == 0) {
            values.push_back(rnd.any(perfect));
        } else if (mode == 1) {
            values.push_back(rnd.any(deficient));
        } else if (mode == 2) {
            values.push_back(rnd.any(abundant));
        } else if (mode == 3) {
            values.push_back(rnd.any(boundary));
        } else if (mode == 4) {
            values.push_back(rnd.next(1, 50));
        } else if (mode == 5) {
            values.push_back(rnd.next(9900, 9999));
        } else {
            int base = rnd.next(1, 1111);
            values.push_back(base * rnd.next(1, 9));
        }
    }

    shuffle(values.begin(), values.end());

    println(t);
    println(values);

    return 0;
}
