#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

struct Example: public ::testing::Test {
	const char* jsonString =
		"{\"items\":[{\"name\":\"foo\",\"url\":\"http://example.com\",\"points\":23.4},{\"name\":\"bar\",\"url\":\"http://example.net\",\"points\":42.15,\"sequence\":[4,8,15,16,23,42]}]}";
	JsonObj obj { jsonString };
};

TEST_F(Example, SubscriptOperatorCanRetrieveAChild) {
	auto items = obj["items"];
	ASSERT_TRUE(items.isArray());
	auto item0 = obj["items"][0];
	ASSERT_TRUE(item0.isObject());
	auto url0 = obj["items"][0]["url"];
	ASSERT_TRUE(url0.isString());
}

TEST_F(Example, AChildCanBeCastToAPrimitiveTypeWithToMethod) {
	auto url = obj["items"][1]["url"].to<std::string>();
	ASSERT_EQ("http://example.net", url);
}

TEST_F(Example, AChildCanBeCastToAPrimitiveTypeWithStaticCast) {
	auto url = static_cast<std::string>(obj["items"][1]["url"]);
	ASSERT_EQ("http://example.net", url);
}

TEST_F(Example, AChildCanBeCastToAPrimitiveTypeWithExplicitInitialization) {
	std::string url { obj["items"][1]["url"] };
	// std::string url = obj["items"][1]["url"]; This is implicit, it doesn't work
	ASSERT_EQ("http://example.net", url);
}

struct CustomType1 {
	CustomType1(const JsonObj& j) :
			name { j["name"] },
			url { j["url"] },
			points { j["points"] } {

	}
	const std::string name;
	const std::string url;
	const double points;
};

TEST_F(Example, ACustomTypeExample1) {
	CustomType1 item(obj["items"][0]);
	ASSERT_EQ("foo", item.name);
	ASSERT_EQ("http://example.com", item.url);
	ASSERT_EQ(23.4, item.points);
}

struct CustomType2 {
	const std::string name;
	const std::string url;
	const double points;
};

namespace jxxson {
template<>
CustomType2 JsonObj::to<CustomType2>() const {
	auto& j = *this;
	return CustomType2 {
		j["name"].to<std::string>(),
		j["url"].to<std::string>(),
		j["points"].to<double>()
	};
}
}

TEST_F(Example, ACustomTypeExample2) {
	CustomType2 item(obj["items"][0]);
	ASSERT_EQ("foo", item.name);
	ASSERT_EQ("http://example.com", item.url);
	ASSERT_EQ(23.4, item.points);
}

struct CustomType3 {
	std::string name;
	std::string url;
	double points;
};

namespace jxxson {
void translate(CustomType3& dst, const JsonObj& j) {
	translate(dst.name, j["name"]);
	translate(dst.url, j["url"]);
	translate(dst.points, j["points"]);
}
}

TEST_F(Example, ACustomTypeExample3) {
	CustomType3 item(obj["items"][0]);
	ASSERT_EQ("foo", item.name);
	ASSERT_EQ("http://example.com", item.url);
	ASSERT_EQ(23.4, item.points);
}
