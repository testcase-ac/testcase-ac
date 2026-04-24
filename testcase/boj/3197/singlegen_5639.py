R, C = 1500, 1500
print(R, C)
for i in range(R):
    if i == 0:
        # Top‐left corner is the first swan
        print('L' + 'X' * (C - 1))
    elif i == R - 1:
        # Bottom‐right corner is the second swan
        print('X' * (C - 1) + 'L')
    else:
        # All other cells are ice
        print('X' * C)
