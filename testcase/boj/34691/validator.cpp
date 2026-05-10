#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MIN_Q = 1;
    const int MAX_Q = 1000;

    int cntQuestions = 0;
    bool ended = false;

    while (true) {
        // Read next line as a token (no spaces allowed in this problem).
        // Allowed tokens: "animal", "tree", "flower", "end".
        string s = inf.readToken("animal|tree|flower|end", "query_or_end");
        // Each token must be followed by a newline.
        inf.readEoln();

        if (s == "end") {
            // "end" must appear only once and must be the last line.
            ensuref(!ended, "Multiple 'end' lines are not allowed");
            ended = true;
            break;
        } else {
            // Count questions
            cntQuestions++;
            ensuref(cntQuestions <= MAX_Q,
                    "Number of questions exceeds maximum %d", MAX_Q);
        }
    }

    // At least one question must be present.
    ensuref(cntQuestions >= MIN_Q,
            "Number of questions must be at least %d", MIN_Q);

    // After 'end' there must be EOF immediately.
    inf.readEof();
}
