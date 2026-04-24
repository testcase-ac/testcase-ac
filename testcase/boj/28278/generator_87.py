import random as __otac_random
import sys as __otac_sys
if len(__otac_sys.argv) > 1:
    __otac_random.seed(int(__otac_sys.argv[1]))

import random

# Constants
MIN_N = 3  # Minimum number of commands
MAX_N = 10  # Maximum number of commands (for small output)
MIN_X = 1   # Minimum value of X for '1 X' command
MAX_X = 9  # Maximum value of X for '1 X' command

def generate_test_case():
    N = random.randint(MIN_N, MAX_N)
    commands = []
    
    # Ensure at least one output producing command
    output_commands = [2, 3, 4, 5]
    has_output_command = False

    for _ in range(N):
        cmd_type = random.randint(1, 5)

        if cmd_type == 1:
            # Command 1 X: Push a random integer X onto the stack
            X = random.randint(MIN_X, MAX_X)
            commands.append(f"1 {X}")
        elif cmd_type in output_commands:
            # Commands 2, 3, 4, 5 produce output
            commands.append(str(cmd_type))
            has_output_command = True

    # Ensure there is at least one output producing command
    if not has_output_command:
        commands.append(str(random.choice(output_commands)))

    # Print the total number of commands and the list of commands
    print(len(commands))
    print("\n".join(commands))

# Example usage
generate_test_case()
