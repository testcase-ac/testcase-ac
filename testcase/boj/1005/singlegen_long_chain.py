def main():
    buildings = 1000
    print(1)
    print(buildings, buildings - 1)
    print(" ".join(["1"] * buildings))
    for building in range(1, buildings):
        print(building, building + 1)
    print(buildings)


if __name__ == "__main__":
    main()
