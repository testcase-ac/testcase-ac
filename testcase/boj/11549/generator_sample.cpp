#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tea = rnd.next(1, 4);
    int mode = rnd.next(0, 4);
    vector<int> answers(5);

    if (mode == 0) {
        for (int& answer : answers) answer = tea;
    } else if (mode == 1) {
        for (int& answer : answers) {
            do {
                answer = rnd.next(1, 4);
            } while (answer == tea);
        }
    } else if (mode == 2) {
        int correctCount = rnd.next(0, 5);
        for (int i = 0; i < 5; ++i) answers[i] = i < correctCount ? tea : rnd.next(1, 4);
        for (int i = correctCount; i < 5; ++i) {
            while (answers[i] == tea) answers[i] = rnd.next(1, 4);
        }
        shuffle(answers.begin(), answers.end());
    } else {
        int commonWrong = rnd.next(1, 4);
        while (commonWrong == tea) commonWrong = rnd.next(1, 4);

        for (int& answer : answers) {
            if (rnd.next(0, 99) < 35) {
                answer = tea;
            } else if (rnd.next(0, 99) < 70) {
                answer = commonWrong;
            } else {
                answer = rnd.next(1, 4);
            }
        }
    }

    println(tea);
    println(answers);
    return 0;
}
