from cs50 import get_int

# get height
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
# iterate over the given height [i = 0, 1, 2, ... , (height - 1)]
for i in range(height):
    # print appriopirate blank spaces without \n in the end
    print(" " * (height - i - 1), end="")
    # print appriopirate hashes after blank spaces
    print("#" * (i + 1))