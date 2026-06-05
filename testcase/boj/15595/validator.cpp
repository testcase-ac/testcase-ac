#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    set<int> submissionIds;
    int previousSubmissionId = 0;
    for (int i = 0; i < n; ++i) {
        int submissionId = inf.readInt(1, 8000000, "submission_id");
        inf.readSpace();
        string userId = inf.readToken("[a-zA-Z0-9_]{1,20}", "user_id");
        inf.readSpace();
        int result = inf.readInt(4, 11, "result");
        inf.readSpace();
        int memory = inf.readInt(0, 3000000, "memory");
        inf.readSpace();
        int time = inf.readInt(0, 200000, "time");
        inf.readSpace();
        int language = inf.readInt(0, 100, "language");
        inf.readSpace();
        int codeLength = inf.readInt(1, 524288, "code_length");
        inf.readEoln();

        ensuref(submissionIds.insert(submissionId).second,
                "duplicate submission id at row %d: %d", i + 1, submissionId);
        ensuref(submissionId > previousSubmissionId,
                "submission ids must be in increasing order at row %d: %d after %d",
                i + 1, submissionId, previousSubmissionId);
        previousSubmissionId = submissionId;

        (void)userId;
        (void)result;
        (void)memory;
        (void)time;
        (void)language;
        (void)codeLength;
    }

    inf.readEof();
}
