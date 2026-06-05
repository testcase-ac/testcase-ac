#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Submission {
    string user;
    int result;
    int memory;
    int time;
    int language;
    int codeLength;
};

int randomResult(bool acceptedAllowed) {
    if (acceptedAllowed && rnd.next(0, 4) == 0) return 4;
    int result = rnd.next(5, 11);
    return result;
}

Submission makeSubmission(const string& user, int result) {
    int style = rnd.next(0, 3);
    int memory = style == 0 ? rnd.next(0, 3000) : rnd.next(0, 3000000);
    int time = style == 1 ? rnd.next(0, 2000) : rnd.next(0, 200000);
    int language = rnd.any(vector<int>{0, 1, 3, 28, 49, 84, 88, 100});
    int codeLength = style == 2 ? rnd.next(1, 2000) : rnd.next(1, 524288);
    return {user, result, memory, time, language, codeLength};
}

string userName(int index) {
    static const vector<string> base = {
        "baekjoon", "user_1", "USER_2", "team_A", "x9", "long_user_name_0001",
        "WrongBeforeAC", "after_ac", "solo", "mix_42"
    };
    if (index < (int)base.size()) return base[index];
    return "u_" + to_string(index);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Submission> submissions;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            submissions.push_back(makeSubmission("megalusion", randomResult(true)));
        }
    } else {
        int userCount = rnd.next(1, mode == 5 ? 10 : 6);
        for (int i = 0; i < userCount; ++i) {
            string user = userName(i);
            bool solves = mode != 1 && (mode == 2 || rnd.next(0, 2) != 0);
            int wrongBefore = solves ? rnd.next(0, mode == 2 ? 8 : 4) : rnd.next(1, 5);

            for (int j = 0; j < wrongBefore; ++j) {
                submissions.push_back(makeSubmission(user, randomResult(false)));
            }
            if (solves) {
                submissions.push_back(makeSubmission(user, 4));
                int afterAccepted = rnd.next(0, 3);
                for (int j = 0; j < afterAccepted; ++j) {
                    submissions.push_back(makeSubmission(user, randomResult(true)));
                }
            }
        }

        int adminCount = rnd.next(0, 5);
        for (int i = 0; i < adminCount; ++i) {
            submissions.push_back(makeSubmission("megalusion", randomResult(true)));
        }

        shuffle(submissions.begin(), submissions.end());
    }

    int submissionId = rnd.next(1, 8000000 - (int)submissions.size() * 3);
    println((int)submissions.size());
    for (int i = 0; i < (int)submissions.size(); ++i) {
        const Submission& submission = submissions[i];
        println(submissionId,
                submission.user,
                submission.result,
                submission.memory,
                submission.time,
                submission.language,
                submission.codeLength);
        submissionId += rnd.next(1, 3);
    }

    return 0;
}
