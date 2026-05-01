# Generates a test that causes the wrong solution to overflow when using eval on a huge integer division
# Expression: (10^100)^9 / 2, which creates a numerator ~1e900; Python's float conversion in eval overflows

def main():
    n = 10
    x = '1' + '0'*100  # 10^100
    print(n)
    for i in range(n-1):  # print 9 numbers and 9 operators
        print(x)
        if i < n-2:
            print('*')
        else:
            print('/')
    print(2)

if __name__ == "__main__":
    main()
