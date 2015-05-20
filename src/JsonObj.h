#ifndef SRC_JSONOBJ_H_
#define SRC_JSONOBJ_H_

#include <string>

namespace jsonxx {

class JsonObj {
public:
	enum class Type {
		null, boolean, number, object, array, string
	};

	JsonObj(const char* str);

	~JsonObj();

	inline Type type() const {
		return type_;
	}

	JsonObj operator[](const std::string&) const;

	bool isNull() const {
		return type_ == Type::null;
	}

	bool isBoolean() const {
		return type_ == Type::boolean;
	}

	bool isNumber() const {
		return type_ == Type::number;
	}

	bool isObject() const {
		return type_ == Type::object;
	}

	bool isArray() const {
		return type_ == Type::array;
	}

	bool isString() const {
		return type_ == Type::string;
	}

	template<typename T>
	T to() const;

	template<typename T>
	operator T() const {
		return this->to<T>();
	}

private:
	JsonObj(void* impl);
	void* const impl_;
	const Type type_;
};

template<>
int JsonObj::to<int>() const;

template<>
double JsonObj::to<double>() const;

template<>
std::string JsonObj::to<std::string>() const;

template<>
bool JsonObj::to<bool>() const;

}

#endif /* SRC_JSONOBJ_H_ */
