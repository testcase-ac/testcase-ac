# Generate a 50×50 board that after one swap yields a full row of 50 same-colored candies.
N = 50
print(N)
# Row 1: one C then 49 P's → currently length‐49 P's at the end
print('C' + 'P'*49)
# Row 2: P then 49 C's → so swapping (1,1) and (2,1) produces 50 P's in row 1
print('P' + 'C'*49)
# Remaining rows all C
for _ in range(N-2):
    print('C'*50)
