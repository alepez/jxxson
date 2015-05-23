#include "translators.h"

#include "JsonObj.h"
#include <json-c/json.h>

namespace jxxson {

/****************************** primitive types ******************************/

void translator(bool& dst, const JsonObj& src) {
	dst = json_object_get_boolean(reinterpret_cast<json_object*>(src.impl_));
}

void translator(int& dst, const JsonObj& src) {
	dst = json_object_get_int64(reinterpret_cast<json_object*>(src.impl_));
}

void translator(double& dst, const JsonObj& src) {
	dst = json_object_get_double(reinterpret_cast<json_object*>(src.impl_));
}

void translator(std::string& dst, const JsonObj& src) {
	dst = json_object_get_string(reinterpret_cast<json_object*>(src.impl_));
}

/****************************** c++ primitives ********************************/

void translator(char& dst, const JsonObj& src) {
	int result;
	translator(result, src);
	dst = result;
}

void translator(unsigned char& dst, const JsonObj& src) {
	int result;
	translator(result, src);
	dst = result;
}

void translator(unsigned int& dst, const JsonObj& src) {
	int result;
	translator(result, src);
	dst = result;
}

void translator(float& dst, const JsonObj& src) {
	double result;
	translator(result, src);
	dst = result;
}

/****************************** array of primitivs ****************************/

void translator(std::vector<bool>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<char>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<unsigned char>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<int>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<unsigned int>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<float>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<double>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

void translator(std::vector<std::string>& dst, const JsonObj& src) {
	array_translator(dst, src);
}

} /* namespace jxxson */
