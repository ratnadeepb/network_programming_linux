/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  testing the ip math functions
 *
 *        Version:  1.0
 *        Created:  06/07/2019 03:28:21 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ratnadeep Bhattacharya
 *   Organization:  
 *
 * =====================================================================================
 */

#include "ip_maths.h"
#include "../common/dbg.h"

void
test_broadcast_addr(char *ip_address, char mask);

void
test_ip_integral_value(char *ip_address);

void
test_decimal_to_dotted_ipv4(char *ip_address);

void
test_network_id(char *ip_address, char mask);

void
test_subnet_cardinality(char mask);

void
test_ip_membership(char *check_ip, char mask);

void
test_lowest_ip(char *ip_address, char mask);

void
test_highest_ip(char *ip_address, char mask);

int
main(void)
{
        char *ip_address = "192.168.10.100";
        char mask = 24;

        test_broadcast_addr(ip_address, mask);
        test_ip_integral_value(ip_address);
        test_decimal_to_dotted_ipv4(ip_address);
        test_network_id(ip_address, mask);
        test_subnet_cardinality(24);             /* 2^8 - 2 = 254 hosts */
        test_subnet_cardinality(30);             /* 2 hosts */
        test_subnet_cardinality(25);             /* CIDR range; 126 hosts */
        test_ip_membership(ip_address, mask);
        test_lowest_ip(ip_address, mask);
        test_highest_ip(ip_address, mask);

        return 0;
}

void
test_broadcast_addr(char *ip_address, char mask) {
        char *output_buffer = (char *)malloc(sizeof(char) * 20);
        /* preventing stack smashing */
        char *ip_addr = (char *)malloc(sizeof(char) * 20);
        strcpy(ip_addr, ip_address);

        printf("The IP address is: %s\n", ip_addr);
        get_broadcast_address(ip_addr, mask, output_buffer);
        printf("Broadcast address in %s is %s\n", __func__, output_buffer);
        free(output_buffer);
        free(ip_addr);
}

void
test_ip_integral_value(char *ip_address)
{
        unsigned int ip;
        ip = get_ip_integral_equivalent(ip_address);

        if (ip == EXIT_FAILURE) {
                fprintf(stderr, "Function failed\n");
                exit(1);
        }

        printf("From %s\n", __func__);
        printf("The integral equivalent of the ip is: %u\n", ip);
}

void
test_decimal_to_dotted_ipv4(char *ip_address)
{
        /* prevent stack smashing */
        char *ip_addr = (char *)malloc(strlen(ip_address));
        strcpy(ip_addr, ip_address);
        char *output_buffer = (char *)malloc(sizeof(char) * 20);

        unsigned int ip = get_ip_integral_equivalent(ip_addr);
        get_abcd_ip_format(ip, output_buffer);
        printf("converting back: %s\n", output_buffer);
        free(output_buffer);
        free(ip_addr);
}

void
test_network_id(char *ip_address, char mask)
{
        char *output_buffer = (char *)malloc(sizeof(char) * 20);

        get_network_id(ip_address, mask, output_buffer);
        printf("Network ID from %s is %s\n", __func__, output_buffer);
        free(output_buffer);
}

void
test_subnet_cardinality(char mask)
{
        printf("This subnet can fit %u hosts\n", get_subnet_cardinality(mask));
}

void
test_ip_membership(char *check_ip, char mask)
{
        char *nw_id = (char *)malloc(sizeof(char) * 20);

        get_network_id(check_ip, mask, nw_id);
        debug("Network ID: %s", nw_id);
        if (check_ip_subnet_membership(nw_id, mask, check_ip))
                printf("The IP %s belongs to the network %s\n", check_ip, nw_id);
        else
                printf("The IP %s does not belong to the network %s\n", check_ip, nw_id);
}

void
test_lowest_ip(char *ip_address, char mask)
{
        char *nw = (char *)malloc(sizeof(char) * 2);
        check_mem(nw);
        char *lowest = (char *)malloc(sizeof(char) * 2);
        check_mem(lowest);

        get_network_id(ip_address, mask, nw);
        get_abcd_ip_format(get_host_address_min(nw), lowest);

        printf("The minimum host address is: %s\n", lowest);

error:
        if (nw) free(nw);
        if (lowest) free(lowest);
}

void
test_highest_ip(char *ip_address, char mask)
{
        char *nw = (char *)malloc(sizeof(char) * 2);
        check_mem(nw);
        char *highest = (char *)malloc(sizeof(char) * 2);
        check_mem(highest);

        get_network_id(ip_address, mask, nw);
        get_abcd_ip_format(get_host_address_max(nw, mask), highest);

        printf("The maximum host address is: %s\n", highest);

error:
        if (nw) free(nw);
        if (highest) free(highest);
}
