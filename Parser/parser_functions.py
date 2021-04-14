import pandas as pd
import math
import pydot

# converting tokens to appropriate terminal
switcher = {
    'identifier' : 'id',
    'integer': 'num',
    'float': 'num'
}

# open all the necessary files
df_action = pd.read_excel('lalr_parse_table.xlsx', sheet_name='Sheet1')
df_goto = pd.read_excel('lalr_parse_table.xlsx', sheet_name='Sheet2')
tokens = open('../Lexer/output.txt', 'r')
input_string_file = open('input.txt', 'w')
parsed_output_file = open('parsed_syntax.txt', 'w')
cfg = open('cfg.txt')

class Node:

    def __init__(self, data):
        self.children = []
        self.data = data

    def add_child(self, node):
        self.children.append(node)

def pop_stack(LHS, RHS, stack):

    LHS_node = Node(LHS)

    done = False
    while(done is not True):
        if(RHS[-1] == "''"):
            LHS_node.add_child(Node(''))
            break
        if(str(stack[-1]).isnumeric() == True):
            stack.pop()
        else:
            if(str(RHS[-1]) == str(stack[-1].data)):

                LHS_node.add_child(stack[-1])

                RHS.pop()
                stack.pop()

                if(len(RHS) == 0):
                    done = True
            else:
                print('Error')
                exit()
                
    stack.append(LHS_node)
    stack.append(int(df_goto[str(LHS)][stack[-2]]))
    return stack
    
def get_error_lines():
    lines = tokens.readlines()
    errors = []

    for line in lines:
        split_line = line.split(',')
        if(split_line[0][:5] == 'ERROR'):
            errors.append(str(split_line[2][12:]).strip(' ')[:-1])

    return errors

def make_tokens_list():
    

    errors = get_error_lines()

    tokens = open('../Lexer/output.txt', 'r')
    tokens_list = []
    lines = tokens.readlines()

    for line in lines:
        split_line = line.split(',')
        token = split_line[0][3:]
        string = split_line[1][8:]

        line_number = 0

        # the string is ,
        if(len(string) == 0):
            string = ','
            line_number = str(split_line[3][12:]).strip(' ')[:-1]
        else:
            line_number = str(split_line[2][12:]).strip(' ')[:-1]
        
        if(line_number not in errors):
            if(token == 'keyword' or token == 'delimiter' or token == 'operator' or token == 'assignment'):
                tokens_list.append(string)
            else:
                tokens_list.append(switcher.get(token))

    for token in tokens_list:
        input_string_file.write(str(token) + ' ')

    tokens_list.append('$')
    input_string_file.write('$')

    return tokens_list


def begin_parsing(tokens_list):

    stack = []
    grammar_rules = cfg.readlines()

    stack.append(0)

    counter = 0

    while(counter < len(tokens_list)):
        num = stack[-1]

        token_part = str(tokens_list[counter])
        token_node = Node(token_part)

        print(f"Table Entry [{token_part}][{num}]")

        val = df_action[token_part][num]

        if(val == 'acc'):
            print('\n[SUCCESS] String Accepted!\n')
            return stack[1]
        
        if(str(val) == 'nan'):
            print("\n[ERROR] Popping Stack and Skipping till the safe symbol...\n")
            
            if(tokens_list[counter] == ';' or tokens_list[counter] == '}'):
                counter += 1

            while(counter < len(tokens_list) and (tokens_list[counter] != ';' and tokens_list[counter] != '}')):
                counter += 1
            counter += 1
            if(counter >= len(tokens_list)-1):
                print("\nEOF reached, no valid statements found after a safe symbol...\n")
                break
            stack.clear()
            stack.append(0)
            
            val = df_action[tokens_list[counter]][0]

            token_part = str(tokens_list[counter])
            token_node = Node(token_part)
        
        if(str(val).find('/') != -1):
            val = str(val).split('/')[0].strip(" ")

        # if it is a shift action
        if(str(val)[0] == 's'):
            stack.append(token_node)
            stack.append(int(str(val)[1:]))
            counter += 1
        # if it is a reduce action
        else:
            rule_num = int(str(val)[1:])
            rule = grammar_rules[rule_num].split('->')

            RHS = str(rule[1]).lstrip().rstrip().split(' ')
            LHS = str(rule[0]).rstrip()

            stack = pop_stack(LHS, RHS, stack)

        for item in stack:
            if(str(item).isnumeric() == True):
                print(item, end = ", ")
            else:
                print(item.data, end = ", ")
        print()

    return stack[1]


def draw_tree(tree, level):
    for i in range(0, level):
        parsed_output_file.write("    ")
    parsed_output_file.write(tree.data + "\n")

    for child in tree.children:
        draw_tree(child, level + 1)