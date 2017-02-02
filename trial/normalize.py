"""
Normalize a scanner output file so that we can 'diff' outputs
from scanners with different token names and different handling 
of quotation marks.  

Input looks like this: 
5  CLASS "class"
5  IDENT "Robot"
5  ( "("
5  ) ")"
5  { "{"

Normalized output throws away middle column and strips quotes from 
third column.

Usage:   cat srcfile | python3 normalize.py >destfile
"""

import sys

for line in sys.stdin:
    if len(line) < 2 or not line[0] in "0123456789": 
        print(line.strip())
        continue
    ## First field can be isolated by splitting at whitespace
    fields = line.split()
    line_no = fields[0]
    ## Third field can be isolated by splitting at first quote
    pre, quo, yytext = line.partition('"')
    matched = yytext.strip().strip('"')
    print("{}: {}".format(line_no, matched))
    
