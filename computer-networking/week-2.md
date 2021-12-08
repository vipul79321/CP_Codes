### IP Address
* IP address is an 32-bit address having information about how to reach a specific host. IP address is useful in send data between independent networks
* IP address are made four octets. Each octet ranging from 0 to 255. E.g. - `55:12:73:234`. This notation is called dotted decimal notation
* **IP address doesnt belong to devices instead they belong to network**
* Types of IP address | [Link](https://www.javatpoint.com/ip-address) - 
  * **Dynamic IP address** - 
    * Dynamic IP addresses change automatically and frequently.
    *  With this types of IP address, ISPs already purchase a bulk stock of IP addresses and allocate them in some order to their customers. Periodically, they re-allocate the IP addresses and place the used ones back into the IP addresses pool so they can be used later for another client. 
    *  The foundation for this method is to make cost savings profits for the ISP.
  * **Static IP address** - 
    * The network assigns the IP address to the device only once and, it remains consistent. 
    * It is essential to have a static IP address for an organization that wants to host its network server. 
    * This is because a static IP address ensures that websites and email addresses tied to it will have a consistent IP address — vital if you want other devices to be able to find them consistently on the web.

---

### IP Address Classes 
[Link](https://www.geeksforgeeks.org/introduction-of-classful-ip-addressing/)

* IP Address are divided into classes based on which how many octet makes network ID and how many makes up the Host ID

![Address Classes](https://github.com/vipul79321/CP_Codes/blob/main/computer-networking/images/IP-Address-Classes.jpg)

**NOTE** - While finding the total number of host IP addresses, 2 IP addresses are not counted and are therefore, decreased from the total count because the first IP address of any network is the network number and whereas the last IP address is reserved for broadcast IP.

**Problems with Classful Addressing:**
* The problem with this classful addressing method is that millions of class A address are wasted, many of the class B address are wasted, whereas, number of addresses available in class C is so small that it cannot cater the needs of organizations. 
* Class D addresses are used for multicast routing and are therefore available as a single block only. 
* Class E addresses are reserved.
* Since there are these problems, Classful networking was replaced by **Classless Inter-Domain Routing (CIDR)** in 1993.

---

### IP Datagram contents
[Read this link](http://www.tcpipguide.com/free/t_IPDatagramGeneralFormat.htm)

---
### Encapsulation | [Link](https://www.omnisecu.com/tcpip/tcpip-encapsulation-decapsulation.php)
* When data moves from upper layer to lower layer of TCP/IP protocol stack, during an outgoing transmission, each layer includes a bundle of relevant information called "header" along with the actual data. 
* The data package containing the header and the data from the upper layer then becomes the data that is repackaged at the next lower level with lower layer's header. 
* Header is the supplemental data placed at the beginning of a block of data when it is transmitted. 
* This supplemental data is used at the receiving side to extract the data from the encapsulated data packet. 
* This packing of data at each layer is known as **data encapsulation.**

### Decapsulation | [Link](https://www.omnisecu.com/tcpip/tcpip-encapsulation-decapsulation.php)
* The reverse process of encapsulation (or decapsulation) occurs when data is received on the destination computer during an incoming transmission. 
* As the data moves up from the lower layer to the upper layer of TCP/IP protocol stack (incoming transmission), each layer unpacks the corresponding header and uses the information contained in the header to deliver the packet to the exact network application waiting for the data.

---
### Address Resolution Protocol(ARP) | [Link](https://www.geeksforgeeks.org/how-address-resolution-protocol-arp-works/)

* **Address Resolution Protocol (ARP)** is a communication protocol used to find the MAC (Media Access Control) address of a device from its IP address.

**Working of ARP** - 
* Suppose we want to send data to given IP address, to transmit data along data layer we need MAC address corresponding to that IP address
* If there is already an entry in ARP table, then we simply obtain MAC address from there. 
* Otherwise we will send a broadcast over the network, when the device with destined IP address recieves it, it will send a response with its MAC Address
* Response can be used to obtain MAC address for that IP address as well as to update the ARP table for future use

**ARP Terminologies** - 
* **ARP Cache**: After resolving the MAC address, the ARP sends it to the source where it is stored in a table for future reference. The subsequent communications can use the MAC address from the table
* **ARP Cache Timeout**: It indicates the time for which the MAC address in the ARP cache can reside
* **ARP request**: This is nothing but broadcasting a packet over the network to validate whether we came across the destination MAC address or not. 
  * The physical address of the sender.
  * The IP address of the sender.
  * The physical address of the receiver is FF:FF:FF:FF:FF:FF or 1’s.
  * The IP address of the receiver
* **ARP response/reply**: It is the MAC address response that the source receives from the destination which aids in further communication of the data.


**NOTE** - An ARP request is a broadcast, and an ARP response is a Unicast. 

**Standard Cases in working of ARP** - 
* **CASE-1**: _The sender is a host and wants to send a packet to another host on the same network._
  * Use ARP to find another host’s physical address
* **CASE-2**: _The sender is a host and wants to send a packet to another host on another network._
  * The sender looks at its routing table.
  * Find the IP address of the next-hop (router) for this destination.
  * Use ARP to find the router’s physical address
* **CASE-3**: _the sender is a router and received a datagram destined for a host on another network._ 
  * The router checks its routing table.
  * Find the IP address of the next router.
  * Use ARP to find the next router’s physical address.
* **CASE-4**: _The sender is a router that has received a datagram destined for a host in the same network._
  * Use ARP to find this host’s physical address.



