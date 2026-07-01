#include "testlib.h"
#include <set>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 5);
    println(N);
    int c = rnd.next(1, 3);
    set<string> words;
    for (int i = 0; i < N; i++) {
        string word;
        if(c == 1) {
            do {
                word = rnd.next("[a-z]{1,10}");
            } while (!words.insert(word).second);
        } else if(c == 2) {
            do {
                word = rnd.next("[a-b]{1,10}");
            } while (!words.insert(word).second);
        } else if(c == 3) {
            do {
                word = rnd.next("[a-c]{1,10}");
            } while (!words.insert(word).second);
        }
        println(word);
    }
}
