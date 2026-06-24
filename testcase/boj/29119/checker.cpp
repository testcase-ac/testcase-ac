#include "testlib.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

int n;
map<string, int> inputCount;

struct Answer {
    string value;
};

Answer readAnswer(InStream& stream) {
    map<string, int> remaining = inputCount;
    vector<string> order;
    order.reserve(n);

    for (int i = 0; i < n; ++i) {
        string token = stream.readToken("[0-9]+", format("a[%d]", i + 1).c_str());

        if (token.size() > 1 && token[0] == '0') {
            stream.quitf(_wa, "a[%d] has a leading zero: %s", i + 1, token.c_str());
        }
        if (token.size() > 10 || (token.size() == 10 && token > string("1000000000"))) {
            stream.quitf(_wa, "a[%d] is outside input bounds: %s", i + 1, token.c_str());
        }

        auto it = remaining.find(token);
        if (it == remaining.end() || it->second == 0) {
            stream.quitf(_wa, "a[%d]=%s does not match an unused input number", i + 1, token.c_str());
        }
        --it->second;
        order.push_back(token);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d numbers", n);
    }

    string concatenated;
    for (const string& token : order) {
        concatenated += token;
    }
    return {concatenated};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    for (int i = 0; i < n; ++i) {
        string value = inf.readToken();
        ++inputCount[value];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa,
              "jury has better concatenation: jury=%s participant=%s",
              jury.value.c_str(),
              participant.value.c_str());
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant has better concatenation: jury=%s participant=%s",
              jury.value.c_str(),
              participant.value.c_str());
    }
    quitf(_ok, "concatenation=%s", participant.value.c_str());
}
