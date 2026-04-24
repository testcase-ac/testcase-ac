#include <iostream>
// This problem is solved by ChatGPT
int main() {
    // Read each house number
    int houseNumber;
    while(std::cin >> houseNumber && houseNumber != 0) {
        // Calculate the width of the holder
        int width = 1;  // Initialize with the width of the border
        while(houseNumber > 0) {
            // Get the current digit
            int digit = houseNumber % 10;

            // Add the width of the digit to the total width
            if(digit == 0) {
                width += 4;
            } else if(digit == 1) {
                width += 2;
            } else {
                width += 3;
            }

            // Add the width of the gap
            width += 1;

            // Move to the next digit
            houseNumber /= 10;
        }

        // Print the result
        std::cout << width << std::endl;
    }

    return 0;
}
