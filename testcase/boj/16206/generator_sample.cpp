#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) a.push_back(10);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        int need = 0;
        for (int i = 0; i < n; ++i) {
            int pieces = rnd.next(2, 9);
            a.push_back(10 * pieces);
            need += pieces - 1;
        }
        m = rnd.next(1, min(1000, need));
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        for (int i = 0; i < n; ++i) {
            int pieces = rnd.next(1, 8);
            int rem = rnd.next(1, 9);
            a.push_back(10 * pieces + rem);
        }
        m = rnd.next(1, 40);
    } else if (mode == 3) {
        n = rnd.next(5, 25);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 3);
            if (choice == 0) a.push_back(rnd.next(1, 9));
            else if (choice == 1) a.push_back(10);
            else if (choice == 2) a.push_back(10 * rnd.next(2, 7));
            else a.push_back(10 * rnd.next(1, 7) + rnd.next(1, 9));
        }
        m = rnd.next(1, 60);
    } else if (mode == 4) {
        n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 1000));
        m = rnd.next(1, 1000);
    } else if (mode == 5) {
        n = rnd.next(1, 10);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(900, 1000));
        m = rnd.next(1, 1000);
    } else {
        n = rnd.next(900, 1000);
        for (int i = 0; i < n; ++i) {
            int choice = rnd.next(0, 4);
            if (choice == 0) a.push_back(rnd.next(1, 9));
            else if (choice == 1) a.push_back(10);
            else if (choice == 2) a.push_back(10 * rnd.next(2, 100));
            else if (choice == 3) a.push_back(10 * rnd.next(1, 99) + rnd.next(1, 9));
            else a.push_back(rnd.next(1, 1000));
        }
        m = rnd.next(1, 1000);
    }

    shuffle(a.begin(), a.end());

    println(n, m);
    println(a);

    return 0;
}
