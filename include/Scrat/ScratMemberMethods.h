//
// ScratMemberMethods: Member Methods
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

#if !defined(_SCRAT_MEMBER_METHODS_H_)
#define _SCRAT_MEMBER_METHODS_H_

#include <squirrel.h>
#include "ScratTypes.h"

namespace Scrat {

	//
	// Variable Get
	//

	template <class C, class V>
	static SQInteger sqDefaultGet(HSQUIRRELVM vm) {
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);
		
		typedef V C::*M;
		M* memberPtr = NULL;
		sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
		M member = *memberPtr;
		
		PushVar(vm, ptr->*member);

		return 1;
	}

	static SQInteger sqVarGet(HSQUIRRELVM vm) {
		// Find the get method in the get table
		sq_push(vm, 2);
		sq_get(vm, -2);
		
		// push 'this'
		sq_push(vm, 1);

		// Call the getter
		sq_call(vm, 1, true, false);
		return 1;
	}

	//
	// Variable Set
	//

	template <class C, class V>
	static SQInteger sqDefaultSet(HSQUIRRELVM vm) {
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);
		
		typedef V C::*M;
		M* memberPtr = NULL;
		sq_getuserdata(vm, -1, (SQUserPointer*)&memberPtr, NULL); // Get Member...
		M member = *memberPtr;

		ptr->*member = GetVar(TypeWrapper<V>(), vm, 2);
		return 0;
	}

	static SQInteger sqVarSet(HSQUIRRELVM vm) {
		// Find the get method in the get table
		sq_push(vm, 2);
		sq_get(vm, -2);
		
		// push 'this'
		sq_push(vm, 1);
		sq_push(vm, 3);

		// Call the setter
		sq_call(vm, 2, false, false);

		return 0;
	}
	
	//
	// Arg Count 0
	//

	template <class C>
	static SQInteger sqMemberFunc0(HSQUIRRELVM vm) {
		typedef void (C::*M)();
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)();
		return 0;
	}
	
	template <class C>
	static SQInteger sqMemberFunc0C(HSQUIRRELVM vm) {
		typedef void (C::*M)() const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)();
		return 0;
	}

	template <class C, class R>
	static SQInteger sqMemberFuncR0(HSQUIRRELVM vm) {
		typedef R (C::*M)();
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)();

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R>
	static SQInteger sqMemberFuncR0C(HSQUIRRELVM vm) {
		typedef R (C::*M)() const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)();

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 1
	//

	template <class C, class A1>
	static SQInteger sqMemberFunc1(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2)
			);
		return 0;
	}
	
	template <class C, class A1>
	static SQInteger sqMemberFunc1C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2)
			);
		return 0;
	}

	template <class C, class R, class A1>
	static SQInteger sqMemberFuncR1(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1>
	static SQInteger sqMemberFuncR1C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 2
	//

	template <class C, class A1, class A2>
	static SQInteger sqMemberFunc2(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3)
			);
		return 0;
	}
	
	template <class C, class A1, class A2>
	static SQInteger sqMemberFunc2C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2>
	static SQInteger sqMemberFuncR2(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2>
	static SQInteger sqMemberFuncR2C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	//
	// Arg Count 3
	//

	template <class C, class A1, class A2, class A3>
	static SQInteger sqMemberFunc3(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3>
	static SQInteger sqMemberFunc3C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3>
	static SQInteger sqMemberFuncR3(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3>
	static SQInteger sqMemberFuncR3C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 4
	//

	template <class C, class A1, class A2, class A3, class A4>
	static SQInteger sqMemberFunc4(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4>
	static SQInteger sqMemberFunc4C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4>
	static SQInteger sqMemberFuncR4(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4>
	static SQInteger sqMemberFuncR4C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 5
	//

	template <class C, class A1, class A2, class A3, class A4, class A5>
	static SQInteger sqMemberFunc5(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4, class A5>
	static SQInteger sqMemberFunc5C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5>
	static SQInteger sqMemberFuncR5(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5>
	static SQInteger sqMemberFuncR5C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 6
	//

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6>
	static SQInteger sqMemberFunc6(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6>
	static SQInteger sqMemberFunc6C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
	static SQInteger sqMemberFuncR6(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
	static SQInteger sqMemberFuncR6C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 7
	//

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	static SQInteger sqMemberFunc7(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	static SQInteger sqMemberFunc7C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	static SQInteger sqMemberFuncR7(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	static SQInteger sqMemberFuncR7C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 8
	//

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	static SQInteger sqMemberFunc8(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	static SQInteger sqMemberFunc8C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	static SQInteger sqMemberFuncR8(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	static SQInteger sqMemberFuncR8C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Arg Count 9
	//

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	static SQInteger sqMemberFunc9(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9),
			GetVar(TypeWrapper<A9>(), vm, 10)
			);
		return 0;
	}
	
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	static SQInteger sqMemberFunc9C(HSQUIRRELVM vm) {
		typedef void (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;

		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		(ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9),
			GetVar(TypeWrapper<A9>(), vm, 10)
			);
		return 0;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	static SQInteger sqMemberFuncR9(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9);
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9),
			GetVar(TypeWrapper<A9>(), vm, 10)
			);

		PushVar(vm, ret);
		return 1;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	static SQInteger sqMemberFuncR9C(HSQUIRRELVM vm) {
		typedef R (C::*M)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const;
		M* methodPtr;
		sq_getuserdata(vm, -1, (SQUserPointer*)&methodPtr, NULL);
		M method = *methodPtr;
		
		C* ptr = NULL;
		sq_getinstanceup(vm, 1, (SQUserPointer*)&ptr, NULL);

		R ret = (ptr->*method)(
			GetVar(TypeWrapper<A1>(), vm, 2),
			GetVar(TypeWrapper<A2>(), vm, 3),
			GetVar(TypeWrapper<A3>(), vm, 4),
			GetVar(TypeWrapper<A4>(), vm, 5),
			GetVar(TypeWrapper<A5>(), vm, 6),
			GetVar(TypeWrapper<A6>(), vm, 7),
			GetVar(TypeWrapper<A7>(), vm, 8),
			GetVar(TypeWrapper<A8>(), vm, 9),
			GetVar(TypeWrapper<A9>(), vm, 10)
			);

		PushVar(vm, ret);
		return 1;
	}

	//
	// Member Function Resolvers
	//
		
	// Arg Count 0
	template <class C>
	SQFUNCTION SqMemberFunc(void (C::*method)()) {
		return &sqMemberFunc0<C>;
	}
	
	template <class C>
	SQFUNCTION SqMemberFunc(void (C::*method)() const) {
		return &sqMemberFunc0C<C>;
	}

	template <class C, class R>
	SQFUNCTION SqMemberFunc(R (C::*method)()) {
		return &sqMemberFuncR0<C, R>;
	}
	
	template <class C, class R>
	SQFUNCTION SqMemberFunc(R (C::*method)() const) {
		return &sqMemberFuncR0C<C, R>;
	}

	// Arg Count 1
	template <class C, class A1>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1)) {
		return &sqMemberFunc1<C, A1>;
	}

	template <class C, class A1>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1) const) {
		return &sqMemberFunc1C<C, A1>;
	}

	template <class C, class R, class A1>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1)) {
		return &sqMemberFuncR1<C, R, A1>;
	}
	
	template <class C, class R, class A1>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1) const) {
		return &sqMemberFuncR1C<C, R, A1>;
	}

	// Arg Count 2
	template <class C, class A1, class A2>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2)) {
		return &sqMemberFunc2<C, A1, A2>;
	}

	template <class C, class A1, class A2>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2) const) {
		return &sqMemberFunc2C<C, A1, A2>;
	}

	template <class C, class R, class A1, class A2>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2)) {
		return &sqMemberFuncR2<C, R, A1, A2>;
	}
	
	template <class C, class R, class A1, class A2>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2) const) {
		return &sqMemberFuncR2C<C, R, A1, A2>;
	}

	// Arg Count 3
	template <class C, class A1, class A2, class A3>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3)) {
		return &sqMemberFunc3<C, A1, A2, A3>;
	}

	template <class C, class A1, class A2, class A3>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3) const) {
		return &sqMemberFunc3C<C, A1, A2, A3>;
	}

	template <class C, class R, class A1, class A2, class A3>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3)) {
		return &sqMemberFuncR3<C, R, A1, A2, A3>;
	}
	
	template <class C, class R, class A1, class A2, class A3>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3) const) {
		return &sqMemberFuncR3C<C, R, A1, A2, A3>;
	}

	// Arg Count 4
	template <class C, class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4)) {
		return &sqMemberFunc4<C, A1, A2, A3, A4>;
	}

	template <class C, class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4) const) {
		return &sqMemberFunc4C<C, A1, A2, A3, A4>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4)) {
		return &sqMemberFuncR4<C, R, A1, A2, A3, A4>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4) const) {
		return &sqMemberFuncR4C<C, R, A1, A2, A3, A4>;
	}

	// Arg Count 5
	template <class C, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5)) {
		return &sqMemberFunc5<C, A1, A2, A3, A4, A5>;
	}

	template <class C, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5) const) {
		return &sqMemberFunc5C<C, A1, A2, A3, A4, A5>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5)) {
		return &sqMemberFuncR5<C, R, A1, A2, A3, A4, A5>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5) const) {
		return &sqMemberFuncR5C<C, R, A1, A2, A3, A4, A5>;
	}

	// Arg Count 6
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqMemberFunc6<C, A1, A2, A3, A4, A5, A6>;
	}

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6) const) {
		return &sqMemberFunc6C<C, A1, A2, A3, A4, A5, A6>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6)) {
		return &sqMemberFuncR6<C, R, A1, A2, A3, A4, A5, A6>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6) const) {
		return &sqMemberFuncR6C<C, R, A1, A2, A3, A4, A5, A6>;
	}

	// Arg Count 7
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqMemberFunc7<C, A1, A2, A3, A4, A5, A6, A7>;
	}

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7) const) {
		return &sqMemberFunc7C<C, A1, A2, A3, A4, A5, A6, A7>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7)) {
		return &sqMemberFuncR7<C, R, A1, A2, A3, A4, A5, A6, A7>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7) const) {
		return &sqMemberFuncR7C<C, R, A1, A2, A3, A4, A5, A6, A7>;
	}

	// Arg Count 8
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqMemberFunc8<C, A1, A2, A3, A4, A5, A6, A7, A8>;
	}

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
		return &sqMemberFunc8C<C, A1, A2, A3, A4, A5, A6, A7, A8>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8)) {
		return &sqMemberFuncR8<C, R, A1, A2, A3, A4, A5, A6, A7, A8>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8) const) {
		return &sqMemberFuncR8C<C, R, A1, A2, A3, A4, A5, A6, A7, A8>;
	}

	// Arg Count 9
	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqMemberFunc9<C, A1, A2, A3, A4, A5, A6, A7, A8, A9>;
	}

	template <class C, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberFunc(void (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
		return &sqMemberFunc9C<C, A1, A2, A3, A4, A5, A6, A7, A8, A9>;
	}

	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9)) {
		return &sqMemberFuncR9<C, R, A1, A2, A3, A4, A5, A6, A7, A8, A9>;
	}
	
	template <class C, class R, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
	SQFUNCTION SqMemberFunc(R (C::*method)(A1, A2, A3, A4, A5, A6, A7, A8, A9) const) {
		return &sqMemberFuncR9C<C, R, A1, A2, A3, A4, A5, A6, A7, A8, A9>;
	}
}

#endif
