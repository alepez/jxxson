#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

struct Foo {
	const std::string a;
	const bool b;
	const int c;
	const double d;
	const std::vector<int> cc;
};

namespace jxxson {

template<>
Foo JsonObj::to<Foo>() const {
	auto& j = *this;
	return Foo {
		j["a"].to<std::string>(),
		j["b"].to<bool>(),
		j["c"].to<int>(),
		j["d"].to<double>(),
		j["cc"].to<std::vector<int>>()
	};
}

}

TEST(AJsonObj, CanBeCastToCustomObjectBySpecialization) {
	JsonObj obj("{\"a\": \"ciao\",\"b\": true,\"c\": 42,\"d\": 3.14, \"cc\":[4,8,15,16,23,42]}");
	auto foo = obj.to<Foo>();
	ASSERT_EQ("ciao", foo.a);
	ASSERT_EQ(true, foo.b);
	ASSERT_EQ(42, foo.c);
	ASSERT_EQ(3.14, foo.d);
	ASSERT_EQ(23, foo.cc[4]);
}
