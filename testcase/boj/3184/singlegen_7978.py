R = 250
C = 4
print(f"{R} {C}")
# Row 0: open cell at col 0, walls elsewhere
print(".###")
# Row 1: an enclosed sheep region at (1,2) surrounded by '#'
print(".#o#")
# Rows 2..249: maintain open column at col 0 connecting to bottom border
for _ in range(2, R):
    print(".###")
