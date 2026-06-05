#include "testlib.h"

#include <set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_M = 100000;
    const int MAX_K = 10000;
    const long long MAX_KEY_VALUE = 1000000000LL;

    int n = inf.readInt(1, MAX_N, "n");
    inf.readSpace();
    int m = inf.readInt(1, MAX_M, "m");
    inf.readSpace();
    inf.readInt(1, MAX_K, "k");
    inf.readEoln();

    set<long long> keys;
    for (int i = 0; i < n; ++i) {
        long long key = inf.readLong(0LL, MAX_KEY_VALUE, "initial_key");
        inf.readSpace();
        inf.readLong(0LL, MAX_KEY_VALUE, "initial_value");
        inf.readEoln();

        ensuref(keys.insert(key).second, "duplicate initial key at index %d: %lld", i + 1, key);
    }

    for (int i = 0; i < m; ++i) {
        int command = inf.readInt(1, 3, "command");
        inf.readSpace();
        long long key = inf.readLong(0LL, MAX_KEY_VALUE, "command_key");

        if (command == 3) {
            inf.readEoln();
            continue;
        }

        inf.readSpace();
        inf.readLong(0LL, MAX_KEY_VALUE, "command_value");
        inf.readEoln();

        if (command == 1) {
            ensuref(keys.insert(key).second, "inserted key already exists at command %d: %lld", i + 1, key);
        }
    }

    inf.readEof();
}
