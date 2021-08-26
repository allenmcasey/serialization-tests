## Protobuf notes

### Configuring Protobuf ###

(coming soon)

### Running the Serialization Test ###

First, navigate to the /protobuf/src directory. Then, compile the .proto and source files, and finish by executing the serialization. This process is done with the following commands:

`protoc -I=. --cpp_out=. test-object.proto` <br>
`g++ -std=c++17 TestSerialization-proto.cpp TestObject.pb.cc -lprotobuf -pthread` <br>
`./a.out`


### File Sizes ###
The TestObject message format is defined in a .proto file that is 13 lines long. <br/>
When compiled, this .proto results in two files being generated - a .ph.h file and a .pb.cc file. <br/>
The combined lengths of these two files is nearly 1300 lines, which means the file size increase is nearly 10,000%.

### Execution Performance ###
The average time to create and serialize the test object was approximately 25 ms. <br/>
The average time to deserialize the test object was 18 ms. The size of the serialized object is 115 bytes.
