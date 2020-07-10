import sys
import zlib
import os

#Step 1
a = os.getcwd() #a is the original path
b = False #b represents whether there is .git or not

while a != "": #check while there are no more parent directories
    c = os.listdir(a) #c is the current directory

    if ".git" in c: #if .git is found
        b = True #change b to true
        break #break out of loop

    d = a.rfind("/") #d is where the parent directory begins
    a = a[:d] #change current directory to the parent

if not b: #if .git is not found
    sys.stderr.write("Not inside a Git repository") #print error message
    exit(1) #exit

#Step 2
e = a + "/.git/refs/heads" #e is the directory of the branches
f = os.listdir(e) #f holds the list of local branc names
