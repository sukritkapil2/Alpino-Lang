# import the libraries
from parser_functions import *

# get the tokens and strings from the tokens file
tokens_list = make_tokens_list(input_string_file)

# append a 0 to the stack
begin_parsing(tokens_list)