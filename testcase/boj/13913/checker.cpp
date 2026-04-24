#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

const int COORD_MIN = 0;
const int COORD_MAX = 200000;          // generous upper-bound after teleports

int N, K;                              // start and target positions

// Reads one answer (jury or participant), checks it and returns the reported time.
int readAns(InStream& stream)
{
    // 1. time
    int reportedTime = stream.readInt(0, COORD_MAX, "time");

    // 2. path: must contain exactly reportedTime + 1 integers
    vector<int> path;
    path.reserve(reportedTime + 1);
    for (int i = 0; i <= reportedTime; ++i)
        path.push_back(stream.readInt(COORD_MIN, COORD_MAX, 
                       (string("path[") + to_string(i) + "]").c_str()));

    // there must be nothing beyond the declared path
    stream.seekEof();
    
    // 3. reported time must equal (path length − 1)
    if (reportedTime != (int)path.size() - 1)
        stream.quitf(_wa,
                     "reported time = %d but path length = %zu (they must differ by exactly 1)",
                     reportedTime, path.size());


    // 4. basic path checks
    if (path.front() != N)
        stream.quitf(_wa, "path must start at N (%d), found %d", N, path.front());
    if (path.back()  != K)
        stream.quitf(_wa, "path must finish at K (%d), found %d", K, path.back());

    // 5. step-by-step validity
    for (size_t i = 1; i < path.size(); ++i)
    {
        long long prev = path[i - 1];
        long long cur  = path[i];

        bool ok = (cur == prev + 1) ||
                  (cur == prev - 1) ||
                  (cur == prev * 2);

        if (!ok)
            stream.quitf(_wa,
                         "invalid transition: %lld → %lld (only −1, +1 or ×2 allowed)",
                         prev, cur);
    }

    return reportedTime;               // smaller is better
}

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);

    // read test data
    N = inf.readInt(COORD_MIN, 100000, "N");
    K = inf.readInt(COORD_MIN, 100000, "K");

    // read and check jury & participant answers
    int juryTime        = readAns(ans);
    int participantTime = readAns(ouf);

    if (juryTime < participantTime)
        quitf(_wa, "jury found a faster or equal path: jury = %d, participant = %d",
              juryTime, participantTime);
    else if (juryTime == participantTime)
        quitf(_ok, "correct minimal time = %d", participantTime);
    else
        quitf(_fail,
              "participant’s path (%d) is faster than jury’s (%d) — check the jury output",
              participantTime, juryTime);
}
