#include "testlib.h"
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

// Global data: the nine hat numbers and mapping to their indices
vector<int> hats;
map<int, int> hatIndex;

// readAns reads seven integers from the given stream, checks validity, and returns
// the sorted list of the seven chosen numbers. On error, it reports _wa for contestant
// stream and _fail for jury stream.
vector<int> readAns(InStream& stream) {
    vector<bool> used(9, false);
    vector<int> chosen;
    int sum = 0;
    for (int i = 0; i < 7; i++) {
        // Read the i-th dwarf number
        int x = stream.readInt(1, 99, format("dwarf[%d]", i + 1).c_str());
        // Check it's one of the original nine
        auto it = hatIndex.find(x);
        if (it == hatIndex.end()) {
            stream.quitf(_wa, "number %d is not among the nine input numbers", x);
        }
        int idx = it->second;
        // Check it's not used twice
        if (used[idx]) {
            stream.quitf(_wa, "number %d is used more than once", x);
        }
        used[idx] = true;
        chosen.push_back(x);
        sum += x;
    }
    // Check sum is exactly 100
    if (sum != 100) {
        stream.quitf(_wa, "sum of chosen numbers is %d, but expected 100", sum);
    }
    sort(chosen.begin(), chosen.end());
    return chosen;
}

// Helper to join vector<int> into a string
string vec2str(const vector<int>& v) {
    string s;
    for (size_t i = 0; i < v.size(); i++) {
        if (i) s += ' ';
        s += to_string(v[i]);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read the nine input hat numbers
    hats.resize(9);
    for (int i = 0; i < 9; i++) {
        hats[i] = inf.readInt(1, 99);
        if (hatIndex.count(hats[i])) {
            // input guarantees distinct, but we guard anyway
            quitf(_fail, "input contains duplicate number %d", hats[i]);
        }
        hatIndex[hats[i]] = i;
    }

    // Read the jury's answer and the participant's answer
    vector<int> juryAns = readAns(ans);
    vector<int> partAns = readAns(ouf);

    // Check no extra tokens in participant output
    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens after reading 7 numbers");
    }

    // Compare the two sorted lists
    if (juryAns != partAns) {
        quitf(_wa,
              "answer differs\nexpected: %s\nfound:    %s",
              vec2str(juryAns).c_str(),
              vec2str(partAns).c_str());
    }

    // All good
    quitf(_ok, "correct");
    return 0;
}
