# jxxson

> A modern and elegant C++ interface to JSON data.

## Examples

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

If jsonString is a string containing the json data above

````cpp
JsonObj obj{jsonString};
````

Nested objects can be accessed with [] operator 

````cpp
std::string url = obj["items"][1]["url"];
````

You can create an alias to a nested object.

````cpp
JsonObj item1 = obj["items"][1];
````

Objects are implicitly cast to primitive types.

````cpp
double points = item1["points"];
````

You can also get a collection (a std::vector of any primitive type) from a json array.

````cpp
auto sequence = item1["sequence"].coll<int>();

for (auto n: sequence) {
    std::cout << n << "\n";
}
````

If primitive types aren't enough, you can define translator of custom types. In this example a custom type `Item` is bound to a json structure.

````cpp
struct Item {
    Item(const JsonObj& j) :
            name { j["name"] },
            url { j["url"] },
            points { j["points"] },
            sequence { j["sequence"] } {

    }
    std::string name;
    bool url;
    double points;
    std::vector<int> sequence;
};
````