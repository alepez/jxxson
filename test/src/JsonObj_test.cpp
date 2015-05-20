#include <gtest/gtest.h>

#include <JsonObj.h>

using namespace jsonxx;

TEST(AJsonObj, CanBeLoadedByString) {
	JsonObj obj("{\"foo\": 1}");
	ASSERT_EQ(JsonObj::Type::object, obj.type());
}

TEST(AJsonObj, CanReadNullChild) {
	JsonObj obj("{\"child\": null}");
	ASSERT_EQ(JsonObj::Type::null, obj["child"].type());
	ASSERT_TRUE(obj["child"].isNull());
}

TEST(AJsonObj, CanReadBooleanChild) {
	JsonObj obj("{\"child\": true}");;
	ASSERT_EQ(JsonObj::Type::boolean, obj["child"].type());
	ASSERT_EQ(true, obj["child"].to<bool>());
	ASSERT_TRUE(obj["child"].isBoolean());
}

TEST(AJsonObj, CanReadIntegerNumberChild) {
	JsonObj obj("{\"child\": 42}");;
	ASSERT_EQ(JsonObj::Type::number, obj["child"].type());
	ASSERT_EQ(42, obj["child"].to<int>());
	ASSERT_EQ(42, static_cast<int>(obj["child"]));
	int child = obj["child"];
	ASSERT_EQ(42, child);
	ASSERT_TRUE(obj["child"].isNumber());
}

TEST(AJsonObj, CanReadFloatingNumberChild) {
	JsonObj obj("{\"child\": 1.234}");;
	ASSERT_EQ(JsonObj::Type::number, obj["child"].type());
	ASSERT_EQ(1.234, obj["child"].to<double>());
	ASSERT_TRUE(obj["child"].isNumber());
}

TEST(AJsonObj, CanReadObjectChild) {
	JsonObj obj("{\"child\":{\"foo\":1}}");;
	ASSERT_EQ(JsonObj::Type::object, obj["child"].type());
	ASSERT_TRUE(obj["child"].isObject());
}

TEST(AJsonObj, CanReadArrayChild) {
	JsonObj obj("{\"child\":[4,8,15,16,23,42]}");;
	ASSERT_EQ(JsonObj::Type::array, obj["child"].type());
	ASSERT_TRUE(obj["child"].isArray());
}

TEST(AJsonObj, CanReadStringChild) {
	JsonObj obj("{\"child\": \"ciao\"}");;
	ASSERT_EQ(JsonObj::Type::string, obj["child"].type());
	ASSERT_EQ("ciao", obj["child"].to<std::string>());
	ASSERT_TRUE(obj["child"].isString());
}
