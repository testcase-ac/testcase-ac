#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Employee {
    int manager;
    int rank;
    int time;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int e = (mode == 0 ? 1 : rnd.next(2, 18));

    vector<int> parent(e, -1);
    for (int i = 1; i < e; ++i) {
        if (mode == 1) {
            parent[i] = i - 1;
        } else if (mode == 2) {
            parent[i] = 0;
        } else if (mode == 3) {
            parent[i] = (i - 1) / 2;
        } else {
            parent[i] = rnd.next(0, i - 1);
        }
    }

    vector<int> rank(e);
    int rankMode = rnd.next(0, 4);
    int base = rnd.next(1, 20);
    for (int i = 0; i < e; ++i) {
        if (rankMode == 0) {
            rank[i] = i + 1;
        } else if (rankMode == 1) {
            rank[i] = e - i;
        } else if (rankMode == 2) {
            rank[i] = rnd.next(1, 6);
        } else if (rankMode == 3) {
            rank[i] = (i % 2 == 0 ? 1 : 100000);
        } else {
            rank[i] = min(100000, base + rnd.next(0, 40));
        }
    }

    vector<int> label(e);
    iota(label.begin(), label.end(), 1);
    shuffle(label.begin(), label.end());

    vector<Employee> employees(e + 1);
    for (int oldId = 0; oldId < e; ++oldId) {
        int newId = label[oldId];
        int manager = parent[oldId] == -1 ? -1 : label[parent[oldId]];
        int reviewTime = rnd.next(0, 5) == 0 ? rnd.next(90000, 100000) : rnd.next(1, 200);
        employees[newId] = {manager, rank[oldId], reviewTime};
    }

    println(e);
    for (int id = 1; id <= e; ++id) {
        println(employees[id].manager, employees[id].rank, employees[id].time);
    }

    return 0;
}
