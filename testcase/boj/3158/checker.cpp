#include "testlib.h"

#include <set>
#include <string>

using namespace std;

bool isValidTriangleName(const string& name) {
    if (name.size() < 2 || name.size() > 50 || name[0] != 'T') {
        return false;
    }
    for (int i = 1; i < (int)name.size(); ++i) {
        if (name[i] < '1' || name[i] > '4') {
            return false;
        }
    }
    for (int i = 1; i + 1 < (int)name.size(); ++i) {
        if (name[i] == '4') {
            return false;
        }
    }
    return true;
}

struct Answer {
    set<string> names;
};

Answer readAnswer(InStream& stream) {
    Answer result;
    int index = 0;

    while (!stream.seekEof()) {
        string name = stream.readToken();
        if (!isValidTriangleName(name)) {
            stream.quitf(_wa, "triangle[%d] is not a valid triangle name: %s",
                         index + 1, name.c_str());
        }
        if (!result.names.insert(name).second) {
            stream.quitf(_wa, "duplicate triangle name: %s", name.c_str());
        }
        ++index;
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    for (const string& name : jury.names) {
        if (!participant.names.count(name)) {
            quitf(_wa, "missing triangle name: %s", name.c_str());
        }
    }
    for (const string& name : participant.names) {
        if (!jury.names.count(name)) {
            quitf(_wa, "unexpected triangle name: %s", name.c_str());
        }
    }

    quitf(_ok, "%d triangle name(s)", (int)participant.names.size());
}
