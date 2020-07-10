#!/usr/bin/python

#import the required packages/libraries
import sys, random, string, argparse
from optparse import OptionParser

#return a list containing all the lines of the file
def readFiles(filepath):
    with open(filepath, mode = 'r') as ffile:
        llist = [lines.strip() for lines in ffile]
    return llist

#define the class
class shuffleLines:
    def __init__(self, lines):
        self.llist = lines[:]
        self.lnum = len(lines)

    #shuffle the lines in the list
    def shufLines(self, onum = None, replace = False):
        if replace:
            if onum == None:
                return random.choice(self.llist)
            else:
                choice = []
                for _ in range(onum):
                    choice.append(random.choice(self.llist))
                return choice
        else:
            if onum == None:
                choice = self.llist[:]
                random.shuffle(choice)
                return choice
            else:
                if onum > self.lnum:
                    return random.sample(self.llist, self.lnum)
                else:
                    return random.sample(self.llist, onum)

#define the main function
def main():
    usage_msg = """shuf [option] [file]
Write to stdout with a file present, otherwise read stdin."""
    opt = OptionParser(usage=usage_msg)
    opt.add_option("-i",
                   "--input-range",
                       action = "store",
                   dest = "ipRange",
                   default = None,
                       type = "string",
                       help = "treat each number low through high as input line\n")
    opt.add_option("-n",
                   "--head-count",
                       action = "store",
                   dest = "hdCount",
                   default = None,
                       help = "output at most count lines\n")
    opt.add_option("-r",
                   "--repeat",
                      action = "store_true",
                   dest = "Replace",
                   default = False,
                      help = "output lines can be repeated\n")
    option, argument = opt.parse_args(sys.argv[1:])

    opti = option.ipRange
    optn = option.hdCount
    optr = option.Replace

    #deal with the -i option
    if opti != None:
        if len(argument) != 0:
            opt.error("too many operands".
                         format(argument[0]))

        lowhigh = opti.split('-', 1)
        if len(lowhigh) == 1:
            opt.error("input range problem".
                         format(lowhigh[0]))
        try:
            low = int(lowhigh[0])
        except:
            opt.error("input range problem".
                         format(lowhigh[0]))
        try:
            high = int(lowhigh[1])
        except:
            opt.error("input range problem".
                         format(lowhigh[1]))
        if low > high + 1:
            opt.error("input range problem".
                         format(opti))

        llines = list(range(low, high + 1))
    else:
        if len(argument) > 1:
            opt.error("too many operands".
                         format(argument[1]))
        elif (not argument):
            try:
                llines = sys.stdin.read().splitlines()
            except:
                opt.error("no input")
        elif argument[0] == '-':
            try:
                llines = sys.stdin.read().splitlines()
            except:
                opt.error("no input")
        else:
            FILE_PATH = str(argument[0])
            try:
                temp_f = open(FILE_PATH, 'r')
                temp_f.close()
            except:
                opt.error("wrong file".
                             format(FILE_PATH))
            llines = readFiles(FILE_PATH) 

    #deal with the -n option
    if optn != None:
        try:
            nout = int(optn)
        except:
            opt.error("line count problem".
                         format(optn))
        if nout <= -1:
            opt.error("line count problem".
                         format(nout))

    shuffl = shuffleLines(llines)

    #deal with the -r option
    if optr:
        if not llines:
            opt.error("no lines")
        if optn == None:
            while(True):
                sys.stdout.write(str(shuffl.shufLines(replace = True)) + '\n')
        else:
            output = shuffl.shufLines(onum = nout,
                                           replace = True)
            for item in output:
                sys.stdout.write(str(item) + '\n')
    else:
        if optn == None:
            output = shuffl.shufLines()
            for item in output:
                sys.stdout.write(str(item) + '\n')
        else:
            output = shuffl.shufLines(onum = nout)
            for item in output:
                sys.stdout.write(str(item) + '\n')

if __name__ == "__main__":
    main()
