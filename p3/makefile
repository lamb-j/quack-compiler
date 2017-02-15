CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

quack: y.tab.o lex.yy.o quack.o class_tree.o print_AST.o evaluate_AST.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o quack.o class_tree.o print_AST.o evaluate_AST.o -o quack -lfl

quack.o: quack.cpp quack.h
	${CCC} -c quack.cpp 
class_tree.o: class_tree.cpp
	${CCC} -c class_tree.cpp
print_AST.o: print_AST.cpp
	${CCC} -c print_AST.cpp
evaluate_AST.o: evaluate_AST.cpp
	${CCC} -c evaluate_AST.cpp
y.tab.o: quack.y
	${YACC} ${YFLAGS} quack.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: quack.l
	${LEX} $(LFLAGS) quack.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o quack
