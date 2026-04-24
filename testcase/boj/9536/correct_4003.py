T = int(input())
for _ in range(T):
    s = input().split()
    st = set()
    while True:
        i = input().split()
        if len(i) == 5:
            break
        st.add(i[2])
    print(' '.join(i for i in s if i not in st))
