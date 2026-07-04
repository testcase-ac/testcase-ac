#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

static vector<int> makeRecord() {
    int rooms = rnd.next(2, 14);
    int backEdges = rnd.next(1, min(10, rooms - 1));

    vector<int> targets;
    targets.push_back(1);
    for (int i = 1; i < backEdges; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0) {
            targets.push_back(1);
        } else if (mode == 1) {
            targets.push_back(rnd.next(1, rooms - 1));
        } else {
            targets.push_back(max(1, rooms - rnd.next(2, min(rooms, 6))));
        }
    }
    shuffle(targets.begin(), targets.end());

    vector<int> degree(rooms + 1, 0);
    degree[1] = 1;
    for (int i = 2; i < rooms; ++i) {
        degree[i] = 2;
    }
    degree[rooms] = 1;

    for (int target : targets) {
        ++degree[target];
        ++degree[rooms];
    }

    vector<int> record;
    for (int i = 1; i <= rooms; ++i) {
        record.push_back(degree[i]);
    }
    for (int target : targets) {
        record.push_back(target - rooms);
    }
    return record;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 8);
    println(n);
    for (int tc = 0; tc < n; ++tc) {
        vector<int> record = makeRecord();
        int lineTokens = rnd.next(6, 14);
        for (int i = 0; i < (int)record.size(); ++i) {
            if (i > 0) {
                if (i % lineTokens == 0) {
                    printf("\n");
                } else {
                    printf(" ");
                }
            }
            printf("%d", record[i]);
        }
        printf(" 0\n");
    }

    return 0;
}
