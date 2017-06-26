ccminus
this is a ccm test demo on ccl booddk
use the two way scanner
##################################################
keyword: 
else if int return void while
##################################################
special symbol :
+ - * / < <= > >= == != = ; , () []{} 
#################################################
other tokens :
ID = letter letter*
NUM = digit digit*
letter = [a-z][A-Z]
digit = [0-9]
###############################################
while space :blank,newlines,tabs
##############################################
comment: //
#############################################

#####################################################
following syntax check
1 find the parse table,hand write or user some algorithm to find
2 find the syntax_tree this is very important ,after that use can do run time work
3 from the syntax_tree generate the code 
4 run the code 
###################################################
1 find the first set.
2 find the follow set.
3 use map to present the ll(1) parse select table. eg:map<none terminal,token>->production
3 find the parse stack.
