#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

TEST(AJsonObj, CanBeLoadedByString) {
	JsonObj obj("{\"foo\": 1}");
}

TEST(AJsonObj, CanBeNull) {
	JsonObj obj("{\"child\": null}");
	ASSERT_TRUE(obj["child"].isNull());
}

TEST(AJsonObj, CanBeBoolean) {
	JsonObj obj("{\"child\": true}");;
	ASSERT_TRUE(obj["child"].isBoolean());
}

TEST(AJsonObj, CanBeNumber) {
	JsonObj obj("{\"child\": 42}");;
	ASSERT_TRUE(obj["child"].isNumber());
}

TEST(AJsonObj, CanBeObject) {
	JsonObj obj("{\"child\":{\"foo\":42}}");;
	ASSERT_TRUE(obj["child"].isObject());
}

TEST(AJsonObj, CanBeArray) {
	JsonObj obj("{\"child\":[4,8,15,16,23,42]}");;
	ASSERT_TRUE(obj["child"].isArray());
}

TEST(AJsonObj, CanBeString) {
	JsonObj obj("{\"child\": \"ciao\"}");;
	ASSERT_TRUE(obj["child"].isString());
}

TEST(AJsonObj, CanBeConvertedToArray) {
	JsonObj obj("[1,2,3,4,5]");
	auto arr = obj.toArray();
	ASSERT_EQ(1, arr[0].to<int>());
	ASSERT_EQ(2, arr[1].to<int>());
	ASSERT_EQ(3, arr[2].to<int>());
	std::string keys = "";
	int values = 0;
	for (const auto& j: arr) {
		values += j.to<int>();
	}
	ASSERT_EQ(15, values);
}

TEST(AJsonObj, CanBeConvertedToHash) {
	JsonObj obj("{\"a\": 1, \"b\": 2, \"c\": 3}");
	auto hash = obj.toHash();
	ASSERT_EQ(1, hash.at("a").to<int>());
	ASSERT_EQ(2, hash.at("b").to<int>());
	ASSERT_EQ(3, hash.at("c").to<int>());
	std::string keys = "";
	int values = 0;
	for (const auto& it: hash) {
		keys+= it.first;
		values += it.second.to<int>();
	}
	ASSERT_EQ(6, values);
	ASSERT_EQ("abc", keys);
}

TEST(AJsonObj, CanBeCopyConstructed) {
	JsonObj obj("{\"child\": \"ciao\"}");;
	JsonObj obj2 = obj;
	JsonObj obj3 = obj;
	JsonObj obj4 = obj;
	ASSERT_EQ("ciao", obj3["child"].to<std::string>());
	ASSERT_TRUE(obj4["child"].isString());
}

TEST(AJsonObj, CanBeCopied) {
	JsonObj obj("{\"child\": \"ciao\"}");;
	JsonObj obj2 = obj;
	JsonObj obj3 = obj;
	obj3 = obj2;
	obj2 = obj;
	ASSERT_EQ("ciao", obj3["child"].to<std::string>());
	ASSERT_TRUE(obj["child"].isString());
}

TEST(AJsonObj, CanBeCopyMoved) {
	JsonObj obj2 = []{
		JsonObj obj("{\"child\": \"ciao\"}");;
		return obj;
	}();
	ASSERT_EQ("ciao", obj2["child"].to<std::string>());
	ASSERT_TRUE(obj2["child"].isString());
}


TEST(AJsonObj, CanBeMoved) {
	JsonObj obj2("{}");
	obj2 = []{
		JsonObj obj("{\"child\": \"ciao\"}");;
		return obj;
	}();
	ASSERT_EQ("ciao", obj2["child"].to<std::string>());
	ASSERT_TRUE(obj2["child"].isString());
}
