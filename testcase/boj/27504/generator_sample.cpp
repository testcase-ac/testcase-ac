#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeNotesFromDiffs(int start, const vector<int>& diffs) {
    vector<int> notes(1, start);
    for (int diff : diffs) notes.push_back(notes.back() + diff);
    return notes;
}

bool fitsFromStart(int start, const vector<int>& diffs) {
    int cur = start;
    if (cur < 1 || cur > 10000) return false;
    for (int diff : diffs) {
        cur += diff;
        if (cur < 1 || cur > 10000) return false;
    }
    return true;
}

vector<int> randomDiffs(int len, int span) {
    vector<int> diffs;
    for (int i = 0; i + 1 < len; ++i) {
        int diff = rnd.next(-span, span);
        if (rnd.next(4) == 0) diff = 0;
        diffs.push_back(diff);
    }
    return diffs;
}

vector<int> boundedNotesFromDiffs(const vector<int>& diffs) {
    int low = 0;
    int high = 0;
    int cur = 0;
    for (int diff : diffs) {
        cur += diff;
        low = min(low, cur);
        high = max(high, cur);
    }

    int minStart = 1 - low;
    int maxStart = 10000 - high;
    int start = rnd.next(minStart, maxStart);
    return makeNotesFromDiffs(start, diffs);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 8);
    int l = rnd.next(2, 8);
    int span = rnd.next(0, 9);

    vector<int> melodyDiffs;
    if (mode == 0) {
        for (int i = 0; i + 1 < l; ++i) melodyDiffs.push_back(0);
    } else if (mode == 1) {
        int step = rnd.next(1, 5);
        for (int i = 0; i + 1 < l; ++i) melodyDiffs.push_back(i % 2 == 0 ? step : -step);
    } else {
        melodyDiffs = randomDiffs(l, span);
    }

    vector<vector<int>> songs;
    int guaranteedMatches = mode == 5 ? 0 : rnd.next(1, n);
    for (int i = 0; i < n; ++i) {
        int k = rnd.next(2, 14);
        vector<int> diffs;

        bool makeMatch = i < guaranteedMatches && k >= l;
        if (makeMatch) {
            int prefixLen = rnd.next(0, k - l);
            int suffixLen = k - l - prefixLen;
            for (int j = 0; j < prefixLen; ++j) diffs.push_back(rnd.next(-span, span));
            diffs.insert(diffs.end(), melodyDiffs.begin(), melodyDiffs.end());
            for (int j = 0; j < suffixLen; ++j) diffs.push_back(rnd.next(-span, span));
        } else {
            diffs = randomDiffs(k, span);
            if (k == l && diffs == melodyDiffs) {
                if (diffs.empty()) diffs.push_back(1);
                else diffs[rnd.next((int)diffs.size())] += diffs.back() == 9 ? -1 : 1;
            }
        }

        songs.push_back(boundedNotesFromDiffs(diffs));
    }

    shuffle(songs.begin(), songs.end());
    vector<int> melody = boundedNotesFromDiffs(melodyDiffs);

    println(n);
    for (const vector<int>& song : songs) {
        printf("%d", (int)song.size());
        for (int note : song) printf(" %d", note);
        printf("\n");
    }
    println(l);
    println(melody);

    return 0;
}
