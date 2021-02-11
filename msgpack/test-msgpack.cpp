#include <iostream>
#include <sstream>
#include <cassert>
#include <msgpack.hpp>

struct your_type {
    int a;
    int b;
    std::string s;
    MSGPACK_DEFINE(a, b, s);
};

bool operator==(your_type const& lhs, your_type const& rhs) {
    return lhs.a == rhs.a && lhs.b == rhs.b;
}

int main() {

    int x = 5;
    std::string test = "test1";
    std::cout << "Size of int: " << sizeof(x) << std::endl;
    std::cout << "Size of string: " << sizeof(test) << std::endl;

    // packing
    std::stringstream ss;
    std::vector<std::map<std::string, your_type> > v 
    { 
        { 
            { "key1", {1,2, "test1"} },
            { "key2", {3,4, "test2"} }
        },
        {
            {"key3", {5, 6, "test3"} },
            {"key4", {7, 8, "test4"} } 
        }
    };
    msgpack::pack(ss, v);

    std::cout << "Size of stringstream: " << sizeof(ss.str()) << std::endl;
    
    // unpacking
    msgpack::object_handle oh = msgpack::unpack(ss.str().data(), ss.str().size());
    msgpack::object const& obj = oh.get();
    std::cout << "object: " << obj << std::endl;

    // converting
    auto v2 = obj.as<std::vector<std::map<std::string, your_type> > >();
    //assert(v == v2);
}
