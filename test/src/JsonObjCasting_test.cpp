#include <gtest/gtest.h>

#include <JsonObj.h>

using namespace jxxson;

struct Foo {
	std::string a;
	bool b;
	int c;
	double d;
	std::vector<int> cc;
};

namespace jxxson {

template<>
Foo JsonObj::to<Foo>() const {
	auto& j = *this;
	return Foo {
		j["a"], j["b"], j["c"], j["d"], j["cc"]
	};
}

}

TEST(AJsonObj, CanBeCastedToACustomObject) {
	JsonObj obj("{\"a\": \"ciao\",\"b\": true,\"c\": 42,\"d\": 3.14, \"cc\":[4,8,15,16,23,42]}");
	Foo foo = obj;
	ASSERT_EQ("ciao", foo.a);
	ASSERT_EQ(true, foo.b);
	ASSERT_EQ(42, foo.c);
	ASSERT_EQ(3.14, foo.d);
	ASSERT_EQ(23, foo.cc[4]);
}
