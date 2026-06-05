#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;
    vector<int> lengths;

    if (mode == 0) {
        x = rnd.next(1, 30);
        int n = rnd.next(1, min(x, 8));
        for (int i = 1; i <= x; ++i) lengths.push_back(i);
        shuffle(lengths.begin(), lengths.end());
        lengths.resize(n);
    } else if (mode == 1) {
        x = rnd.next(20, 120);
        int n = rnd.next(5, min(x, 20));
        for (int i = 1; i <= x; ++i) lengths.push_back(i);
        shuffle(lengths.begin(), lengths.end());
        lengths.resize(n);
    } else if (mode == 2) {
        x = rnd.next(2, 100);
        int n = rnd.next(1, min(x / 2 + x % 2, 12));
        for (int i = 1; i <= x; i += 2) lengths.push_back(i);
        shuffle(lengths.begin(), lengths.end());
        lengths.resize(n);
    } else if (mode == 3) {
        x = rnd.next(10, 200);
        int n = rnd.next(2, min(x, 18));
        for (int i = max(1, x - 2 * n); i <= x; ++i) lengths.push_back(i);
        shuffle(lengths.begin(), lengths.end());
        lengths.resize(n);
    } else if (mode == 4) {
        x = rnd.next(50, 300);
        int n = rnd.next(15, min(x, 60));
        for (int i = 1; i <= x; ++i) lengths.push_back(i);
        shuffle(lengths.begin(), lengths.end());
        lengths.resize(n);
    } else {
        x = rnd.next(9000, 10000);
        int n = rnd.next(20, 100);
        for (int i = 0; i < n; ++i) lengths.push_back(x - n + 1 + i);
    }

    sort(lengths.begin(), lengths.end());

    println((int)lengths.size(), x);
    for (int length : lengths) {
        int count;
        if (mode == 0) {
            count = rnd.next(1, 5);
        } else if (mode == 1) {
            count = rnd.next(1, 12);
        } else if (mode == 2) {
            count = rnd.next(1, 20);
        } else if (mode == 3) {
            count = rnd.next(1, 3);
        } else if (mode == 4) {
            count = rnd.next(1, 100);
        } else {
            count = rnd.next(1, 2);
        }
        println(length, count);
    }

    return 0;
}
