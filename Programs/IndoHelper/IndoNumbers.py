from random import *

digits = {
    0:'',
    1:'satu',
    2:'dua',
    3:'tiga',
    4:'empat',
    5:'lima',
    6:'enam',
    7:'tujuh',
    8:'delapan',
    9:'sembilan',
}

def randIndo(start, end):
    return intToIndo(randint(start, end))

def intToIndo(i):
    """
    Converts a positive integer within the range [MIN_INT, MAX_INT] into Bahasa Indonesia
    :type i: Integer
    :rtype ans: String
    """

    # Return string
    ans = ''

    # Recursively checks the integer and appends to answer string
    if i < 0: # Check for negative value
        ans = 'negatif ' + intToIndo(i * -1)
    elif i > 0 and i < 100:
        if i < 10:
            ans = ans + ' ' + digits[i]
        elif i == 10:
            ans = ans + ' sepuluh'
        elif i == 11:
            ans = ans + ' sebelas'
        elif i >= 11 and i < 20:
            ans = ans + ' ' + digits[i % 10] + ' belas'
        else:
            ans = ans + ' ' + digits[i // 10] + ' puluh ' + digits[i % 10]
    elif i >= 100 and i < 1000:
        ans = ans + ' seratus ' + intToIndo(i % 100) if i // 100 == 1 else ans + ' ' + digits[i // 100] + ' ratus ' + intToIndo(i % 100)
    elif i >= 1000 and i < 10**6:
        ans = ans + ' seribu ' + intToIndo(i % 1000) if i // 1000 == 1 else ans + ' ' + intToIndo(i // 1000) + ' ribu ' + intToIndo(i % 1000)
    elif i >= 10**6 and i < 10**9:
        ans = ans + ' ' + intToIndo(i // 10**6) + ' juta ' + intToIndo(i % 10**6)
    elif i >= 10**9:
        ans = ans + ' ' + intToIndo(i // 10**9) + ' miliar ' + intToIndo(i % 10**9)
    elif len(ans) == 0 and i == 0: # Check if nothing else and return 'nol' if so
        ans = 'nol'

    # Last check for if it ends with nol
    if ans[len(ans) - 3:len(ans)] == 'nol' and len(ans) > 3:
        ans = ans[:len(ans) - 3]

    # Returns string witout the left spaces and right spaces
    return ans.lstrip().rstrip()

