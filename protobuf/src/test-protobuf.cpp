#include "TestObject.pb.h"
#include <iostream>
#include <chrono>

int main() {

    std::vector<int> intVect{1, 2, 3, 4, 5};
    std::vector<std::string> strVect{"str1", "str2", "str3", "str4", "str5"};
    std::unordered_map<int, std::string> mapTest({{1, "val1"}, {2, "val2"}, {3, "val3"}});
    std::string data;

    // create object
    auto t1 = std::chrono::high_resolution_clock::now();
    TestObject testObject;
    testObject.set_int1(1);
    testObject.set_int2(2);
    testObject.set_int3(3);
    testObject.set_int4(4);
    testObject.set_s1("string 1");
    testObject.set_s2("string 2");
    testObject.set_s3("string 3");
    testObject.set_s4("string 4");
    *testObject.mutable_strings() = {strVect.begin(), strVect.end()}; 
    *testObject.mutable_ints() = {intVect.begin(), intVect.end()};
    *testObject.mutable_testmap() = {mapTest.begin(), mapTest.end()};

    // serialize object
    testObject.SerializeToString(&data);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("\nObject packed successfully... Time: %lld ms\n", duration);
    
    // deserialize previous object into new object
    t1 = std::chrono::high_resolution_clock::now();
    TestObject testObject2;
    testObject2.ParseFromString(data);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("Object unpacked successfully... Time: %lld ms\n\n", duration);

    // access object members
    auto int1_2 = testObject2.int1();
    auto int2_2 = testObject2.int2();
    auto int3_2 = testObject2.int3();
    auto int4_2 = testObject2.int4();

    auto s1_2 = testObject2.s1().c_str();
    auto s2_2 = testObject2.s2().c_str();
    auto s3_2 = testObject2.s3().c_str();
    auto s4_2 = testObject2.s4().c_str();

    auto intVect_2 = testObject2.mutable_ints();
    auto strVect_2 = testObject2.mutable_strings();
    auto mapTest2 = testObject2.mutable_testmap();
    
    // print certain members
    std::cout << s1_2 << std::endl;
    std::cout << (int4_2 + 1) << std::endl;
    std::cout << (*intVect_2).at(3) << std::endl;
    std::cout << (*strVect_2).at(2) << std::endl;
    std::cout << (*mapTest2)[3] << std::endl;
}
