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

#include <gtest/gtest.h>
#include <sqrat.h>
#include "Vector.h"
#include "Fixture.h"

using namespace Sqrat;

const Sqrat::string Vec2ToString(const Vec2* v) {
	std::basic_stringstream<SQChar> out;
	out << _SC("Vec2(") << v->x << _SC(", ") << v->y << _SC(")");
	return out.str();
}

TEST_F(SqratTest, SimpleClassBinding) {
	DefaultVM::Set(vm);

	Class<Vec2> vec2;

	vec2
		// Variables
		.Var(_SC("x"), &Vec2::x)
		.Var(_SC("y"), &Vec2::y)
		
		// Operators
		.Func(_SC("_add"), &Vec2::operator +)
		.Func(_SC("_mul"), &Vec2::operator *)
		.Func(_SC("_div"), &Vec2::operator /)
		
		// Function Disambiguation
		.Func<Vec2 (Vec2::*)(void) const>(_SC("_unm"), &Vec2::operator -)
		.Func<Vec2 (Vec2::*)(const Vec2&) const>(_SC("_sub"), &Vec2::operator -)
		
		// Member Functions
		.Func(_SC("Length"), &Vec2::Length)
		.Func(_SC("Distance"), &Vec2::Distance)
		.Func(_SC("Normalize"), &Vec2::Normalize)
		.Func(_SC("Dot"), &Vec2::Dot)

		// Global Static Function bound as a member function
		.GlobalFunc(_SC("_tostring"), &Vec2ToString)
		;

	RootTable().Bind(_SC("Vec2"), vec2);

	Script script;

	try {
		script.CompileString(_SC(" \
			v <- Vec2(); \
			v.x = 1.2; \
			v.y = 3.4; \
			v *= 2.0; \
			gTest.EXPECT_FLOAT_EQ(2.4, v.x); \
			gTest.EXPECT_FLOAT_EQ(6.8, v.y); \
			::print(v + \"\\n\"); // Invokes _tostring \
			::print(\"Length:\" + v.Length() + \"\\n\"); \
			"));
	} catch(Exception ex) {
		FAIL() << _SC("Compile Failed: ") << ex.Message();
	}
	
	try {
		script.Run();
	} catch(Exception ex) {
		FAIL() << _SC("Run Failed: ") << ex.Message();
	}
}

class Animal {
public:
	virtual string Speak() { return _SC("[Silent]"); }
};

class Cat : public Animal {
public:
	virtual string Speak() { return _SC("Meow!"); }
};

class Dog : public Animal {
public:
	virtual string Speak() { return _SC("Woof!"); }
};

string MakeSpeak(Animal* a) {
	return a->Speak();
}

TEST_F(SqratTest, InheritedClassBinding) {
	DefaultVM::Set(vm);

	// Defining class definitions inline
	RootTable().Bind(_SC("Animal"), 
		Class<Animal>()
		.Func(_SC("Speak"), &Animal::Speak)
		);

	RootTable().Bind(_SC("Cat"), 
		DerivedClass<Cat, Animal>()
		.Func(_SC("Speak"), &Cat::Speak)
		);
	
	RootTable().Bind(_SC("Dog"),
		DerivedClass<Dog, Animal>()
		.Func(_SC("Speak"), &Dog::Speak)
		);

	RootTable().Func(_SC("MakeSpeak"), &MakeSpeak);

	Script script;

	try {
		script.CompileString(_SC(" \
			class Mouse extends Animal { \
				function Speak() { \
					return \"Squeak!\"; \
				} \
			} \
			\
			c <- Cat(); \
			d <- Dog(); \
			m <- Mouse(); \
			\
			gTest.EXPECT_STREQ(c.Speak(), \"Meow!\"); \
			gTest.EXPECT_STREQ(d.Speak(), \"Woof!\"); \
			gTest.EXPECT_STREQ(m.Speak(), \"Squeak!\"); \
			\
			gTest.EXPECT_STREQ(MakeSpeak(c), \"Meow!\"); \
			gTest.EXPECT_STREQ(MakeSpeak(d), \"Woof!\"); \
			/*gTest.EXPECT_STREQ(MakeSpeak(m), \"Squeak!\");*/ /* This will fail! Classes overridden in squirrel will be exposed as their base native class to C++ */ \
			"));
	} catch(Exception ex) {
		FAIL() << _SC("Compile Failed: ") << ex.Message();
	}
	
	try {
		script.Run();
	} catch(Exception ex) {
		FAIL() << _SC("Run Failed: ") << ex.Message();
	}
}