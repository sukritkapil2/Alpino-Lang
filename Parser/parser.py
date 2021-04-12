# import the libraries
import pandas as pd

# import the parse table
df_action = pd.read_excel('lalr_parse_table.xlsx', sheet_name='Sheet1')
df_goto = pd.read_excel('lalr_parse_table.xlsx', sheet_name='Sheet2')

def pop_stack(LHS, RHS, stack):

    done = False

    while(done is not True):

        if(RHS[-1] == "''"):
            break

        if(str(stack[-1]).isnumeric() == True):
            stack.pop()
        else:
            if(str(RHS[-1]) == str(stack[-1])):
                RHS.pop()
                stack.pop()

                if(len(RHS) == 0):
                    done = True
            else:
                print('Error')
                exit()

    stack.append(LHS)
    stack.append(int(df_goto[str(LHS)][stack[-2]]))

    return stack

# import the token file
tokens = open('../Lexer/output.txt')

input_string_file = open('input.txt', 'w')

# import the grammar
cfg = open('cfg.txt')

lines = tokens.readlines()
grammar_rules = cfg.readlines()

# contains the input string for the parser
tokens_list = []

# stack for performing parsing operations
stack = []

# converting tokens to appropriate terminal
switcher = {
    'identifier' : 'id',
    'integer': 'num',
    'float': 'num'
}

# get the tokens and strings from the tokens file
for line in lines:
    split_line = line.split(',')

    if(split_line[0][:5] == 'ERROR'):
        print('Lexical Error Found. Exiting ...')
        exit()

    token = split_line[0][3:]
    string = split_line[1][8:]

    # the string is ,
    if(len(string) == 0):
        string = ','

    if(token == 'keyword' or token == 'delimiter' or token == 'operator' or token == 'assignment'):
        tokens_list.append(string)
    else:
        tokens_list.append(switcher.get(token))

for token in tokens_list:
    input_string_file.write(str(token) + ' ')

tokens_list.append('$')

# Parsing Process

# append a 0 to the stack
stack.append(0)
counter = 0

while(counter < len(tokens_list)):

    num = stack[-1]
    token_part = str(tokens_list[counter])

    print(f"Table Entry [{token_part}][{num}]")

    val = df_action[token_part][num]

    if(val == 'acc'):
        print('\n[SUCCESS] String Accepted!\n')
        exit()

    if(str(val).find('/') != -1):
        val = str(val).split('/')[0].strip(" ")
        
    # if it is a shift action
    if(str(val)[0] == 's'):
        stack.append(token_part)
        stack.append(int(str(val)[1:]))
        counter += 1
    # if it is a reduce action
    else:
        rule_num = int(str(val)[1:])
        rule = grammar_rules[rule_num].split('->')

        RHS = str(rule[1]).lstrip().rstrip().split(' ')
        LHS = str(rule[0]).rstrip()

        stack = pop_stack(LHS, RHS, stack)

    print(stack)