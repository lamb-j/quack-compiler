CCC = g++
UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
CCFLAGS= -O2 -std=c++11 
CCLIBS= -lfl
endif
ifeq ($(UNAME), Darwin)
CCFLAGS= -std=c++11 
CCLIBS= -ll
endif
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

quack: y.tab.o lex.yy.o quack.o class_tree.o print_AST.o build_classTree.o type_checks.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o quack.o class_tree.o print_AST.o build_classTree.o type_checks.o -o quack ${CCLIBS}

quack.o: quack.cpp quack.h
	${CCC} -c quack.cpp 
class_tree.o: class_tree.cpp
	${CCC} -c class_tree.cpp
print_AST.o: print_AST.cpp
	${CCC} -c print_AST.cpp
build_classTree.o: build_classTree.cpp
	${CCC} -c build_classTree.cpp
type_checks.o: type_checks.cpp
	${CCC} -c type_checks.cpp
y.tab.o: quack.y
	${YACC} ${YFLAGS} quack.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: quack.l
	${LEX} $(LFLAGS) quack.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o quack
