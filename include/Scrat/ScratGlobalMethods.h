//
// ScratGlobalMethods: Global Methods
//

//
// Copyright (c) 2009 Brandon Jones
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//	1. The origin of this software must not be misrepresented; you must not
//	claim that you wrote the original software. If you use this software
//	in a product, an acknowledgment in the product documentation would be
//	appreciated but is not required.
//
//	2. Altered source versions must be plainly marked as such, and must not be
//	misrepresented as being the original software.
//
//	3. This notice may not be removed or altered from any source
//	distribution.
//

#if !defined(_SCRAT_GLOBAL_METHODS_H_)
#define _SCRAT_GLOBAL_METHODS_H_

#include <squirrel.h>
#include "ScratTypes.h"

namespace Scrat {

	//
	// Squirrel Global Functions
	//

	// Arg Count 0
	static SQInteger sqGlobalFunc0(HSQUIRRELVM vm) {
		typedef void (*M)();
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		(*method)();
		return 0;
	}

	template <class R>
	static SQInteger sqGlobalFuncR0(HSQUIRRELVM vm) {
		typedef R (*M)();
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		R ret = (*method)();

		PushVar(vm, ret);
		return 1;
	}


	// Arg Count 1
	template <class A1, SQInteger startIdx>
	static SQInteger sqGlobalFunc1(HSQUIRRELVM vm) {
		typedef void (*M)(A1);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx)
			);
		return 0;
	}

	template <class R, class A1, SQInteger startIdx>
	static SQInteger sqGlobalFuncR1(HSQUIRRELVM vm) {
		typedef R (*M)(A1);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 2
	template <class A1, class A2, SQInteger startIdx>
	static SQInteger sqGlobalFunc2(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1)
			);
		return 0;
	}

	template <class R, class A1, class A2, SQInteger startIdx>
	static SQInteger sqGlobalFuncR2(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 3
	template <class A1, class A2, class A3, SQInteger startIdx>
	static SQInteger sqGlobalFunc3(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, SQInteger startIdx>
	static SQInteger sqGlobalFuncR3(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 4
	template <class A1, class A2, class A3, class A4, SQInteger startIdx>
	static SQInteger sqGlobalFunc4(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, SQInteger startIdx>
	static SQInteger sqGlobalFuncR4(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 5
	template <class A1, class A2, class A3, class A4, class A5, SQInteger startIdx>
	static SQInteger sqGlobalFunc5(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4, A5);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, class A5, SQInteger startIdx>
	static SQInteger sqGlobalFuncR5(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4, A5);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 6
	template <class A1, class A2, class A3, class A4, class A5, class A6, SQInteger startIdx>
	static SQInteger sqGlobalFunc6(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4, A5, A6);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, SQInteger startIdx>
	static SQInteger sqGlobalFuncR6(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4, A5, A6);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 7
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, SQInteger startIdx>
	static SQInteger sqGlobalFunc7(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4, A5, A6, A7);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, SQInteger startIdx>
	static SQInteger sqGlobalFuncR7(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4, A5, A6, A7);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 8
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, SQInteger startIdx>
	static SQInteger sqGlobalFunc8(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6),
			GetVar(TypeWrapper<A8>(), vm, startIdx + 7)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, SQInteger startIdx>
	static SQInteger sqGlobalFuncR8(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6),
			GetVar(TypeWrapper<A8>(), vm, startIdx + 7)
			);

		PushVar(vm, ret);
		return 1;
	}

	// Arg Count 9
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, SQInteger startIdx>
	static SQInteger sqGlobalFunc9(HSQUIRRELVM vm) {
		typedef void (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);

		(*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6),
			GetVar(TypeWrapper<A8>(), vm, startIdx + 7),
			GetVar(TypeWrapper<A9>(), vm, startIdx + 8)
			);
		return 0;
	}

	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9, SQInteger startIdx>
	static SQInteger sqGlobalFuncR9(HSQUIRRELVM vm) {
		typedef R (*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
		M* method;
		sq_getuserdata(vm, -1, (SQUserPointer*)&method, NULL);
		
		R ret = (*method)(
			GetVar(TypeWrapper<A1>(), vm, startIdx),
			GetVar(TypeWrapper<A2>(), vm, startIdx + 1),
			GetVar(TypeWrapper<A3>(), vm, startIdx + 2),
			GetVar(TypeWrapper<A4>(), vm, startIdx + 3),
			GetVar(TypeWrapper<A5>(), vm, startIdx + 4),
			GetVar(TypeWrapper<A6>(), vm, startIdx + 5),
			GetVar(TypeWrapper<A7>(), vm, startIdx + 6),
			GetVar(TypeWrapper<A8>(), vm, startIdx + 7),
			GetVar(TypeWrapper<A9>(), vm, startIdx + 8)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Global Function Resolvers
	//
	
	// Arg Count 0
	SQFUNCTION SqGlobalFunc(void (*method)()) {
		return &sqGlobalFunc0;
	}
	
	template <class R>
	SQFUNCTION SqGlobalFunc(R (*method)()) {
		return &sqGlobalFuncR0<R>;
	}
	
	// Arg Count 1
	template <class A1>
	SQFUNCTION SqGlobalFunc(void (*method)(A1)) {
		return &sqGlobalFunc1<A1, 2>;
	}
	
	template <class R, class A1>
	SQFUNCTION SqGlobalFunc(R (*method)(A1)) {
		return &sqGlobalFuncR1<R, A1, 2>;
	}
	
	// Arg Count 2
	template <class A1, class A2>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2)) {
		return &sqGlobalFunc2<A1, A2, 2>;
	}
	
	template <class R, class A1, class A2>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2)) {
		return &sqGlobalFuncR2<R, A1, A2, 2>;
	}

	// Arg Count 3
	template <class A1, class A2, class A3>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3)) {
		return &sqGlobalFunc3<A1, A2, A3, 2>;
	}
	
	template <class R, class A1, class A2, class A3>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3)) {
		return &sqGlobalFuncR3<R, A1, A2, A3, 2>;
	}

	// Arg Count 4
	template <class A1, class A2, class A3, class A4>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4)) {
		return &sqGlobalFunc4<A1, A2, A3, A4, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4)) {
		return &sqGlobalFuncR4<R, A1, A2, A3, A4, 2>;
	}

	// Arg Count 5
	template <class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4, A5)) {
		return &sqGlobalFunc5<A1, A2, A3, A4, A5, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4, A5)) {
		return &sqGlobalFuncR5<R, A1, A2, A3, A4, A5, 2>;
	}

	// Arg Count 6
	template <class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqGlobalFunc6<A1, A2, A3, A4, A5, A6, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqGlobalFuncR6<R, A1, A2, A3, A4, A5, A6, 2>;
	}

	// Arg Count 7
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqGlobalFunc7<A1, A2, A3, A4, A5, A6, A7, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqGlobalFuncR7<R, A1, A2, A3, A4, A5, A6, A7, 2>;
	}

	// Arg Count 8
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqGlobalFunc8<A1, A2, A3, A4, A5, A6, A7, A8, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqGlobalFuncR8<R, A1, A2, A3, A4, A5, A6, A7, A8, 2>;
	}

	// Arg Count 9
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqGlobalFunc9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 2>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqGlobalFuncR9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, 2>;
	}

	//
	// Member Global Function Resolvers
	//
	
	// Arg Count 1
	template <class A1>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1)) {
		return &sqGlobalFunc1<A1, 1>;
	}
	
	template <class R, class A1>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1)) {
		return &sqGlobalFuncR1<R, A1, 1>;
	}
	
	// Arg Count 2
	template <class A1, class A2>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2)) {
		return &sqGlobalFunc2<A1, A2, 1>;
	}
	
	template <class R, class A1, class A2>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2)) {
		return &sqGlobalFuncR2<R, A1, A2, 1>;
	}

	// Arg Count 3
	template <class A1, class A2, class A3>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3)) {
		return &sqGlobalFunc3<A1, A2, A3, 1>;
	}
	
	template <class R, class A1, class A2, class A3>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3)) {
		return &sqGlobalFuncR3<R, A1, A2, A3, 1>;
	}

	// Arg Count 4
	template <class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4)) {
		return &sqGlobalFunc4<A1, A2, A3, A4, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4)) {
		return &sqGlobalFuncR4<R, A1, A2, A3, A4, 1>;
	}

	// Arg Count 5
	template <class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4, A5)) {
		return &sqGlobalFunc5<A1, A2, A3, A4, A5, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4, A5)) {
		return &sqGlobalFuncR5<R, A1, A2, A3, A4, A5, 1>;
	}

	// Arg Count 6
	template <class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqGlobalFunc6<A1, A2, A3, A4, A5, A6, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqGlobalFuncR6<R, A1, A2, A3, A4, A5, A6, 1>;
	}

	// Arg Count 7
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqGlobalFunc7<A1, A2, A3, A4, A5, A6, A7, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqGlobalFuncR7<R, A1, A2, A3, A4, A5, A6, A7, 1>;
	}

	// Arg Count 8
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqGlobalFunc8<A1, A2, A3, A4, A5, A6, A7, A8, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqGlobalFuncR8<R, A1, A2, A3, A4, A5, A6, A7, A8, 1>;
	}

	// Arg Count 9
	template <class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberGlobalFunc(void (*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqGlobalFunc9<A1, A2, A3, A4, A5, A6, A7, A8, A9, 1>;
	}
	
	template <class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberGlobalFunc(R (*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqGlobalFuncR9<R, A1, A2, A3, A4, A5, A6, A7, A8, A9, 1>;
	}

}

#endif