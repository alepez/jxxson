#ifndef SRC_JSONOBJ_H_
#define SRC_JSONOBJ_H_

#include <string>
#include <vector>
#include <map>

namespace jxxson {

class JsonObj {
public:
	enum class Type {
		null, boolean, number, object, array, string
	};

	/** create a JsonObj from json rapresentation */
	JsonObj(const char* str);

	/** can be copy constructed */
	JsonObj(const JsonObj&);

	/** can be copied */
	JsonObj& operator=(const JsonObj&);

	/** can be move contructed */
	JsonObj(JsonObj&&);

	/** can be moved */
	JsonObj& operator=(JsonObj&&);

	/** destructor is needed */
	~JsonObj();

	/** access a child by name (if it is of type object) */
	JsonObj operator[](const std::string&) const;

	/** access a child by index (if it is of type array) */
	JsonObj operator[](const size_t) const;

	/** return true it is null */
	bool isNull() const {
		return type_ == Type::null;
	}

	/** return true it is a boolean */
	bool isBoolean() const {
		return type_ == Type::boolean;
	}

	/** return true it is a number */
	bool isNumber() const {
		return type_ == Type::number;
	}

	/** return true it is an object */
	bool isObject() const {
		return type_ == Type::object;
	}

	/** return true it is an array */
	bool isArray() const {
		return type_ == Type::array;
	}

	/** return true it is a string */
	bool isString() const {
		return type_ == Type::string;
	}

	/** explicit cast to type T */
	template<typename T>
	T to() const;

	/** implicit cast to type T */
	template<typename T>
	operator T() const {
		return this->to<T>();
	}

	/** get a collection of T (if it is of type array) */
	template<typename T>
	std::vector<T> coll() const {
		std::vector<T> result;
		auto arr = this->toArray();
		for (const auto& el: arr) {
			result.push_back(el.to<T>());
		}
		return result;
	}

private:
	JsonObj(void* impl);
	std::vector<JsonObj> toArray() const;
	std::map<std::string, JsonObj> toHash() const;
	void* impl_;
	Type type_;
};

/* Specializations for primitives and string */

template<>
int JsonObj::to<int>() const;

template<>
double JsonObj::to<double>() const;

template<>
std::string JsonObj::to<std::string>() const;

template<>
bool JsonObj::to<bool>() const;


template<>
std::vector<int> JsonObj::to<std::vector<int>>() const;

template<>
std::vector<double> JsonObj::to<std::vector<double>>() const;

template<>
std::vector<std::string> JsonObj::to<std::vector<std::string>>() const;

template<>
 std::vector<bool> JsonObj::to<std::vector<bool>>() const;

}

#endif /* SRC_JSONOBJ_H_ */
