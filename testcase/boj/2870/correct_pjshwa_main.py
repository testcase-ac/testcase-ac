import sys, re

class BJ02870:
  def run(self):
    line_numbers = int(input())
    numbers_array = []
    for i in range(line_numbers):
      numbers_array.extend(map(int, filter(lambda x: x != '', re.sub(r'[a-z]+', ',', sys.stdin.readline().rstrip()).split(','))))
    for number in sorted(numbers_array):
      print(number)

BJ02870().run()