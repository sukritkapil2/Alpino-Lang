# Roadmap of making a new language

## Lexer

A lexer takes in the language and scans through it. It appropriately takes out lexemes from the input code and assigns them the correct tokens as decided by the language maker. These tokens are then used in the syntactical analysis of the language.

## How to construct a lexer ?

With respect to this project, for the alpino language, we have a driver code that scans through the input program and appropriately according to some rules seperates out the lexemes. These lexems are then sent to the lexer which decides the token for the received lexeme and sends it back to the driver which then prints it out.

## Step by step lexing process

* Driver starts scanning the input program
* Driver has a logic according to which it finds that the lexeme starts here and ends here and then it sends it to the lexer.
* The lexer receives the lexeme and finds the appropriate token and returns it back to the driver.
* The driver prints the token and the line number.