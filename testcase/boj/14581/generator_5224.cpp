#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Decide whether to force max length or random length
    bool maxLen = rnd.next(0, 1);
    int L = maxLen ? 20 : rnd.next(1, 20);
    // Choose type of ID: 0 = digits, 1 = lowercase, 2 = uppercase, 3 = mixed
    int type = rnd.next(0, 3);
    string digits = "0123456789";
    string lower = "abcdefghijklmnopqrstuvwxyz";
    string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string pool;
    if (type == 0) pool = digits;
    else if (type == 1) pool = lower;
    else if (type == 2) pool = upper;
    else pool = digits + lower + upper;
    // Build the ID
    string id;
    for (int i = 0; i < L; i++) {
        id += rnd.any(pool);
    }
    // Output
    println(id);
    return 0;
}
