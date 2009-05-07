//
// ScratTypes: Type Translators
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

#if !defined(_SCRAT_TYPES_H_)
#define _SCRAT_TYPES_H_

#include <squirrel.h>
#include <string>

namespace Scrat {

	//
	// Generic Variable Template
	//

	template<class T>
	class VarType {
	public:
		static T& get(HSQUIRRELVM vm, SQInteger idx) {
			return *Class<T>::GetInstance(vm, idx);
		}
		static void push(HSQUIRRELVM vm, T& value) {
			Class<T>::PushInstanceCopy(vm, value);
		}
		static void push(HSQUIRRELVM vm, T* value) {
			Class<T>::PushInstance(vm, value);
		}
	};

	//
	// Variable Specializations
	//

	//
	// Integer
	//

	#define SCRAT_INTEGER( type ) \
	template<> \
	class VarType<type> { \
	public: \
		static type get(HSQUIRRELVM vm, SQInteger idx) { \
			SQInteger value; \
			sq_getinteger(vm, idx, &value); \
			return static_cast<type>(value); \
		} \
		static void push(HSQUIRRELVM vm, type& value) { \
			sq_pushinteger(vm, static_cast<SQInteger>(value)); \
		} \
	};
	
	SCRAT_INTEGER(unsigned int)
	SCRAT_INTEGER(signed int)
	SCRAT_INTEGER(unsigned long)
	SCRAT_INTEGER(signed long)
	SCRAT_INTEGER(unsigned short)
	SCRAT_INTEGER(signed short)

#if defined(__int64)
	SCRAT_INTEGER(unsigned __int64)
	SCRAT_INTEGER(signed __int64)
#endif
	
	//
	// Float
	//

	#define SCRAT_FLOAT( type ) \
	template<> \
	class VarType<type> { \
	public: \
		static type get(HSQUIRRELVM vm, SQInteger idx) { \
			SQFloat value; \
			sq_getfloat(vm, idx, &value); \
			return static_cast<type>(value); \
		} \
		static void push(HSQUIRRELVM vm, type& value) { \
			sq_pushfloat(vm, static_cast<SQFloat>(value)); \
		} \
	};

	SCRAT_FLOAT(float)
	SCRAT_FLOAT(double)

	//
	// Bool
	//

	template<>
	class VarType<bool> {
	public:
		static bool get(HSQUIRRELVM vm, SQInteger idx) {
			SQBool value;
			sq_tobool(vm, idx, &value);
			return (value != 0);
		}
		static void push(HSQUIRRELVM vm, bool& value) {
			sq_pushbool(vm, static_cast<SQBool>(value));
		}
	};

	//
	// String
	//

	template<>
	class VarType<const SQChar*> {
	public:
		static const SQChar* get(HSQUIRRELVM vm, SQInteger idx) {
			const SQChar* ret;
			sq_tostring(vm, idx);
			sq_getstring(vm, -1, &ret);
			return ret;
		}
		static void push(HSQUIRRELVM vm, const SQChar* value) {
			sq_pushstring(vm, value, -1);
		}
	};
	
	template<>
	class VarType<std::basic_string<SQChar>> {
	public:
		static std::wstring get(HSQUIRRELVM vm, SQInteger idx) {
			const SQChar* ret;
			sq_tostring(vm, idx);
			sq_getstring(vm, -1, &ret);
			return std::wstring(ret);
		}
		static void push(HSQUIRRELVM vm, std::wstring value) {
			sq_pushstring(vm, value.c_str(), -1);
		}
	};

	//
	// Variable Accessors
	//

	template<class T> struct TypeWrapper {};
		
	// Get
	template<class T>
	inline T GetVar(TypeWrapper<T>, HSQUIRRELVM vm, SQInteger idx) {
		return VarType<T>::get(vm, idx);
	}

	template<class T>
	inline T& GetVar(TypeWrapper<T&>, HSQUIRRELVM vm, SQInteger idx) {
		return VarType<T>::get(vm, idx);
	}

	template<class T>
	inline T* GetVar(TypeWrapper<T*>, HSQUIRRELVM vm, SQInteger idx) {
		return &VarType<T>::get(vm, idx);
	}

	template<class T>
	inline const T& GetVar(TypeWrapper<const T&>, HSQUIRRELVM vm, SQInteger idx) {
		return VarType<T>::get(vm, idx);
	}

	template<class T>
	inline const T* GetVar(TypeWrapper<const T*>, HSQUIRRELVM vm, SQInteger idx) {
		return &VarType<T>::get(vm, idx);
	}
	
	// Push
	template<class T>
	inline void PushVar(HSQUIRRELVM vm, T& value) {
		VarType<T>::push(vm, value);
	}

	template<class T>
	inline void PushVar(HSQUIRRELVM vm, T* value) {
		VarType<T>::push(vm, *value);
	}

	template<class T>
	inline void PushVar(HSQUIRRELVM vm, const T& value) {
		VarType<T>::push(vm, const_cast<T&>(value));
	}

	template<class T>
	inline void PushVar(HSQUIRRELVM vm, const T* value) {
		VarType<T>::push(vm, const_cast<T&>(*value));
	}

	// Special case for text (Don't know how else to do it)
	template<>
	inline const SQChar* GetVar<SQChar>(TypeWrapper<const SQChar*>, HSQUIRRELVM vm, SQInteger idx) {
		return VarType<const SQChar*>::get(vm, idx);
	}

	template<>
	inline void PushVar<SQChar>(HSQUIRRELVM vm, const SQChar* value) {
		VarType<const SQChar*>::push(vm, value);
	}

}

#endif