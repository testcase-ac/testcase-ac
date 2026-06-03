#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string start = "고무오리 디버깅 시작";
    const string end = "고무오리 디버깅 끝";
    const string duck = "고무오리";
    const string problem = "문제";

    string line = inf.readLine("[^]+", "line_1");
    ensuref(line == start, "line 1 must be the start command");

    int lineCount = 1;
    bool ended = false;
    while (!ended) {
        ensuref(lineCount < 102, "input must contain at most 102 lines");
        ++lineCount;

        line = inf.readLine("[^]+", format("line_%d", lineCount));
        if (line == end) {
            ended = true;
        } else {
            ensuref(line == duck || line == problem,
                    "line %d must be a duck command, problem command, or end command",
                    lineCount);
        }
    }

    inf.readEof();
}
