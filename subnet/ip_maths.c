/*
 * =====================================================================================
 *
 *       Filename:  ip_maths.c
 *
 *    Description:  subnet related functions
 *
 *        Version:  1.0
 *        Created:  06/13/2019 03:06:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ratnadeep Bhattacharya
 *   Organization:  
 *
 * =====================================================================================
 */

#include <math.h>
#include <assert.h>
#include "ip_maths.h"
#include "../common/dbg.h"

unsigned int
convert_mask(char mask)
{
        int i;
        unsigned int mask_int;
        if (mask < 8 || mask > 30) {
                fprintf(stderr, "Wrong mask\n");
                exit(1);
        }

        i = 31;
        mask_int = 0;

        while (1) {
                if (i < (32 - mask)) break;
                mask_int += (unsigned int)pow(2, (double)i);
                i--;
        }

        debug("Mask is: %u", mask_int);
        return mask_int;
}

void
get_broadcast_address(char *ip_address, char mask, char *output_buffer)
{
        unsigned int ip;
        unsigned int broadcast_ip;
        unsigned int mask_int;

        mask_int = convert_mask(mask);
        ip = get_ip_integral_equivalent(ip_address);
        broadcast_ip = (ip | ~mask_int);
        get_abcd_ip_format(broadcast_ip, output_buffer);
}

unsigned int
get_ip_integral_equivalent(char *ip_address)
{
        unsigned int ip;
        double lim;
        char *delim;
        char *ip_copy;
        int i;
        unsigned int temp;

        ip = 0;
        lim = 256;
        delim = ".";
        // strtok modifies its argument. With a string literal, placed in read-only memory
        // this will cause a segmentation fault
        ip_copy = strdup(ip_address); 
        i = 3;
        temp = 0;
        debug("ip address: %s", ip_address);

        while (1) {
                char *tok;
                if (i == 3) {
                        if ((tok = strtok(ip_copy, delim)) == NULL)
                                return EXIT_FAILURE;
                        else temp = (unsigned int)atoi(tok);

                }
                else {
                        if ((tok = strtok(NULL, delim)) == NULL)
                                return EXIT_FAILURE;
                        else temp = (unsigned int)atoi(tok);
                }
                ip += temp * (unsigned int)pow(lim, (double)i);
                i--;
                
                if (i < 0) break;
        }
        return ip;
}

void
get_abcd_ip_format(unsigned int ip_address, char *output_buffer)
{
        unsigned int tmp;
        char *octet;
        double lim;
        int i;
        int j;

        tmp = 0;
        octet = (char *)malloc(sizeof(char) * 4);
        check_mem(octet);
        lim = 256;
        i = 3;
        j = 0;

        for (; i >= 0; i--) {
                tmp = (unsigned int)(ip_address / pow(lim, (double)i)); // get the octet
                //sprintf(octet, "%u", tmp);                              // convert to string
                snprintf(octet, sizeof(tmp), "%u", tmp);                              // convert to string
                ip_address -= tmp * (int)(pow(lim, (double)i));         // reduce IP address int by appropriate amount
                memcpy(&output_buffer[j], octet, strlen(octet));        // copy octet over
                j += strlen(octet);                                     // increment array counter
                if (i != 0) {                                           // don't add the dot at the end of the last octet
                        memcpy(&output_buffer[j], ".", 1);
                        j++;
                }
                memset(octet, 0, strlen(octet));
        }
error:
        if (octet) free(octet);
}

void
get_network_id(char *ip_address, char mask, char *output_buffer)
{
        unsigned int ip;
        unsigned int nw;
        char *network_id;
        unsigned int mask_int;

        mask_int = convert_mask(mask);
        debug("Mask is: %u", mask_int);
        network_id = (char *)malloc(sizeof(char) * strlen(ip_address));
        ip = get_ip_integral_equivalent(ip_address);
        debug("IP address: %u", ip);
        nw = (ip & mask_int);
        debug("Network ID: %u", nw);
        get_abcd_ip_format(nw, network_id);
        debug("dotted format: %s", network_id);
        memcpy(output_buffer, network_id, strlen(network_id));
}

unsigned int
get_subnet_cardinality(char mask)
{
        int i;
        unsigned int cardinality;
        
        i = 31;
        cardinality = 0;

        while (1) {
                if (i < (32 - mask)) cardinality += (unsigned int)pow(2.0, (double)i);
                i--;
                if (i < 0) break;
        }

        return cardinality - 1;
}

int /* return 0 if true, -1 if false */
check_ip_subnet_membership(char *network_id, char mask, char *check_ip)
{
        char *output_buffer;

        output_buffer = (char *)malloc(sizeof(char) * 20);
        check_mem(output_buffer);
        get_network_id(check_ip, mask, output_buffer);
        debug("Network ID: %s", network_id);
        debug("IP: %s", output_buffer);

error:
        if (output_buffer) free(output_buffer);

        //if (strcmp(output_buffer, network_id) == 0) return 0;
        if (get_ip_integral_equivalent(network_id)
                        == get_ip_integral_equivalent(output_buffer))
                return 0;
        return -1;
}

unsigned int
get_host_address_min(char *network_id)
{
        unsigned int lowest_ip;

        lowest_ip = get_ip_integral_equivalent(network_id);
        lowest_ip++;
        return lowest_ip;
}

unsigned int
get_host_address_max(char *network_id, char mask)
{
        unsigned int nw;
        unsigned int highest_ip;
        int i;

        nw = get_ip_integral_equivalent(network_id);
        highest_ip = 0;

        for (i = 0; i < (32 - mask); i++) highest_ip += (unsigned int)pow(2.0, (double)i);
        highest_ip--;
        highest_ip += nw;

        return highest_ip;
}
