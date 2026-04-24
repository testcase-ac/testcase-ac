#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of scoring events
    int N = rnd.next(1, 10);

    // Total game seconds = 48 minutes
    int totalSeconds = 48 * 60;

    // Hyper-parameters for diversity
    int timeBias = rnd.next(-2, 2);   // bias for event times
    int teamBias = rnd.next(-2, 2);   // bias for team selection

    // Generate N unique event times
    set<int> times;
    while ((int)times.size() < N) {
        int t = rnd.wnext(totalSeconds, timeBias);
        // rnd.wnext returns in [0, totalSeconds), so t is valid
        times.insert(t);
    }

    // Sort times and assign teams
    vector<int> vt(times.begin(), times.end());
    sort(vt.begin(), vt.end());
    vector<pair<int,int>> events;
    for (int t : vt) {
        int team = rnd.wnext(2, teamBias) + 1; // yields 1 or 2
        events.emplace_back(team, t);
    }

    // Output
    println(N);
    for (auto &e : events) {
        int team = e.first;
        int t = e.second;
        int mm = t / 60;
        int ss = t % 60;
        char buf[6];
        sprintf(buf, "%02d:%02d", mm, ss);
        println(team, buf);
    }

    return 0;
}
