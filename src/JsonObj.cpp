#include "JsonObj.h"

#include <json-c/json.h>

namespace jsonxx {

namespace {

static JsonObj::Type fromImplType(const json_type implType) noexcept {
	switch (implType) {
	case json_type_null:
		return JsonObj::Type::null;
	case json_type_boolean:
		return JsonObj::Type::boolean;
	case json_type_double:
		return JsonObj::Type::number;
	case json_type_int:
		return JsonObj::Type::number;
	case json_type_object:
		return JsonObj::Type::object;
	case json_type_array:
		return JsonObj::Type::array;
	case json_type_string:
		return JsonObj::Type::string;
	}
	return JsonObj::Type::null;
}

constexpr json_object* getImpl(void* impl) {
	return reinterpret_cast<json_object*>(impl);
}

}

JsonObj::JsonObj(const JsonObj& src) :
		impl_ { src.impl_ },
		type_ { src.type_ } {
	json_object_get(getImpl(impl_));
}

JsonObj& JsonObj::operator=(const JsonObj& src) {
	json_object_put(getImpl(impl_));
	impl_ = src.impl_;
	type_ = src.type_;
	json_object_get(getImpl(impl_));
	return *this;
}

JsonObj::JsonObj(JsonObj&& src) :
		impl_ { src.impl_ },
		type_ { src.type_ } {

}

JsonObj& JsonObj::operator=(JsonObj&& src) {
	impl_ = src.impl_;
	type_ = src.type_;
	return *this;
}

JsonObj::JsonObj(const char* str) :
		impl_ { json_tokener_parse(str) },
		type_ { fromImplType(json_object_get_type(getImpl(impl_))) } {

}

JsonObj::JsonObj(void* impl) :
		impl_ { impl },
		type_ { fromImplType(json_object_get_type(getImpl(impl_))) } {
	json_object_get(getImpl(impl_));
}

JsonObj::~JsonObj() {
	json_object_put(getImpl(impl_));
}

JsonObj JsonObj::operator[](const std::string& key) const {
	return JsonObj(json_object_object_get(getImpl(impl_), key.c_str()));
}

JsonObj JsonObj::operator[](const size_t key) const {
	return JsonObj(json_object_array_get_idx(getImpl(impl_), key));
}

template<>
int JsonObj::to<int>() const {
	return json_object_get_int64(getImpl(impl_));
}

template<>
double JsonObj::to<double>() const {
	return json_object_get_double(getImpl(impl_));
}

template<>
std::string JsonObj::to<std::string>() const {
	return json_object_get_string(getImpl(impl_));
}

template<>
bool JsonObj::to<bool>() const {
	return json_object_get_boolean(getImpl(impl_));
}

}
