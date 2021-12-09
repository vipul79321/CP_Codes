## Transport Layer
[Link](https://www.geeksforgeeks.org/layers-of-osi-model/)

* The transport layer provides services to the application layer and takes services from the network layer. 
* The data in the transport layer is referred to as Segments. It is responsible for the End to End Delivery of the complete message. 
* The transport layer also provides the acknowledgement of the successful data transmission and re-transmits the data if an error is found. 


---

### TCP Socket States
* Socket is the instantiation of an endpoint in a potential TCP connection.
*  An instantiation is the actual implementation of something defined elsewhere. 
*  TCP sockets require actual programs to instantiate them. 
*  You can contrast this with a port which is more of a virtual descriptive thing. In other words, you can send traffic to any port you want, but you're only going to get a response if a program has opened a socket on that port

#### Major TCP Socket States( terms are operating system dependent) - 
| States | Description | 
| ------ | ----------- |
| LISTEN |  Listen means that a TCP socket is ready and listening for incoming connections. You'd see this on the **server side only**. |
| SYN_SENT | This means that a synchronization request has been sent, but the connection hasn't been established yet. You'd see this on the **client side only.** |
| SYN_RECEIVED | This means that a socket previously in a listener state, has received a synchronization request and sent a SYN_ACK back. But it hasn't received the final ACK from the client yet. You'd see this on the **server side only**. |
| ESTABLISHED | This means that the TCP connection is in working order, and both sides are free to send each other data. You'd see this state on both the client and server sides of the connection. |
| FIN_WAIT | This means that a FIN has been sent, but the corresponding ACK from the other end hasn't been received yet. | 
| CLOSE_WAIT | This means that the connection has been closed at the TCP layer, but that the application that opened the socket hasn't released its hold on the socket yet.|
| CLOSED | This means that the connection has been fully terminated, and that no further communication is possible.|

