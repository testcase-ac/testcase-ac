import sys

board_height = 12
board_width = 6
board_size = board_height * board_width
block_list = []

for i in range(board_height):
  f_line = sys.stdin.readline().rstrip("\n")
  for j in range(board_width):
    block_string = f_line[j]
    if f_line[j] not in ['R', 'Y', 'G', 'B', 'P']:
      block_string = "."
    block_list.append(block_string)

def search(successive_indexes, block_string, index):
  successive_indexes.append(index)
  return 1 + search_right(successive_indexes, block_string, index) + search_down(successive_indexes, block_string, index)\
   + search_left(successive_indexes, block_string, index) + search_up(successive_indexes, block_string, index)

def search_right(successive_indexes, block_string, index):
  if (index % board_width == board_width - 1) or index + 1 in successive_indexes:
    return 0
  elif (block_list[index+1] == block_string):
    return search(successive_indexes, block_string, index+1)
  else:
    return 0

def search_down(successive_indexes, block_string, index):
  if (index > board_size - board_width - 1) or index + board_width in successive_indexes:
    return 0
  elif (block_list[index+board_width] == block_string):
    return search(successive_indexes, block_string, index+board_width)
  else:
    return 0

def search_left(successive_indexes, block_string, index):
  if (index % board_width == 0) or index - 1 in successive_indexes:
    return 0
  elif (block_list[index-1] == block_string):
    return search(successive_indexes, block_string, index-1)
  else:
    return 0

def search_up(successive_indexes, block_string, index):
  if (index < board_width) or index - board_width in successive_indexes:
    return 0
  elif (block_list[index-board_width] == block_string):
    return search(successive_indexes, block_string, index-board_width)
  else:
    return 0

def check_and_explode(block_string, index):
  successive_indexes = []
  gravity_list = set()
  if search(successive_indexes, block_string, index) >= 4:
    for idx in successive_indexes:
      block_list[idx] = "."
      gravity_list.add(idx % board_width)
  return gravity_list

def wipe():
  explode_number = 0
  gravity_list = set()
  for index in range(board_size):
    if not block_list[index] == ".":
      gravity_list |= check_and_explode(block_list[index], index)

  if gravity_list:
    for pull_index in gravity_list:
      for height in range(1, board_height):
        cur_height_idx = board_height - height - 1
        if block_list[cur_height_idx * board_width + pull_index] != '.':
          char = block_list[cur_height_idx * board_width + pull_index]
          gap = 0
          while (cur_height_idx + gap + 1) * board_width < board_size and \
            block_list[(cur_height_idx + gap + 1) * board_width + pull_index] == '.':
            gap += 1

          if gap > 0:
            block_list[(cur_height_idx + gap) * board_width + pull_index] = char
            block_list[cur_height_idx * board_width + pull_index] = '.'
    return 1
  else:
    return 0

a = 0
while True:
  b = wipe()
  if b == 0:
    print(a)
    break

  a += b
