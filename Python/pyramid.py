from cs50 import get_int

def main():

    #get pyramid height from user
    while True:
        n = get_int("Height: ")
        if not n < 1 and not n > 8:
            break

    for i in range(n):

        for j in range(n - (i+1)):
            print(" ", end = "")

        for k in range(i+1):
            print("#", end = "")

        print("")

if __name__ == "__main__":
    main()