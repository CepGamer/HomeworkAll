__author__ = 'Sergey Bolotov'

import sys
import string

space = 'space'
newline = 'newline'
backslash = 'backslash'

stringEnd = '#'

FAIL = 'FAIL'

# noinspection PyMethodParameters
class CreationRule:
    """class representing basic grammar rule"""
    # def __init__(self, arg):
    # super(Symbol, self).__init__()
    # self.arg = arg
    def __init__ ( self, rule ):
        self.Prod = []
        self.Rule = rule
        splitted = rule.split(" ")
        self.Var = splitted[0]
        # temp = splitted[-1]

        i = 0
        self.Prod = [splitted[2:]]
        # while i < len(temp):
        # if temp[i] in string.ascii_uppercase:
        #         var = findVar(temp, i)
        #         if var:
        #             self.Prod += [var]
        #             i += len(var) - 1
        #         else:
        #             print("FAIL")
        #             exit()
        #     else:
        #         self.Prod +=[temp[i]]
        #     i += 1

    @classmethod
    def fromRule ( self, Rule ):
        self.Prod = Rule.Prod
        self.Rule = Rule.Rule
        self.Var = Rule.Var
        return self

    def addRule ( self, rule ):
        tmp = rule.split(" ")[2:]
        if tmp in self.Prod:
            return
        self.Prod += [tmp]

    def prints ( self ):
        toPrint = []
        for prod in self.Prod:
            toPrint += [self.Var + ' -> ' + " ".join(prod)]
        return toPrint

def noNonTerms(prod):
    if len(prod) == 0:
        return True
    if prod[0] == '':
        return True
    for item in prod:
        if item[0] in string.ascii_uppercase:
            return False
    return True

def nonTerm(toCheck):
    if toCheck == '':
        return False
    return (toCheck[0] in string.ascii_uppercase)

def First(nterm):
    global RulesCreation
    first = []
    changed = True

    while changed:
        changed = False
        for rule in nterm.Prod:
            i = 0
            temp = rule[i]
            while temp == nterm.Var:
                i += 1
                if i == len(rule):
                    continue
                else:
                    temp = rule[i]
            if not nonTerm(temp):
                if temp not in first:
                    first += [temp]
                    changed = True
            else:
                for i in First(RulesCreation[temp]):
                    if i not in first:
                        first += [i]
                        changed = True
    return first

def Follow(nterm):
    global RulesCreation
    follow = []
    changed = True

    while changed:
        changed = False
        for nterms in RulesCreation:
            for rule in RulesCreation[nterms].Prod:
                if len(rule) == 1:
                    if rule[0] == "":
                        continue
                    else:
                        if rule[0] not in follow:
                            changed = True
                            follow += [rule[0]]
                for i in range(0, len(rule) - 2):
                    if rule[i] != nterm.Var:
                        continue

                    if rule[i + 1] == '':
                        continue
                    elif not nonTerm(rule[i + 1]):
                        if rule[i + 1] not in follow:
                            changed = True
                            follow += [rule[i + 1]]
                        continue

                    temp = First(RulesCreation[rule[i + 1]])

                    # try:
                    #     temp.remove('')
                    # except:
                    #     pass
                    for item in temp:
                        if item == '':
                            continue
                        if item not in follow:
                            changed = True
                            follow += [item]

                    if '' in temp:
                        temp = Follow(RulesCreation[nterms].Var)
                        for item in temp:
                            if item not in follow:
                                changed = True
                                follow += [item]

    return follow

def printStackFail(analysisStack):
    tmp = "" if analysisStack == [] else (" ".join(analysisStack) + " ")
    print (tmp + FAIL)

def printStack(analysisStack):
    print (" ".join(analysisStack))

def analyse(stringFile):
    global RulesCreation
    global ManagementTable
    global analysisStack

    currOverview = [startTerm, stringEnd]

    analysisStack = []
    for sym in stringFile:
        while nonTerm(currOverview[0]):
            if sym not in Follow(currOverview[0]):
                printStackFail(analysisStack)
                exit()
            analysisStack += currOverview[0]
            try:
                temp = ManagementTable[(currOverview[0], sym)]
            except:
                printStackFail(analysisStack)
                exit()
            del(currOverview[0])
            currOverview = temp + currOverview
        if sym != currOverview[0]:
            printStackFail(analysisStack)
            exit()
        elif sym == stringEnd:
            printStack(analysisStack)
            return
        analysisStack += [currOverview[0]]
        del (currOverview[0])
        if currOverview == []:
            printStackFail(analysisStack)
            exit()

RulesCreation = dict([])
ManagementTable = dict([])
startTerm = ""

analysisStack = []

FileNameRules = sys.argv[1]
FileNameString = sys.argv[2]
grammarFile = open(FileNameRules, "r").read().split("\n")
stringFile = open(FileNameString, "r").read()

stringFile = stringFile\
    .replace("\\ ", space)\
    .replace("\\n", newline)\
    .replace("\\\\", backslash)

stringFile = stringFile\
    .replace(" ", "")\
    .replace("\n", "")

stringFile += stringEnd

for i in range(0, len(grammarFile)):
    grammarFile[i] = grammarFile[i]\
        .replace("\\ ", space)\
        .replace("\\n", newline)\
        .replace("\\\\", backslash)

for i in range(0, len(grammarFile)):
    item = grammarFile[i]
    if item == "":
        break
    temp = item.split(" ")
    if len(RulesCreation) == 0:
        startTerm = temp[0]
    if temp[0] == startTerm:
        temp += [stringEnd]
    if temp[0] in RulesCreation:
        RulesCreation[temp[0]].addRule(item)
    else:
        RulesCreation[temp[0]] = CreationRule(item)

for i in RulesCreation:
    temp = RulesCreation[i]
    temp.Prod = map(lambda a: [''] if a == [] else a, temp.Prod)
    for item in temp.Prod:
        if not nonTerm(item[0]):
            if (temp.Var, item[0]) in ManagementTable:
                printStackFail(analysisStack)
                exit()
            else:
                ManagementTable[(temp.Var, item[0])] = item
        else:
            first = First(RulesCreation[item[0]])
            if "" in first:
                first += Follow(item[0])

            for sym in first:
                if (temp.Var, sym) in ManagementTable:
                    printStackFail(analysisStack)
                    exit()
                else:
                    ManagementTable[(temp.Var, sym)] = item

analyse(stringFile)

tmp = First(RulesCreation['A'])
print(tmp)

tmp = Follow(RulesCreation['A'])
print(tmp)
