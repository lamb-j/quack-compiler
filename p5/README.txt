Introduction to Compilers
Winter 2017
Quack Compiler
Rajan Sawhney and Jacob Lambert

Description: 
  We have built the lexer, parser, typechecker, and code generation steps
  of a compiler for the Quack language. Our compiler takes an input program written 
  in Quack, and generates LLVM code. Lexing and parsing is done using flex/bison and C++. 
  The typechecker is written in pure C++. Finally the code generation is done using the 
  LLVM C++ API.

Usage:
  quack input.q codegen_flag[0, 1]

  Setting a codegen_flag of 1 enables code generation. Also, within quack.y, the
  DEBUG_FLAG = 0 macro can be changed to DEBUG_FLAG = 1 to enable verbose 
  details about the compilation process.

Typechecking:
  Our typechecker is robust to several different types and classes of errors. 
  Specifically, we identify and report:
    - class hierarchy errors 
    - undefined methods or classes
    - covariance and contravariance violations in method overriding
    - uninitalized variables
    - type mismatches
    - attempts to access field values outside class scope

  The following test files demonstrate quack programs that both pass and fail
  the typechecker. They can be run with the following command:

  ./quack file.q 0  (the 0 disables the codegen pass)

  Correct programs in ./test/good:
	  GoodWalk.qk
		schroedinger.qk

  Incorrect programs in ./test/bad:
	  bad_classes.qk
		bad_methods.qk
		bad_override.qk
		hands.qk
		not_a_duck.qk
		robot.qk
		SqrDecl.qk

Code Generation:
  Code generation is currently only supported for a subset of the Quack language. We
  currently support:

    - the Int class and integer operations
    - boolean expressions involving integers
		- control flow (if, elif, else, while)
    - method calls within classes

  The following Quack language features are unsupported:

    - the String class and string operations
    - the Boolean class and vairables of type Boolean
    - short-circuit evaluation 
    - Setting and accessing field variables in classes
    - class constructors with arguments "A(x : Int)"
		- dynamic dispatching

  The following test files contain only supported features, and can be used to 
  test code generation. They can be compiled and run by:

     ./quack file.q 1  (The "1" flag enables code generation)
     lli file.ll        (This compiles and executes the llvm code)

     Programs in ./test/codegen
		   fib.qk
       control_flow.qk
