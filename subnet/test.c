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

void
test_broadcast_addr(char *ip_address, char mask);

void
test_ip_integral_value(char *ip_address);

void
test_decimal_to_dotted_ipv4(char *ip_address);

int
main(void)
{
        char *ip_address = "192.168.10.100";
        char mask = 25;

        test_broadcast_addr(ip_address, mask);
        test_ip_integral_value(ip_address);
        test_decimal_to_dotted_ipv4(ip_address);

        return 0;
}

void
test_broadcast_addr(char *ip_address, char mask) {
        char *output_buffer;
        /* preventing stack smashing */
        char *ip_addr = (char *)malloc(sizeof(char) * 20);
        strcpy(ip_addr, ip_address);

        printf("The IP address is: %s\n", ip_addr);
        get_broadcast_address(ip_addr, mask, &output_buffer);
        printf("Broadcast address in %s is %s\n", __func__, output_buffer);
}

void
test_ip_integral_value(char *ip_address)
{
        unsigned int ip;
        ip = get_ip_integral_equivalent(ip_address);

        printf("From %s\n", __func__);
        printf("The integral equivalent of the ip is: %u\n", ip);
}

void
test_decimal_to_dotted_ipv4(char *ip_address)
{
        unsigned int ip = get_ip_integral_equivalent(ip_address);
        printf("converting back: %s\n", decimal_to_dotted_ipv4(ip));
}
