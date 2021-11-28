from IndoNumbers import *

def numbers():
    return 0

def main():
    select = input("Hi! Welcome to IndoHelper. We have a couple of little games to help you learn Bahasa Indonesia. Please select from the list below.\n- numbers\n\nSelection: ")
    notSelected = True

    while notSelected == True:
        if select.lower() == 'numbers':
            numbers()
            notSelected = False
        else:
            select = input("Sorry! That was an invalid selection. Please select another option: ")
        
    return 0

if __name__=="__main__":
    main()