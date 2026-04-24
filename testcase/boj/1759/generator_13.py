import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds
MIN_L = 3
MAX_L = 12
VOWELS = ['a', 'e', 'i', 'o', 'u']
CONSONANTS = [chr(i) for i in range(ord('a'), ord('z')+1) if chr(i) not in VOWELS]

def generate_test_case():
    # Randomly select L and C
    L = random.randint(MIN_L, MAX_L)   # Length of the password
    C = random.randint(L, MAX_L)       # Number of available characters

    # Choose a random distribution type
    distribution_type = random.choice(['balanced', 'vowel-heavy', 'consonant-heavy'])

    # Generate the character pool based on the distribution type
    if distribution_type == 'balanced':
        # Random distribution of vowels and consonants (no specific bias)
        num_vowels = random.randint(1, min(C - 2, len(VOWELS)))  # Ensure at least 2 consonants
        num_consonants = C - num_vowels
    elif distribution_type == 'vowel-heavy':
        # Maximize the number of vowels, with at least 2 consonants
        num_vowels = min(C - 2, len(VOWELS))  # Max vowels possible, ensuring 2 consonants
        num_consonants = C - num_vowels
    else:  # consonant-heavy
        # Maximize the number of consonants, with at least 1 vowel
        num_consonants = min(C - 1, len(CONSONANTS))  # Max consonants possible, ensuring 1 vowel
        num_vowels = C - num_consonants

    # Select vowels and consonants for the character pool
    chosen_vowels = random.sample(VOWELS, num_vowels)
    chosen_consonants = random.sample(CONSONANTS, num_consonants)
    
    # Combine the selected vowels and consonants to form the character pool
    character_pool = chosen_vowels + chosen_consonants
    random.shuffle(character_pool)  # Shuffle the character pool

    # Output the test case
    print(f"{L} {C}")
    print(" ".join(sorted(character_pool)))

# Example of generating a test case
generate_test_case()
