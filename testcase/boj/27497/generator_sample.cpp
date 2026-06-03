#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

char randomLetter() {
    const string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return rnd.any(letters);
}

void addInsert(vector<string>& ops, int type) {
    ops.push_back(to_string(type) + " " + string(1, randomLetter()));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 80);
    vector<string> ops;
    ops.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next() < 0.35) {
                ops.push_back("3");
            } else {
                addInsert(ops, rnd.next(1, 2));
            }
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 2) {
                ops.push_back("3");
            } else {
                addInsert(ops, (i % 2) + 1);
            }
        }
    } else if (mode == 2) {
        while ((int)ops.size() < n) {
            int inserts = rnd.next(1, min(8, n - (int)ops.size()));
            for (int i = 0; i < inserts; ++i) {
                addInsert(ops, rnd.next(1, 2));
            }
            int remaining = n - (int)ops.size();
            int deletes = rnd.next(0, min(remaining, inserts + 3));
            for (int i = 0; i < deletes; ++i) {
                ops.push_back("3");
            }
        }
    } else if (mode == 3) {
        int deletePrefix = rnd.next(1, min(20, n));
        for (int i = 0; i < deletePrefix; ++i) {
            ops.push_back("3");
        }
        while ((int)ops.size() < n) {
            addInsert(ops, rnd.next(1, 2));
            if ((int)ops.size() < n && rnd.next() < 0.45) {
                ops.push_back("3");
            }
        }
    } else {
        while ((int)ops.size() < n) {
            int block = rnd.next(1, min(6, n - (int)ops.size()));
            int type = rnd.next(1, 2);
            for (int i = 0; i < block; ++i) {
                addInsert(ops, type);
            }
            if ((int)ops.size() < n) {
                ops.push_back("3");
            }
        }
    }

    println((int)ops.size());
    for (const string& op : ops) {
        println(op);
    }

    return 0;
}
