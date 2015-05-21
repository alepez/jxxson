#include <gtest/gtest.h>

#include <JsonObj.h>

using namespace jsonxx;

struct Foo {
	std::string a;
	bool b;
	int c;
	double d;
};

namespace jsonxx {

template<>
Foo JsonObj::to<Foo>() const {
	auto& j = *this;
	return Foo {
		j["a"], j["b"], j["c"], j["d"]
	};
}

}

TEST(AJsonObj, CanBeCastedToACustomObject) {
	JsonObj obj("{\"a\": \"ciao\",\"b\": true,\"c\": 42,\"d\": 3.14}");
	Foo foo = obj;
	ASSERT_EQ("ciao", foo.a);
	ASSERT_EQ(true, foo.b);
	ASSERT_EQ(42, foo.c);
	ASSERT_EQ(3.14, foo.d);
}
