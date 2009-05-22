//
// SqratClass: Class Binding
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

#if !defined(_SCRAT_CLASS_H_)
#define _SCRAT_CLASS_H_

#include <squirrel.h>
#include <string.h>

#include "SqratObject.h"
#include "SqratClassType.h"
#include "SqratMemberMethods.h"
#include "SqratAllocator.h"

namespace Sqrat {

	//
	// Class
	//

	template<class C, class A = DefaultAllocator<C> >
	class Class : public Object {
	public:
		// Create a new table
		Class(HSQUIRRELVM v = DefaultVM::Get(), bool createClass = true) : Object(v, false) {
			if(createClass && !ClassType<C>::Initialized()) {
				sq_newclass(vm, false);
				sq_getstackobj(vm, -1, &ClassType<C>::ClassObject());

				sq_pop(vm, -1);

				InitClass();

				ClassType<C>::Initialized() = true;
			}
		}

		// Get the Squirrel Object for this Class
		virtual HSQOBJECT GetObject() const {
			return ClassType<C>::ClassObject();
		}

		// Get the Squirrel Object for this Class
		virtual HSQOBJECT& GetObject() {
			return ClassType<C>::ClassObject();
		}

	public:
		//
		// Variable Binding
		//

		template<class V>
		Class& SetStaticValue(const SQChar* name, const V& val) {
			BindValue<V>(name, val, true);
			return *this;
		}

		template<class V>
		Class& SetValue(const SQChar* name, const V& val) {
			BindValue<V>(name, val, false);
			return *this;
		}

		template<class V>
		Class& Var(const SQChar* name, V C::* var) {
			// Add the getter
			BindAccessor(name, &var, sizeof(var), &sqDefaultGet<C, V>, ClassType<C>::GetTable());

			// Add the setter
			BindAccessor(name, &var, sizeof(var), &sqDefaultSet<C, V>, ClassType<C>::SetTable());

			return *this;
		}

		// TODO: Handle static instance vars

		//
		// Function Binding
		//

		template<class F>
		Class& Func(const SQChar* name, F method) {
			BindFunc(name, &method, sizeof(method), SqMemberFunc(method));
			return *this;
		}

		template<class F>
		Class& GlobalFunc(const SQChar* name, F method) {
			BindFunc(name, &method, sizeof(method), SqMemberGlobalFunc(method));
			return *this;
		}

		template<class F>
		Class& StaticFunc(const SQChar* name, F method) {
			BindFunc(name, &method, sizeof(method), SqGlobalFunc(method));
			return *this;
		}

		template<class F>
		Class& SquirrelFunc(const SQChar* name, SQFUNCTION func) {
			sq_pushobject(vm, ClassType<C>::ClassObject());
			sq_pushstring(vm, name, -1);
			sq_newclosure(vm, func, 0);
			sq_newslot(vm, -3, false);
			sq_pop(vm,-1); // pop table

			return *this;
		}

	protected:
		// Initialize the required data structure for the class
		void InitClass() {
			HSQOBJECT& classObj = ClassType<C>::ClassObject();
			HSQOBJECT& setTable = ClassType<C>::SetTable();
			HSQOBJECT& getTable = ClassType<C>::GetTable();

			// push the class
			sq_pushobject(vm, classObj);

			ClassType<C>::CopyFunc() = &A::Copy;

			// add the default constructor
			sq_pushstring(vm,_SC("constructor"), -1);
			sq_newclosure(vm, &A::New, 0);
			sq_newslot(vm, -3, false);

			// add the set table (static)
			sq_resetobject(&setTable);
			sq_pushstring(vm,_SC("__setTable"), -1);
			sq_newtable(vm);
			sq_getstackobj(vm, -1, &setTable);
			sq_newslot(vm, -3, true);

			// add the get table (static)
			sq_resetobject(&getTable);
			sq_pushstring(vm,_SC("__getTable"), -1);
			sq_newtable(vm);
			sq_getstackobj(vm, -1, &getTable);
			sq_newslot(vm, -3, true);

			// override _set
			sq_pushstring(vm, _SC("_set"), -1);
			sq_pushobject(vm, setTable); // Push the set table as a free variable
			sq_newclosure(vm, &sqVarSet, 1);
			sq_newslot(vm, -3, false);

			// override _get
			sq_pushstring(vm, _SC("_get"), -1);
			sq_pushobject(vm, getTable); // Push the get table as a free variable
			sq_newclosure(vm, &sqVarGet, 1);
			sq_newslot(vm, -3, false);

			// pop the class
			sq_pop(vm, 1);
		}

		// Helper function used to bind getters and setters
		inline void BindAccessor(const SQChar* name, void* var, size_t varSize, SQFUNCTION func, HSQOBJECT table) {
			// Push the get or set table
			sq_pushobject(vm, table);
			sq_pushstring(vm, name, -1);

			// Push the variable offset as a free variable
			SQUserPointer varPtr = sq_newuserdata(vm, static_cast<SQUnsignedInteger>(varSize));
			memcpy(varPtr, var, varSize);

			// Create the accessor function
			sq_newclosure(vm, func, 1);

			// Add the accessor to the table
			sq_newslot(vm, -3, false);

			// Pop get/set table
			sq_pop(vm,-1);
		}

	};

	template<class C, class B, class A = DefaultAllocator<C> >
	class DerivedClass : public Class<C, A> {
	public:
		DerivedClass(HSQUIRRELVM v) : Class<C, A>(v, false) {
			if(!ClassType<C>::Initialized()) {
				sq_pushobject(v, ClassType<B>::ClassObject());
				sq_newclass(v, true);
				sq_getstackobj(v, -1, &ClassType<C>::ClassObject());

				sq_pop(v, -1);

				InitDerivedClass(v);
				ClassType<C>::Initialized() = true;
			}
		}

	protected:
		void InitDerivedClass(HSQUIRRELVM vm) {
			HSQOBJECT& classObj = ClassType<C>::ClassObject();
			HSQOBJECT& setTable = ClassType<C>::SetTable();
			HSQOBJECT& getTable = ClassType<C>::GetTable();

			// push the class
			sq_pushobject(vm, classObj);

			ClassType<C>::CopyFunc() = &A::Copy;

			// add the default constructor
			sq_pushstring(vm,_SC("constructor"), -1);
			sq_newclosure(vm, &A::New, 0);
			sq_newslot(vm, -3, false);

			// clone the base classes set table (static)
			sq_resetobject(&setTable);
			sq_pushobject(vm, setTable);
			sq_pushstring(vm,_SC("__setTable"), -1);
			sq_clone(vm, -2);
			sq_remove(vm, -3);
			sq_getstackobj(vm, -1, &setTable);
			sq_newslot(vm, -3, true);

			// clone the base classes get table (static)
			sq_resetobject(&getTable);
			sq_pushobject(vm, getTable);
			sq_pushstring(vm,_SC("__getTable"), -1);
			sq_clone(vm, -2);
			sq_remove(vm, -3);
			sq_getstackobj(vm, -1, &getTable);
			sq_newslot(vm, -3, true);

			// override _set
			sq_pushstring(vm, _SC("_set"), -1);
			sq_pushobject(vm, setTable); // Push the set table as a free variable
			sq_newclosure(vm, sqVarSet, 1);
			sq_newslot(vm, -3, false);

			// override _get
			sq_pushstring(vm, _SC("_get"), -1);
			sq_pushobject(vm, getTable); // Push the get table as a free variable
			sq_newclosure(vm, sqVarGet, 1);
			sq_newslot(vm, -3, false);

			// pop the class
			sq_pop(vm, 1);
		}
	};

}

#endif
