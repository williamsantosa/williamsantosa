from IndoNumbers import *
from time import *

def guess():

    # Welcome message with delay
    print("Hi! Welcome to 'Guess the Number', where you'll be translating the given number (in Bahasa Indonesia) to a digit! For example: 'lima' -> 5 and 'seratus tiga puluh satu' -> 131\n")
    sleep(1)

    # Min number with error check
    while True:
        try:
            start = int(input("Please select the minimum number you want to translate: "))
            break
        except ValueError:
            print("Whoops! That was an invalid input. Please try again.")
    
    # Max number with error check
    validEnd = False
    while validEnd == False:
        try:
            end = int(input("Please select the maximum number you want to translate: "))
            if end >= start:
                validEnd = True
            else:
                print("Sorry! That number was less than the starting number. Please try again.")
        except ValueError:
            print("Whoops! That was an invalid input. Please try again.")
    
    # Create number and string for Bahasa Indonesia
    number = randint(start, end)
    indo = intToIndo(number)

    # Print out the word in Indonesian and prompt user for input
    print("\nPlease translate the following into digits:")
    g = input(indo + '\n')

    # Check the input if it's correct or not and if the user would like to play again
    q = ''
    while True:
        try:
            if int(g) == number:
                q = input("Congrats! Would you like to play again? (Y/N): ")
            else:
                q = input("Aw! The answer was " + str(number) + ". You'll get it next time for sure. Would you like to play again? (Y/N): ")
            break
        except ValueError:
            q = input("Aw! The answer was " + str(number) + ". You'll get it next time for sure. Would you like to play again? (Y/N): ")
            break

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