#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players
    int N = inf.readInt(3, 500000, "N");
    inf.readEoln();

    // Read skill values
    vector<long long> skills;
    skills.reserve(N);
    for (int i = 0; i < N; i++) {
        long long s = inf.readLong(1LL, 1000000000LL, "skill");
        inf.readEoln();
        skills.push_back(s);
    }

    // Check all skills are distinct
    vector<long long> tmp = skills;
    sort(tmp.begin(), tmp.end());
    for (int i = 1; i < N; i++) {
        ensuref(tmp[i] != tmp[i-1],
                "Duplicate skill value detected: %lld", tmp[i]);
    }

    // No extra data
    inf.readEof();
    return 0;
}
