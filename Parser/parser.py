# import the libraries
import pandas as pd

# import the parse table
df = pd.read_excel('lalr_parse_table.xlsx')

# import the token file
tokens = open('../Lexer/output.txt')

lines = tokens.readlines()

# contains the input string for the parser
tokens_list = []

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
    print(token)