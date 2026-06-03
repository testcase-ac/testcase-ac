#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    int y;
    vector<int> found;

    if (mode == 0) {
        n = rnd.next(1, 12);
        y = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        y = n;
        for (int i = 0; i < n; ++i) found.push_back(i);
        shuffle(found.begin(), found.end());
    } else if (mode == 2) {
        n = rnd.next(2, 35);
        y = rnd.next(n, 200);
        int common = rnd.next(0, n - 1);
        for (int i = 0; i < y; ++i) {
            if (rnd.next(0, 99) < 65)
                found.push_back(common);
            else
                found.push_back(rnd.next(0, n - 1));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 60);
        set<int> chosen;
        int distinct = rnd.next(1, n - 1);
        while ((int)chosen.size() < distinct) chosen.insert(rnd.next(0, n - 1));
        found.assign(chosen.begin(), chosen.end());
        shuffle(found.begin(), found.end());
        y = (int)found.size();
    } else {
        n = rnd.next(70, 100);
        y = rnd.next(100, 200);
        for (int i = 0; i < y; ++i) found.push_back(rnd.next(0, n - 1));
    }

    println(n, y);
    for (int k : found) println(k);

    return 0;
}
