#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

TEST(AJsonObj, CanBeLoadedByString) {
	JsonObj obj("{\"foo\": 1}");
}

TEST(AJsonObj, CanReadNullChild) {
	JsonObj obj("{\"child\": null}");
	ASSERT_TRUE(obj["child"].isNull());
}

TEST(AJsonObj, CanReadBooleanChild) {
	JsonObj obj("{\"child\": true}");;
	ASSERT_EQ(true, obj["child"].to<bool>());
	ASSERT_TRUE(obj["child"].isBoolean());
}

TEST(AJsonObj, CanReadIntegerNumberChild) {
	JsonObj obj("{\"child\": 42}");;
	ASSERT_EQ(42, obj["child"].to<int>());
	ASSERT_EQ(42, static_cast<int>(obj["child"]));
	int child = obj["child"];
	ASSERT_EQ(42, child);
	ASSERT_TRUE(obj["child"].isNumber());
}

TEST(AJsonObj, CanReadFloatingNumberChild) {
	JsonObj obj("{\"child\": 1.234}");;
	ASSERT_EQ(1.234, obj["child"].to<double>());
	ASSERT_TRUE(obj["child"].isNumber());
}

TEST(AJsonObj, CanReadObjectChild) {
	JsonObj obj("{\"child\":{\"foo\":42}}");;
	ASSERT_EQ(42, obj["child"]["foo"].to<int>());
	ASSERT_TRUE(obj["child"].isObject());
}

TEST(AJsonObj, CanReadArrayChild) {
	JsonObj obj("{\"child\":[4,8,15,16,23,42]}");;
	ASSERT_EQ(23, obj["child"][4].to<int>());
	ASSERT_TRUE(obj["child"].isArray());
}

TEST(AJsonObj, CanReadStringChild) {
	JsonObj obj("{\"child\": \"ciao\"}");;
	ASSERT_EQ("ciao", obj["child"].to<std::string>());
	ASSERT_TRUE(obj["child"].isString());
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

TEST(AJsonObj, CanBeMoved) {
	JsonObj obj2 = []{
		JsonObj obj("{\"child\": \"ciao\"}");;
		return obj;
	}();
	ASSERT_EQ("ciao", obj2["child"].to<std::string>());
	ASSERT_TRUE(obj2["child"].isString());
}
