#ifndef SRC_TRANSLATORS_H_
#define SRC_TRANSLATORS_H_

#include <vector>
#include <string>
#include "JsonObj.h"

namespace jxxson {

class JsonObj;

template<typename T>
void array_translate(std::vector<T>& dst, const JsonObj& src) {
	auto arr = src.toArray();
	for (const auto& el : arr) {
		dst.push_back(el.to<T>());
	}
}

void translate(bool& dst, const JsonObj& src);
void translate(int& dst, const JsonObj& src);
void translate(double& dst, const JsonObj& src);
void translate(std::string& dst, const JsonObj& src);

void translate(char& dst, const JsonObj& src);
void translate(unsigned char& dst, const JsonObj& src);
void translate(unsigned int& dst, const JsonObj& src);
void translate(float& dst, const JsonObj& src);

void translate(std::vector<bool>& dst, const JsonObj& src);
void translate(std::vector<char>& dst, const JsonObj& src);
void translate(std::vector<unsigned char>& dst, const JsonObj& src);
void translate(std::vector<int>& dst, const JsonObj& src);
void translate(std::vector<unsigned int>& dst, const JsonObj& src);
void translate(std::vector<float>& dst, const JsonObj& src);
void translate(std::vector<double>& dst, const JsonObj& src);
void translate(std::vector<std::string>& dst, const JsonObj& src);

} /* namespace jxxson */

#endif /* SRC_TRANSLATORS_H_ */
