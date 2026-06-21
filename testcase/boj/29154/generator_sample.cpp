#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int randomNote(int alphabetSize) {
    return rnd.next(1, alphabetSize);
}

vector<int> randomNotes(int size, int alphabetSize) {
    vector<int> notes(size);
    for (int &note : notes) note = randomNote(alphabetSize);
    return notes;
}

int differentNote(int note, int alphabetSize) {
    if (alphabetSize == 1) return note;
    int next = rnd.next(1, alphabetSize - 1);
    if (next >= note) ++next;
    return next;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int alphabetSize = rnd.next(1, 20);
    int n = rnd.next(1, 30);
    int m = rnd.next(1, 20);

    vector<int> s;
    vector<int> l;

    if (mode == 0) {
        n = rnd.next(1, 25);
        m = rnd.next(1, min(12, n));
        alphabetSize = rnd.next(1, 6);
        s = randomNotes(n, alphabetSize);
        int start = rnd.next(0, n - m);
        l.assign(s.begin() + start, s.begin() + start + m);
    } else if (mode == 1) {
        n = rnd.next(5, 30);
        m = rnd.next(1, min(15, n));
        alphabetSize = rnd.next(2, 8);
        int background = rnd.next(1, alphabetSize);
        int melody = differentNote(background, alphabetSize);
        s.assign(n, background);
        l.assign(m, melody);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) s[i] = melody;
        }
    } else if (mode == 2) {
        n = rnd.next(8, 30);
        m = rnd.next(2, min(18, n));
        alphabetSize = rnd.next(2, 10);
        int period = rnd.next(1, min(5, n));
        vector<int> base = randomNotes(period, alphabetSize);
        for (int i = 0; i < n; ++i) s.push_back(base[i % period]);
        int offset = rnd.next(0, period - 1);
        for (int i = 0; i < m; ++i) l.push_back(base[(offset + i) % period]);
    } else if (mode == 3) {
        n = rnd.next(3, 30);
        m = rnd.next(1, min(20, n + 5));
        alphabetSize = rnd.next(2, 20);
        s = randomNotes(n, alphabetSize);
        l = randomNotes(m, alphabetSize);
        int copyLen = rnd.next(1, min(n, m));
        int sStart = rnd.next(0, n - copyLen);
        int lStart = rnd.next(0, m - copyLen);
        for (int i = 0; i < copyLen; ++i) l[lStart + i] = s[sStart + i];
    } else if (mode == 4) {
        n = rnd.next(1, 30);
        m = rnd.next(1, 20);
        alphabetSize = 20;
        int scoreAlphabet = rnd.next(1, 10);
        s = randomNotes(n, scoreAlphabet);
        l.resize(m);
        for (int &note : l) note = rnd.next(scoreAlphabet + 1, 20);
    } else {
        n = rnd.next(1, 30);
        m = rnd.next(1, 20);
        alphabetSize = rnd.next(1, 20);
        s = randomNotes(n, alphabetSize);
        l = randomNotes(m, alphabetSize);
    }

    println(n, m);
    println(s);
    println(l);

    return 0;
}
