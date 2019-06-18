# APIs in this project

## List of possibly useful APIs
1. **Subnet Related**
    * Find the Broadcast IP of a subnet
        - void get_broadcast_address(char *ip_address, char mask, char *output_buffer);
    * Find the network ID of a subnet
        - void get_network_id(char *ip_address, char mask, char *output_buffer);
    * Find how many hosts can a subnet fit
        - unsigned int get_subnet_cardinality(char mask);
    * Find the lowest and highest assignable IP in a network with a given mask
        - unsigned int get_host_address_min(char *network_id);
        - unsigned int get_host_address_max(char *network_id, char mask);
    * Check if an IP belongs to a particular subnet
        - int check_ip_subnet_membership(char *network_id, char mask, char *check_ip);

2. **Testing**
    * From the main ("networking") folder simply run "make test"
        - At the moment, it only runs the subnet unit tests
    * From the "subnet" folder, run "make && ../build/subnet.o"

3. **DEBUGGING**
    * Define the NDEBUG variable to enable debug mode in the code
        - "export NDEGUB=1" or any non-empty value

***Help***
- Look at *../subnet/test.c* for usage of these functions
- Look at *../ip_maths.h* for detailed API and a few more APIs
