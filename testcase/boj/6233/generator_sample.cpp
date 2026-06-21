#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 40);
    vector<char> cows(n, 'F');

    if (mode == 0) {
        n = rnd.next(1, 4);
        cows.assign(n, rnd.next(0, 1) ? 'B' : 'F');
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        cows.resize(n);
        char cur = rnd.next(0, 1) ? 'B' : 'F';
        for (int i = 0; i < n; ++i) {
            cows[i] = cur;
            cur = (cur == 'F' ? 'B' : 'F');
        }
    } else if (mode == 2) {
        n = rnd.next(3, 40);
        cows.assign(n, 'F');
        int flips = rnd.next(1, min(n, 8));
        for (int i = 0; i < flips; ++i) cows[rnd.next(0, n - 1)] = 'B';
    } else if (mode == 3) {
        n = rnd.next(3, 40);
        cows.assign(n, 'B');
        int forwards = rnd.next(1, min(n, 8));
        for (int i = 0; i < forwards; ++i) cows[rnd.next(0, n - 1)] = 'F';
    } else if (mode == 4) {
        n = rnd.next(5, 45);
        cows.clear();
        char cur = rnd.next(0, 1) ? 'B' : 'F';
        while ((int)cows.size() < n) {
            int len = rnd.next(1, 7);
            for (int i = 0; i < len && (int)cows.size() < n; ++i) cows.push_back(cur);
            cur = (cur == 'F' ? 'B' : 'F');
        }
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        cows.resize(n);
        int backwardPercent = rnd.next(15, 85);
        for (int i = 0; i < n; ++i) cows[i] = rnd.next(1, 100) <= backwardPercent ? 'B' : 'F';
    } else {
        n = rnd.next(100, 220);
        cows.resize(n);
        int backwardPercent = rnd.next(35, 65);
        for (int i = 0; i < n; ++i) cows[i] = rnd.next(1, 100) <= backwardPercent ? 'B' : 'F';
    }

    println(n);
    for (char cow : cows) println(string(1, cow));

    return 0;
}
