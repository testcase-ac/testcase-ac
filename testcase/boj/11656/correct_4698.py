(lambda s:[print(i) for i in sorted([s[-i:] for i in range(len(s))])])(input())
