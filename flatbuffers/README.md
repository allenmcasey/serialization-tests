## FlatBuffers notes

### File sizes ###
The size of the .fbs schema file that defines the test object is 14 lines.<br/>
The size of the associated automatically-generated header file is 200 lines.<br/>
This is an approximate growth of 1330%

### Execution Performance ###
The average time to create and serialize the test object was approximately 12 ms.<br/>
The average time to deserialize the test object was <1 ms.<br/>
The size of a serialized object is 228 bytes (this doesn't include the map structure that the other libraries were tested with).

### Other Notes ###
FlatBuffers doesn't natively support map structures. They can still be serialized, but it is more difficult to accomplish than with the other two libraries.
