#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

static string indexedLabel(const string& prefix, int index, bool spaced) {
    if (spaced) {
        return prefix + " " + to_string(index);
    }
    return prefix + to_string(index);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(2, 12);
    bool useSpacedLabels = rnd.next(0, 1);

    vector<pair<string, string>> candidates;
    candidates.reserve(n);

    for (int i = 0; i < n; ++i) {
        string candidate = indexedLabel("Candidate", i + 1, useSpacedLabels);
        string party;
        if (i == 0 || rnd.next(0, 3) == 0) {
            party = "independent";
        } else {
            party = indexedLabel("Party", i + 1, useSpacedLabels);
        }
        candidates.push_back({candidate, party});
    }

    vector<int> votes(n, 0);
    if (mode == 0) {
        int winner = rnd.next(0, n - 1);
        if (candidates[winner].second == "independent" && n > 1) {
            winner = 1;
            candidates[winner].second = indexedLabel("Party", winner + 1, useSpacedLabels);
        }
        int winVotes = rnd.next(2, 8);
        votes[winner] = winVotes;
        for (int i = 0; i < n; ++i) {
            if (i != winner) {
                votes[i] = rnd.next(0, winVotes - 1);
            }
        }
    } else if (mode == 1) {
        int winner = rnd.next(0, n - 1);
        candidates[winner].second = "independent";
        int winVotes = rnd.next(2, 8);
        votes[winner] = winVotes;
        for (int i = 0; i < n; ++i) {
            if (i != winner) {
                votes[i] = rnd.next(0, winVotes - 1);
            }
        }
    } else if (mode == 2) {
        int first = rnd.next(0, n - 1);
        int second = rnd.next(0, n - 2);
        if (second >= first) {
            ++second;
        }
        int tiedVotes = rnd.next(1, 6);
        votes[first] = tiedVotes;
        votes[second] = tiedVotes;
        for (int i = 0; i < n; ++i) {
            if (i != first && i != second) {
                votes[i] = rnd.next(0, tiedVotes);
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            votes[i] = rnd.next(0, 3);
        }
    }

    vector<string> ballots;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < votes[i]; ++j) {
            ballots.push_back(candidates[i].first);
        }
    }

    int unknownCount = rnd.next(1, 8);
    for (int i = 0; i < unknownCount; ++i) {
        ballots.push_back(indexedLabel("Unknown", i + 1, useSpacedLabels));
    }
    shuffle(ballots.begin(), ballots.end());

    println(n);
    for (const auto& [candidate, party] : candidates) {
        println(candidate);
        println(party);
    }

    println(int(ballots.size()));
    for (const string& ballot : ballots) {
        println(ballot);
    }

    return 0;
}
