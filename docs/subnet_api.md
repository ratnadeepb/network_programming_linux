**This document presents the API for doing basic IP/Netmask related calculations**

**Available APIs**
1. **Subnet Related**
        * Find the Broadcast IP of a subnet
                - void get_broadcast_address(char *ip_address, char mask, char *output_buffer);
        * Find the network ID of a subnet
                - void get_network_id(char *ip_address, char mask, char *output_buffer);
        * Find how many hosts can a subnet fit
                - unsigned int get_subnet_cardinality(char mask);
        * Check if an IP belongs to a particular subnet
                - int check_ip_subnet_membership(char *network_id, char mask, char *check_ip);

***Help***
- Look at ../subnet/test.c for usage of these functions
- Look at ../ip_maths.h for detailed API and a few more APIs
