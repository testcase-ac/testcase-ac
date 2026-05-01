# Generates a worst-case string that causes the given solution to TLE due to O(n^3) behavior
# The string length is the maximum allowed (2500) and consists of the same character,
# making the number of palindromic substrings ~ n(n+1)/2 and triggering the heavy inner loops.
print("A" * 2500)
