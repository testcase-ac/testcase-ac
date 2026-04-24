#include "testlib.h"
#include <string>
#include <vector>
#include <set>
using namespace std;

static vector<string> split_str(const string &s, char delim) {
    vector<string> res;
    string cur;
    for (char c : s) {
        if (c == delim) {
            res.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    res.push_back(cur);
    return res;
}

static bool is_lower_alpha(const string &s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (c < 'a' || c > 'z') return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases T: 1 .. 100000
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // 1) Recorded sound line
        //    Read entire line, then validate no leading/trailing spaces and no double spaces
        string rec = inf.readLine("[^]+", "recorded_sound");
        // cannot be empty
        ensuref(!rec.empty(),
                "Testcase %d: recorded sound line is empty", tc);
        // no leading or trailing space
        ensuref(rec.front() != ' ' && rec.back() != ' ',
                "Testcase %d: recorded sound line has leading or trailing space: '%s'",
                tc, rec.c_str());
        // no double spaces
        ensuref(rec.find("  ") == string::npos,
                "Testcase %d: recorded sound line has consecutive spaces: '%s'",
                tc, rec.c_str());

        // split into words
        vector<string> recWords = split_str(rec, ' ');
        int R = recWords.size();
        ensuref(R >= 1 && R <= 100,
                "Testcase %d: number of recorded words out of bounds: got %d, expected 1..100",
                tc, R);
        for (int i = 0; i < R; i++) {
            const string &w = recWords[i];
            ensuref((int)w.size() >= 1 && (int)w.size() <= 100,
                    "Testcase %d: recorded word %d length out of range: %d",
                    tc, i, (int)w.size());
            ensuref(is_lower_alpha(w),
                    "Testcase %d: recorded word %d contains non-lowercase letters: '%s'",
                    tc, i, w.c_str());
        }

        // 2) Animal sound lines, ending with "what does the fox say?"
        vector<string> animalLines;
        while (true) {
            string line = inf.readLine("[^]+", "line");
            if (line == "what does the fox say?") {
                break;
            }
            animalLines.push_back(line);
        }
        int A = animalLines.size();
        ensuref(A >= 1 && A <= 100,
                "Testcase %d: number of animal lines out of bounds: got %d, expected 1..100",
                tc, A);

        set<string> known_sounds;
        for (int i = 0; i < A; i++) {
            const string &ln = animalLines[i];
            // split by single space
            // line must not be empty and must not have leading/trailing spaces or double spaces
            ensuref(!ln.empty(),
                    "Testcase %d: animal line %d is empty", tc, i);
            ensuref(ln.front() != ' ' && ln.back() != ' ',
                    "Testcase %d: animal line %d has leading/trailing space: '%s'",
                    tc, i, ln.c_str());
            ensuref(ln.find("  ") == string::npos,
                    "Testcase %d: animal line %d has consecutive spaces: '%s'",
                    tc, i, ln.c_str());
            vector<string> tok = split_str(ln, ' ');
            ensuref((int)tok.size() == 3,
                    "Testcase %d: animal line %d does not have exactly 3 tokens: '%s'",
                    tc, i, ln.c_str());
            // tok[1] must be "goes"
            ensuref(tok[1] == "goes",
                    "Testcase %d: animal line %d token 2 is not 'goes': '%s'",
                    tc, i, tok[1].c_str());
            // tok[0] and tok[2] must be lowercase words length 1..100
            for (int j = 0; j <= 2; j += 2) {
                const string &s = tok[j];
                ensuref((int)s.size() >= 1 && (int)s.size() <= 100,
                        "Testcase %d: animal line %d token %d length out of range: %d",
                        tc, i, j, (int)s.size());
                ensuref(is_lower_alpha(s),
                        "Testcase %d: animal line %d token %d contains non-lowercase letters: '%s'",
                        tc, i, j, s.c_str());
            }
            known_sounds.insert(tok[2]);
        }

        // 3) Ensure at least one recorded word is not a known sound (fox sound exists)
        bool has_unknown = false;
        for (const string &w : recWords) {
            if (!known_sounds.count(w)) {
                has_unknown = true;
                break;
            }
        }
        ensuref(has_unknown,
                "Testcase %d: no fox sound found among recorded words", tc);
    }

    inf.readEof();
    return 0;
}
