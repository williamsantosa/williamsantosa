from IndoNumbers import *
from time import *

def guess():
    print("Hi! Welcome to 'Guess the Number', where you'll be translating the given number (in Bahasa Indonesia) to a digit! For example: 'lima' -> 5 and 'seratus tiga puluh satu' -> 131\n")
    sleep(1)
    start = int(input("Please select the minimum number you want to translate: "))
    end = int(input("Please select the maximum number you want to translate: "))

    number = randint(start, end)
    indo = intToIndo(number)
    print("\nPlease translate the following:")
    g = input(indo + '\n')

    q = ''


    if int(g) == number:
        q = input("Congrats! Would you like to play again? (Y/N): ")
    else:
        q = input("Aw! You'll get it next time. Would you like to play again? (Y/N): ")

    # Ask again to replay with error checks
    while True:
        if q.lstrip().lower().startswith('y'):
            print("All right!")
            guess()
        elif q.lstrip().lower().startswith('n'):
            print("That's a shame. See you next time!")
            exit()
        else:
            q = input("Sorry! That's an invalid option. Please choose again (Y/N): ")
    return 0

def main():
    select = input("Hi! Welcome to IndoHelper. We have a couple of little games to help you learn Bahasa Indonesia. Please select from the list below.\n- Guess\n\nSelection: ")
    notSelected = True

    # Ask which game to play with false selection check
    while notSelected == True:
        if select.lstrip().lower() == 'guess':
            guess()
            notSelected = False
        else:
            select = input("Sorry! That was an invalid selection. Please select another option: ")
        
    return 0

if __name__=="__main__":
    main()