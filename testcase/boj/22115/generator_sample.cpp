#include "testlib.h"
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<int> caffeine(n);
    int k = 0;

    if (mode == 0) {
        k = 0;
        for (int& x : caffeine) x = rnd.next(1, 1000);
    } else if (mode == 1) {
        int answer = rnd.next(1, 1000);
        k = answer;
        caffeine[0] = answer;
        for (int i = 1; i < n; ++i) caffeine[i] = rnd.next(1, 1000);
    } else if (mode == 2) {
        n = rnd.next(2, 18);
        caffeine.assign(n, 0);
        for (int& x : caffeine) x = rnd.next(1, 80);
        int take = rnd.next(2, n);
        shuffle(caffeine.begin(), caffeine.end());
        k = accumulate(caffeine.begin(), caffeine.begin() + take, 0);
    } else if (mode == 3) {
        n = rnd.next(8, 30);
        caffeine.assign(n, 0);
        int unit = rnd.next(1, 40);
        for (int& x : caffeine) x = unit * rnd.next(1, 5);
        k = unit * rnd.next(1, min(20, n * 5));
        if (rnd.next(0, 1)) ++k;
    } else if (mode == 4) {
        n = rnd.next(1, 25);
        caffeine.assign(n, 0);
        for (int& x : caffeine) x = rnd.next(1, 60);
        k = accumulate(caffeine.begin(), caffeine.end(), 0) + rnd.next(1, 100);
    } else {
        n = rnd.next(70, 100);
        caffeine.assign(n, 0);
        for (int& x : caffeine) x = rnd.next(1, 1000);
        k = rnd.next(1, 100000);
    }

    shuffle(caffeine.begin(), caffeine.end());
    println(n, k);
    println(caffeine);
    return 0;
}
