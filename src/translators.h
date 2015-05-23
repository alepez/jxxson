#ifndef SRC_TRANSLATORS_H_
#define SRC_TRANSLATORS_H_

#include <vector>
#include <string>
#include "JsonObj.h"

namespace jxxson {

class JsonObj;

template<typename T>
void array_translator(std::vector<T>& dst, const JsonObj& src) {
	auto arr = src.toArray();
	for (const auto& el : arr) {
		dst.push_back(el.to<T>());
	}
}

void translator(bool& dst, const JsonObj& src);
void translator(int& dst, const JsonObj& src);
void translator(double& dst, const JsonObj& src);
void translator(std::string& dst, const JsonObj& src);

void translator(char& dst, const JsonObj& src);
void translator(unsigned char& dst, const JsonObj& src);
void translator(unsigned int& dst, const JsonObj& src);
void translator(float& dst, const JsonObj& src);

void translator(std::vector<bool>& dst, const JsonObj& src);
void translator(std::vector<char>& dst, const JsonObj& src);
void translator(std::vector<unsigned char>& dst, const JsonObj& src);
void translator(std::vector<int>& dst, const JsonObj& src);
void translator(std::vector<unsigned int>& dst, const JsonObj& src);
void translator(std::vector<float>& dst, const JsonObj& src);
void translator(std::vector<double>& dst, const JsonObj& src);
void translator(std::vector<std::string>& dst, const JsonObj& src);

} /* namespace jxxson */

#endif /* SRC_TRANSLATORS_H_ */
