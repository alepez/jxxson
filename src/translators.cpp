#include "translators.h"

#include "JsonObj.h"
#include <json-c/json.h>

namespace jxxson {

/****************************** primitive types ******************************/

void translate(bool& dst, const JsonObj& src) {
	dst = json_object_get_boolean(reinterpret_cast<json_object*>(src.impl_));
}

void translate(int& dst, const JsonObj& src) {
	dst = json_object_get_int64(reinterpret_cast<json_object*>(src.impl_));
}

void translate(double& dst, const JsonObj& src) {
	dst = json_object_get_double(reinterpret_cast<json_object*>(src.impl_));
}

void translate(std::string& dst, const JsonObj& src) {
	dst = json_object_get_string(reinterpret_cast<json_object*>(src.impl_));
}

/****************************** c++ primitives ********************************/

void translate(char& dst, const JsonObj& src) {
	if (src.isNumber()) {
		int result;
		translate(result, src);
		dst = result;
	} else if (src.isString()) {
		std::string result;
		translate(result, src);
		if (result.size() > 0) {
			dst = result[0];
		} else {
			dst = '\0';
		}
	}
}

void translate(unsigned char& dst, const JsonObj& src) {
	int result;
	translate(result, src);
	dst = result;
}

void translate(unsigned int& dst, const JsonObj& src) {
	int result;
	translate(result, src);
	dst = result;
}

void translate(float& dst, const JsonObj& src) {
	double result;
	translate(result, src);
	dst = result;
}

/****************************** array of primitivs ****************************/

void translate(std::vector<bool>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<char>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<unsigned char>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<int>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<unsigned int>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<float>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<double>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

void translate(std::vector<std::string>& dst, const JsonObj& src) {
	array_translate(dst, src);
}

} /* namespace jxxson */
