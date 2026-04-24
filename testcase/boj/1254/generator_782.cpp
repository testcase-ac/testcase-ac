#include "testlib.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    // Initialize the generator with command-line arguments
    registerGen(argc, argv, 1);

    // Randomly choose the length of the palindrome (between 1 and 50)
    int len = rnd.next(1, 20);

    // Decide the largest character, mostly 'b' or 'c'
    char maxChar = (rnd.next(1, 10) <= 7) ? rnd.next('b', 'c') : rnd.next('b', 'z');

    // Generate the first half of the palindrome
    string half;
    for (int i = 0; i < (len + 1) / 2; i++) {
        half += rnd.next('a', maxChar);
    }

    // Construct the full palindrome
    string palindrome = half;
    for (int i = len / 2 - 1; i >= 0; i--) {
        palindrome += half[i];
    }

    // Randomly cut off some characters from the end of the palindrome
    int cut = rnd.next(0, len - 1);
    string s = palindrome.substr(0, len - cut);

    // Print the generated string
    println(s);

    return 0;
}
