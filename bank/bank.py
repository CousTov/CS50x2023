def main():
    greet = input("Greeting: ")
    validGreet(greet.lower())

def validGreet(greet):
    if "hello" in greet:
        print("$0")
    elif greet[0] == "h":
        print("$20")
    else:
        print("$100")

main()