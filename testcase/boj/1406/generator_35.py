import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random
import string

# Constants for input generation
MIN_TEXT_LENGTH = 1
MAX_TEXT_LENGTH = 8  # Adjust these constants for smaller test sizes as needed
MIN_OPS = 1
MAX_OPS = 15  # Adjust these constants for fewer operations as needed

def generate_random_string(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

def generate_random_operations(num_operations):
    operations = []
    
    for _ in range(num_operations):
        op_type = random.choice(["L", "D", "B", "P"])
        
        if op_type == "L":
            operations.append("L")
        elif op_type == "D":
            operations.append("D")
        elif op_type == "B":
            operations.append("B")
        elif op_type == "P":
            char_to_insert = random.choice(string.ascii_lowercase)
            operations.append(f"P {char_to_insert}")
    
    return operations

def generate_minimal_testcase():
    text = generate_random_string(MIN_TEXT_LENGTH)
    operations = generate_random_operations(MIN_OPS)
    return text, operations

def generate_maximal_testcase():
    text = generate_random_string(MAX_TEXT_LENGTH)
    operations = generate_random_operations(MAX_OPS)
    return text, operations

def generate_balanced_testcase():
    text_length = random.randint(MIN_TEXT_LENGTH, MAX_TEXT_LENGTH)  
    num_operations = random.randint(MIN_OPS, MAX_OPS)
    text = generate_random_string(text_length)
    operations = generate_random_operations(num_operations)
    return text, operations

def generate_random_testcase():
    text_length = random.randint(MIN_TEXT_LENGTH, MAX_TEXT_LENGTH)
    num_operations = random.randint(MIN_OPS, MAX_OPS)
    text = generate_random_string(text_length)
    operations = generate_random_operations(num_operations)
    return text, operations

def generate_testcase():
    # Randomly select a testcase type to generate
    test_type = random.choice(["minimal", "maximal", "balanced", "random"])
    
    if test_type == "minimal":
        text, operations = generate_minimal_testcase()
    elif test_type == "maximal":
        text, operations = generate_maximal_testcase()
    elif test_type == "balanced":
        text, operations = generate_balanced_testcase()
    else:
        text, operations = generate_random_testcase()
    
    # Print the generated testcase
    print(text)
    print(len(operations))
    for op in operations:
        print(op)

# Generate a random testcase
generate_testcase()
