#ifndef SRC_JSONOBJ_H_
#define SRC_JSONOBJ_H_

#include <string>
#include <vector>
#include <map>
#include <type_traits>

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

	/** map all children to a hash (if it is of type array) */
	std::map<std::string, JsonObj> toHash() const;

	/** map all children to a vector (if it is of type array) */
	std::vector<JsonObj> toArray() const;

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
	T to() const {
		using TT = typename std::remove_const<T>::type;
		TT result;
		translate(result, *this);
		return result;
	}

	/** automatic cast to type T */
	template<typename T>
	explicit operator T() const {
		return this->to<T>();
	}

//	/** automatic cast to type T */
//	template<typename T>
//	explicit operator const T() const {
//		return this->to<T>();
//	}


private:
	/** translator to json primitive types */
	friend void translate(bool& dst, const JsonObj& src);
	friend void translate(int& dst, const JsonObj& src);
	friend void translate(double& dst, const JsonObj& src);
	friend void translate(std::string& dst, const JsonObj& src);

	JsonObj(void* impl);
	void* impl_;
	Type type_;
};

}

#endif /* SRC_JSONOBJ_H_ */
