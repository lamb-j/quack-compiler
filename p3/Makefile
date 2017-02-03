quack:	quack.l quack.y
				bison -d quack.y
				flex quack.l
				cc -o $@ quack.tab.c lex.yy.c -lfl
	
clean:
				rm lex.yy.c quack.tab.c quack.tab.h quack
