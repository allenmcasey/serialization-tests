#include <iostream>
#include <chrono>
#include "TestObject_generated.h"

using namespace Test;

int main(int /*argc*/, const char * /*argv*/[]) {

    std::vector<int> int_vector;
    int_vector.push_back(10);
    int_vector.push_back(20);
    int_vector.push_back(30);
    int_vector.push_back(40);
    int_vector.push_back(50);

    std::vector<std::string> string_vector;
    string_vector.push_back("String 1");
    string_vector.push_back("String 2");
    string_vector.push_back("String 3");
    string_vector.push_back("String 4");
    string_vector.push_back("String 5");

    auto t1 = std::chrono::high_resolution_clock::now();

    // Create object
    flatbuffers::FlatBufferBuilder builder;
    auto s1 = builder.CreateString("S1_ABCDEFG");
    auto s2 = builder.CreateString("S2_ABCDEFGABCDEFG");
    auto s3 = builder.CreateString("S3_ABCDEFGABCDEFGABCDEFGABCDEFG");
    auto s4 = builder.CreateString("S4_ABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFGABCDEFG");

    flatbuffers::Offset<flatbuffers::Vector<int32_t>> intVec = builder.CreateVector(int_vector);
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<flatbuffers::String>>> stringVec = builder.CreateVectorOfStrings(string_vector);

    // Serialize the object
    auto object = CreateTestObject(builder, 1, 2, 3, 4, s1, s2, s3, s4, intVec, stringVec);
    builder.Finish(object);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("\nObject packed successfully... Time: %lld ms\n", duration);

    /*======================================================================================*/

    // Deserialize the object
    t1 = std::chrono::high_resolution_clock::now();
    auto sentObject = GetTestObject(builder.GetBufferPointer());
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    printf("Object unpacked successfully... Time: %lld ms\n\n", duration);

    // Print object's contents
    std::cout << "Object contents:" << std::endl;
    printf("int1: %d\n", sentObject->int1());
    printf("int2: %d\n", sentObject->int2());
    printf("int3: %d\n", sentObject->int3());
    printf("int4: %d\n", sentObject->int4());

    printf("String1: %s\n", sentObject->string1()->str().c_str());
    printf("String2: %s\n", sentObject->string2()->str().c_str());
    printf("String3: %s\n", sentObject->string3()->str().c_str());
    printf("String4: %s\n", sentObject->string4()->str().c_str());

    std::cout << "Int vector: ";
    auto ints = sentObject->intVec();
    for (unsigned int i = 0; i < ints->size(); i++) {
        printf("%d ", ints->Get(i));
    }

    std::cout << "\nString vector: ";
    auto strings = sentObject->stringVec();
    for (unsigned int i = 0; i < strings->size(); i++) {
        printf("%s ", strings->Get(i)->str().c_str());
    }
    std::cout << std::endl;

    printf("\nThe FlatBuffer was successfully created and verified!\n");
}
