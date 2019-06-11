/*
 * =====================================================================================
 *
 *       Filename:  ip_maths.h
 *
 *    Description:  Some functions that help calculate assignable and broadcast IP addresses
 *
 *        Version:  1.0
 *        Created:  06/06/2019 08:39:45 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ratnadeep Bhattacharya (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __IP_MATHS_H__
#define __IP_MATHS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Given an IP address and network mask return the broadcast IP of the network
 * @param ip_address is the network IP address in question
 * @param mask is the network mask
 * @param output_buffer stores the octet representation of the broadcast
 * address
 */
void
get_broadcast_address(char *ip_address, char mask, char *output_buffer);

unsigned int
get_ip_integral_equivalent(char *ip_address);

/*
 * Return the octet representation of a given ip in decimal format
 * @param ip_address is the decimal format of an IP address
 * @param output_buffer is the octet representation of the same IP in the
 * octet format
 */
void
get_abcd_ip_format(unsigned int ip_address, char *output_buffer);

/*
 * Get the network id for a given ip and network mask
 * @param ip_address is a character array that stores the string representation
 * of the IP in octet format
 * @param mask is the network mask of the network
 * @output_buffer is a character array that stores the result in the octet
 * representation of the network ID
 */
void
get_network_id(char *ip_address, char mask, char *output_buffer);

/*
 * Get the maximum number of hosts that can be fitted into this network
 * @param mask is the network mask for the subnet in question
 * @returns an unsigned int indicating the cardinality of the subent
 */
unsigned int
get_subnet_cardinality(char mask);

/* 
 * Check if IP address belongs to the given network ID with the given mask
 * @param network_id is the id of the network
 * @param mask is the network mask
 * @param check_ip is the IP that is being checked for
 */
int /* return 0 if true, -1 if false */
check_ip_subnet_membership(char *network_id, char mask, char *check_ip);

#endif
