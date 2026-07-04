#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> books;

    if (mode == 0) {
        n = rnd.next(1, 12);
        int value = rnd.next(1, 1000);
        books.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int cur = rnd.next(1, 1000 - n + 1);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 2);
            books.push_back(min(cur, 1000));
        }
        sort(books.begin(), books.end());
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        int cur = rnd.next(1, 1000 - n + 1);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 3);
            books.push_back(min(cur, 1000));
        }
        sort(books.rbegin(), books.rend());
    } else if (mode == 3) {
        n = rnd.next(4, 25);
        int lo = rnd.next(1, 900);
        int hi = rnd.next(lo, min(1000, lo + rnd.next(0, 80)));
        for (int i = 0; i < n; ++i) {
            books.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 30);
        for (int i = 0; i < n; ++i) {
            books.push_back(rnd.any(vector<int>{1, 2, 999, 1000, rnd.next(1, 1000)}));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 40);
        int start = rnd.next(1, 1000 - n + 1);
        for (int i = 0; i < n; ++i) {
            books.push_back(start + i);
        }
        int swaps = rnd.next(1, min(8, n - 1));
        for (int i = 0; i < swaps; ++i) {
            int left = rnd.next(0, n - 2);
            int right = rnd.next(left + 1, n - 1);
            swap(books[left], books[right]);
        }
    } else {
        n = rnd.next(1, 100);
        int lo = rnd.next(1, 1000);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) {
            books.push_back(rnd.next(lo, hi));
        }
    }

    println(n);
    println(books);

    return 0;
}
