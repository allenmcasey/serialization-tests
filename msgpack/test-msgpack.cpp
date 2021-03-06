#include <iostream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <msgpack.hpp>

struct testStruct {
    
    // struct members
    int int1, int2, int3, int4;
    std::string s1, s2, s3, s4;
    std::vector<int> intVect;
    std::vector<std::string> strVect;
    std::unordered_map<int, std::string> testMap;
    bool boolean;
    
    // define message members for MsgPack
    MSGPACK_DEFINE(int1, int2, int3, int4,
                    s1, s2, s3, s4,
                    intVect, strVect, testMap, boolean);
};

int main() {

    // create object
    std::vector<int> testIntVector{1, 2, 3, 4, 5};
    std::vector<std::string> testStringVector{"s1", "s2", "s3", "s4", "s5"};
    std::unordered_map<int, std::string> map{{1, "str1"}, {2, "str2"}, {3, "str3"}};
    testStruct test = {1, 2, 3, 4, "string1", "string2", "string3", "string4", testIntVector, testStringVector, map, true};

    // packing
    auto t1 = std::chrono::high_resolution_clock::now();
    std::stringstream ss;
    msgpack::pack(ss, test);
    
    std::ofstream outFile;
    outFile.open("test_out.txt");
    outFile << ss.rdbuf();
    outFile.close();

    ss.seekg(0, std::ios::end);
    int size = ss.tellg();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("\nObject packed successfully... Time: %lld ms\nObject size: %d bytes\n", duration, size);

    // unpacking
    t1 = std::chrono::high_resolution_clock::now();
    std::ifstream file("test_out.txt");
    std::stringstream buffer;
    if ( file )
    {
        buffer << file.rdbuf();
        file.close();
    }
 
    msgpack::object_handle oh = msgpack::unpack(buffer.str().data(), buffer.str().size());
    msgpack::object const& obj = oh.get();
    auto test2 = obj.as<testStruct>();
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("Object unpacked successfully... Time: %lld ms\n", duration);


    // Printing results
    std::cout << "\nObject contents:\n-------------------------" << std::endl;
    printf("Object integers: %d %d %d %d\n", test2.int1, test2.int2, test2.int3, test2.int4);
    printf("Object strings: %s %s %s %s\n", test2.s1.c_str(), test2.s2.c_str(), test2.s3.c_str(), test2.s4.c_str());
    std::cout << "Object integer vector: ";
    for (int i = 0; i < test2.intVect.size(); i++) {
        std::cout << test2.intVect.at(i) << " ";
    }
    std::cout << "\nObject string vector: ";
    for (int i = 0; i < test2.strVect.size(); i++) {
        std::cout << test2.strVect.at(i) << " ";
    }
    printf("\nMap value for Key '1': %s\n", test2.testMap[1].c_str());
    printf("Object boolean: %d\n", test2.boolean);
}
