## MessagePack notes

### Configuring MsgPack ###

(coming soon)

### Running the Serialization Test ###

First, navigate to the `/msgpack` directory. Then, compile and run the MessagePack serialization by executing the following commands:

`g++ -std=c++11 test-msgpack.cpp -o msgpack` <br>
`./msgpack`

### File sizes ###
MessagePack does not produce an automatically-generated header file like the other two libraries tested here, so the file growth is N/A or 0%.

### Execution Performance ###
The average time to create and serialize the test object was approximately 18 ms.<br/>
The average time to deserialize the test object was 58 ms.<br/>
The size of the resulting serialized object is 79 bytes.
