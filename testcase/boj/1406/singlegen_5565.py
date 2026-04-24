# Generate maximum testcase for the editor problem:
# - Initial string length N = 100_000 (max)
# - Number of commands M = 500_000 (max)
# - All commands are "P b", which cumulatively append 500_000 characters,
#   yielding a final string of length 600_000 (max for the editor).

import sys

N = 100_000
M = 500_000

# Print initial string of 'a's
sys.stdout.write("a" * N + "\n")
# Print number of commands
sys.stdout.write(str(M) + "\n")
# Print M insert commands
for _ in range(M):
    sys.stdout.write("P b\n")
