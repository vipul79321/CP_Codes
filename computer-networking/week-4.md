### Domain Name System(DNS)
[Link](https://www.javatpoint.com/computer-network-dns) |

* DNS is a service that translates the domain name into IP addresses. This allows the users of networks to utilize user-friendly names when looking for other hosts instead of remembering the IP addresses.
* It is an application layer protocol.
* DNS is a client/server network communication protocol. DNS clients send requests to the server while DNS servers send responses to the client.
* Client requests contain a name which is converted into an IP address known as a **forward DNS lookups** while requests containing an IP address which is converted into a name known as **reverse DNS lookups**.

**Types of DNS Servers** - 
* `Caching Name Servers` - It stores result of domain-resolution lookup for certain amount of time
* `Recursive Name Servers` - They perform full DNS request resolution. In most cases a single server will act as caching and recursive name server.
* `Root Name Servers` - It is contacted by name servers that can not resolve the name. It directs query to appropriate TLD if it doesnt know the mapping. It then gets the mapping and return the IP address to the host.
* `TLD Name Servers` - It is responsible for com, org, edu etc and all top level country domains like uk, fr, ca, in etc. They have info about authoritative domain servers and know names and IP addresses of each authoritative name server for the second level domains.
* `Authoritative Name Servers` - This is organization’s DNS server, providing authoritative hostName to IP mapping for organization servers. It can be maintained by organization or service provider.

**Name to IP Address Resolution** | From video - 
* The first step is always to contact a root named server and they're responsible for directing queries toward the appropriate TLD name server.
* TLD stands for top level domain and represents the top of the hierarchical DNS name resolution system. A TLD is the last part of any domain name, using `www.facebook.com` as an example again, the dot com portion should be thought of as the TLD.
* The TLD name servers will respond again with a redirect, this time informing the computer performing the name lookup with what authoritative name server to contact.
* Authoritative name servers are responsible for the last two parts of any domain name which is the resolution at which a single organization may be responsible for DNS lookups. 
* Using `www.weather.com` as an example, the TLD name server would point a lookup at the authoritative server for Weather.com, which would likely be controlled by the Weather Channel, the organization itself that runs the site. Finally, the DNS lookup could be redirected at the authoritative server for weather.com which would finally provide the actual IP of the server in question.

**NOTE** - This strict hierarchy is very important to the stability of the internet, making sure that all full DNS resolutions go through a strictly regulated and controlled series of lookups to get the correct responses, is the best way to protect against malicious parties redirecting traffic. Your computer will blindly send traffic to whatever IP it's told to. So by using a hierarchical system controlled by trusted entities in the way DNS does, we can better ensure that the responses to DNS lookups are accurate.

**NOTE** - 
* DNS Lookup generally follow UDP protocol to avoid congestion and increase speed.
* As the Web has gotten more complex, it's no longer the case that all DNS lookup responses can fit in a single UDP datagram. 
* In these situations, a DNS name server would respond with a packet explaining that the response is too large. The DNS client would then establish a TCP connection in order to perform the lookup.

---

### Resource Record Types
[From Video](https://www.coursera.org/learn/computer-networking/lecture/a6Fwe/resource-record-types) | [Link](https://docs.microsoft.com/en-us/windows/win32/dns/managing-dns-resource-records)

A **resource record**, commonly referred to as an RR, is the unit of information entry in DNS zone files; RRs are the basic building blocks of host-name and IP information and are used to resolve all DNS queries. Resource records come in a fairly wide variety of types in order to provide extended name-resolution services.

* **A Record** - 
  * An A record is used to point a certain domain name at a certain IPv4 IP address(es). 
  * In its most basic use, a single A record is configured for a single domain name. But, a single domain name can have multiple A records, too. This allows for a technique known as DNS round robin to be used to balance traffic across multiple IPs.
  * In DNS Round Robin, on certain dns lookup all the mapped IPs are returned, on next lookup all the mapped IPs will be returned but with one cyclic shift as compared to previous lookup
* **Quad A** - A Quad A record is very similar to an A record except that it returns in IPv6 address instead of an IPv4 address 
* **CNAME** - Cannonical Name Record. Maps cannonical name such as `microsoft.com` to `www.microsoft.com`
* **MX** -  
  * MX stands for mail exchange and this resource record is used in order to deliver e-mail to the correct server.
  * Many companies run their web and mail servers on different machines with different IPs, so the MX record makes it easy to ensure that email gets delivered to a company's mail server, while other traffic like web traffic would get delivered to their web server.
* **SRV** -  
  * SRV stands for service record, and it's used to define the location of various specific services. 
  * It serves the exact same purpose as the MX resource record type except for one thing, while MX is only for mail services, an SRV record can be defined to return the specifics of many different service types. 
  * For example, SRV records are often used to return the records of services like CalDAV, which has a calendar and scheduling service.
* **TXT**  - 
  * TXT stands for text and was originally intended to be used only for associating some descriptive text with a domain name for human consumption.  
* **PTR** - 
  * Used in reverse DNS lookup, i.e resolve IP to name. 

---

### Anatomy of Domain Name
[From Video](https://www.coursera.org/learn/computer-networking/lecture/iJ8pX/anatomy-of-a-domain-name)

* For e.g `www.google.com` is made of three parts - `www is subdomain, google is domain, com is TLD(Top Level Domain)`
* **TLDs** -
  * Last part of domain name is called TLD  
  * E.g. of some famous TLDs are com, edu, net, etc
  * Administration and definition of TLDs is handled by a non-profit organization known as **ICANN, or the Internet Corporation for Assigned Names and Numbers**
* **Domain** -
  * A domain is the name commonly used to refer to the second part of a domain name. 
  * Domains are used to demarcate where control moves from a TLD name server, to an authoritative name server. 
  * This is typically under the control of an independent organization, or someone outside of ICANN.
  * It costs some money to register domain with the registrar.
* **Sub Domain** - 
  * It is also referred to as **Hostname**, signifies the name of host where our domain resides
  * Technically speaking, a hostname is a domain name assigned to a host computer.
  * Subdomains can be **freely** chosen and assigned by anyone who controls such a registered domain. A registrar is just a company that has an agreement with ICANN to sell unregistered domain names.
* **Full-Qualified Domain Name(FQDN)** - 
  * All the above parts combined together makes an FQDN

**NOTE** - 
* DNS can technically support up to **127** levels(levels are generally separated by dots) of domain in total for a single fully qualified domain name.
* Each individual level can only be **63** characters long
* Complete FQDN is limited to a total of **255** characters

---

### DNS Zones
[Link](https://www.geeksforgeeks.org/domain-name-system-dns-zones/)

* Domain Name System (DNS) Zones is any distinct, connecting segment of domain name space in Domain Name System (DNS) for which administrative responsibility has been delegated to single administrative space which allows for more smooth control of DNS components.
* DNS zones are hierarchical concept.
* The purpose of DNS zones is to permit easier control over multiple levels of website.
* Zones dont overlap, For example, the administrative authority of the TLD name server for the.com TLD doesn't encompass the `google.com` domain. Instead, it ends at the authoritative server responsible for `google.com`. 


**Important Points** - 
* Zones are configured through what are known as zone files.
* Zone files are simple configuration files that declare all resource records for a particular zone. 
* So a zone file has to contain an **SOA, or a Start of Authority** resource record declaration. This SOA record declares the zone and the name of the name server that is authoritative for it. Along with the SOA record, you'll usually find NS records which indicate other name servers that may also be responsible for this zone. Mutliple name server can be useful in case of hardware failure in a single name server
* Other resource records such as A, quad A, CNAME will also be present. And also a global TTL value

---

**NOTE** - 
* Every single computer on a modern TCP/IP based network needs to have at least four things specifically configured. 
* `An IP address`
* `The Subnet Mask for the local network`
* `A Primary Gateway`
* `A Name Server`

---

### Dynamic Host Control Protocol(DHCP)
[From Video](https://www.coursera.org/learn/computer-networking/lecture/FmEsd/overview-of-dhcp) | [From Video](https://www.coursera.org/learn/computer-networking/lecture/NU8C2/dhcp-in-action)

* DHCP is an **application layer protocol** that automates the configuration process of hosts on a network. 
* With DHCP, a machine can query a DHCP server when the computer connects to the network and receive all the networking configuration in one go.
* Out of the four things neccessary for configuration(mentioned in note above), three are likely the same on just about every node on the network. The subnet mask, the primary gateway, and DNS server. But the last item an IP address needs to be different on every single node on the network.


#### Different types of DHCP allocation** - 
* _Dynamic Allocation_ - 
  * A range of IP addresses is set aside for client devices and one of these IPs is issued to these devices when they request one. 
  * Under a dynamic allocation the IP of a computer could be different almost every time it connects to the network.
* _Automatic Allocation_ - 
  * Very similar to Dynamic Allocation.
  * The main difference here is that, the DHCP server is asked to keep track of which IPs it's assigned to certain devices in the past. 
  * Using this information, the DHCP server will assign the same IP to the same machine each time if possible. 
* _Fixed Allocation_ - 
  * Fixed allocation requires a manually specified list of MAC address and their corresponding IPs.
  * If the MAC address is not found the IP allocation request is denied

**NOTE** - NTP stands for Network Time Protocol and is used to keep all computers on a network synchronized in time. DHCP can be used to assign NTP Servers

#### DHCP in Action - 

* DHCP is an application layer protocol, which means it relies on the transport, network, data link and physical layers to operate. But you might have noticed that the entire point of DHCP is to help configure the network layer itself. 
* `DHCP Discovery` - The process by which a client configured to use DHCP attempts to get network configuration information is known as DHCP discovery

**NOTE** - `Port number for DHCP server is 67 and DHCP client is 68`

##### Steps involved in DHCP Discovery Process | [Can read more here](https://www.geeksforgeeks.org/dynamic-host-configuration-protocol-dhcp/) - 
* `DHCP discover message` - 
  * First, an UDP datagram is formed with source port as `68` and destination port as `67` 
  * Then this UDP datagram is encapsulated in an IP datagram with source IP as `0.0.0.0` and destination IP as `255.255.255.255`. Hence a broadcast message
  * If DHCP server is present it will recieve this broadcast and decide which IP to assign based on allocation strategy
* `DHCP offer message` - 
  * DHCP server in response to DHCP discovery message, will send a broadcast with source port as `67` , destination port as `68` , source IP as `its own IP` and destination IP as `255.255.255.255`.
  * Now this broadcast message will be interpreted by DHCP client because it contains its MAC address
* `DHCP Request message` - 
  * Based on the IP recieved in DHCP offer message, client would send yes as broadcast message with source Port as `67` and Client Port as `68`, source IP as `0.0.0.0` and destination IP `255.255.255.255`
* `DHCPACK | DHCP Acknowledgement message` - 
  * DHCP server will respond to DHCP request message with DHCPACK message broadcasted with source IP as its own IP and destination IP as `255.255.255.255`
* After all the four steps, client network stack has all the neccessary resources to configure its own network layer
* All of this configuration is known as **DHCP lease** as it includes an expiration time.

---

### Network Address Translation
[Video Link](https://www.coursera.org/learn/computer-networking/lecture/UnKO5/basics-of-nat) | [Video Link](https://www.coursera.org/learn/computer-networking/lecture/Onnzx/nat-and-the-transport-layer) | [Video Link](https://www.coursera.org/learn/computer-networking/lecture/R9sHu/nat-non-routable-address-space-and-the-limits-of-ipv4)

* NAT is a **technology(not a protocol)** that allows a gateway, usually a router or firewall, to rewrite the source IP of an outgoing IP datagram while retaining the original IP in order to rewrite it into the response.
* Since NAT will re-write the source IP, original IP will be unknown to outer world and this is known as **IP Masquerading**
* NAT at network layer is generally performed by router
* By using NAT, we could actually have hundreds of computers on one network, all of their IPs being translated by the router to its own. To the outside world, the entire address space of that network is protected and invisible. This is known as **one-to-many NAT**

**Challenges in one-to-many NAT at Transport Layer** - 
* With one-to-many NAT, we dont know which destination IP to assign to recieved response. 
* To solve this we can use **Port Preservation**. Port preservation is a technique where the source port chosen by a client, is the same port used by the router.
* It's still possible for two different computers on a network to both choose the same source port around the same time. When this happens, the router normally selects an unused port at random to use instead. And use that to assign response.


**Port Forwarding** - 
* Port forwarding is a technique where a specific destination ports can be configured to always be delivered to specific nodes.
* This technique allows for complete IP masquerading, while still having services that can respond to incoming traffic.
* Let's imagine a company with both a web server and mail server, both need to be accessible to the outside world but they run on different servers with different IPs. Again, let's say the web server has an IP of 10.1.1.5, and the mail server has an IP of 10.1.1.6. With port forwarding, traffic for either of these services could be aimed at the same external IP and therefore the same DNS name, but it would get delivered to entirely different internal servers due to their different destination ports.

---

**NOTE** -
* Only 4.7 billion IPv4 addresses are possible, which have already exhausted, IPv6 can solve this problem, but shift to IPv6 will take time.
* In meanwhile, another alternate is to use NAT and Non-Routable Address Space together.
* The way it will work is all the internal computers on the network will be assigned IP from Non-Routable Address Space and when they need to communicate to external network they can be assigned IP of router using NAT

---

  



