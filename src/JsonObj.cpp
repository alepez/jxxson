#include "JsonObj.h"

#include <json-c/json.h>
#include <stdexcept>

namespace jxxson {

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
	json_object_get(getImpl(impl_));
}

JsonObj& JsonObj::operator=(JsonObj&& src) {
	json_object_put(getImpl(impl_));
	impl_ = src.impl_;
	type_ = src.type_;
	json_object_get(getImpl(impl_));
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
	json_object* impl = nullptr;
	if (!json_object_object_get_ex(getImpl(impl_), key.c_str(), &impl)) {
		throw std::out_of_range("undefined key");
	}
	return JsonObj(impl);
}

JsonObj JsonObj::operator[](const size_t key) const {
	auto impl = json_object_array_get_idx(getImpl(impl_), key);
	if (!impl) {
		throw std::out_of_range("undefined key");
	}
	return JsonObj(impl);
}

std::vector<JsonObj> JsonObj::toArray() const {
	if (type_ != Type::array) {
		throw std::runtime_error("not an array");
	}
	std::vector<JsonObj> result;
	for (int i = 0;; ++i) {
		json_object* impl = json_object_array_get_idx(getImpl(impl_), i);
		if (!impl) {
			break;
		}
		result.push_back(impl);
	}
	return result;
}

std::map<std::string, JsonObj> JsonObj::toHash() const {
	std::map<std::string, JsonObj> result;
	json_object_iterator it = json_object_iter_begin(getImpl(impl_));
	json_object_iterator end = json_object_iter_end(getImpl(impl_));
	while (!json_object_iter_equal(&it, &end)) {
		const char* name = json_object_iter_peek_name(&it);
		json_object* impl = json_object_iter_peek_value(&it);
		result.insert(std::make_pair<std::string, JsonObj>(name, impl));
		json_object_iter_next(&it);
	}
	return result;
}

}
