## FlatBuffers notes

### Configuring Flatbuffers ###

(coming soon)

### Running the Serialization Test ###

First, navigate to the `/flatbuffers/src` directory. Then, compile the schema and source files, and finish by executing the serialization. This process is done with the following commands:

`flatc --cpp test-object.fbs` <br>
`g++ -std=c++17 test-flatbuffers.cpp -o fbout` <br>
`./fbout`

### File sizes ###
The size of the .fbs schema file that defines the test object is 14 lines.<br/>
The size of the associated automatically-generated header file is 200 lines.<br/>
This is an approximate growth of 1330%

### Execution Performance ###
The average time to create and serialize the test object was approximately 12 ms.<br/>
The average time to deserialize the test object was <1 ms.<br/>
The size of a serialized object is 228 bytes (this doesn't include the map structure that the other libraries were tested with).
