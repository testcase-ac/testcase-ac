#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(mode == 0 ? 2 : 3, 12);
    vector<int> parent(n + 1);
    vector<long long> skill(n + 1);

    for (int i = 2; i <= n; ++i) {
        if (mode == 0) parent[i] = i - 1;
        else if (mode == 1) parent[i] = 1;
        else if (i <= 3) parent[i] = 1;
        else parent[i] = rnd.next(mode == 2 ? 1 : 2, i - 1);
    }

    for (int i = 1; i <= n; ++i) {
        if (mode == 0) skill[i] = rnd.next(-30, -1);
        else if (mode == 1) skill[i] = rnd.next(1, 30);
        else if (mode == 2) skill[i] = rnd.next(-30, 30);
        else skill[i] = i % 2 ? rnd.next(0, 1000000000) : rnd.next(-1000000000, 0);
    }

    println(n);
    for (int i = 1; i <= n; ++i) println(skill[i], i == 1 ? -1 : parent[i]);
}
