## Protobuf notes

### File Sizes ###
The TestObject message format is defined in a .proto file that is 13 lines long. <br/>
When compiled, this .proto results in two files being generated - a .ph.h file and a .pb.cc file. <br/>
The combined lengths of these two files is nearly 1300 lines, which means the file size increase is nearly 10,000%.

### Execution Performance ###
The average time to create and serialize the test object was approximately 25 ms. <br/>
The average time to deserialize the test object was 18 ms. The size of the serialized object is 115 bytes.
