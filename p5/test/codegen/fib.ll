; ModuleID = 'quack llvm'
source_filename = "quack llvm"

@0 = private unnamed_addr constant [12 x i8] c"value = %d\0A\00"

declare i32 @printf(i8*, ...)

define i32 @PLUS(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %addtmp = add i32 %x_load, %y_load
  ret i32 %addtmp
}

define i32 @MINUS(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %minus_tmp = sub i32 %x_load, %y_load
  ret i32 %minus_tmp
}

define i32 @TIMES(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %multmp = mul i32 %x_load, %y_load
  ret i32 %multmp
}

define i32 @DIVIDE(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %divtmp = sdiv i32 %x_load, %y_load
  ret i32 %divtmp
}

define i1 @ATMOST(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %cmptmp = icmp ule i32 %x_load, %y_load
  ret i1 %cmptmp
}

define i1 @ATLEAST(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %cmptmp = icmp uge i32 %x_load, %y_load
  ret i1 %cmptmp
}

define i1 @LESS(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %cmptmp = icmp ult i32 %x_load, %y_load
  ret i1 %cmptmp
}

define i1 @MORE(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %cmptmp = icmp ugt i32 %x_load, %y_load
  ret i1 %cmptmp
}

define i1 @EQUALS(i32 %x, i32 %y) {
entry:
  %x_ptr = alloca i32
  %y_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  store i32 %y, i32* %y_ptr
  %x_load = load i32, i32* %x_ptr
  %y_load = load i32, i32* %y_ptr
  %cmptmp = icmp eq i32 %x_load, %y_load
  ret i1 %cmptmp
}

define i32 @PRINT(i32 %this) {
entry:
  %calltemp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @0, i32 0, i32 0), i32 %this)
  ret i32 %calltemp
}

define i32 @fib(i32 %x, i32 %this) {
entry:
  %x_ptr = alloca i32
  store i32 %x, i32* %x_ptr
  %this_ptr = alloca i32
  store i32 %this, i32* %this_ptr
  %load_var_ptr = load i32, i32* %x_ptr
  %calltmp = call i1 @ATMOST(i32 %load_var_ptr, i32 2)
  %if_cond = icmp eq i1 %calltmp, true
  br i1 %if_cond, label %if_body, label %else_body

if_body:                                          ; preds = %entry
  ret i32 1
  br label %if_cont

else_body:                                        ; preds = %entry
  %load_var_ptr1 = load i32, i32* %x_ptr
  %calltmp2 = call i32 @MINUS(i32 %load_var_ptr1, i32 1)
  %calltmp3 = call i32 @fib(i32 %calltmp2, i32 0)
  %load_var_ptr4 = load i32, i32* %x_ptr
  %calltmp5 = call i32 @MINUS(i32 %load_var_ptr4, i32 2)
  %calltmp6 = call i32 @fib(i32 %calltmp5, i32 0)
  %calltmp7 = call i32 @PLUS(i32 %calltmp3, i32 %calltmp6)
  ret i32 %calltmp7
  br label %if_cont

if_cont:                                          ; preds = %else_body, %if_body
  ret i32 0
}

define i32 @main() {
entry:
  %calltmp = call i32 @fib(i32 10, i32 0)
  %calltmp1 = call i32 @PRINT(i32 %calltmp)
  ret i32 0
}
