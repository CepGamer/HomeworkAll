import string
import sys

def removeRule(RulesCreation, rule):
    for item in RulesCreation:
        toRem = []
        for x in item.Prod:
            if rule.Var in x:
                toRem += [x]
        for x in toRem:
            item.Prod.remove(x)
            if item.Prod == []:
                removeRule(RulesCreation, item)
    if rule in RulesCreation:
        RulesCreation.remove(rule)

'''
def delEpsilon(RulesCreation):
    """

    :param RulesCreation:
    :type RulesCreation: list of [CreationRule]
    :return:
    """
    def renFirst(x, name, new):
        for item in range(0, len(x) - 1):
            if x[item] == name:
                x[item] = new
                return x
        return x
    def convert(epsilon, item, flag):
        toRem = []
        toRet = False
        #   If epsilon rule occurs in production
        for itemProd in item.Prod:
            for x in itemProd:
                if epsilon.Var == x:
                    toRet = True
                    temp = renFirst(itemProd[:], x, x + '\'')
                    if not flag and not [temp] in item.Prod:
                        item.Prod += [temp]
                    temp = itemProd[:]
                    temp.remove(x)
                    if temp != [] and temp != None and not [temp] in item.Prod:
                        item.Prod += [temp]
                    # item.Prod.remove(itemProd)
                    if itemProd in toRem:
                        toRem += [itemProd]
            for x in toRem:
                item.Prod.remove(x)
        return toRet

    toDel = []
    toAdd = []
    for epsilon in RulesCreation:
        # If only epsilon rule - we delete it
        flag = len(epsilon.Prod) == 1
        # Search epsilon rules
        if [""] in epsilon.Prod:
            #   Check if epsilon rule is starting rule
            if epsilon.Var == RulesCreation[0].Var:
                continue
            #   Check all occurrences
            for item in RulesCreation:
                cond = convert(epsilon, item, flag)
                while cond:
                    cond = convert(epsilon, item, flag)
            if flag:
                toDel += [epsilon]
            else:
                epsilon.Prod.remove([""])
                epsilon.Var += '\''
    # Delete all epsilon non-terminals
    for epsilon in toDel:
        removeRule(RulesCreation, epsilon)
    return RulesCreation
'''

def delEpsilon(RulesCreation):
    def findEpsilon():
        toRet = []
        toAdd = []
        changed = True

        for x in RulesCreation:
            if [""] in x.Prod or [] in x.Prod:
                toRet += [x]

        while changed:
            changed = False
            for x in RulesCreation:
                if x in toRet:
                    continue
                for lst in x.Prod:
                    chk = True
                    for item in lst:
                        check = False
                        for eps in toRet:
                            check = check or (eps.Var == item)
                            if check:
                                break
                        chk = check and chk
                    if chk:
                        toAdd += [x]
                        changed = True
            if changed:
                toRet += toAdd

        return toRet

    epsProds = findEpsilon()
    for x in RulesCreation:
        i = 0
        while i < len(x.Prod):
            for epsProd in epsProds:
                if epsProd.Var in x.Prod[i]:
                    tmp = x.Prod[i][:]
                    tmp.remove(epsProd.Var)
                    x.Prod += [tmp]
            i += 1

    for x in RulesCreation:
        i = 0
        while i < len(x.Prod):
            rule = x.Prod[i]
            if rule == [""] or rule == []:
                x.Prod.remove(rule)
            else:
                i += 1

    if RulesCreation[0] in epsProds:
        RulesCreation[0].Prod += ['']

    return RulesCreation

'''
def delCycles(RulesCreation):
    def addToCyclic(cyclic, pair):
        if not (pair in cyclic):
            cyclic += [pair]
        return cyclic

    changed = True
    while changed:
        cyclicRules = []
        toRem = []
        changed = False
        for rule in RulesCreation:
            for x in rule.Prod:
                # Check whether non-term
                if x == [""]:
                    continue
                if len(x) == 1 and x[0][0] in string.ascii_uppercase:
                    tmp = (rule.Var, x[0])
                    changed = True
                    # Add cycle
                    addToCyclic(cyclicRules, tmp)
                    # Update all cycles
                    # for (l, r) in cyclicRules:
                    #     if l == x[0]:
                    #         cyclicRules = addToCyclic(cyclicRules, (rule.Var, r))
                    #     if r == rule.Var:
                    #         cyclicRules = addToCyclic(cyclicRules, (l, x[0]))
        # Don't delete A -> A rules
        cyclicRules = filter(lambda (l, r): l != r, cyclicRules)
        if cyclicRules == []:
            return RulesCreation
        for (l, r) in cyclicRules:
            left = None
            right = None
            # find left and right
            for i in RulesCreation:
                if i.Var == l:
                    left = i
                elif i.Var == r:
                    right = i
            # move right prods to left
            for i in right.Prod:
                if not (i in left.Prod) and not (i != [left.Var]):
                    left.Prod += [i]
            left.Prod.remove([r])
    return RulesCreation
'''

def delCycles(RulesCreation):
    toRet = []
    def findCycles(toRet):
        def addCycles(var, cycle, toRet):
            toAdd = []
            for (l, r) in toRet:
                if r == var.Var:
                    toAdd += [(l, cycle)]
            toRet += toAdd

        for x in RulesCreation:
            toRet += [(x.Var, x.Var)]
        for x in RulesCreation:
            for rule in x.Prod:
                if len(rule) == 1 and nonTerm(rule[0]):
                    addCycles(x, rule[0], toRet)
        return toRet

    def addProds(Var, prodVar):
        for prod in prodVar.Prod:
            if not (prod in Var.Prod):
                Var.Prod += [prod]
        return Var

    cycles = findCycles(toRet)
    for x in RulesCreation:
        for y in RulesCreation:
            if (x.Var, y.Var) in cycles:
                x = addProds(x, y)
    for x in RulesCreation:
        i = 0
        while i < len(x.Prod):
            if len(x.Prod[i]) == 1 and nonTerm(x.Prod[i][0]):
                x.Prod.remove(x.Prod[i])
            else:
                i += 1

    return RulesCreation


def delNoProd(RulesCreation):
    Productive = []
    for i in RulesCreation:
        for x in i.Prod:
            if noNonTerms(x):
                Productive += [i.Var]
                continue
    prev = len(Productive)
    if prev == 0:
        print("FAIL")
        exit()
    while True:
        for i in RulesCreation:
            flag = False
            if i.Var in Productive:
                continue
            for x in i.Prod:
                if flag:
                    break
                for prod in Productive:
                    if prod in x:
                        Productive += [i.Var]
                        flag = True
                        break
        if len(Productive) == prev:
            break
        else:
            prev = len(Productive)
    toRem = []
    for item in RulesCreation:
        if not(item.Var in Productive):
            toRem += [item]
    for x in toRem:
        removeRule(RulesCreation, x)
    return RulesCreation

def delNoReach(RulesCreation):
    def dfs(reachable, toReach):
        if toReach in reachable:
            return reachable
        reachable +=[toReach]
        for x in RulesCreation:
            if x.Var == toReach:
                for prod in x.Prod:
                    for vals in prod:
                        if nonTerm(vals):
                            reachable = dfs(reachable, vals)
                break
        return reachable
    reachable = dfs([], RulesCreation[0].Var)
    toDel = []
    for x in RulesCreation:
        if not(x.Var in reachable):
            toDel += [x]
    for x in toDel:
        removeRule(RulesCreation, x)
    return RulesCreation

def reduceMany(RulesCreation):
    toAdd = []
    ComplexNonTerm = 1
    for item in RulesCreation:
        for prod in item.Prod:
            if len(prod) > 2:
                terms = prod[1:]
                rule = 'ComplexNonTerm' + str(ComplexNonTerm) + ' -> ' + " ".join(terms)
                ComplexNonTerm += 1
                x = CreationRule(rule)
                prod[1:] = [x.Var]
                RulesCreation += [x]
    return RulesCreation

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
    if toCheck[0] in string.ascii_uppercase:
        return True
    return False

class CreationRule:
    """class representing basic grammar rule"""
    # def __init__(self, arg):
    # super(Symbol, self).__init__()
    # self.arg = arg
    def __init__(self, rule):
        self.Prod = []
        self.Rule = rule
        splitted = rule.split(" ")
        self.Var = splitted[0]
        temp = splitted[-1]

        i = 0
        self.Prod = [splitted[2:]]
        # while i < len(temp):
        #     if temp[i] in string.ascii_uppercase:
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
    def fromRule(self, Rule):
        self.Prod = Rule.Prod
        self.Rule = Rule.Rule
        self.Var = Rule.Var
        return self

    def addRule(self, rule):
        tmp = rule.split(" ")[2:]
        if tmp in self.Prod:
            return
        self.Prod += [tmp]

    def prints(self):
        toPrint = []
        for prod in self.Prod:
            toPrint += [self.Var + ' -> ' + " ".join(prod)]
        return toPrint

def convTerm(RulesCreation):
    # insert term in list of creation
    def insert(terms, sym):
        for x in terms:
            if sym == x:
                return terms
        return terms + [sym]
    terms = []
    for item in RulesCreation:
        for prod in item.Prod:
            for sym in prod:
                if (not nonTerm(sym)) and sym != '':
                    terms = insert(terms, sym)
    symRules = []
    for sym in terms:
        rule = sym.upper() + 'Term -> ' + sym
        newVar = CreationRule(rule)
        symRules += [newVar]
    for item in RulesCreation:
        for prod in item.Prod:
            if len(prod) < 2:
                continue
            for sym in prod:
                if (not nonTerm(sym)) and sym != '':
                    for x in symRules:
                        if x.Prod[0] == [sym]:
                            prod[prod.index(sym)] = x.Var
    return RulesCreation + symRules

def exists(RulesCreation):
    for item in RulesCreation:
        toRem = []
        for x in item.Prod:
            for term in x:
                if not nonTerm(term):
                    continue
                found = False
                for find in RulesCreation:
                    if term == find.Var:
                        found = True
                        break
                if not found:
                    toRem += [x]
                    break
        for x in toRem:
            item.Prod.remove(x)
    toRem = []
    for x in RulesCreation:
        if x.Prod == [[]]:
            toRem += [x]
    for x in toRem:
        removeRule(RulesCreation,x)
    return RulesCreation

RulesCreation = []

FileName = sys.argv[1]
grammarFile = open(FileName, "r").read().split("\n")

# Getting rules and variables from grammar
for item in grammarFile:
    if item == "":
        break
    temp = item.split(" ")
    i = True
    for x in RulesCreation:
        if x.Var == temp[0]:
            x.addRule(item)
            i = False
            break
    if i:
        temp = CreationRule(item)
        RulesCreation += [temp]

for i in RulesCreation:
    i.Prod = map(lambda a: [''] if a == [] else a, i.Prod)

RulesCreation = delEpsilon(RulesCreation)
RulesCreation = delCycles(RulesCreation)
RulesCreation = delNoProd(RulesCreation)
RulesCreation = delNoReach(RulesCreation)
RulesCreation = convTerm(RulesCreation)
RulesCreation = reduceMany(RulesCreation)
# RulesCreation = exists(RulesCreation)
RulesCreation = delNoReach(RulesCreation)

toPrint = []
if RulesCreation == []:
    print('FAIL')
    exit()
for i in RulesCreation[1:]:
    toPrint += i.prints()

for i in (RulesCreation[0].prints() + sorted(toPrint)):
    print(i)
