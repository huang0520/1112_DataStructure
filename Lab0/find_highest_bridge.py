# Read number of bridges
n = int(input())

# Read height of each bridge
tmp = input()
height = list(enumerate(tmp.split(" ", n - 1), start = 1))

height.sort(key = lambda height: height[1], reverse = True)

print(height[0][0])