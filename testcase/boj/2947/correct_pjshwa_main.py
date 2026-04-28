import sys

wood_piece = list(map(int, sys.stdin.readline().split()))

def print_wood_piece():
    for element in wood_piece:
        print("{} ".format(element), end="")
    print()

def bubble(index):
    if(wood_piece[index+1] < wood_piece[index]):
        wood_piece[index], wood_piece[index+1] = wood_piece[index+1], wood_piece[index]
        print_wood_piece()
        
def check():
    for i in range(4):
        if(wood_piece[i+1] < wood_piece[i]):
            return False
    return True

while(True):
    for i in range(4):
        bubble(i)
    if check(): break