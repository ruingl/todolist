import time

def bprint(text):
    text_length = len(text)
    border_length = text_length + 4

    for i in range(border_length):
        print("*", end="", flush=True)
        time.sleep(0.055)
    print("")

    print("* ", end="")
    for i in range(text_length):
        print(text[i], end="", flush=True)
        time.sleep(0.055)
    print(" *")

    for i in range(border_length):
        print("*", end="", flush=True)
        time.sleep(0.055)
    print("")
