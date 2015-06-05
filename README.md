# jxxson

> A modern and elegant C++ interface to JSON data.

## Usage

````json
{
    "items": [
        {
            "name": "foo",
            "url": "http://example.com",
            "points": 23.4
        },
        {
            "name": "bar",
            "url": "http://example.net",
            "points": 42.15,
            "sequence": [4,8,15,16,23,42]
        }
    ]
}
````

Given `jsonString`, a string containing the json data above

````cpp
JsonObj obj{jsonString};
````

You can access nested objects with subscript operator:

````cpp
auto items = obj["items"];
````

You can access deeper object with multiple nested operators:

````cpp
auto url0 = obj["items"][0]["url"];
````

### Conversion

An object can be converted to any of: bool, int, double, std::string. It's done by JsonObj::to<T>() template function.

````cpp
auto url = obj["items"][1]["url"].to<std::string>();
````

But you can use a more familiar `static_cast`:

````cpp
auto url = static_cast<std::string>(obj["items"][1]["url"]);
````

And you can also save some typing with explicit initialization:

````cpp
std::string url { obj["items"][1]["url"] };
````

Only universal initialization works, the assignment operator `=` doesn't work. Implicit convertion is disabled, cause it can be harmful.

````cpp
std::string url = obj["items"][1]["url"]; // THIS DOES NOT WORK!!!
````

### Conversion to custom types

If primitive types aren't enough, you can bind custom types to json structures.

This works with all the examples below:

````cpp
    CustomType item(obj["items"][0]);
    // item.name == "foo";
    // item.url == "http://example.com";
    // item.points == 23.4;
````

#### Add a constructor to custom type

````cpp
struct CustomType {
    CustomType(const JsonObj& j) :
            name { j["name"] },
            url { j["url"] },
            points { j["points"] } {

    }
    const std::string name;
    const std::string url;
    const double points;
};
````
#### Add a `JsonObj::to<CustomType>()` specialization

````cpp
struct CustomType {
    const std::string name;
    const std::string url;
    const double points;
};

namespace jxxson {
template<>
CustomType JsonObj::to<CustomType>() const {
    auto& j = *this;
    return CustomType2 {
        j["name"].to<std::string>(),
        j["url"].to<std::string>(),
        j["points"].to<double>()
    };
}
}
````

#### Overload `translate` function

````cpp
struct CustomType {
    std::string name;
    std::string url;
    double points;
};

namespace jxxson {
void translate(CustomType& dst, const JsonObj& j) {
    translate(dst.name, j["name"]);
    translate(dst.url, j["url"]);
    translate(dst.points, j["points"]);
}
}
````


## Development

### Test

You can test with:

    make test

You can memcheck with:

    make memcheck

You can test code coverage with:

    make DEBUG=1 COVERAGE=1 coverage
