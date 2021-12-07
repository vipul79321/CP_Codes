### Basics of Computer Networking Devices

#### Cables
[Link](https://www.coursera.org/learn/computer-networking/lecture/WAp4V/cables)

* Cables are what connect different devices to each other, allowing data to be transmitted over them. 
* Copper Cables - 
  * Transmit 0 and 1 by fluctuating voltages in copper wire
  * Some common copper cables - cat5, cat5e, cat6(in increasing order of data reliability and speed of transfer).
  * Major difference among in these cable types is how the twisted pairs are arranged inside the cable
* Fiber Optic Cables - 
  * Fiber cables contain individual optical fibers, which are tiny tubes made out of glass about the width of a human hair.
  * These tubes of glass can transport beams of light.
  * They are faster, reliable, fragile and expensive as compared to copper wires

**NOTE** - Crosstalk is when an electrical pulse on one wire is accidentally detected on another wire. The receiving end isn't able to understand the data causing a network error.

---

#### Hubs and Switches
[Link](https://www.coursera.org/learn/computer-networking/lecture/8rMWU/hubs-and-switches)

##### Hubs
* A hub is a **physical layer device** that allows for connections from many computers at once. 
* All the devices connected to a hub will end up talking to all other devices at the same time. It's up to each system connected to the hub to determine if the incoming data was meant for them, or to ignore it if it isn't. 
* This causes a lot of noise on the network and creates what's called a collision domain.
* **A collision domain**, is a network segment where only one device can communicate at a time. If multiple systems try sending data at the same time, the electrical pulses sent across the cable can interfere with each other. This causes these systems to have to wait for a quiet period before they try sending their data again. 
* Therefore hubs are not used anymore

##### Switches
* A hub is a **data layer device** that allows for connections from many computers at once.
* Being a data layer device, this means that a switch can actually inspect the contents of the ethernet protocol data being sent around the network. Determine which system the data is intended for and then only send that data to that one system. 
* This reduces/eliminates collision domain and lead to fewer re-transmissions and higher overall throughput.

**NOTE** - Hubs and switches are only useful for sending/recieving data on Local Area Network(LAN). 


#### Router - Basics
* A router is a **network layer device** that knows how to forward data between independent networks.
* Routers share data with each other via a protocol known as **Border Gateway Protocol(BGP)**, that let's them learn about the most optimal paths to forward traffic

---

### Physical Layer
[Physical Layer Application](https://www.geeksforgeeks.org/layers-of-osi-model/)

* The physical layer consists of devices and means of transmitting bits across computer networks. It contains information in the form of bits.
* The functions of the physical layer are :  
  * **Bit synchronization**: The physical layer provides the synchronization of the bits by providing a clock. This clock controls both sender and receiver thus providing synchronization at bit level.
  * **Bit rate control**: The Physical layer also defines the transmission rate i.e. the number of bits sent per second.
  * **Physical topologies**: Physical layer specifies the way in which the different, devices/nodes are arranged in a network i.e. bus, star, or mesh topology.
  * **Transmission mode**: Defines duplex or simplex communication
* E.g. - Hub, Repeater, Modem, Cables are Physical Layer devices. 

#### Duplex & Simplex Communication
* Duplex communication is the concept that information can flow in both directions across the cable. 
  * Full-Duplex - Information can flow in both direction at the same time
  * Half-Duplex - Information can flow in one direction at a time
* Simplex communication is the concept that information can only flow in one direction across the cable

**NOTE** - The type of modulation used by twisted pair cable computer networks known as **Line Coding**

---

### Data Link Layer
[]

* One of the primary purposes of this layer is to essentially abstract away the need for any other layers to care about the physical layer and what hardware is in use.
* Ethernet, as a protocol, solved this problem by using a technique known as **carrier sense multiple access with collision detection(CSMA/CD).**
* Working of **CSMA/CD** - 
  * If there's no data currently being transmitted on the network segment, a node will feel free to send data. 
  * If it turns out that two or more computers end up trying to send data at the same time, the computers detect this collision and stop sending data. 
  * Each device involved with the collision then waits a random interval of time before trying to send data again. 
  * This random interval helps to prevent all the computers involved in the collision from colliding again the next time they try to transmit anything.

* **Media Access Control(MAC)** address is a globally unique identifier attached to an individual network interface. 
* It's a 48-bit number normally represented by six groupings of two hexadecimal numbers(two hexa-decimal numbers make an octet).
* A MAC address is split into two sections. 
  * organizationally unique identifier (or OUI) is made of first three octet. These are assigned to individual hardware manufacturer by IEEE
  * Last three octet can be randomly assigned by manufacturer with condition to maintain unqiue MAC address

* Ethernet uses MAC addresses to ensure that the data it sends has both an address for the machine that sent the transmission, as well as the one that the transmission was intended for. In this way, even on a network segment, acting as a single collision domain, each node on that network knows when traffic is intended for it.


* A unicast transmission is always meant for just one receiving address. 
* At the Ethernet level, this is done by looking at a special bit in the destination MAC address. 
* If the least significant bit in the first octet of a destination address is set to zero, it means that Ethernet frame is intended for only the destination address and hence will be processed by assigned destination

* A multicast frame is similarly set to all devices on the local network signal. But it will be accepted or discarded by each device depending on criteria aside from their own hardware MAC address. 
* Least significant bit in the first octet of a destination address is set to one in multicast

* An Ethernet broadcast is sent to every single device on a LAN.
*  This is accomplished by using a special destination known as a broadcast address. The Ethernet broadcast address is `FF:FF:FF:FF:FF:FF`


#### Contents of Ethernet Frames

* **Preamble** – informs the receiving system that a frame is starting and enables synchronisation. It contains a series of 0's and 1's
* **SFD (Start Frame Delimiter)** – signifies that the Destination MAC Address field begins with the next byte. It is always equal to `10101011`
* **Destination MAC** – identifies the receiving system.
* **Source MAC** – identifies the sending system.
* **Type** – Contains the information of the upper layer protocol in source computer. Using this, the data link layer of the destination computer can easily determine the upper layer protocol to which it should hand over the received frame. for example IPv4 or IPv6.
* **Data and Pad | Payload** – contains the payload data. Padding data is added to meet the minimum length requirement for this field (46 bytes). Maximum payload length can be 1500 bytes
* **FCS (Frame Check Sequence)** – contains a 32-bit Cyclic Redundancy Check (CRC) which allows detection of corrupted data.

See image below - 
![Contents of Ethernet](https://github.com/vipul79321/CP_Codes/blob/main/computer-networking/images/contents-of-ethernet-frame.png)
 
