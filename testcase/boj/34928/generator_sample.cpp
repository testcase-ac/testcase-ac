#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char fillerChar() {
    const string letters = "BCDEFGHIJKMNOQRSTUVWXYZX";
    return rnd.any(letters);
}

string randomFill(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) s.push_back(fillerChar());
    return s;
}

void placeRequired(string& s, vector<int> positions, string letters) {
    shuffle(positions.begin(), positions.end());
    shuffle(letters.begin(), letters.end());
    for (int i = 0; i < 4; ++i) s[positions[i]] = letters[i];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(4, 28);
        s = randomFill(n);

        vector<int> pos;
        int cur = rnd.next(0, min(2, n - 4));
        pos.push_back(cur);
        for (int i = 1; i < 4; ++i) {
            int remaining = 4 - i;
            int maxStep = n - remaining - cur;
            int step = 1 + 2 * rnd.next(0, max(0, (maxStep - 1) / 2));
            cur += step;
            pos.push_back(cur);
        }
        s[pos[0]] = 'P';
        s[pos[1]] = 'A';
        s[pos[2]] = 'U';
        s[pos[3]] = 'L';
    } else if (mode == 1) {
        int n = rnd.next(4, 28);
        s = randomFill(n);
        vector<int> pos = {0, 1, 2, 3};
        if (n > 4) {
            int start = rnd.next(0, n - 4);
            for (int i = 0; i < 4; ++i) pos[i] = start + i;
        }
        s[pos[0]] = 'P';
        s[pos[1]] = 'A';
        s[pos[2]] = 'U';
        s[pos[3]] = 'L';
        if (rnd.next(2) && n >= 6) swap(s[pos[rnd.next(0, 2)]], s[pos[rnd.next(1, 3)]]);
    } else if (mode == 2) {
        int n = rnd.next(4, 30);
        s = randomFill(n);
        vector<int> positions;
        for (int i = 0; i < n; ++i) positions.push_back(i);
        placeRequired(s, positions, "PAUL");
    } else if (mode == 3) {
        int blocks = rnd.next(1, 7);
        string pattern = rnd.any(vector<string>{"PAXUL", "PPAAUULL", "LUAAPP", "AUPL", "PXXAUL"});
        for (int i = 0; i < blocks; ++i) {
            s += pattern;
            if (rnd.next(2)) s.push_back(fillerChar());
        }
        if ((int)s.size() > 30) s.resize(30);
        if (s.find('P') == string::npos || s.find('A') == string::npos ||
            s.find('U') == string::npos || s.find('L') == string::npos) {
            s = "PAUL";
        }
    } else if (mode == 4) {
        int n = rnd.next(20, 60);
        s = randomFill(n);
        vector<int> positions;
        for (int i = 0; i < n; ++i) {
            if (rnd.next(3) == 0) positions.push_back(i);
        }
        while ((int)positions.size() < 4) positions.push_back(rnd.next(n));
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());
        while ((int)positions.size() < 4) {
            int p = rnd.next(n);
            if (find(positions.begin(), positions.end(), p) == positions.end()) positions.push_back(p);
        }
        placeRequired(s, positions, "PAUL");
    } else {
        int n = rnd.next(4, 100);
        s = randomFill(n);
        int edge = rnd.next(4);
        if (edge == 0) {
            s[0] = 'P';
            s[1] = 'A';
            s[n - 2] = 'U';
            s[n - 1] = 'L';
        } else if (edge == 1) {
            s[0] = 'L';
            s[1] = 'U';
            s[n - 2] = 'A';
            s[n - 1] = 'P';
        } else if (edge == 2) {
            s[0] = 'P';
            s[n / 3] = 'A';
            s[(2 * n) / 3] = 'U';
            s[n - 1] = 'L';
        } else {
            vector<int> positions = {0, n / 2, max(0, n / 2 - 1), n - 1};
            placeRequired(s, positions, "PAUL");
        }
    }

    println((int)s.size());
    println(s);
    return 0;
}
