CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

quack: y.tab.o lex.yy.o quack.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o quack.o -o quack -lfl

quack.o: quack.cpp quack.h
	${CCC} -c quack.cpp
y.tab.o: quack.y
	${YACC} ${YFLAGS} quack.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: quack.l
	${LEX} $(LFLAGS) quack.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o quack
