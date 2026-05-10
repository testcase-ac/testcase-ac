#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // To check for global constraints, store all arrival and duration pairs
    vector<pair<int, int>> cows;

    for (int i = 0; i < N; ++i) {
        int arrival = inf.readInt(1, 1000000, "arrival_time");
        inf.readSpace();
        int duration = inf.readInt(1, 1000000, "duration");
        inf.readEoln();
        cows.emplace_back(arrival, duration);
    }

    inf.readEof();
}
