#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int parseTime(const string &s, const char *what, int lineIdx) {
    // s should be exactly "hh:mm:ss"
    ensuref((int)s.size() == 8,
            "%s on line %d must have length 8, got \"%s\"",
            what, lineIdx, s.c_str());
    ensuref(s[2] == ':' && s[5] == ':',
            "%s on line %d must be in hh:mm:ss format, got \"%s\"",
            what, lineIdx, s.c_str());
    auto isDigit = [](char c){ return '0' <= c && c <= '9'; };
    for (int i : {0,1,3,4,6,7}) {
        ensuref(isDigit(s[i]),
                "%s on line %d has non-digit character at position %d: \"%s\"",
                what, lineIdx, i, s.c_str());
    }
    int hh = (s[0]-'0')*10 + (s[1]-'0');
    int mm = (s[3]-'0')*10 + (s[4]-'0');
    int ss = (s[6]-'0')*10 + (s[7]-'0');

    ensuref(0 <= hh && hh < 24,
            "hour in %s on line %d out of range [0,23], got %d",
            what, lineIdx, hh);
    ensuref(0 <= mm && mm < 60,
            "minute in %s on line %d out of range [0,59], got %d",
            what, lineIdx, mm);
    ensuref(0 <= ss && ss < 60,
            "second in %s on line %d out of range [0,59], got %d",
            what, lineIdx, ss);

    return hh * 3600 + mm * 60 + ss;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // We will also check the implied global constraint:
    // For each train, departure time < arrival time (no crossing midnight).
    // Additionally, we will compute the minimal number of trains needed
    // and (lightly) ensure it's within a reasonable bound.
    int datasetId = 0;

    while (true) {
        ++datasetId;
        int n = inf.readInt(0, 10000, "n");
        inf.readEoln();

        if (n == 0) break;

        vector<pair<int,int>> intervals;
        intervals.reserve(n);

        for (int i = 0; i < n; ++i) {
            // We read each hh:mm:ss as a token with simple "match-all" regex,
            // then validate manually.
            string depTok = inf.readToken("[^]+", "departure");
            inf.readSpace();
            string arrTok = inf.readToken("[^]+", "arrival");
            inf.readEoln();

            int lineIdx = i + 2; // within this dataset (1-based, 1st line is n)
            int dep = parseTime(depTok, "departure time", lineIdx);
            int arr = parseTime(arrTok, "arrival time", lineIdx);

            ensuref(dep < arr,
                    "In dataset %d, line %d: departure time (%s) must be strictly earlier than arrival time (%s)",
                    datasetId, lineIdx, depTok.c_str(), arrTok.c_str());

            intervals.emplace_back(dep, arr);
        }

        // Global consistency check related to the intended answer:
        // The minimal number of vehicles equals the maximum number of
        // overlapping intervals at any time. We can compute it and
        // optionally assert it stays within a sane bound (though with
        // n <= 10000 this is always <= 10000).
        vector<pair<int,int>> events;
        events.reserve(2 * n);
        for (auto &iv : intervals) {
            int s = iv.first;
            int e = iv.second;
            // departure at time s starts usage, arrival at time e ends usage,
            // and an arriving train can depart immediately at the same time.
            // That means we should process end events before start events
            // at equal times. We'll encode type: 0 = end, 1 = start.
            events.push_back({s, 1});
            events.push_back({e, 0});
        }
        sort(events.begin(), events.end(),
             [](const pair<int,int> &a, const pair<int,int> &b) {
                 if (a.first != b.first) return a.first < b.first;
                 return a.second < b.second; // end(0) before start(1)
             });
        int cur = 0, maxNeed = 0;
        for (auto &ev : events) {
            if (ev.second == 0) {
                // end
                cur--;
                ensuref(cur >= 0,
                        "Internal error in dataset %d: negative active count",
                        datasetId);
            } else {
                // start
                cur++;
                if (cur > maxNeed) maxNeed = cur;
            }
        }
        ensuref(cur == 0,
                "Internal error in dataset %d: active count not zero after sweep", datasetId);
        ensuref(1 <= maxNeed || n == 0,
                "Internal error in dataset %d: computed vehicles %d inconsistent with n=%d",
                datasetId, maxNeed, n);
        ensuref(maxNeed <= n,
                "Internal error in dataset %d: computed vehicles %d exceeds number of trains %d",
                datasetId, maxNeed, n);
    }

    inf.readEof();
}
