# InterfaceMonitor
Monitoring Interfaces

InMn

In This project we provide a prototype implementation of a firewall in Unix along with Interface Monitor system. Interface Monitor System is used to keep forwarding table entries for Firewall input.

Execution:


InMn -h
Option:
       -h -> help
       -p -> Run in Process Model
       -t -> Run in Thread Model
       -n -> Name of Specifc Interface Eg: -n eth0 
       -s -> Provide the list Firewall (Try InMn -p for complete List of Filters 
       -o -> Provide the output Eg: -o "port 2200" or -o "netport eth1" 


-s options can be as following


Following are the Filter options can be provided 


host host 
    True if either the IPv4/v6 source or destination of the packet is host. 
    Any of the above host expressions can be prepended with the keywords, ip, arp, rarp, or ip6 as in: 

    ip host host

    which is equivalent to: 

    ether proto \ip and host host

    If host is a name with multiple IP addresses, each address will be checked for a match. 
ether dst ehost
    True if the Ethernet destination address is ehost. Ehost may be either a name from /etc/ethers or a number (see ethers(3N) for numeric format). 
ether src ehost
    True if the Ethernet source address is ehost. 
ether host ehost
    True if either the Ethernet source or destination address is ehost. 
gateway host
    True if the packet used host as a gateway. I.e., the Ethernet source or destination address was host but neither the IP source nor the IP destination was host. Host must be a name and must be found both by the machine's host-name-to-IP-address resolution mechanisms (host name file, DNS, NIS, etc.) and by the machine's host-name-to-Ethernet-address resolution mechanism (/etc/ethers, etc.). (An equivalent expression is 

    ether host ehost and not host host

    which can be used with either names or numbers for host / ehost.) This syntax does not work in IPv6-enabled configuration at this moment. 
dst net net
    True if the IPv4/v6 destination address of the packet has a network number of net. Net may be either a name from the networks database (/etc/networks, etc.) or a network number. An IPv4 network number can be written as a dotted quad (e.g., 192.168.1.0), dotted triple (e.g., 192.168.1), dotted pair (e.g, 172.16), or single number (e.g., 10); the netmask is 255.255.255.255 for a dotted quad (which means that it's really a host match), 255.255.255.0 for a dotted triple, 255.255.0.0 for a dotted pair, or 255.0.0.0 for a single number. An IPv6 network number must be written out fully; the netmask is ff:ff:ff:ff:ff:ff:ff:ff, so IPv6 "network" matches are really always host matches, and a network match requires a netmask length. 
src net net
    True if the IPv4/v6 source address of the packet has a network number of net. 
net net
    True if either the IPv4/v6 source or destination address of the packet has a network number of net. 
net net mask netmask
    True if the IPv4 address matches net with the specific netmask. May be qualified with src or dst. Note that this syntax is not valid for IPv6 net. 
net net/len
    True if the IPv4/v6 address matches net with a netmask len bits wide. May be qualified with src or dst. 
dst port port
    True if the packet is ip/tcp, ip/udp, ip6/tcp or ip6/udp and has a destination port value of port. The port can be a number or a name used in /etc/services (see tcp(4P) and udp(4P)). If a name is used, both the port number and protocol are checked. If a number or ambiguous name is used, only the port number is checked (e.g., dst port 513 will print both tcp/login traffic and udp/who traffic, and port domain will print both tcp/domain and udp/domain traffic). 
src port port
    True if the packet has a source port value of port. 
port port
    True if either the source or destination port of the packet is port. 
dst portrange port1-port2
    True if the packet is ip/tcp, ip/udp, ip6/tcp or ip6/udp and has a destination port value between port1 and port2. port1 and port2 are interpreted in the same fashion as the port parameter for port. 
src portrange port1-port2
    True if the packet has a source port value between port1 and port2. 
portrange port1-port2
    True if either the source or destination port of the packet is between port1 and port2. 
    Any of the above port or port range expressions can be prepended with the keywords, tcp or udp, as in: 

    tcp src port port

    which matches only tcp packets whose source port is port. 
less length
    True if the packet has a length less than or equal to length. This is equivalent to: 

    len <= length.

greater length
    True if the packet has a length greater than or equal to length. This is equivalent to: 

    len >= length.

ip proto protocol
    True if the packet is an IPv4 packet (see ip(4P)) of protocol type protocol. Protocol can be a number or one of the names icmp, icmp6, igmp, igrp, pim, ah, esp, vrrp, udp, or tcp. Note that the identifiers tcp, udp, and icmp are also keywords and must be escaped via backslash (\), which is \\ in the C-shell. Note that this primitive does not chase the protocol header chain. 
ip6 proto protocol
    True if the packet is an IPv6 packet of protocol type protocol. Note that this primitive does not chase the protocol header chain. 
ip6 protochain protocol
    True if the packet is IPv6 packet, and contains protocol header with type protocol in its protocol header chain. For example, 

    ip6 protochain 6

    matches any IPv6 packet with TCP protocol header in the protocol header chain. The packet may contain, for example, authentication header, routing header, or hop-by-hop option header, between IPv6 header and TCP header. The BPF code emitted by this primitive is complex and cannot be optimized by the BPF optimizer code, so this can be somewhat slow. 
ip protochain protocol
    Equivalent to ip6 protochain protocol, but this is for IPv4. 
ether broadcast
    True if the packet is an Ethernet broadcast packet. The ether keyword is optional. 
ip broadcast
    True if the packet is an IPv4 broadcast packet. It checks for both the all-zeroes and all-ones broadcast conventions, and looks up the subnet mask on the interface on which the capture is being done. 
    If the subnet mask of the interface on which the capture is being done is not available, either because the interface on which capture is being done has no netmask or because the capture is being done on the Linux "any" interface, which can capture on more than one interface, this check will not work correctly. 
ether multicast
    True if the packet is an Ethernet multicast packet. The ether keyword is optional. This is shorthand for 'ether[0] & 1 != 0'. 
