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

}

JsonObj::JsonObj(const char* str) :
		impl_ { json_tokener_parse(str) },
		type_ { fromImplType(json_object_get_type(reinterpret_cast<json_object*>(impl_))) } {

}

JsonObj::JsonObj(void* impl) :
		impl_ { impl },
		type_ { fromImplType(json_object_get_type(reinterpret_cast<json_object*>(impl_))) } {
	json_object_get(reinterpret_cast<json_object*>(impl_));
}

JsonObj::~JsonObj() {
	json_object_put(reinterpret_cast<json_object*>(impl_));
}

JsonObj JsonObj::operator[](const std::string& name) const {
	return JsonObj(json_object_object_get(reinterpret_cast<json_object*>(impl_), name.c_str()));
}

template<>
int JsonObj::to<int>() const {
	return json_object_get_int64(reinterpret_cast<json_object*>(impl_));
}

template<>
double JsonObj::to<double>() const {
	return json_object_get_double(reinterpret_cast<json_object*>(impl_));
}

template<>
std::string JsonObj::to<std::string>() const {
	return json_object_get_string(reinterpret_cast<json_object*>(impl_));
}

template<>
bool JsonObj::to<bool>() const {
	return json_object_get_boolean(reinterpret_cast<json_object*>(impl_));
}

}
