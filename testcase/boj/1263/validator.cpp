#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    vector<int> T(N), S(N);

    for (int i = 0; i < N; ++i) {
        T[i] = inf.readInt(1, 1000, "T_i");
        inf.readSpace();
        S[i] = inf.readInt(1, 1000000, "S_i");
        inf.readEoln();
    }

    // Check if there exists at least one valid schedule (i.e., starting at 0 is possible)
    // Simulate the greedy algorithm: sort by S_i descending, schedule backwards
    vector<pair<int, int>> jobs(N);
    for (int i = 0; i < N; ++i) {
        jobs[i] = make_pair(S[i], T[i]);
    }
    // Sort by deadline descending
    sort(jobs.begin(), jobs.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        return a.first > b.first;
    });

    long long cur = jobs[0].first;
    for (int i = 0; i < N; ++i) {
        cur = min(cur, 1LL * jobs[i].first);
        cur -= jobs[i].second;
        // After each job, cur is the latest possible start time for the previous jobs
    }
    // After all jobs, cur is the latest possible start time
    // But we need to check if starting at 0 is possible
    if (cur < 0) {
        ensuref(false, "It is impossible to finish all jobs even if starting at 0.");
    }

    inf.readEof();
}
