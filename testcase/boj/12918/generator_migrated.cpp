#include "testlib.h"

#include <utility>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // TLE 데이터 (large)
    int N = rnd.next(10, 50);
    int R = 100;

    set<pair<int, int>> s;
    while (s.size() < N) {
        int x = rnd.next(-R, R);
        if (x == 0) { continue; }
        s.insert(make_pair(x, rnd.next(-R, R)));
    }

    vector<pair<int, int>> vec(s.begin(), s.end());
    shuffle(vec.begin(), vec.end());

    println(N);
    for (auto& [x, y] : vec) {
        printf("%d %d\n", x, y);
    }

    return 0;
}
