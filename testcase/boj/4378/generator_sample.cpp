#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string randomLine(const string& alphabet, int len, int spaceWeight) {
    string line;
    line.reserve(len);
    for (int i = 0; i < len; ++i) {
        if (rnd.next(100) < spaceWeight) {
            line.push_back(' ');
        } else {
            line.push_back(rnd.any(alphabet));
        }
    }
    return line;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string digits = "1234567890-=";
    const string top = "WERTYUIOP[]\\";
    const string middle = "SDFGHJKL;'";
    const string bottom = "XCVBNM,./";
    const string all = digits + top + middle + bottom;

    int mode = rnd.next(0, 4);
    vector<string> lines;

    if (mode == 0) {
        int lineCount = rnd.next(1, 6);
        int maxLen = rnd.next(1, 24);
        int spaceWeight = rnd.next(0, 35);
        for (int i = 0; i < lineCount; ++i) {
            lines.push_back(randomLine(all, rnd.next(0, maxLen), spaceWeight));
        }
    } else if (mode == 1) {
        vector<string> rows = {digits, top, middle, bottom};
        shuffle(rows.begin(), rows.end());
        int lineCount = rnd.next(1, 4);
        for (int i = 0; i < lineCount; ++i) {
            string row = rows[i];
            if (rnd.next(2) == 0) {
                shuffle(row.begin(), row.end());
            }
            lines.push_back(row);
        }
    } else if (mode == 2) {
        int lineCount = rnd.next(2, 8);
        for (int i = 0; i < lineCount; ++i) {
            if (rnd.next(100) < 35) {
                lines.push_back(string(rnd.next(0, 12), ' '));
            } else {
                lines.push_back(randomLine(all, rnd.next(1, 18), rnd.next(45, 80)));
            }
        }
    } else if (mode == 3) {
        string clusteredAlphabet = rnd.any(vector<string>{digits, top, middle, bottom});
        int lineCount = rnd.next(1, 5);
        for (int i = 0; i < lineCount; ++i) {
            lines.push_back(randomLine(clusteredAlphabet, rnd.next(1, 28), rnd.next(0, 20)));
        }
    } else {
        vector<string> alphabets = {digits, top, middle, bottom, all};
        int len = rnd.next(1, 40);
        string line;
        line.reserve(len);
        for (int i = 0; i < len; ++i) {
            const string& alphabet = rnd.any(alphabets);
            line.push_back(rnd.any(alphabet));
            if (rnd.next(100) < 20) {
                line.push_back(' ');
            }
        }
        lines.push_back(line);
    }

    bool hasNonSpace = false;
    for (const string& line : lines) {
        for (char ch : line) {
            if (ch != ' ') {
                hasNonSpace = true;
            }
        }
    }
    if (!hasNonSpace) {
        lines[rnd.next(static_cast<int>(lines.size()))].push_back(rnd.any(all));
    }

    for (string& line : lines) {
        while (!line.empty() && line.front() == ' ') line.erase(line.begin());
        while (!line.empty() && line.back() == ' ') line.pop_back();
        if (line.empty()) line.push_back(rnd.any(all));
        println(line);
    }

    return 0;
}
