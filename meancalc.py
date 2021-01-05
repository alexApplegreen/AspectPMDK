import sys

file = open(sys.arg[1], 'r')
lines = file.readlines()

sum = 0
for line in lines:
    sumn += line

print(sum /= 100)
