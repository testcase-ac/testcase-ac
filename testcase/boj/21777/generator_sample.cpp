#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = rnd.next(1, 35);
    vector<int> ids;
    ids.reserve(t);

    if (mode == 0) {
        int id = rnd.next(1, 1000000);
        ids.assign(t, id);
    } else if (mode == 1) {
        int start = rnd.next(1, 1000000 - t + 1);
        for (int i = 0; i < t; ++i) ids.push_back(start + i);
    } else if (mode == 2) {
        int start = rnd.next(t, 1000000);
        for (int i = 0; i < t; ++i) ids.push_back(start - i);
    } else if (mode == 3) {
        int distinct = rnd.next(2, min(8, t + 1));
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int id = rnd.next(1, 1000000);
            if (find(pool.begin(), pool.end(), id) == pool.end()) pool.push_back(id);
        }
        sort(pool.begin(), pool.end());
        for (int i = 0; i < t; ++i) ids.push_back(pool[i % distinct]);
    } else if (mode == 4) {
        vector<int> pool = {1, 2, 999999, 1000000};
        for (int i = 0; i < t; ++i) ids.push_back(pool[i % (int)pool.size()]);
    } else {
        int distinct = rnd.next(1, min(10, t));
        vector<int> pool;
        while ((int)pool.size() < distinct) {
            int id = rnd.next(1, 1000000);
            if (find(pool.begin(), pool.end(), id) == pool.end()) pool.push_back(id);
        }
        sort(pool.begin(), pool.end());
        for (int i = 0; i < t; ++i) ids.push_back(pool[i % distinct]);
    }

    println(t);
    println(ids);

    return 0;
}
