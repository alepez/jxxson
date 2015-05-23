#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

struct Foo {
	Foo(const JsonObj& j) :
			a { j["a"] },
			b { j["b"] },
			c { j["c"] },
			d { j["d"] },
			cc { j["cc"] } {

	}
	const std::string a;
	const bool b;
	const int c;
	const double d;
	const std::vector<int> cc;
};

TEST(AJsonObj, CanBeCastToCustomObjectByConstructor) {
	JsonObj obj("{\"a\": \"ciao\",\"b\": true,\"c\": 42,\"d\": 3.14, \"cc\":[4,8,15,16,23,42]}");
	Foo foo = obj;
	ASSERT_EQ(std::string("ciao"), std::string(foo.a));
	ASSERT_EQ(true, foo.b);
	ASSERT_EQ(42, foo.c);
	ASSERT_EQ(3.14, foo.d);
	ASSERT_EQ(23, foo.cc[4]);
}
