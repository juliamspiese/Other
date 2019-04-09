from cs50 import get_string
import sys


def main():

    # Checking for argument length
    if len(sys.argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    # Assigns argument to file
    infile = sys.argv[1]

    # Creates ban: set data structre to store words in for later access
    ban = set()

    # Opens file to read
    with open(infile, "r") as dictionary:
        # Copies word to 'ban' set
        for line in dictionary:
            ban.add(line.strip())

    # Prompts for message
    message = get_string("What message would you like to censor? \n")
    # Splits into words
    words = message.split(" ")

    # Creates empty string to be filled with censored message
    censored = ""

    # Iterates over user input message
    for word in words:
        # Bleeps out words if they are in 'ban' set
        if word.lower() in ban:
            censored += ("*" * len(word)) + " "
        # Else leaves words intact
        else:
            censored += word + " "

    # prints censored message
    print(censored.strip())

if __name__ == "__main__":
    main()
