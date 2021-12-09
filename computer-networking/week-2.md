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

---

### Subnetting and Subnet Masks
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-subnetting-in-computer-networks-explained.html) | [Explanation](https://www.computernetworkingnotes.com/ccna-study-guide/subnetting-tutorial-subnetting-explained-with-examples.html) | [Numericals](https://www.computernetworkingnotes.com/ccna-study-guide/subnetting-tricks-subnetting-made-easy-with-examples.html)

* Subnetting is a process of dividing a single large network in multiple smaller networks. 
* Need for subnetting - 
  * A default class A, B and C network provides 16777214, 65534, 254 hosts respectively. Having so many hosts in a single network always creates several issues such as broadcast, collision, congestion, etc.
  * Computers use broadcast messages to access and provide information in network. If the size of network is very large this results in lots of problems

**Advantage of Subnetting**
* Subnetting allows us to break a single large network in smaller networks. Small networks are easy to manage.
* Subnetting reduces network traffic by allowing only the broadcast traffic which is relevant to the subnet.
* By reducing unnecessary traffic, Subnetting improves overall performance of the network.
* By blocking a subnet’ traffic in subnet, Subnetting increases security of the network.
* Subnetting reduces the requirement of IP range.


**Disadvantage of Subnetting**
* Different subnets need an intermediate device known as router to communicate with each other.
* Since each subnet uses its own network address and broadcast address, more subnets mean more wastage of IP addresses.
* Subnetting ads complexity in network. An experienced network administrator is required to manage the subnetted network. 

**How subnetting works** - 
* Identifying network portion and host portion in an IP address is the first step of Subnetting. **Subnetting can only be done in host portion of IP address, with last two bits(31 & 32) being reserved for host ID.**
* **Subnet Mask** - 
  * It is of 32-bit in size and the portion of IP address that belongs to network Id are all 1s in subnet mask and remaining portion is all 0s
  * Subnet Mask are generally represented in decimal or slash notation. In slash notation - `IP address/length(network Id portion)`
 
**Network address and Broadcast address**
* In each network there are two special addresses; network address and broadcast address.
*  Network address represents the network itself while broadcast address represents all the hosts which belong to it. 
*  These two addresses can’t be assigned to any individual host in network.(Hence the rule of total count - 2) 
*  Since each subnet represents an individual network, it also uses these two addresses.

**NOTE** - In simple language, in a single network only two IP addresses will be used for these addresses. But if we breaks this network in two small networks then four IP addressed will be used for these addresses.

**Valid Host Address** - All the address in range of network address and broadcast address are valid host address

**Type of Subnetting**
* There are two types of Subnetting **FLSM and VLSM**.
* In FLSM, all subnets have equal number of host addresses and use same Subnet mask. 
* In VLSM, subnets have flexible number of host addresses and use different subnet mask.

**NOTE** - Visit numerical link for solved examples on subnetting

---

### Classless Inter-Domain Routing (CIDR)
[Link](https://www.geeksforgeeks.org/cidr-full-form/)

* CIDR stands for Classless Inter-Domain Routing. 
* It is an IP address assigning method that improves the efficiency of address distribution. 
* It is also known as **supernetting** that replaces the older system based on classes A, B, and C networks. 
* By using a single CIDR IP address many unique IP addresses can be designated. 
* CIDR IP address is the same as the normal IP address except that it ends with a slash followed by a number.
* E.g 172.200.0.0/16 It is called **IP network prefix**.

---

### Routing 
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-of-ip-routing-explained-with-example.html) | [Link](https://www.geeksforgeeks.org/routing-v-s-routed-protocols-in-computer-network/) | [Link](https://www.computernetworkingnotes.com/ccna-study-guide/types-of-routing-and-types-of-routes-explained.html) | [Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-routing-concepts-and-protocols-explained.html) | [Link](https://ecomputernotes.com/computernetworkingnotes/routing/routing-protocols)

* **IP routing** is a process of transferring data from one network to another as **IP packets**. By default, hosts of different networks cannot communicate with each other. If two hosts located in different IP networks want to communicate with each other, they use IP routing. And the device used for routing is called **router**.
* All of this happens at Network Layer
* There are two types of packets used at this layer :
  * **Data Packets** –
    * The user data is transferred in the inter-network by these data packets. **`Routed protocols`** are those protocols which support such data traffic. Examples of routed protocols are IPv4, IPv6 and AppleTalk.
  * **Route Update Packets** –
    * The information about the networks connected to all the routers is updated to the neighbouring routers through route update packets. 
    * **`Routing protocols`** are the ones that are responsible for sending them. 
    * Examples of routing protocols are RIP(Routing Information Protocol), EIGRP(Enhanced Interior Gateway Routing Protocol) and OSPF(Open Shortest Path First).

**Working of IP Routing** |
[Read section How does IP routing work from this link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-of-ip-routing-explained-with-example.html)

**NOTE** - A **default gateway** is an interface of a router that connects the local network with the remote network. By default, an IP protocol forwards all packets to the default gateway except the packets that belong to the local IP network.

**Types of Routing | Static Routing vs Dynamic Routing** | [Link](https://www.computernetworkingnotes.com/ccna-study-guide/types-of-routing-and-types-of-routes-explained.html)
* A router can, on its own, only learn networks that are directly connected to its active interfaces.
* If a network is available on the interface of another router, a router cannot learn that network on its own.
* A router can learn about the paths that are not available on its interfaces through two types of routing; static routing and dynamic routing.

| Static Routing | Dynamic Routing | 
| -------------- | --------------- |
| We have to add the remote paths manually. | We configure a routing protocol and later the routing protocol automatically discovers the remote paths and adds them into the routing table.|
| Doesnt require any routing protocol | Require knowledge of the routing protocol that will be used in the network. | 
| Any change in the path information requires a manual update on all routers. | If the path information changes, the routing protocol automatically updates all routers. | 
| Since routes are configured manually, the static routing is considered more secure than the dynamic routing. | Since routers learn routes from the routing protocol, the dynamic routing is considered less secure than the static routing. | 
| Do not use any additional hardware resources. | Consume CPU, memory and link bandwidth. |
| Well suited for small size networks | Well suited for large size networks |


**Features / Functions of Routing Protocols** - 
* To know all the available paths of the network
* To select the best and fastest path for each destination in the network
* To select a single and fastest path if more than one path exists for a single destination
* Update Routing Tables by learning from neighboring routers and Advertise local routing information to neighboring routers


**Types of Routing Protocols**
* Distance Vector Routing Protocol
* Link-state Routing Protocol
* Hybrid Routing Protocol

#### Distance Vector Routing Protocol | Similar to Bellman-Ford
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-routing-concepts-and-protocols-explained.html) | [Working Explained](https://www.computernetworkingnotes.com/ccna-study-guide/how-rip-routing-protocol-works.html) | [Link](https://www.geeksforgeeks.org/distance-vector-routing-dvr-protocol/)
* Updates of the network are exchanged periodically. 
* Updates (routing information) are always broadcast. Full routing tables are sent in updates. 
* Routers always trust routing information received from neighbor routers. This is also known as _routing on rumors_. 
* A router transmits its _distance vector_ to each of its neighbors in a routing packet. Distance is generally calculated in terms of Hop Count
* Each router receives and saves the most recently received distance vector from each of its neighbors.
* A router recalculates its distance vector when:
  * It receives a distance vector from a neighbor containing different information than before.
  * It discovers that a link to a neighbor has gone down.


#### Link-State Routing Protocol | Similar to Dijkstra Algorithm
[Link](https://www.geeksforgeeks.org/classes-of-routing-protocols/) | [Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-routing-concepts-and-protocols-explained.html) | [Link](https://ecomputernotes.com/computernetworkingnotes/routing/routing-protocols)
* A link state is the description of an interface on a router and its relationship to neighboring routers.
* To discover neighbors, link-state protocols use a special protocol known as the **hello protocol.**
* Each router will send information of its links (Link-State) to its neighbor who will in turn propagate the information to its neighbors, etc. This occurs until all routers have built a topology of the network.
* Each router will then prune the topology, with itself as the root, choosing the least-cost-path to each router, then build a routing table based on the pruned topology. Shortest Path First(Dijkstra Algorithm) is used for this purpose
* In link-state routing, updates are only sent when a change is detected in topology. 
* Link-State routing verifies all the routing updates. After recieving updates, destination router will respond to source router with an acknowledgement
* Link state routing protocol maintains three tables namely: 
  * **Neighbor table**- the table which contains information about the neighbors of the router only, i.e, to which adjacency has been formed. 
  * **Topology table**- This table contains information about the whole topology. 
  * **Routing table**- This table contains all the best routes to the advertised network. 

#### Hybrid Routing Protocol
[Link](https://www.computernetworkingnotes.com/ccna-study-guide/basic-routing-concepts-and-protocols-explained.html)

* Hybrid routing protocols are the combination of both distance-vector and link-state protocols. Hybrid routing protocols are based on distance-vector routing protocols but contain many of the features and functions of link-state routing protocols.
* Hybrid protocols use a Hello protocol to discover neighbors and form neighbor relationships. Hybrid protocols also send updates only when a change occurs.
* Hybrid routing protocols reduce the CPU and memory overhead by functioning like a distance-vector protocol when it comes to processing routing updates; but instead of sending out periodic updates like a distance-vector protocol, hybrid routing protocols send out incremental, reliable updates via multicast messages, providing a more network- and router-friendly environment.

