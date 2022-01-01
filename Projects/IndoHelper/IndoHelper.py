from IndoNumbers import *
from time import *

# Print statements for help()
def hbas():
    print("Here is some information on the single digits and other basic information.")

    digits_copy = digits.copy()
    digits_copy[0] = 'nol'
    for i in digits_copy:
        print('- ' + str(i) + ' -> ' + str(digits_copy[i]))

    print("Negative numbers are denoted by putting 'negatif' before the number. e.g negatif " + str(randIndo(1, 9)))
    print("Adding 'belas' after a single digit means 'teen' like 'sixteen' or 'fourteen' in English. Adding 'Puluh' means something is in the ten digits place. Consequently:")
    print("- ten -> puluh\n- hundred -> ratus\n- thousand -> ribu\n- million -> juta\n- billion -> milliar")

def hadv():
    print("Here is some extra knowledge on numbers.")

    print("There are a few special cases for numbers in Bahasa Indonesia like in English. Namely:")
    print("- 10 -> sepuluh\n- 11 -> sebelas\n- 100 -> seratus\n- 1000 -> seribu")

def hall():
    hbas()
    print()
    hadv()

def help():
    # Welcome message with delay
    print("Welcome to the help menu where I'll give an explanation on how to convert a number from digits to Bahasa Indonesia.\n")
    sleep(1)

    # All possible choices and error checks
    validChoices = ('basic', 'advanced', 'all')
    validEnd = False
    while validEnd == False:
        try:
            select = input("Please specify what explanation you'd like (Basic/Advanced/All): ")
            select = select.lstrip().lower()
            if select in validChoices:
                validEnd = True
            else:
                print("Whoops! That was an invalid input. Please try again.")
        except ValueError:
            print("Whoops! That was an invalid input. Please try again.")

    # Selection
    if select == 'basic':
        hbas()
    elif select == 'advanced':
        hadv()
    elif select == 'all':
        hall()

    q = input("Would you like another explanation? (Y/N): ")
    # Ask again to replay with error checks
    while True:
        if q.lstrip().lower().startswith('y'):
            print("All right!")
            help()
        elif q.lstrip().lower().startswith('n'):
            print("No problem. See you again!")
            exit()
        else:
            q = input("Sorry! That's an invalid option. Please choose again (Y/N): ")
    return 0

def convert():
    # Welcome message with delay
    print("Welcome to 'Convert the Digits' where you'll specify a number or range of numbers to be converted into Bahasa Indonesia.\n")
    sleep(1)

    # Selection of input
    validEnd = False
    while validEnd == False:
        try:
            select = input("Please specify whether you'd like to convert a single number or a range of numbers (S/M): ")
            select = select.lstrip().lower()
            if select == 's' or select == 'm':
                validEnd = True
            else:
                print("Whoops! That was an invalid input. Please try again.")
        except ValueError:
            print("Whoops! That was an invalid input. Please try again.")

    if select == 'm':
        # Min number with error check
        while True:
            try:
                start = int(input("Please select the first number you would like to translate: "))
                break
            except ValueError:
                print("Whoops! That was an invalid input. Please try again.")
        
        # Max number with error check
        validEnd = False
        while validEnd == False:
            try:
                end = int(input("Please select the last number you want to translate: "))
                if end >= start:
                    validEnd = True
                else:
                    print("Sorry! That number was less than the first number. Please try again.")
            except ValueError:
                print("Whoops! That was an invalid input. Please try again.")

    elif select == 's':
        # Min number with error check
        while True:
            try:
                start = int(input("Please select the number you want to translate: "))
                end = start
                break
            except ValueError:
                print("Whoops! That was an invalid input. Please try again.")

    print("Here is your number:") if select == 's' else print("Here are your numbers:")
    for i in range(start, end + 1):
        print(intToIndo(i))

    # Ask if the user would like to convert another number or numbers
    q = ''
    while True:
        try:
            q = input("Would you like to convert another number? (Y/N): ") if select == 's' else input("Would you like to convert more numbers? (Y/N): ")
            break
        except ValueError:
            q = input("Sorry! That's an invalid option. Would you like to convert another number? (Y/N): ") if select == 's' else input("Sorry! That's an invalid option. Would you like to convert more numbers? (Y/N): ")
            break

    # Ask again to replay with error checks
    while True:
        if q.lstrip().lower().startswith('y'):
            print("All right!")
            convert()
        elif q.lstrip().lower().startswith('n'):
            print("That's a shame. See you next time!")
            exit()
        else:
            q = input("Sorry! That's an invalid option. Please choose again (Y/N): ")

    return 0

def guess():

    # Welcome message with delay
    print("Welcome to 'Guess the Number', where you'll be translating the given number (in Bahasa Indonesia) to a digit! For example: 'lima' -> 5 and 'seratus tiga puluh satu' -> 131\n")
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
    select = input("Hi! Welcome to IndoHelper. We have a couple of little games to help you learn Bahasa Indonesia. Please select from the list below.\n- Help\n- Convert\n- Guess\n\nSelection: ")
    notSelected = True

    # Ask which game to play with false selection check
    while notSelected == True:
        if select.lstrip().lower() == 'help':
            help()
            notSelected = False
        elif select.lstrip().lower() == 'convert':
            convert()
            notSelected = False
        elif select.lstrip().lower() == 'guess':
            guess()
            notSelected = False
        else:
            select = input("Sorry! That was an invalid selection. Please select another option: ")
        
    return 0

if __name__=="__main__":
    main()