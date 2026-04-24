# Generates a test where there is one big column (>250 points on same x) and one small column
# sharing two y-values, so the correct answer is 1 but the wrong solution outputs 0

def main():
    n_big = 251  # bigger than sq=250 in the wrong solution
    points = []
    # Big column at x=0 with y=0..250
    for y in range(n_big):
        points.append((0, y))
    # Small column at x=1 with two points sharing y with the big column
    points.append((1, 0))
    points.append((1, 1))

    print(len(points))
    for x, y in points:
        print(x, y)

if __name__ == "__main__":
    main()
