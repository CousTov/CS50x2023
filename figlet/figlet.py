from pyfiglet import Figlet
from sys import argv, exit
from cs50 import get_string
from random import choice

def main():
    figlet = Figlet()
    fonts = figlet.getFonts()
    argNum = len(argv) - 1

    # Specified font in CLI
    if (argNum == 2) and (argv[1] == '-f' or argv[1] == '--font') and (argv[2] in fonts):
        txtIn = get_string("Input: ")
        figlet.setFont(font=argv[2])
        print(figlet.renderText(txtIn))
        exit(0)

    # No args
    elif argNum == 0:
        txtIn = get_string("Input: ")
        figlet.setFont(font=choice(fonts))
        print(figlet.renderText(txtIn))
        exit(0)

    # Invalid usage
    else:
        print("Invalid Usage")
        exit(1)

main()