#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool tryMatch(int video, const vector<vector<int>>& available,
              vector<int>& matchedVideo, vector<int>& seen) {
    for (int time : available[video]) {
        if (seen[time]) {
            continue;
        }
        seen[time] = 1;
        if (matchedVideo[time] == -1 ||
            tryMatch(matchedVideo[time], available, matchedVideo, seen)) {
            matchedVideo[time] = video;
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    vector<vector<int>> available(n);
    for (int i = 0; i < n; ++i) {
        int t = inf.readInt(1, 30, "t_i");
        available[i].reserve(t);
        for (int j = 0; j < t; ++j) {
            inf.readSpace();
            int start = inf.readInt(1, 1000, "start_time");
            if (j > 0) {
                ensuref(available[i].back() < start,
                        "times for video %d are not strictly increasing at position %d",
                        i + 1, j + 1);
            }
            available[i].push_back(start);
        }
        inf.readEoln();
    }
    inf.readEof();

    vector<int> matchedVideo(1001, -1);
    int matched = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> seen(1001, 0);
        if (tryMatch(i, available, matchedVideo, seen)) {
            ++matched;
        }
    }
    ensuref(matched == n,
            "there is no arrangement that allows watching all videos");
}
