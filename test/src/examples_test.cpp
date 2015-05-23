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
