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

If jsonString is a string containing the json data above

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

Only universal initialization works, the old one with `=` doesn't work. Implicit convertion operator is disabled, cause it can be armful.

````cpp
std::string url = obj["items"][1]["url"]; // THIS DOES NOT WORK!!!
````

If primitive types aren't enough, you can bind custom types to json structures.



## Development

### Test

You can test with:

    make DEBUG=1 test

You can test code coverage with:

    make DEBUG=1 COVERAGE=1 coverage
