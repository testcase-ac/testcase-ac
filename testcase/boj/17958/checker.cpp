#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

struct Claim {
    bool possible;
    string restored;
};

int n;
int totalLen;
vector<int> inputFreq(26);

vector<int> buildSuffixArray(const string& s) {
    int len = (int)s.size();
    vector<int> sa(len), rank(len), nextRank(len);
    iota(sa.begin(), sa.end(), 0);
    for (int i = 0; i < len; ++i) {
        rank[i] = s[i];
    }

    for (int k = 1;; k <<= 1) {
        sort(sa.begin(), sa.end(), [&](int a, int b) {
            if (rank[a] != rank[b]) {
                return rank[a] < rank[b];
            }
            int ra = a + k < len ? rank[a + k] : -1;
            int rb = b + k < len ? rank[b + k] : -1;
            return ra < rb;
        });

        nextRank[sa[0]] = 0;
        for (int i = 1; i < len; ++i) {
            int prev = sa[i - 1];
            int cur = sa[i];
            bool different = rank[prev] != rank[cur];
            if (!different) {
                int rPrev = prev + k < len ? rank[prev + k] : -1;
                int rCur = cur + k < len ? rank[cur + k] : -1;
                different = rPrev != rCur;
            }
            nextRank[cur] = nextRank[prev] + (different ? 1 : 0);
        }
        rank.swap(nextRank);
        if (rank[sa.back()] == len - 1) {
            break;
        }
    }
    return sa;
}

vector<int> buildLcp(const string& s, const vector<int>& sa) {
    int len = (int)s.size();
    vector<int> rank(len), lcp(max(0, len - 1));
    for (int i = 0; i < len; ++i) {
        rank[sa[i]] = i;
    }

    int matched = 0;
    for (int i = 0; i < len; ++i) {
        int pos = rank[i];
        if (pos == len - 1) {
            matched = 0;
            continue;
        }
        int j = sa[pos + 1];
        while (i + matched < len && j + matched < len &&
               s[i + matched] == s[j + matched]) {
            ++matched;
        }
        lcp[pos] = matched;
        if (matched > 0) {
            --matched;
        }
    }
    return lcp;
}

bool hasDistinctCyclicSubstrings(const string& restored) {
    string doubled = restored + restored;
    vector<int> sa = buildSuffixArray(doubled);
    vector<int> lcp = buildLcp(doubled, sa);

    int previousCycleStart = -1;
    int intervalMinLcp = totalLen;
    for (int i = 0; i < (int)sa.size(); ++i) {
        if (previousCycleStart != -1) {
            intervalMinLcp = min(intervalMinLcp, lcp[i - 1]);
        }
        if (sa[i] >= totalLen) {
            continue;
        }
        if (previousCycleStart != -1 && intervalMinLcp >= n) {
            return false;
        }
        previousCycleStart = sa[i];
        intervalMinLcp = totalLen;
    }
    return true;
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("[A-Z]+", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false, ""};
    }
    if (verdict != "YES") {
        stream.quitf(_wa, "verdict must be YES or NO, found %s", verdict.c_str());
    }

    string restored = stream.readToken("[a-z]+", "restored string");
    if ((int)restored.size() != totalLen) {
        stream.quitf(_wa, "restored string length is %d, expected %d",
                     (int)restored.size(), totalLen);
    }
    vector<int> freq(26);
    for (char ch : restored) {
        ++freq[ch - 'a'];
    }
    if (freq != inputFreq) {
        stream.quitf(_wa, "restored string is not a permutation of the input string");
    }
    if (!hasDistinctCyclicSubstrings(restored)) {
        stream.quitf(_wa, "restored string has repeated cyclic substrings of length %d", n);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after restored string");
    }
    return {true, restored};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    string input = inf.readToken("[a-z]+", "input string");
    totalLen = (int)input.size();
    n = totalLen / 2;
    for (char ch : input) {
        ++inputFreq[ch - 'a'];
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (!jury.possible) {
        if (participant.possible) {
            quitf(_fail, "participant found a valid restoration while jury says NO");
        }
        quitf(_ok, "both outputs say NO");
    }
    if (!participant.possible) {
        quitf(_wa, "jury provides a valid restoration but participant says NO");
    }
    quitf(_ok, "valid restoration");
}
