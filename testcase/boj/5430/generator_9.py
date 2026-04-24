import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants for bounds
MAX_PROGRAM_LENGTH = 5  # Adjusted for smaller test cases
MAX_LIST_LENGTH = 10  # Adjusted for smaller test cases
MAX_ELEMENT_VALUE = 100
MIN_ELEMENT_VALUE = 1
MAX_TEST_CASES = 10  # Adjusted for smaller number of test cases

def generate_program():
    # Generates a random BAPC program consisting of 'R' and 'D'
    program_length = random.randint(1, MAX_PROGRAM_LENGTH)
    program = ''.join(random.choice(['R', 'D']) for _ in range(program_length))
    return program

def generate_list(length):
    # Generates a list of integers with different types of distributions
    distribution_type = random.choice(['increasing', 'decreasing', 'random', 'constant', 'close_to_min', 'close_to_max'])

    if distribution_type == 'increasing':
        return sorted([random.randint(MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE) for _ in range(length)])
    elif distribution_type == 'decreasing':
        return sorted([random.randint(MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE) for _ in range(length)], reverse=True)
    elif distribution_type == 'constant':
        element = random.randint(MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE)
        return [element] * length
    elif distribution_type == 'close_to_min':
        return [random.randint(MIN_ELEMENT_VALUE, MIN_ELEMENT_VALUE + 10) for _ in range(length)]  # Close to min
    elif distribution_type == 'close_to_max':
        return [random.randint(MAX_ELEMENT_VALUE - 10, MAX_ELEMENT_VALUE) for _ in range(length)]  # Close to max
    else:  # random
        return [random.randint(MIN_ELEMENT_VALUE, MAX_ELEMENT_VALUE) for _ in range(length)]

def generate_test_case():
    # Generates one valid test case
    program = generate_program()
    n = random.randint(0, MAX_LIST_LENGTH)
    if n == 0:
        input_list = []
    else:
        input_list = generate_list(n)

    # Format list as string
    input_list_str = "[" + ",".join(map(str, input_list)) + "]"
    return program, n, input_list_str

def generate_test_cases():
    num_cases = random.randint(1, MAX_TEST_CASES)
    test_cases = []
    
    for _ in range(num_cases):
        program, n, input_list_str = generate_test_case()
        test_cases.append(f"{program}\n{n}\n{input_list_str}")
    
    return test_cases

if __name__ == "__main__":
    test_cases = generate_test_cases()
    
    # Print the generated test cases
    print(len(test_cases))
    for case in test_cases:
        print(case)
