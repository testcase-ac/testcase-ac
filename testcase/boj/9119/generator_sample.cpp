#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

void applyTransposition(vector<int>& books) {
    int n = static_cast<int>(books.size());
    if (n < 2) {
        return;
    }

    int i = rnd.next(0, n - 2);
    int j = rnd.next(i, n - 2);
    int k = rnd.next(j + 1, n - 1);

    vector<int> next;
    next.reserve(n);
    next.insert(next.end(), books.begin(), books.begin() + i);
    next.insert(next.end(), books.begin() + j + 1, books.begin() + k + 1);
    next.insert(next.end(), books.begin() + i, books.begin() + j + 1);
    next.insert(next.end(), books.begin() + k + 1, books.end());
    books.swap(next);
}

vector<int> makePermutation(int n) {
    vector<int> books(n);
    iota(books.begin(), books.end(), 1);
    if (n == 1) {
        return books;
    }

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        return books;
    }
    if (mode == 1) {
        reverse(books.begin(), books.end());
        return books;
    }
    if (mode == 2) {
        rotate(books.begin(), books.begin() + rnd.next(1, n - 1), books.end());
        return books;
    }
    if (mode == 3) {
        for (int i = 0; i < rnd.next(1, 4); ++i) {
            applyTransposition(books);
        }
        return books;
    }
    if (mode == 4) {
        for (int i = 0; i < rnd.next(1, n); ++i) {
            swap(books[rnd.next(0, n - 1)], books[rnd.next(0, n - 1)]);
        }
        return books;
    }
    if (mode == 5) {
        int block = rnd.next(1, max(1, n / 3));
        for (int start = 0; start < n; start += block) {
            int finish = min(n, start + block);
            reverse(books.begin() + start, books.begin() + finish);
        }
        return books;
    }

    shuffle(books.begin(), books.end());
    return books;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int sizeMode = rnd.next(0, 4);
        int n;
        if (sizeMode == 0) {
            n = 1;
        } else if (sizeMode == 1) {
            n = rnd.next(2, 5);
        } else if (sizeMode == 2) {
            n = rnd.next(6, 10);
        } else {
            n = rnd.next(11, 15);
        }

        println(n);
        println(makePermutation(n));
    }

    return 0;
}
