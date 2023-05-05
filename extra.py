blank = [' ', '\n', '\t']
connectable = ['=', '!', '<', '>', ':', '*', '/', '+', '-', '&', '|']
connect_equal = ['!', '/', '=']
connect_equal_or_self = ['>', '<', ':', '+', '&', '|', '*']
connect_equal_or_self_or_other = ['-']
independent = ['(', ')', '{', '}', '[', ']', ';', '?', '#', '.']


def isSpecial(char) -> bool:
    return (char in blank) or (char in connectable) or (char in independent)


def nextChar(char) -> list:
    if (char not in connectable):
        return []
    if (char in connect_equal):
        return ['=']
    if (char in connect_equal_or_self):
        return ['=', char]
    if (char == '-'):
        return ['=', '-', '>']
    return []

with open('string.cpp', 'r') as file:
    line_codes = file.readlines()

def extraline(code):
    array = []
    string = ''
    for index, item in enumerate(code):
        if item in blank:
            if len(string):
                array.append(string)
                string = ''
            continue
        if item in independent:
            if len(string):
                array.append(string)
                string = ''
            array.append(item)
            continue
        if item in connectable and code[index + 1] not in nextChar(item):
            string += item
            if len(string):
                array.append(string)
                string = ''
            else:
                array.append(item)
            continue
        if item in connectable and code[index + 1] in nextChar(item):
            if len(string):
                array.append(string)
                string = ''
            string += item
            continue
        string += item
        if isSpecial(code[index + 1]):
            array.append(string)
            string = ''
    return array

for index, item in enumerate(line_codes):
    array = extraline(item)
    print('第', index + 1, '行', '\t', '关键字数量=', len(array), '\t', end='')
    for word in array:
        print(word, ' ', end='')
    print()
