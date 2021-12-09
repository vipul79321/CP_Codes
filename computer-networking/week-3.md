## Transport Layer
[Link](https://www.geeksforgeeks.org/layers-of-osi-model/)

* The transport layer provides services to the application layer and takes services from the network layer. 
* The data in the transport layer is referred to as Segments. It is responsible for the End to End Delivery of the complete message. 
* The transport layer also provides the acknowledgement of the successful data transmission and re-transmits the data if an error is found.


**Port** - 
* It is a `16-bit` number that's used to direct traffic to specific services running on a networked computer.
* Ports are normally denoted with a colon after the IP address. 
* So the full IP and port in this scenario could be described as `10.1.1.100:80`. When written this way, it's known as a **socket address or socket number.**


**Multiplexing** - Gathering data from multiple application processes of the sender, enveloping that data with a header, and sending them as a whole to the intended receiver is called multiplexing.

**Demultiplexing** - Delivering received segments at the receiver side to the correct app layer processes is called demultiplexing. 

---

### Difference between Connection Oriented and Connectionless Protocols | [Link](https://www.geeksforgeeks.org/difference-between-connection-oriented-and-connection-less-services/)

---

### Dissecting TCP Segment
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/segmentation-explained-with-tcp-and-udp-header.html)

| Field | Size | Description |
| ----- | ---- | ----------- |
| Source port	| 16 bits |Used to identify the application that is sending data from the source host |
| Destination port | 16 bits | Used to identify the application that will receive the data at destination host |
| Sequence Number	| 32 bits | Used to identify the lost segments and maintain the sequencing in transmission. |
| Acknowledgment Number |	32 bits | Used to send a verification of received segments and to ask for the next segments |
| Header Length | 4 bits | A number that indicates where the data begin in segment |
| Reserved | 6 bits | Reserve for future use. Always set to zero.|
| Control Flags | 6 bits | Used to define the control functions such as setting up and terminating the session |
| Window size	| 16 bits | Used to set the number of segments that can be sent before waiting for a confirmation from the destination. |
| Checksum | 16 bits | CRC (cyclic redundancy check) of the header and data piece. |
| Urgent | 16 bits | Used to point any urgent data in the segment. |
| Options | 0 or 16 if any | Used to define any additional options such as maximum segment size |
| padding | 32 - options size | Use to pad the options field |
| Data	| varies | A data piece that is produced from the segmentation |

---

### Dissecting UDP Segment
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/segmentation-explained-with-tcp-and-udp-header.html)

| Field | Size | Description |
| ----- | ---- | ----------- |
| Source port	| 16 bits |Used to identify the application that is sending data from the source host |
| Destination port | 16 bits | Used to identify the application that will receive the data at destination host |
| Length | 16 bits | Denotes the length of the UDP header and the UDP data|
| Checksum | 16 bits | CRC of the complete segment |
| Data | varies | Data which it received from the application |

---

### Key differences between TCP and UDP
| Transmission control protocol (TCP) | User datagram protocol (UDP) |
| ----------------------------------- | ---------------------------- |
| TCP is a connection-oriented protocol. Connection-orientation means that the communicating devices should establish a connection before transmitting data and should close the connection after transmitting the data.	| UDP is the Datagram oriented protocol. This is because there is no overhead for opening a connection, maintaining a connection, and terminating a connection. UDP is efficient for broadcast and multicast type of network transmission. |
| TCP is reliable as it guarantees the delivery of data to the destination router. | The delivery of data to the destination cannot be guaranteed in UDP. |
| TCP provides extensive error checking mechanisms. It is because it provides flow control and acknowledgement of data. | UDP has only the basic error checking mechanism using checksums. |
| Acknowledgement segment is present.|	No acknowledgement segment. |
| Sequencing of data is a feature of Transmission Control Protocol (TCP). this means that packets arrive in-order at the receiver.|	There is no sequencing of data in UDP. If the order is required, it has to be managed by the application layer.|
| TCP is comparatively slower than UDP.	| UDP is faster, simpler, and more efficient than TCP. |
| Retransmission of lost packets is possible in TCP, but not in UDP. | There is no retransmission of lost packets in the User Datagram Protocol (UDP). |
| TCP has a (20-60) bytes variable length header.	| UDP has an 8 bytes fixed-length header. |
| TCP is heavy-weight. | UDP is lightweight. |
| Uses handshakes such as SYN, ACK, SYN-ACK	| It’s a connectionless protocol i.e. No handshake |
| TCP doesn’t support Broadcasting.	| UDP supports Broadcasting. |
| TCP is used by HTTP, HTTPs, FTP, SMTP and Telnet.	| UDP is used by DNS, DHCP, TFTP, SNMP, RIP, and VoIP. |

---
### TCP Three-way handshake process
* **SYN** - Source sends a SYN (synchronization) segment to the destination. This segment indicates that source want to establish a reliable session with destination.
* **SYN/ACK** - Destination responds back with a SYN/ACK (synchronization/acknowledgement) segment. This segment indicates that destination received the source’s connection request and ready to setup a reliable session with source.
* **ACK** - Upon receiving a SYN/ACK segment from destination, source sends an ACK (acknowledgement) segment to the destination. This segment indicates that source received the confirmation from destination and the session is now fully reliable.

Following figure shows an example of Three-way handshake process - 
![TCP Three Way Handshake](https://github.com/vipul79321/CP_Codes/blob/main/computer-networking/images/Three-way-handshake.png)

---

### Four-Way Handshake | [From Video](https://www.coursera.org/learn/computer-networking/lecture/hGnHm/tcp-control-flags-and-the-three-way-handshake)
* The computer ready to close the connection, sends a **FIN** flag
* which the other computer acknowledges with an **ACK** flag. 
* Then, if this computer is also ready to close the connection, which will almost always be the case. It will send a **FIN** flag. 
* This is again responded to by an **ACK** flag.

---

**NOTE** - 
* [Flow control using window size in TCP segment](https://www.computernetworkingnotes.com/ccna-study-guide/tcp-features-and-functions-explained-with-examples.html)
*  A firewall is just a device that blocks traffic that meets certain criteria.
---

### TCP Socket States | [From Video](https://www.coursera.org/learn/computer-networking/lecture/1ELOr/tcp-socket-states)
* Socket is the instantiation of an endpoint in a potential TCP connection.
*  An instantiation is the actual implementation of something defined elsewhere. 
*  TCP sockets require actual programs to instantiate them. 
*  You can contrast this with a port which is more of a virtual descriptive thing. In other words, you can send traffic to any port you want, but you're only going to get a response if a program has opened a socket on that port

#### Major TCP Socket States( terms are operating system dependent) | [From Video](https://www.coursera.org/learn/computer-networking/lecture/1ELOr/tcp-socket-states)- 
| States | Description | 
| ------ | ----------- |
| LISTEN |  Listen means that a TCP socket is ready and listening for incoming connections. You'd see this on the **server side only**. |
| SYN_SENT | This means that a synchronization request has been sent, but the connection hasn't been established yet. You'd see this on the **client side only.** |
| SYN_RECEIVED | This means that a socket previously in a listener state, has received a synchronization request and sent a SYN_ACK back. But it hasn't received the final ACK from the client yet. You'd see this on the **server side only**. |
| ESTABLISHED | This means that the TCP connection is in working order, and both sides are free to send each other data. You'd see this state on both the client and server sides of the connection. |
| FIN_WAIT | This means that a FIN has been sent, but the corresponding ACK from the other end hasn't been received yet. | 
| CLOSE_WAIT | This means that the connection has been closed at the TCP layer, but that the application that opened the socket hasn't released its hold on the socket yet.|
| CLOSED | This means that the connection has been fully terminated, and that no further communication is possible.|

--- 

