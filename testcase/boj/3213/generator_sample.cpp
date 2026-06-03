#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int c1 = 0;
    int c2 = 0;
    int c3 = 0;

    if (mode == 0) {
        c1 = rnd.next(0, 12);
        c2 = rnd.next(0, 12);
        c3 = rnd.next(0, 12);
    } else if (mode == 1) {
        c3 = rnd.next(1, 12);
        c1 = c3 + rnd.next(0, 8);
        c2 = rnd.next(0, 6);
    } else if (mode == 2) {
        c1 = rnd.next(1, 24);
        c2 = rnd.next(0, 3) * 2 + 1;
        c3 = rnd.next(0, 4);
    } else if (mode == 3) {
        c1 = rnd.next(0, 5);
        c2 = rnd.next(0, 6);
        c3 = rnd.next(1, 24);
    } else if (mode == 4) {
        int groups = rnd.next(1, 8);
        c1 = 4 * groups + rnd.next(0, 3);
        c2 = 2 * rnd.next(0, 6);
        c3 = rnd.next(0, 3);
    } else if (mode == 5) {
        int n = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 2);
            if (pick == 0) ++c1;
            if (pick == 1) ++c2;
            if (pick == 2) ++c3;
        }
    } else {
        int n = rnd.next(100, 10000);
        int bias = rnd.next(0, 2);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(0, 99);
            if (bias == 0) {
                if (pick < 55) ++c1;
                else if (pick < 80) ++c2;
                else ++c3;
            } else if (bias == 1) {
                if (pick < 25) ++c1;
                else if (pick < 70) ++c2;
                else ++c3;
            } else {
                if (pick < 20) ++c1;
                else if (pick < 45) ++c2;
                else ++c3;
            }
        }
    }

    vector<string> slices;
    slices.reserve(c1 + c2 + c3);
    for (int i = 0; i < c1; ++i) slices.push_back("1/4");
    for (int i = 0; i < c2; ++i) slices.push_back("1/2");
    for (int i = 0; i < c3; ++i) slices.push_back("3/4");
    if (slices.empty()) slices.push_back(rnd.any(vector<string>{"1/4", "1/2", "3/4"}));

    shuffle(slices.begin(), slices.end());

    println(static_cast<int>(slices.size()));
    for (const string& slice : slices) println(slice);

    return 0;
}
