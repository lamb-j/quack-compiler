UNAME := $(shell uname)
HOSTNAME := $(shell hostname)
ifeq ($(UNAME), Linux)
CCC= clang++
CCFLAGS= -std=c++11 -I /usr/include/llvm-3.9 -I /usr/include/llvm-c-3.9  -Wno-deprecated-register 
CCLIBS= -lfl
LLVM_CONFIG=llvm-config
endif
ifeq ($(UNAME), Darwin)
CCC= clang++
CCFLAGS= -Wno-deprecated-register -std=c++11 -I/usr/local/Cellar/llvm/3.9.1/include
CCLIBS= -ll 
LLVM_CONFIG=llvm-config
endif
ifeq ($(HOSTNAME), ix-xenial)
CCC=  ~michal/tools/llvm/clang+llvm-3.9.1-x86_64-linux-gnu-ubuntu-16.04/bin/clang++
CCFLAGS= -Wno-deprecated-register -std=c++11 -I /home/faculty/michal/tools/llvm/clang+llvm-3.9.1-x86_64-linux-gnu-ubuntu-16.04/include 
CCLIBS= -ll 
LLVM_CONFIG=~michal/tools/llvm/clang+llvm-3.9.1-x86_64-linux-gnu-ubuntu-16.04/bin/llvm-config
endif

LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

quack: y.tab.o lex.yy.o quack.o class_tree.o print_AST.o build_classTree.o type_checks.o codegen.o defaults.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o quack.o class_tree.o print_AST.o build_classTree.o type_checks.o codegen.o defaults.o -o quack `${LLVM_CONFIG} --cppflags --ldflags --system-libs --libs core` ${CCLIBS} 

quack.o: quack.cpp quack.h
	${CCC} ${CCFLAGS} -c quack.cpp 
class_tree.o: class_tree.cpp
	${CCC} ${CCFLAGS} -c class_tree.cpp
print_AST.o: print_AST.cpp
	${CCC} ${CCFLAGS} -c print_AST.cpp
build_classTree.o: build_classTree.cpp
	${CCC} ${CCFLAGS} -c build_classTree.cpp
type_checks.o: type_checks.cpp
	${CCC} ${CCFLAGS} -c type_checks.cpp
codegen.o: codegen.cpp
	${CCC} ${CCFLAGS} -c codegen.cpp 
defaults.o: defaults.cpp
	${CCC} ${CCFLAGS} -c defaults.cpp 
y.tab.o: quack.y
	${YACC} ${YFLAGS} quack.y
	${CCC} ${CCFLAGS} y.tab.c -c 
lex.yy.o: quack.l
	${LEX} $(LFLAGS) quack.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o quack *.ll
