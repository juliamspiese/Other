from cs50 import get_float

def main():

    while True:
        f = get_float("Change: ")
        if f >= 0:
            break
    change = round(f * 100)
    coins = 0
    coinlist = [25, 10, 5, 1]
    for i in range(4):
        n = coinlist[i]
        while change >= n:
            change -= n
            coins += 1
    print(coins)

if __name__ == "__main__":
    main()