from cs50 import get_string
import sys

def main():

    # Checks for argument count, returns 1 if argument count is not 2
    if len(sys.argv) != 2:
        print("Usage: python caesar.py key")
        exit(1)

    # Makes key by turning second argument into an integer
    key = int(sys.argv[1])

    # Encryption Function
    def encrypt(text, key):
        cipher = ""
        for i in range(len(text)):
            char = text[i]

            if (char.isupper()):
                cipher += chr((ord(char) + key - 65) % 26 + 65)
            else:
                cipher += chr((ord(char) + key - 97) % 26 + 97)
            return cipher

    while True:
        plaintext = get_string("Plaintext: ")
        print("ciphertext: ", end = "")
        for c in plaintext:
            if c.isalpha():
                c = encrypt(c, key)
            print(c, end = "")
        print()
        break

if __name__ == "__main__":
    main()