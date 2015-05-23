#include <gtest/gtest.h>

#include <jxxson.h>

using namespace jxxson;

TEST(Translator, CanTranslateToBool) {
  bool dst;
  JsonObj j("{\"data\": true}");
  translate(dst, j["data"]);
  ASSERT_EQ(true, dst);
}

TEST(Translator, CanTranslateToInt) {
  int dst;
  JsonObj j("{\"data\": -42}");
  translate(dst, j["data"]);
  ASSERT_EQ(-42, dst);
}

TEST(Translator, CanTranslateToDouble) {
  double dst;
  JsonObj j("{\"data\": 12.34}");
  translate(dst, j["data"]);
  ASSERT_EQ(12.34, dst);
}

TEST(Translator, CanTranslateToString) {
  std::string dst;
  JsonObj j("{\"data\": \"ciao\"}");
  translate(dst, j["data"]);
  ASSERT_EQ("ciao", dst);
}

TEST(Translator, CanTranslateToCharWhenDataIsString) {
  char dst;
  JsonObj j("{\"data\": \"x\"}");
  translate(dst, j["data"]);
  ASSERT_DOUBLE_EQ('x', dst);
}

TEST(Translator, CanTranslateToCharWhenDataIsNumber) {
  char dst;
  JsonObj j("{\"data\": 78}");
  translate(dst, j["data"]);
  ASSERT_EQ(78, dst);
}

TEST(Translator, CanTranslateToUnsignedChar) {
  unsigned char dst;
  JsonObj j("{\"data\": 78}");
  translate(dst, j["data"]);
  ASSERT_EQ(78, dst);
}

TEST(Translator, CanTranslateToUnsignedInt) {
  unsigned int dst;
  JsonObj j("{\"data\": 999999}");
  translate(dst, j["data"]);
  ASSERT_EQ(999999, dst);
}

TEST(Translator, CanTranslateToFloat) {
  float dst;
  JsonObj j("{\"data\": 45.67}");
  translate(dst, j["data"]);
  ASSERT_FLOAT_EQ(45.67, dst);
}

TEST(Translator, CanTranslateToVectorOfBool) {
  std::vector<bool> dst;
  JsonObj j("{\"data\": [true,false,true,false]}");
  translate(dst, j["data"]);
  ASSERT_EQ(true, dst[0]);
  ASSERT_EQ(false, dst[1]);
  ASSERT_EQ(true, dst[2]);
  ASSERT_EQ(false, dst[3]);
}

TEST(Translator, CanTranslateToVectorOfString) {
  std::vector<std::string> dst;
  JsonObj j("{\"data\": [\"Donatello\",\"Leonardo\",\"Michelangelo\",\"Raffaello\"]}");
  translate(dst, j["data"]);
  ASSERT_EQ("Donatello", dst[0]);
  ASSERT_EQ("Leonardo", dst[1]);
  ASSERT_EQ("Michelangelo", dst[2]);
  ASSERT_EQ("Raffaello", dst[3]);
}
