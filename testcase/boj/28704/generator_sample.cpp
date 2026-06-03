#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int smallValue() {
    int mode = rnd.next(0, 9);
    if (mode < 5) return rnd.next(1, 4);
    if (mode < 8) return rnd.next(1, 10);
    return rnd.next(1, 300000);
}

void appendOnes(vector<int>& a, int count) {
    for (int i = 0; i < count; ++i) a.push_back(1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 80);
        a.assign(n, 1);
    } else if (mode == 1) {
        int groups = rnd.next(2, 14);
        appendOnes(a, rnd.next(0, 8));
        for (int i = 0; i < groups; ++i) {
            a.push_back(rnd.next(2, 6));
            appendOnes(a, rnd.next(0, 12));
        }
    } else if (mode == 2) {
        int n = rnd.next(2, 60);
        for (int i = 0; i < n; ++i) a.push_back(smallValue());
    } else if (mode == 3) {
        int n = rnd.next(2, 40);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(300000);
            } else if (rnd.next(0, 2) == 0) {
                a.push_back(rnd.next(299990, 300000));
            } else {
                a.push_back(rnd.next(1, 3));
            }
        }
    } else if (mode == 4) {
        int blocks = rnd.next(1, 10);
        for (int i = 0; i < blocks; ++i) {
            int type = rnd.next(0, 3);
            if (type == 0) {
                vector<int> block = {2, 2};
                appendOnes(a, rnd.next(0, 4));
                a.insert(a.end(), block.begin(), block.end());
            } else if (type == 1) {
                vector<int> block = {1, 2, 3};
                if (rnd.next(0, 1)) reverse(block.begin(), block.end());
                a.insert(a.end(), block.begin(), block.end());
            } else {
                appendOnes(a, rnd.next(1, 8));
                a.push_back(rnd.next(2, 5));
            }
            appendOnes(a, rnd.next(0, 5));
        }
    } else {
        int n = rnd.next(1, 120);
        int lo = rnd.next(1, 5);
        int hi = rnd.next(lo, min(300000, lo + rnd.next(0, 30)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
    }

    println((int)a.size());
    println(a);
    return 0;
}
