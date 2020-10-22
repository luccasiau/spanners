import sys

N = 10
if (len(sys.argv) > 1):
  N = int(sys.argv[1])

bottom_x, bottom_y = 0.0, 0.0
top_x, top_y = 0.5, 3**(.5)/2-0.0001

print(2*N)
for _ in range(N):
  print(bottom_x, bottom_y)
  bottom_x += 1

for _ in range(N):
  print(top_x, top_y)
  top_x += 1
