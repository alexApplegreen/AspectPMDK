import sys

file = open(sys.argv[1], 'r')
lines = file.readlines()

sum = 0
min = sys.maxint
max = 0
for line in lines:
    sum += int(line)
    if int(line) < min :
        min = int(line)

    if int(line) > max :
        max = int(line)

print("mean: {}".format(sum / 100))
print("min: {}".format(min))
print("max: {}".format(max))
