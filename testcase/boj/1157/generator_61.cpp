#include "testlib.h"
#include <string>

const int MIN_LEN = 1;
const int MAX_LEN = 12; // For small easily verifiable cases, set this to 1000. For large, change it to 1000000.

std::string generate_uniform_word(int length) {
    std::string word;
    for (int i = 0; i < length; i++) {
        if (rnd.next(0, 1) == 0) {
            word += rnd.next('a', 'z');  // lowercase letter
        } else {
            word += rnd.next('A', 'Z');  // uppercase letter
        }
    }
    return word;
}

std::string generate_single_dominating(int length) {
    std::string word;
    char dominant = rnd.next('a', 'z');  // Choose a random lowercase dominant letter
    int dominant_freq = rnd.next(length / 2, length);  // Dominant character appears more than half the time
    
    // Fill the word with the dominant character first
    for (int i = 0; i < dominant_freq; i++) {
        if (rnd.next(0, 1) == 0) {
            word += dominant;  // lowercase
        } else {
            word += toupper(dominant);  // uppercase version
        }
    }

    // Fill the rest of the word with random characters
    for (int i = dominant_freq; i < length; i++) {
        if (rnd.next(0, 1) == 0) {
            word += rnd.next('a', 'z');  // random lowercase letter
        } else {
            word += rnd.next('A', 'Z');  // random uppercase letter
        }
    }

    // Shuffle the string to avoid ordered patterns
    shuffle(word.begin(), word.end());
    
    return word;
}

std::string generate_tie_word(int length) {
    std::string word;
    char first_char = rnd.next('a', 'z');
    char second_char = rnd.next('a', 'z');
    
    // Ensure that both characters are different
    while (first_char == second_char) {
        second_char = rnd.next('a', 'z');
    }
    
    if(length % 2) {
        length += 1;
    }
    int half_length = length / 2;
    
    // Fill the first half with the first character
    for (int i = 0; i < half_length; i++) {
        if (rnd.next(0, 1) == 0) {
            word += first_char;  // lowercase
        } else {
            word += toupper(first_char);  // uppercase version
        }
    }
    
    // Fill the second half with the second character
    for (int i = half_length; i < length; i++) {
        if (rnd.next(0, 1) == 0) {
            word += second_char;  // lowercase
        } else {
            word += toupper(second_char);  // uppercase version
        }
    }
    
    // Shuffle the string to avoid ordered patterns
    shuffle(word.begin(), word.end());
    
    return word;
}
std::string generate_completely_random_word(int length) {
    std::string word;
    for (int i = 0; i < length; i++) {
        if (rnd.next(0, 1) == 0) {
            word += rnd.next('a', 'z');  // random lowercase letter
        } else {
            word += rnd.next('A', 'Z');  // random uppercase letter
        }
    }
    return word;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int test_type = rnd.next(0, 3);  // Randomly choose the type of test case to generate
    int length = rnd.next(MIN_LEN, MAX_LEN);  // Random length between MIN_LEN and MAX_LEN
    if(rnd.next() < 0.2) {
        length = rnd.next(MAX_LEN+1, 500); // randomly create larger testcase
    }

    std::string test_case;
    
    if (test_type == 0) {
        // Generate uniform word
        test_case = generate_uniform_word(length);
    } else if (test_type == 1) {
        // Generate word with a single dominating character
        test_case = generate_single_dominating(length);
    } else if (test_type == 2) {
        // Generate word with a tie in frequency
        test_case = generate_tie_word(length);
    } else if(test_type == 3) {
        test_case = generate_completely_random_word(length);
    }

    // Output the generated test case
    std::cout << test_case << std::endl;
    
    return 0;
}
