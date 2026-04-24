#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int N;
vector<string> orig;

// Reads an answer (sequence of moves) from the given stream,
// checks its validity, simulates it, and returns its length.
// If something is wrong, quits with _wa for ouf or _fail for ans.
int readAns(InStream &stream) {
    // Read the sequence of commands as one token
    string s = stream.readToken();
    int len = (int)s.size();
    if (len > 500) {
        stream.quitf(_wa, "too many moves: %d > 500", len);
    }
    // Simulate
    vector<string> ch = orig;
    int arrow = 0;  // 0-based index
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c < '1' || c > '4') {
            stream.quitf(_wa, "invalid command '%c' at position %d", c, i+1);
        }
        switch (c) {
            case '1':
                if (arrow + 1 < N) arrow++;
                break;
            case '2':
                if (arrow - 1 >= 0) arrow--;
                break;
            case '3':
                if (arrow + 1 < N) {
                    swap(ch[arrow], ch[arrow+1]);
                    arrow++;
                }
                break;
            case '4':
                if (arrow - 1 >= 0) {
                    swap(ch[arrow], ch[arrow-1]);
                    arrow--;
                }
                break;
        }
    }
    // Check final configuration
    if (ch[0] != "KBS1") {
        stream.quitf(_wa, "first channel is '%s', expected 'KBS1'", ch[0].c_str());
    }
    if (ch.size() >= 2 && ch[1] != "KBS2") {
        stream.quitf(_wa, "second channel is '%s', expected 'KBS2'", ch[1].c_str());
    }
    return len;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    N = inf.readInt();
    orig.resize(N);
    for (int i = 0; i < N; i++) {
        orig[i] = inf.readToken();
    }
    // Validate jury answer
    readAns(ans);
    // Validate participant answer and get its length
    int plen = readAns(ouf);
    // If we reach here, participant is correct
    quitf(_ok, "valid with %d moves", plen);
}
