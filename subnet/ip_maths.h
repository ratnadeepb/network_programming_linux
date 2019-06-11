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

void
get_broadcast_address(char *ip_address, char mask, char **output_buffer);

unsigned int
get_ip_integral_equivalent(char *ip_address);

char *
decimal_to_dotted_ipv4(unsigned int ip_address);

void
get_abcd_ip_format(unsigned int ip_address, char *output_buffer);

void
get_network_id(char *ip_address, char mask, char *output_buffer);

unsigned int
get_subnet_cardinality(char mask);

int /* return 0 if true, -1 if false */
check_ip_subnet_membership(char *network_id, char mask, char *check_ip);

#endif
