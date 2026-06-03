#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> small = {1, 2, 3, 4, 5, 6, 8, 10, 12, 16, 18, 20, 21, 24, 28};
    const vector<int> primes = {2, 3, 5, 7, 11, 97, 997, 999983};
    const vector<int> perfect = {6, 28, 496, 8128};
    const vector<int> abundant = {12, 18, 20, 24, 36, 60, 120, 360, 720, 831600, 982800};
    const vector<int> nearLimit = {999950, 999960, 999970, 999980, 999990, 1000000};

    int mode = rnd.next(0, 5);
    int t = rnd.next(3, 30);
    vector<int> values;
    values.reserve(t);

    for (int i = 0; i < t; ++i) {
        if (mode == 0) {
            values.push_back(rnd.any(small));
        } else if (mode == 1) {
            values.push_back(rnd.any(primes));
        } else if (mode == 2) {
            values.push_back(rnd.any(perfect));
        } else if (mode == 3) {
            values.push_back(rnd.any(abundant));
        } else if (mode == 4) {
            values.push_back(rnd.any(nearLimit));
        } else {
            int choice = rnd.next(0, 5);
            if (choice == 0) {
                values.push_back(rnd.any(small));
            } else if (choice == 1) {
                values.push_back(rnd.any(perfect));
            } else if (choice == 2) {
                values.push_back(rnd.any(abundant));
            } else if (choice == 3) {
                values.push_back(rnd.next(1, 1000));
            } else if (choice == 4) {
                values.push_back(rnd.next(1, 1000000));
            } else {
                int base = rnd.next(2, 1000);
                values.push_back(base * rnd.next(1, 1000000 / base));
            }
        }
    }

    if (mode == 5) {
        shuffle(values.begin(), values.end());
    }

    println(t);
    println(values);

    return 0;
}
