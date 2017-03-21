; ModuleID = 'tmp.cpp'
source_filename = "tmp.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.12.0"

%"class.std::__1::basic_ostream" = type { i32 (...)**, %"class.std::__1::basic_ios.base" }
%"class.std::__1::basic_ios.base" = type <{ %"class.std::__1::ios_base", %"class.std::__1::basic_ostream"*, i32 }>
%"class.std::__1::ios_base" = type { i32 (...)**, i32, i64, i64, i32, i32, i8*, i8*, void (i32, %"class.std::__1::ios_base"*, i32)**, i32*, i64, i64, i64*, i64, i64, i8**, i64, i64 }
%ident_t = type { i32, i32, i32, i32, i8* }
%"class.std::__1::locale::id" = type <{ %"struct.std::__1::once_flag", i32, [4 x i8] }>
%"struct.std::__1::once_flag" = type { i64 }
%"class.std::__1::ctype" = type <{ %"class.std::__1::locale::facet", i32*, i8, [7 x i8] }>
%"class.std::__1::locale::facet" = type { %"class.std::__1::__shared_count" }
%"class.std::__1::__shared_count" = type { i32 (...)**, i64 }
%"class.std::__1::locale" = type { %"class.std::__1::locale::__imp"* }
%"class.std::__1::locale::__imp" = type opaque
%"class.std::__1::basic_ios" = type <{ %"class.std::__1::ios_base", %"class.std::__1::basic_ostream"*, i32, [4 x i8] }>
%"class.std::__1::ostreambuf_iterator" = type { %"class.std::__1::basic_streambuf"* }
%"class.std::__1::basic_streambuf" = type { i32 (...)**, %"class.std::__1::locale", i8*, i8*, i8*, i8*, i8*, i8* }
%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry" = type { i8, %"class.std::__1::basic_ostream"* }
%"struct.std::__1::iterator" = type { i8 }
%"struct.std::__1::nullptr_t" = type { i8* }
%"class.std::__1::allocator" = type { i8 }
%"class.std::__1::__libcpp_compressed_pair_imp" = type { %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep" }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep" = type { %union.anon }
%union.anon = type { %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long" }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long" = type { i64, i64, i8* }
%"class.std::__1::__compressed_pair" = type { %"class.std::__1::__libcpp_compressed_pair_imp" }
%"class.std::__1::basic_string" = type { %"class.std::__1::__compressed_pair" }
%"class.std::__1::__basic_string_common" = type { i8 }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short" = type { %union.anon.0, [23 x i8] }
%union.anon.0 = type { i8 }

@_ZNSt3__14coutE = external global %"class.std::__1::basic_ostream", align 8
@.str = private unnamed_addr constant [3 x i8] c"Hi\00", align 1
@.str.1 = private unnamed_addr constant [23 x i8] c";unknown;unknown;0;0;;\00", align 1
@0 = private unnamed_addr constant %ident_t { i32 0, i32 2, i32 0, i32 0, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.1, i32 0, i32 0) }, align 8
@_ZNSt3__15ctypeIcE2idE = external global %"class.std::__1::locale::id", align 8

; Function Attrs: norecurse ssp uwtable
define i32 @main() #0 {
  call void (%ident_t*, i32, void (i32*, i32*, ...)*, ...) @__kmpc_fork_call(%ident_t* @0, i32 0, void (i32*, i32*, ...)* bitcast (void (i32*, i32*)* @.omp_outlined. to void (i32*, i32*, ...)*))
  ret i32 0
}

; Function Attrs: nounwind ssp uwtable
define internal void @.omp_outlined.(i32* noalias, i32* noalias) #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca i32*, align 8
  %4 = alloca i32*, align 8
  store i32* %0, i32** %3, align 8
  store i32* %1, i32** %4, align 8
  %5 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) @_ZNSt3__14coutE, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0))
          to label %6 unwind label %7

; <label>:6:                                      ; preds = %2
  ret void

; <label>:7:                                      ; preds = %2
  %8 = landingpad { i8*, i32 }
          catch i8* null
  %9 = extractvalue { i8*, i32 } %8, 0
  call void @__clang_call_terminate(i8* %9) #8
  unreachable
}

; Function Attrs: ssp uwtable
define linkonce_odr dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160), i8*) #2 {
  %3 = alloca %"class.std::__1::basic_ostream"*, align 8
  %4 = alloca i8*, align 8
  store %"class.std::__1::basic_ostream"* %0, %"class.std::__1::basic_ostream"** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @_ZNSt3__111char_traitsIcE6lengthEPKc(i8* %7)
  %9 = call dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(%"class.std::__1::basic_ostream"* dereferenceable(160) %5, i8* %6, i64 %8)
  ret %"class.std::__1::basic_ostream"* %9
}

declare i32 @__gxx_personality_v0(...)

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8*) #3 {
  %2 = call i8* @__cxa_begin_catch(i8* %0) #9
  call void @_ZSt9terminatev() #8
  unreachable
}

declare i8* @__cxa_begin_catch(i8*)

declare void @_ZSt9terminatev()

declare void @__kmpc_fork_call(%ident_t*, i32, void (i32*, i32*, ...)*, ...)

; Function Attrs: ssp uwtable
define linkonce_odr dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(%"class.std::__1::basic_ostream"* dereferenceable(160), i8*, i64) #2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::ctype"*, align 8
  %5 = alloca i8, align 1
  %6 = alloca %"class.std::__1::locale"*, align 8
  %7 = alloca %"class.std::__1::basic_ios"*, align 8
  %8 = alloca i8, align 1
  %9 = alloca %"class.std::__1::locale", align 8
  %10 = alloca i8*
  %11 = alloca i32
  %12 = alloca %"class.std::__1::basic_ios"*, align 8
  %13 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  %14 = alloca %"class.std::__1::ios_base"*, align 8
  %15 = alloca %"class.std::__1::ios_base"*, align 8
  %16 = alloca i32, align 4
  %17 = alloca %"class.std::__1::basic_ios"*, align 8
  %18 = alloca i32, align 4
  %19 = alloca %"class.std::__1::ios_base"*, align 8
  %20 = alloca %"class.std::__1::basic_ios"*, align 8
  %21 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  %22 = alloca %"class.std::__1::basic_ostream"*, align 8
  %23 = alloca i8*
  %24 = alloca i32
  %25 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  %26 = alloca %"class.std::__1::basic_ostream"*, align 8
  %27 = alloca %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, align 8
  %28 = alloca %"class.std::__1::basic_ostream"*, align 8
  %29 = alloca i8*, align 8
  %30 = alloca i64, align 8
  %31 = alloca %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry", align 8
  %32 = alloca i8*
  %33 = alloca i32
  %34 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %35 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  store %"class.std::__1::basic_ostream"* %0, %"class.std::__1::basic_ostream"** %28, align 8
  store i8* %1, i8** %29, align 8
  store i64 %2, i64* %30, align 8
  %36 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  invoke void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %31, %"class.std::__1::basic_ostream"* dereferenceable(160) %36)
          to label %37 unwind label %181

; <label>:37:                                     ; preds = %3
  store %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %31, %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"** %27, align 8
  %38 = load %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"** %27, align 8
  %39 = getelementptr inbounds %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry", %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %38, i32 0, i32 0
  %40 = load i8, i8* %39, align 8
  %41 = trunc i8 %40 to i1
  br label %42

; <label>:42:                                     ; preds = %37
  br i1 %41, label %43, label %192

; <label>:43:                                     ; preds = %42
  %44 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  store %"class.std::__1::ostreambuf_iterator"* %34, %"class.std::__1::ostreambuf_iterator"** %25, align 8
  store %"class.std::__1::basic_ostream"* %44, %"class.std::__1::basic_ostream"** %26, align 8
  %45 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %25, align 8
  %46 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %26, align 8
  store %"class.std::__1::ostreambuf_iterator"* %45, %"class.std::__1::ostreambuf_iterator"** %21, align 8
  store %"class.std::__1::basic_ostream"* %46, %"class.std::__1::basic_ostream"** %22, align 8
  %47 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %21, align 8
  %48 = bitcast %"class.std::__1::ostreambuf_iterator"* %47 to %"struct.std::__1::iterator"*
  %49 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %47, i32 0, i32 0
  %50 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %22, align 8
  %51 = bitcast %"class.std::__1::basic_ostream"* %50 to i8**
  %52 = load i8*, i8** %51, align 8
  %53 = getelementptr i8, i8* %52, i64 -24
  %54 = bitcast i8* %53 to i64*
  %55 = load i64, i64* %54, align 8
  %56 = bitcast %"class.std::__1::basic_ostream"* %50 to i8*
  %57 = getelementptr inbounds i8, i8* %56, i64 %55
  %58 = bitcast i8* %57 to %"class.std::__1::basic_ios"*
  store %"class.std::__1::basic_ios"* %58, %"class.std::__1::basic_ios"** %20, align 8
  %59 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %20, align 8
  %60 = bitcast %"class.std::__1::basic_ios"* %59 to %"class.std::__1::ios_base"*
  store %"class.std::__1::ios_base"* %60, %"class.std::__1::ios_base"** %19, align 8
  %61 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %19, align 8
  %62 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %61, i32 0, i32 6
  %63 = load i8*, i8** %62, align 8
  %64 = bitcast i8* %63 to %"class.std::__1::basic_streambuf"*
  store %"class.std::__1::basic_streambuf"* %64, %"class.std::__1::basic_streambuf"** %49, align 8
  %65 = load i8*, i8** %29, align 8
  %66 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  %67 = bitcast %"class.std::__1::basic_ostream"* %66 to i8**
  %68 = load i8*, i8** %67, align 8
  %69 = getelementptr i8, i8* %68, i64 -24
  %70 = bitcast i8* %69 to i64*
  %71 = load i64, i64* %70, align 8
  %72 = bitcast %"class.std::__1::basic_ostream"* %66 to i8*
  %73 = getelementptr inbounds i8, i8* %72, i64 %71
  %74 = bitcast i8* %73 to %"class.std::__1::ios_base"*
  store %"class.std::__1::ios_base"* %74, %"class.std::__1::ios_base"** %14, align 8
  %75 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %14, align 8
  %76 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %75, i32 0, i32 1
  %77 = load i32, i32* %76, align 8
  br label %78

; <label>:78:                                     ; preds = %43
  %79 = and i32 %77, 176
  %80 = icmp eq i32 %79, 32
  br i1 %80, label %81, label %85

; <label>:81:                                     ; preds = %78
  %82 = load i8*, i8** %29, align 8
  %83 = load i64, i64* %30, align 8
  %84 = getelementptr inbounds i8, i8* %82, i64 %83
  br label %87

; <label>:85:                                     ; preds = %78
  %86 = load i8*, i8** %29, align 8
  br label %87

; <label>:87:                                     ; preds = %85, %81
  %88 = phi i8* [ %84, %81 ], [ %86, %85 ]
  %89 = load i8*, i8** %29, align 8
  %90 = load i64, i64* %30, align 8
  %91 = getelementptr inbounds i8, i8* %89, i64 %90
  %92 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  %93 = bitcast %"class.std::__1::basic_ostream"* %92 to i8**
  %94 = load i8*, i8** %93, align 8
  %95 = getelementptr i8, i8* %94, i64 -24
  %96 = bitcast i8* %95 to i64*
  %97 = load i64, i64* %96, align 8
  %98 = bitcast %"class.std::__1::basic_ostream"* %92 to i8*
  %99 = getelementptr inbounds i8, i8* %98, i64 %97
  %100 = bitcast i8* %99 to %"class.std::__1::ios_base"*
  %101 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  %102 = bitcast %"class.std::__1::basic_ostream"* %101 to i8**
  %103 = load i8*, i8** %102, align 8
  %104 = getelementptr i8, i8* %103, i64 -24
  %105 = bitcast i8* %104 to i64*
  %106 = load i64, i64* %105, align 8
  %107 = bitcast %"class.std::__1::basic_ostream"* %101 to i8*
  %108 = getelementptr inbounds i8, i8* %107, i64 %106
  %109 = bitcast i8* %108 to %"class.std::__1::basic_ios"*
  store %"class.std::__1::basic_ios"* %109, %"class.std::__1::basic_ios"** %12, align 8
  %110 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %12, align 8
  %111 = call i32 @_ZNSt3__111char_traitsIcE3eofEv() #9
  %112 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %110, i32 0, i32 2
  %113 = load i32, i32* %112, align 8
  %114 = call zeroext i1 @_ZNSt3__111char_traitsIcE11eq_int_typeEii(i32 %111, i32 %113) #9
  br i1 %114, label %115, label %147

; <label>:115:                                    ; preds = %87
  store %"class.std::__1::basic_ios"* %110, %"class.std::__1::basic_ios"** %7, align 8
  store i8 32, i8* %8, align 1
  %116 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %7, align 8
  %117 = bitcast %"class.std::__1::basic_ios"* %116 to %"class.std::__1::ios_base"*
  invoke void @_ZNKSt3__18ios_base6getlocEv(%"class.std::__1::locale"* sret %9, %"class.std::__1::ios_base"* %117)
          to label %118 unwind label %185

; <label>:118:                                    ; preds = %115
  store %"class.std::__1::locale"* %9, %"class.std::__1::locale"** %6, align 8
  %119 = load %"class.std::__1::locale"*, %"class.std::__1::locale"** %6, align 8
  %120 = invoke %"class.std::__1::locale::facet"* @_ZNKSt3__16locale9use_facetERNS0_2idE(%"class.std::__1::locale"* %119, %"class.std::__1::locale::id"* dereferenceable(16) @_ZNSt3__15ctypeIcE2idE)
          to label %121 unwind label %131

; <label>:121:                                    ; preds = %118
  %122 = bitcast %"class.std::__1::locale::facet"* %120 to %"class.std::__1::ctype"*
  %123 = load i8, i8* %8, align 1
  store %"class.std::__1::ctype"* %122, %"class.std::__1::ctype"** %4, align 8
  store i8 %123, i8* %5, align 1
  %124 = load %"class.std::__1::ctype"*, %"class.std::__1::ctype"** %4, align 8
  %125 = bitcast %"class.std::__1::ctype"* %124 to i8 (%"class.std::__1::ctype"*, i8)***
  %126 = load i8 (%"class.std::__1::ctype"*, i8)**, i8 (%"class.std::__1::ctype"*, i8)*** %125, align 8
  %127 = getelementptr inbounds i8 (%"class.std::__1::ctype"*, i8)*, i8 (%"class.std::__1::ctype"*, i8)** %126, i64 7
  %128 = load i8 (%"class.std::__1::ctype"*, i8)*, i8 (%"class.std::__1::ctype"*, i8)** %127, align 8
  %129 = load i8, i8* %5, align 1
  %130 = invoke signext i8 %128(%"class.std::__1::ctype"* %124, i8 signext %129)
          to label %143 unwind label %131

; <label>:131:                                    ; preds = %121, %118
  %132 = landingpad { i8*, i32 }
          cleanup
          catch i8* null
  %133 = extractvalue { i8*, i32 } %132, 0
  store i8* %133, i8** %10, align 8
  %134 = extractvalue { i8*, i32 } %132, 1
  store i32 %134, i32* %11, align 4
  invoke void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"* %9)
          to label %135 unwind label %140

; <label>:135:                                    ; preds = %131
  %136 = load i8*, i8** %10, align 8
  %137 = load i32, i32* %11, align 4
  %138 = insertvalue { i8*, i32 } undef, i8* %136, 0
  %139 = insertvalue { i8*, i32 } %138, i32 %137, 1
  br label %187

; <label>:140:                                    ; preds = %131
  %141 = landingpad { i8*, i32 }
          catch i8* null
          catch i8* null
  %142 = extractvalue { i8*, i32 } %141, 0
  call void @__clang_call_terminate(i8* %142) #8
  unreachable

; <label>:143:                                    ; preds = %121
  invoke void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"* %9)
          to label %144 unwind label %185

; <label>:144:                                    ; preds = %143
  %145 = sext i8 %130 to i32
  %146 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %110, i32 0, i32 2
  store i32 %145, i32* %146, align 8
  br label %147

; <label>:147:                                    ; preds = %87, %144
  %148 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %110, i32 0, i32 2
  %149 = load i32, i32* %148, align 8
  %150 = trunc i32 %149 to i8
  br label %151

; <label>:151:                                    ; preds = %147
  %152 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %34, i32 0, i32 0
  %153 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %152, align 8
  %154 = invoke %"class.std::__1::basic_streambuf"* @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(%"class.std::__1::basic_streambuf"* %153, i8* %65, i8* %88, i8* %91, %"class.std::__1::ios_base"* dereferenceable(136) %100, i8 signext %150)
          to label %155 unwind label %185

; <label>:155:                                    ; preds = %151
  %156 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %35, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* %154, %"class.std::__1::basic_streambuf"** %156, align 8
  store %"class.std::__1::ostreambuf_iterator"* %35, %"class.std::__1::ostreambuf_iterator"** %13, align 8
  %157 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %13, align 8
  %158 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %157, i32 0, i32 0
  %159 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %158, align 8
  %160 = icmp eq %"class.std::__1::basic_streambuf"* %159, null
  br i1 %160, label %161, label %191

; <label>:161:                                    ; preds = %155
  %162 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  %163 = bitcast %"class.std::__1::basic_ostream"* %162 to i8**
  %164 = load i8*, i8** %163, align 8
  %165 = getelementptr i8, i8* %164, i64 -24
  %166 = bitcast i8* %165 to i64*
  %167 = load i64, i64* %166, align 8
  %168 = bitcast %"class.std::__1::basic_ostream"* %162 to i8*
  %169 = getelementptr inbounds i8, i8* %168, i64 %167
  %170 = bitcast i8* %169 to %"class.std::__1::basic_ios"*
  store %"class.std::__1::basic_ios"* %170, %"class.std::__1::basic_ios"** %17, align 8
  store i32 5, i32* %18, align 4
  %171 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %17, align 8
  %172 = bitcast %"class.std::__1::basic_ios"* %171 to %"class.std::__1::ios_base"*
  %173 = load i32, i32* %18, align 4
  store %"class.std::__1::ios_base"* %172, %"class.std::__1::ios_base"** %15, align 8
  store i32 %173, i32* %16, align 4
  %174 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %15, align 8
  %175 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %174, i32 0, i32 4
  %176 = load i32, i32* %175, align 8
  %177 = load i32, i32* %16, align 4
  %178 = or i32 %176, %177
  invoke void @_ZNSt3__18ios_base5clearEj(%"class.std::__1::ios_base"* %174, i32 %178)
          to label %179 unwind label %185

; <label>:179:                                    ; preds = %161
  br label %180

; <label>:180:                                    ; preds = %179
  br label %191

; <label>:181:                                    ; preds = %192, %3
  %182 = landingpad { i8*, i32 }
          catch i8* null
  %183 = extractvalue { i8*, i32 } %182, 0
  store i8* %183, i8** %32, align 8
  %184 = extractvalue { i8*, i32 } %182, 1
  store i32 %184, i32* %33, align 4
  br label %195

; <label>:185:                                    ; preds = %143, %115, %161, %151
  %186 = landingpad { i8*, i32 }
          catch i8* null
  br label %187

; <label>:187:                                    ; preds = %135, %185
  %188 = phi { i8*, i32 } [ %186, %185 ], [ %139, %135 ]
  %189 = extractvalue { i8*, i32 } %188, 0
  store i8* %189, i8** %32, align 8
  %190 = extractvalue { i8*, i32 } %188, 1
  store i32 %190, i32* %33, align 4
  invoke void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %31)
          to label %194 unwind label %220

; <label>:191:                                    ; preds = %180, %155
  br label %192

; <label>:192:                                    ; preds = %191, %42
  invoke void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %31)
          to label %193 unwind label %181

; <label>:193:                                    ; preds = %192
  br label %208

; <label>:194:                                    ; preds = %187
  br label %195

; <label>:195:                                    ; preds = %194, %181
  %196 = load i8*, i8** %32, align 8
  %197 = call i8* @__cxa_begin_catch(i8* %196) #9
  %198 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  %199 = bitcast %"class.std::__1::basic_ostream"* %198 to i8**
  %200 = load i8*, i8** %199, align 8
  %201 = getelementptr i8, i8* %200, i64 -24
  %202 = bitcast i8* %201 to i64*
  %203 = load i64, i64* %202, align 8
  %204 = bitcast %"class.std::__1::basic_ostream"* %198 to i8*
  %205 = getelementptr inbounds i8, i8* %204, i64 %203
  %206 = bitcast i8* %205 to %"class.std::__1::ios_base"*
  invoke void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(%"class.std::__1::ios_base"* %206)
          to label %207 unwind label %210

; <label>:207:                                    ; preds = %195
  call void @__cxa_end_catch()
  br label %208

; <label>:208:                                    ; preds = %207, %193
  %209 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %28, align 8
  ret %"class.std::__1::basic_ostream"* %209

; <label>:210:                                    ; preds = %195
  %211 = landingpad { i8*, i32 }
          cleanup
  %212 = extractvalue { i8*, i32 } %211, 0
  store i8* %212, i8** %32, align 8
  %213 = extractvalue { i8*, i32 } %211, 1
  store i32 %213, i32* %33, align 4
  invoke void @__cxa_end_catch()
          to label %214 unwind label %220

; <label>:214:                                    ; preds = %210
  br label %215

; <label>:215:                                    ; preds = %214
  %216 = load i8*, i8** %32, align 8
  %217 = load i32, i32* %33, align 4
  %218 = insertvalue { i8*, i32 } undef, i8* %216, 0
  %219 = insertvalue { i8*, i32 } %218, i32 %217, 1
  resume { i8*, i32 } %219

; <label>:220:                                    ; preds = %210, %187
  %221 = landingpad { i8*, i32 }
          catch i8* null
  %222 = extractvalue { i8*, i32 } %221, 0
  call void @__clang_call_terminate(i8* %222) #8
  unreachable
}

; Function Attrs: inlinehint ssp uwtable
define linkonce_odr i64 @_ZNSt3__111char_traitsIcE6lengthEPKc(i8*) #4 align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i64 @strlen(i8* %3)
  ret i64 %4
}

declare void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, %"class.std::__1::basic_ostream"* dereferenceable(160)) unnamed_addr #5

; Function Attrs: ssp uwtable
define linkonce_odr hidden %"class.std::__1::basic_streambuf"* @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(%"class.std::__1::basic_streambuf"*, i8*, i8*, i8*, %"class.std::__1::ios_base"* dereferenceable(136), i8 signext) #2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %7 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %8 = alloca %"class.std::__1::allocator"*, align 8
  %9 = alloca %"class.std::__1::__libcpp_compressed_pair_imp"*, align 8
  %10 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %11 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %12 = alloca %"class.std::__1::basic_string"*, align 8
  %13 = alloca i64, align 8
  %14 = alloca i8, align 1
  %15 = alloca %"class.std::__1::basic_string"*, align 8
  %16 = alloca i64, align 8
  %17 = alloca i8, align 1
  %18 = alloca i8*, align 8
  %19 = alloca %"class.std::__1::__libcpp_compressed_pair_imp"*, align 8
  %20 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %21 = alloca %"class.std::__1::basic_string"*, align 8
  %22 = alloca i8*, align 8
  %23 = alloca i8*, align 8
  %24 = alloca %"class.std::__1::__libcpp_compressed_pair_imp"*, align 8
  %25 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %26 = alloca %"class.std::__1::basic_string"*, align 8
  %27 = alloca %"class.std::__1::__libcpp_compressed_pair_imp"*, align 8
  %28 = alloca %"class.std::__1::__compressed_pair"*, align 8
  %29 = alloca %"class.std::__1::basic_string"*, align 8
  %30 = alloca %"class.std::__1::basic_string"*, align 8
  %31 = alloca %"class.std::__1::basic_string"*, align 8
  %32 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %33 = alloca i64, align 8
  %34 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %35 = alloca i64, align 8
  %36 = alloca %"struct.std::__1::nullptr_t", align 8
  %37 = alloca %"class.std::__1::basic_streambuf"*, align 8
  %38 = alloca i8*, align 8
  %39 = alloca i64, align 8
  %40 = alloca %"class.std::__1::basic_streambuf"*, align 8
  %41 = alloca i8*, align 8
  %42 = alloca i64, align 8
  %43 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %44 = alloca i64, align 8
  %45 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %46 = alloca i64, align 8
  %47 = alloca %"struct.std::__1::nullptr_t", align 8
  %48 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %49 = alloca %"class.std::__1::ios_base"*, align 8
  %50 = alloca %"class.std::__1::basic_streambuf"*, align 8
  %51 = alloca i8*, align 8
  %52 = alloca i64, align 8
  %53 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %54 = alloca i64, align 8
  %55 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %56 = alloca i64, align 8
  %57 = alloca %"struct.std::__1::nullptr_t", align 8
  %58 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %59 = alloca %"class.std::__1::ios_base"*, align 8
  %60 = alloca i64, align 8
  %61 = alloca i64, align 8
  %62 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %63 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %64 = alloca i64, align 8
  %65 = alloca %"struct.std::__1::nullptr_t"*, align 8
  %66 = alloca i64, align 8
  %67 = alloca %"struct.std::__1::nullptr_t", align 8
  %68 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %69 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %70 = alloca i8*, align 8
  %71 = alloca i8*, align 8
  %72 = alloca i8*, align 8
  %73 = alloca %"class.std::__1::ios_base"*, align 8
  %74 = alloca i8, align 1
  %75 = alloca %"struct.std::__1::nullptr_t", align 8
  %76 = alloca i64, align 8
  %77 = alloca i64, align 8
  %78 = alloca i64, align 8
  %79 = alloca %"struct.std::__1::nullptr_t", align 8
  %80 = alloca %"class.std::__1::basic_string", align 8
  %81 = alloca i8*
  %82 = alloca i32
  %83 = alloca %"struct.std::__1::nullptr_t", align 8
  %84 = alloca i32
  %85 = alloca %"struct.std::__1::nullptr_t", align 8
  %86 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* %0, %"class.std::__1::basic_streambuf"** %86, align 8
  store i8* %1, i8** %70, align 8
  store i8* %2, i8** %71, align 8
  store i8* %3, i8** %72, align 8
  store %"class.std::__1::ios_base"* %4, %"class.std::__1::ios_base"** %73, align 8
  store i8 %5, i8* %74, align 1
  %87 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  %88 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %87, align 8
  store %"struct.std::__1::nullptr_t"* %67, %"struct.std::__1::nullptr_t"** %65, align 8
  store i64 -1, i64* %66, align 8
  %89 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %65, align 8
  %90 = load i64, i64* %66, align 8
  store %"struct.std::__1::nullptr_t"* %89, %"struct.std::__1::nullptr_t"** %63, align 8
  store i64 %90, i64* %64, align 8
  %91 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %63, align 8
  %92 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %91, i32 0, i32 0
  store i8* null, i8** %92, align 8
  %93 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %67, i32 0, i32 0
  %94 = load i8*, i8** %93, align 8
  %95 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %75, i32 0, i32 0
  store i8* %94, i8** %95, align 8
  store %"struct.std::__1::nullptr_t"* %75, %"struct.std::__1::nullptr_t"** %62, align 8
  %96 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %62, align 8
  %97 = icmp eq %"class.std::__1::basic_streambuf"* %88, null
  br i1 %97, label %98, label %101

; <label>:98:                                     ; preds = %6
  %99 = bitcast %"class.std::__1::ostreambuf_iterator"* %68 to i8*
  %100 = bitcast %"class.std::__1::ostreambuf_iterator"* %69 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %99, i8* %100, i64 8, i32 8, i1 false)
  br label %304

; <label>:101:                                    ; preds = %6
  %102 = load i8*, i8** %72, align 8
  %103 = load i8*, i8** %70, align 8
  %104 = ptrtoint i8* %102 to i64
  %105 = ptrtoint i8* %103 to i64
  %106 = sub i64 %104, %105
  store i64 %106, i64* %76, align 8
  %107 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %73, align 8
  store %"class.std::__1::ios_base"* %107, %"class.std::__1::ios_base"** %49, align 8
  %108 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %49, align 8
  %109 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %108, i32 0, i32 3
  %110 = load i64, i64* %109, align 8
  store i64 %110, i64* %77, align 8
  %111 = load i64, i64* %77, align 8
  %112 = load i64, i64* %76, align 8
  %113 = icmp sgt i64 %111, %112
  br i1 %113, label %114, label %118

; <label>:114:                                    ; preds = %101
  %115 = load i64, i64* %76, align 8
  %116 = load i64, i64* %77, align 8
  %117 = sub nsw i64 %116, %115
  store i64 %117, i64* %77, align 8
  br label %119

; <label>:118:                                    ; preds = %101
  store i64 0, i64* %77, align 8
  br label %119

; <label>:119:                                    ; preds = %118, %114
  %120 = load i8*, i8** %71, align 8
  %121 = load i8*, i8** %70, align 8
  %122 = ptrtoint i8* %120 to i64
  %123 = ptrtoint i8* %121 to i64
  %124 = sub i64 %122, %123
  store i64 %124, i64* %78, align 8
  %125 = load i64, i64* %78, align 8
  %126 = icmp sgt i64 %125, 0
  br i1 %126, label %127, label %155

; <label>:127:                                    ; preds = %119
  %128 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  %129 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %128, align 8
  %130 = load i8*, i8** %70, align 8
  %131 = load i64, i64* %78, align 8
  store %"class.std::__1::basic_streambuf"* %129, %"class.std::__1::basic_streambuf"** %37, align 8
  store i8* %130, i8** %38, align 8
  store i64 %131, i64* %39, align 8
  %132 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %37, align 8
  %133 = bitcast %"class.std::__1::basic_streambuf"* %132 to i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)***
  %134 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)**, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*** %133, align 8
  %135 = getelementptr inbounds i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %134, i64 12
  %136 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %135, align 8
  %137 = load i8*, i8** %38, align 8
  %138 = load i64, i64* %39, align 8
  %139 = call i64 %136(%"class.std::__1::basic_streambuf"* %132, i8* %137, i64 %138)
  %140 = load i64, i64* %78, align 8
  %141 = icmp ne i64 %139, %140
  br i1 %141, label %142, label %154

; <label>:142:                                    ; preds = %127
  store %"struct.std::__1::nullptr_t"* %36, %"struct.std::__1::nullptr_t"** %34, align 8
  store i64 -1, i64* %35, align 8
  %143 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %34, align 8
  %144 = load i64, i64* %35, align 8
  store %"struct.std::__1::nullptr_t"* %143, %"struct.std::__1::nullptr_t"** %32, align 8
  store i64 %144, i64* %33, align 8
  %145 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %32, align 8
  %146 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %145, i32 0, i32 0
  store i8* null, i8** %146, align 8
  %147 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %36, i32 0, i32 0
  %148 = load i8*, i8** %147, align 8
  %149 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %79, i32 0, i32 0
  store i8* %148, i8** %149, align 8
  store %"struct.std::__1::nullptr_t"* %79, %"struct.std::__1::nullptr_t"** %7, align 8
  %150 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %7, align 8
  %151 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %151, align 8
  %152 = bitcast %"class.std::__1::ostreambuf_iterator"* %68 to i8*
  %153 = bitcast %"class.std::__1::ostreambuf_iterator"* %69 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %152, i8* %153, i64 8, i32 8, i1 false)
  br label %304

; <label>:154:                                    ; preds = %127
  br label %155

; <label>:155:                                    ; preds = %154, %119
  %156 = load i64, i64* %77, align 8
  %157 = icmp sgt i64 %156, 0
  br i1 %157, label %158, label %258

; <label>:158:                                    ; preds = %155
  %159 = load i64, i64* %77, align 8
  %160 = load i8, i8* %74, align 1
  store %"class.std::__1::basic_string"* %80, %"class.std::__1::basic_string"** %15, align 8
  store i64 %159, i64* %16, align 8
  store i8 %160, i8* %17, align 1
  %161 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %15, align 8
  %162 = load i64, i64* %16, align 8
  %163 = load i8, i8* %17, align 1
  store %"class.std::__1::basic_string"* %161, %"class.std::__1::basic_string"** %12, align 8
  store i64 %162, i64* %13, align 8
  store i8 %163, i8* %14, align 1
  %164 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %12, align 8
  %165 = bitcast %"class.std::__1::basic_string"* %164 to %"class.std::__1::__basic_string_common"*
  %166 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %164, i32 0, i32 0
  store %"class.std::__1::__compressed_pair"* %166, %"class.std::__1::__compressed_pair"** %11, align 8
  %167 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %11, align 8
  store %"class.std::__1::__compressed_pair"* %167, %"class.std::__1::__compressed_pair"** %10, align 8
  %168 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %10, align 8
  %169 = bitcast %"class.std::__1::__compressed_pair"* %168 to %"class.std::__1::__libcpp_compressed_pair_imp"*
  store %"class.std::__1::__libcpp_compressed_pair_imp"* %169, %"class.std::__1::__libcpp_compressed_pair_imp"** %9, align 8
  %170 = load %"class.std::__1::__libcpp_compressed_pair_imp"*, %"class.std::__1::__libcpp_compressed_pair_imp"** %9, align 8
  %171 = bitcast %"class.std::__1::__libcpp_compressed_pair_imp"* %170 to %"class.std::__1::allocator"*
  store %"class.std::__1::allocator"* %171, %"class.std::__1::allocator"** %8, align 8
  %172 = load %"class.std::__1::allocator"*, %"class.std::__1::allocator"** %8, align 8
  %173 = getelementptr inbounds %"class.std::__1::__libcpp_compressed_pair_imp", %"class.std::__1::__libcpp_compressed_pair_imp"* %170, i32 0, i32 0
  %174 = bitcast %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %173 to i8*
  call void @llvm.memset.p0i8.i64(i8* %174, i8 0, i64 24, i32 8, i1 false) #9
  %175 = load i64, i64* %13, align 8
  %176 = load i8, i8* %14, align 1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc(%"class.std::__1::basic_string"* %164, i64 %175, i8 signext %176)
  %177 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  %178 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %177, align 8
  store %"class.std::__1::basic_string"* %80, %"class.std::__1::basic_string"** %31, align 8
  %179 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %31, align 8
  store %"class.std::__1::basic_string"* %179, %"class.std::__1::basic_string"** %30, align 8
  %180 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %30, align 8
  store %"class.std::__1::basic_string"* %180, %"class.std::__1::basic_string"** %29, align 8
  %181 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %29, align 8
  %182 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %181, i32 0, i32 0
  store %"class.std::__1::__compressed_pair"* %182, %"class.std::__1::__compressed_pair"** %28, align 8
  %183 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %28, align 8
  %184 = bitcast %"class.std::__1::__compressed_pair"* %183 to %"class.std::__1::__libcpp_compressed_pair_imp"*
  store %"class.std::__1::__libcpp_compressed_pair_imp"* %184, %"class.std::__1::__libcpp_compressed_pair_imp"** %27, align 8
  %185 = load %"class.std::__1::__libcpp_compressed_pair_imp"*, %"class.std::__1::__libcpp_compressed_pair_imp"** %27, align 8
  %186 = getelementptr inbounds %"class.std::__1::__libcpp_compressed_pair_imp", %"class.std::__1::__libcpp_compressed_pair_imp"* %185, i32 0, i32 0
  %187 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %186, i32 0, i32 0
  %188 = bitcast %union.anon* %187 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"*
  %189 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"* %188, i32 0, i32 0
  %190 = bitcast %union.anon.0* %189 to i8*
  %191 = load i8, i8* %190, align 8
  %192 = zext i8 %191 to i32
  %193 = and i32 %192, 1
  %194 = icmp ne i32 %193, 0
  br i1 %194, label %195, label %206

; <label>:195:                                    ; preds = %158
  store %"class.std::__1::basic_string"* %180, %"class.std::__1::basic_string"** %21, align 8
  %196 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %21, align 8
  %197 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %196, i32 0, i32 0
  store %"class.std::__1::__compressed_pair"* %197, %"class.std::__1::__compressed_pair"** %20, align 8
  %198 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %20, align 8
  %199 = bitcast %"class.std::__1::__compressed_pair"* %198 to %"class.std::__1::__libcpp_compressed_pair_imp"*
  store %"class.std::__1::__libcpp_compressed_pair_imp"* %199, %"class.std::__1::__libcpp_compressed_pair_imp"** %19, align 8
  %200 = load %"class.std::__1::__libcpp_compressed_pair_imp"*, %"class.std::__1::__libcpp_compressed_pair_imp"** %19, align 8
  %201 = getelementptr inbounds %"class.std::__1::__libcpp_compressed_pair_imp", %"class.std::__1::__libcpp_compressed_pair_imp"* %200, i32 0, i32 0
  %202 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %201, i32 0, i32 0
  %203 = bitcast %union.anon* %202 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long"*
  %204 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long"* %203, i32 0, i32 2
  %205 = load i8*, i8** %204, align 8
  br label %219

; <label>:206:                                    ; preds = %158
  store %"class.std::__1::basic_string"* %180, %"class.std::__1::basic_string"** %26, align 8
  %207 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %26, align 8
  %208 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %207, i32 0, i32 0
  store %"class.std::__1::__compressed_pair"* %208, %"class.std::__1::__compressed_pair"** %25, align 8
  %209 = load %"class.std::__1::__compressed_pair"*, %"class.std::__1::__compressed_pair"** %25, align 8
  %210 = bitcast %"class.std::__1::__compressed_pair"* %209 to %"class.std::__1::__libcpp_compressed_pair_imp"*
  store %"class.std::__1::__libcpp_compressed_pair_imp"* %210, %"class.std::__1::__libcpp_compressed_pair_imp"** %24, align 8
  %211 = load %"class.std::__1::__libcpp_compressed_pair_imp"*, %"class.std::__1::__libcpp_compressed_pair_imp"** %24, align 8
  %212 = getelementptr inbounds %"class.std::__1::__libcpp_compressed_pair_imp", %"class.std::__1::__libcpp_compressed_pair_imp"* %211, i32 0, i32 0
  %213 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %212, i32 0, i32 0
  %214 = bitcast %union.anon* %213 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"*
  %215 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"* %214, i32 0, i32 1
  %216 = getelementptr inbounds [23 x i8], [23 x i8]* %215, i64 0, i64 0
  store i8* %216, i8** %23, align 8
  %217 = load i8*, i8** %23, align 8
  store i8* %217, i8** %22, align 8
  %218 = load i8*, i8** %22, align 8
  br label %219

; <label>:219:                                    ; preds = %195, %206
  %220 = phi i8* [ %205, %195 ], [ %218, %206 ]
  store i8* %220, i8** %18, align 8
  %221 = load i8*, i8** %18, align 8
  %222 = load i64, i64* %77, align 8
  store %"class.std::__1::basic_streambuf"* %178, %"class.std::__1::basic_streambuf"** %40, align 8
  store i8* %221, i8** %41, align 8
  store i64 %222, i64* %42, align 8
  %223 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %40, align 8
  %224 = bitcast %"class.std::__1::basic_streambuf"* %223 to i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)***
  %225 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)**, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*** %224, align 8
  %226 = getelementptr inbounds i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %225, i64 12
  %227 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %226, align 8
  %228 = load i8*, i8** %41, align 8
  %229 = load i64, i64* %42, align 8
  %230 = invoke i64 %227(%"class.std::__1::basic_streambuf"* %223, i8* %228, i64 %229)
          to label %231 unwind label %249

; <label>:231:                                    ; preds = %219
  br label %232

; <label>:232:                                    ; preds = %231
  %233 = load i64, i64* %77, align 8
  %234 = icmp ne i64 %230, %233
  br i1 %234, label %235, label %253

; <label>:235:                                    ; preds = %232
  store %"struct.std::__1::nullptr_t"* %47, %"struct.std::__1::nullptr_t"** %45, align 8
  store i64 -1, i64* %46, align 8
  %236 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %45, align 8
  %237 = load i64, i64* %46, align 8
  store %"struct.std::__1::nullptr_t"* %236, %"struct.std::__1::nullptr_t"** %43, align 8
  store i64 %237, i64* %44, align 8
  %238 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %43, align 8
  %239 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %238, i32 0, i32 0
  store i8* null, i8** %239, align 8
  %240 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %47, i32 0, i32 0
  %241 = load i8*, i8** %240, align 8
  br label %242

; <label>:242:                                    ; preds = %235
  %243 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %83, i32 0, i32 0
  store i8* %241, i8** %243, align 8
  store %"struct.std::__1::nullptr_t"* %83, %"struct.std::__1::nullptr_t"** %48, align 8
  %244 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %48, align 8
  br label %245

; <label>:245:                                    ; preds = %242
  %246 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %246, align 8
  %247 = bitcast %"class.std::__1::ostreambuf_iterator"* %68 to i8*
  %248 = bitcast %"class.std::__1::ostreambuf_iterator"* %69 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %247, i8* %248, i64 8, i32 8, i1 false)
  store i32 1, i32* %84, align 4
  br label %254

; <label>:249:                                    ; preds = %219
  %250 = landingpad { i8*, i32 }
          cleanup
  %251 = extractvalue { i8*, i32 } %250, 0
  store i8* %251, i8** %81, align 8
  %252 = extractvalue { i8*, i32 } %250, 1
  store i32 %252, i32* %82, align 4
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %80)
          to label %257 unwind label %312

; <label>:253:                                    ; preds = %232
  store i32 0, i32* %84, align 4
  br label %254

; <label>:254:                                    ; preds = %253, %245
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %80)
  %255 = load i32, i32* %84, align 4
  switch i32 %255, label %315 [
    i32 0, label %256
    i32 1, label %304
  ]

; <label>:256:                                    ; preds = %254
  br label %258

; <label>:257:                                    ; preds = %249
  br label %307

; <label>:258:                                    ; preds = %256, %155
  %259 = load i8*, i8** %72, align 8
  %260 = load i8*, i8** %71, align 8
  %261 = ptrtoint i8* %259 to i64
  %262 = ptrtoint i8* %260 to i64
  %263 = sub i64 %261, %262
  store i64 %263, i64* %78, align 8
  %264 = load i64, i64* %78, align 8
  %265 = icmp sgt i64 %264, 0
  br i1 %265, label %266, label %294

; <label>:266:                                    ; preds = %258
  %267 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  %268 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %267, align 8
  %269 = load i8*, i8** %71, align 8
  %270 = load i64, i64* %78, align 8
  store %"class.std::__1::basic_streambuf"* %268, %"class.std::__1::basic_streambuf"** %50, align 8
  store i8* %269, i8** %51, align 8
  store i64 %270, i64* %52, align 8
  %271 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %50, align 8
  %272 = bitcast %"class.std::__1::basic_streambuf"* %271 to i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)***
  %273 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)**, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*** %272, align 8
  %274 = getelementptr inbounds i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %273, i64 12
  %275 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %274, align 8
  %276 = load i8*, i8** %51, align 8
  %277 = load i64, i64* %52, align 8
  %278 = call i64 %275(%"class.std::__1::basic_streambuf"* %271, i8* %276, i64 %277)
  %279 = load i64, i64* %78, align 8
  %280 = icmp ne i64 %278, %279
  br i1 %280, label %281, label %293

; <label>:281:                                    ; preds = %266
  store %"struct.std::__1::nullptr_t"* %57, %"struct.std::__1::nullptr_t"** %55, align 8
  store i64 -1, i64* %56, align 8
  %282 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %55, align 8
  %283 = load i64, i64* %56, align 8
  store %"struct.std::__1::nullptr_t"* %282, %"struct.std::__1::nullptr_t"** %53, align 8
  store i64 %283, i64* %54, align 8
  %284 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %53, align 8
  %285 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %284, i32 0, i32 0
  store i8* null, i8** %285, align 8
  %286 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %57, i32 0, i32 0
  %287 = load i8*, i8** %286, align 8
  %288 = getelementptr inbounds %"struct.std::__1::nullptr_t", %"struct.std::__1::nullptr_t"* %85, i32 0, i32 0
  store i8* %287, i8** %288, align 8
  store %"struct.std::__1::nullptr_t"* %85, %"struct.std::__1::nullptr_t"** %58, align 8
  %289 = load %"struct.std::__1::nullptr_t"*, %"struct.std::__1::nullptr_t"** %58, align 8
  %290 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %69, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %290, align 8
  %291 = bitcast %"class.std::__1::ostreambuf_iterator"* %68 to i8*
  %292 = bitcast %"class.std::__1::ostreambuf_iterator"* %69 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %291, i8* %292, i64 8, i32 8, i1 false)
  br label %304

; <label>:293:                                    ; preds = %266
  br label %294

; <label>:294:                                    ; preds = %293, %258
  %295 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %73, align 8
  store %"class.std::__1::ios_base"* %295, %"class.std::__1::ios_base"** %59, align 8
  store i64 0, i64* %60, align 8
  %296 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %59, align 8
  %297 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %296, i32 0, i32 3
  %298 = load i64, i64* %297, align 8
  store i64 %298, i64* %61, align 8
  %299 = load i64, i64* %60, align 8
  %300 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %296, i32 0, i32 3
  store i64 %299, i64* %300, align 8
  %301 = load i64, i64* %61, align 8
  %302 = bitcast %"class.std::__1::ostreambuf_iterator"* %68 to i8*
  %303 = bitcast %"class.std::__1::ostreambuf_iterator"* %69 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %302, i8* %303, i64 8, i32 8, i1 false)
  br label %304

; <label>:304:                                    ; preds = %294, %281, %254, %142, %98
  %305 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %68, i32 0, i32 0
  %306 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %305, align 8
  ret %"class.std::__1::basic_streambuf"* %306

; <label>:307:                                    ; preds = %257
  %308 = load i8*, i8** %81, align 8
  %309 = load i32, i32* %82, align 4
  %310 = insertvalue { i8*, i32 } undef, i8* %308, 0
  %311 = insertvalue { i8*, i32 } %310, i32 %309, 1
  resume { i8*, i32 } %311

; <label>:312:                                    ; preds = %249
  %313 = landingpad { i8*, i32 }
          catch i8* null
  %314 = extractvalue { i8*, i32 } %313, 0
  call void @__clang_call_terminate(i8* %314) #8
  unreachable

; <label>:315:                                    ; preds = %254
  unreachable
}

declare void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*) unnamed_addr #5

declare void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(%"class.std::__1::ios_base"*) #5

declare void @__cxa_end_catch()

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i32, i1) #6

declare void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"*) unnamed_addr #5

declare void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc(%"class.std::__1::basic_string"*, i64, i8 signext) #5

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #6

declare void @__cxa_call_unexpected(i8*)

; Function Attrs: inlinehint nounwind ssp uwtable
define linkonce_odr zeroext i1 @_ZNSt3__111char_traitsIcE11eq_int_typeEii(i32, i32) #7 align 2 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = icmp eq i32 %5, %6
  ret i1 %7
}

; Function Attrs: inlinehint nounwind ssp uwtable
define linkonce_odr i32 @_ZNSt3__111char_traitsIcE3eofEv() #7 align 2 {
  ret i32 -1
}

declare void @_ZNKSt3__18ios_base6getlocEv(%"class.std::__1::locale"* sret, %"class.std::__1::ios_base"*) #5

declare void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"*) unnamed_addr #5

declare %"class.std::__1::locale::facet"* @_ZNKSt3__16locale9use_facetERNS0_2idE(%"class.std::__1::locale"*, %"class.std::__1::locale::id"* dereferenceable(16)) #5

declare void @_ZNSt3__18ios_base5clearEj(%"class.std::__1::ios_base"*, i32) #5

declare i64 @strlen(i8*) #5

attributes #0 = { norecurse ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noinline noreturn nounwind }
attributes #4 = { inlinehint ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { inlinehint nounwind ssp uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="core2" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"clang version 3.9.1 (tags/RELEASE_391/final)"}
