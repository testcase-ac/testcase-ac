n = int(input())

import math

result_board = [[' '] * n for _ in range(n)]

def mark_star(magnitude, x_idx, y_idx):
    for i in range(3):
            for j in range(3):
                if i == 1 and i == j: continue
    
                if magnitude == 1:
                    result_board[y_idx + j][x_idx + i] = '*'
                else:
                    mark_star(magnitude // 3, 3 * (x_idx + i), 3 * (y_idx + j))

mark_star(n // 3, 0, 0)
print('\n'.join(map(lambda x: ''.join(x), result_board)))
