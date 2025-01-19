# lexical-analyzer
Report: Steps for Lexical Analyzer Implementation

Introduction

This report provides detailed steps for lexical analyzer development without using the Lex tool, based only on the C programming language. The purpose of the task is to develop a program that can recognize and categorize lexical components of the source program, or syntax elements.

Goals

Identify keywords, identifiers, numerical constants, operators, and delimiters.

Handle unknown characters.

Ensure good code structure with perspectives of future lexical analyzer enhancements.

Realization Steps

Analyze the demand :

Understand the types of lexical components that the program has to identify:

keywords – if, else, int, float, etc.

identifier – variable and function names.

numbers – integer and float constants.

operators – +, -, *, /, =, etc.

delimiters – ;, ,, (, ), {, }.

others – unknown characters.

Project creation :

we c language 

Implement the next states:

Begin – Identifies what type of token the next symbol belongs to.

Inside identifier – Accumulating set of alphanumerics.

Inside number – Accumulating set of digits – possibly with a a’s.

Inside operator – Recognize only one character.

Inside delimiter – Recognize only one character.

Implementation 

Define structures:

choose constants for keywords.

define utility functions to check the keyword and classify the tokens.

handling whitespaces and non-printables.

States handling:

Use the start state to decide what type of token the next symbol belongs to:

choose others as unknown characters.

Processing the tokens :

Accumulate the characters in a buffer until the token is fully formed.

Call a function to classify and display the token.

Testing and validation :

Create a source file with the following:

keywords – int, return.

identifiers – main, variable.

numbers – 123, 45.67.

operators +, =.

delimiters ;, (, ), {, }.

Run the lexical analyzer and check if each token is properly recognized and classified.

Code Example :

You will find the source file in my github

