#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

struct Foo {
	std::string a;
	bool b;
	int c;
	double d;
	std::vector<int> cc;
};

namespace jxxson {

void translate(Foo& dst, const JsonObj& j) {
	translate(dst.a, j["a"]);
	translate(dst.b, j["b"]);
	translate(dst.c, j["c"]);
	translate(dst.d, j["d"]);
	translate(dst.cc, j["cc"]);
}

}

TEST(AJsonObj, CanBeCastToCustomObjectByTranslator) {
	/* FIXME this isn't working */
	JsonObj obj("{\"a\": \"ciao\",\"b\": true,\"c\": 42,\"d\": 3.14, \"cc\":[4,8,15,16,23,42]}");
	Foo foo = static_cast<Foo>(obj);
	ASSERT_EQ("ciao", foo.a);
	ASSERT_EQ(true, foo.b);
	ASSERT_EQ(42, foo.c);
	ASSERT_EQ(3.14, foo.d);
	ASSERT_EQ(23, foo.cc[4]);
}
