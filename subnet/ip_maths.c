/*
 * =====================================================================================
 *
 *       Filename:  ip_maths.c
 *
 *    Description:  Implement IP math functions
 *
 *        Version:  1.0
 *        Created:  06/06/2019 08:46:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ratnadeep Bhattacharya
 *   Organization:  
 *
 * =====================================================================================
 */

#include <math.h>
#include "ip_maths.h"

char *
get_octets(char *ip_address, char num) {
        int i = 0;
        int j = 0;

        char *temp = (char *)malloc(sizeof(char)
                        * 3 /* size of each octet */
                        * num /* number of octets */
                        + (num - 1) /* space for periods */
                        );

        if (num > 3) return NULL; /* error handling; there can only be 3 periods in an ip address */

        /* j is incremented for each octet
         * the while loop breaks when num octets are found */
        while (j != num) {
                for (; i < (int)strlen(ip_address); i++) {
                        if (ip_address[i] == '.') j++;
                        if (j == num) break;
                }
        }
        memcpy(temp, ip_address, i + 1);
        return temp;
}

unsigned int
get_ip_integral_equivalent(char *ip_address) {
        unsigned int ip = 0;
        int i = 2;
        /* preventing segmentation fault by strtok */
        char *ip_addr = (char *)malloc(sizeof(char) * 20);
        strcpy(ip_addr, ip_address);

        ip = atoi(strtok(ip_addr, ".")) * (int)pow(256.0, 3.0);

        while (1) {
                ip += atoi(strtok(NULL, ".")) * (int)pow(256.0, (double)(i));
                i--;
                if (i < 0) break;
        }
        return ip;
}

void
get_abcd_ip_format(unsigned int ip_address, char *output_buffer)
{
        char *ip_addr;
        char *octet;
        int oct;
        int i;

        /* the max value of ip address can be
         * 255 * (256**3) + 255 * (256*2) + 255 * 256 + 255 */
        if (ip_address > 4278386175) exit(EXIT_FAILURE);
        i = 0;

        ip_addr = (char *)malloc(sizeof(char) * 20);
        octet = (char *)malloc(sizeof(char) * 4);

        /* the first octet */
        oct = (int)(ip_address / pow(256.0, 3.0));
        sprintf(octet, "%d", oct);
        strcpy(ip_addr, octet);
        i += strlen(octet);
        strcpy(&ip_addr[i], ".");
        i++;
        /* the second octet */
        ip_address -= (oct * (int)pow(256.0, 3.0));
        oct = (int)(ip_address / pow(256.0, 2.0));
        sprintf(octet, "%d", oct);
        strcpy(&ip_addr[i], octet);
        i += strlen(octet);
        strcpy(&ip_addr[i], ".");
        i++;
        /* the third octet */
        ip_address -= (oct * (int)pow(256.0, 2.0));
        oct = (int)(ip_address / 256);
        sprintf(octet, "%d", oct);
        strcpy(&ip_addr[i], octet);
        i += strlen(octet);
        strcpy(&ip_addr[i], ".");
        i++;
        /* the final octet */
        ip_address -= oct * 256;
        sprintf(octet, "%d", ip_address);
        strcpy(&ip_addr[i], octet);

        strcpy(output_buffer, ip_addr);
}

void
get_cidr_broadcast_addr(char *ip_address, char mask, char *output_buffer)
{
        unsigned int ip = 0;
        /* prevent stack smashing */
        char * ip_addr = (char *)malloc(strlen(ip_address));
        strcpy(ip_addr, ip_address);
        char *ip_int = (char *)malloc(sizeof(char) * 20);
        if (mask < 8 || mask > 30) exit(EXIT_FAILURE);

        ip = get_ip_integral_equivalent(ip_addr);
        get_abcd_ip_format(ip | mask, ip_int);

        strcpy(output_buffer, ip_int);
}

void
get_broadcast_address(char *ip_address, char mask, char *output_buffer)
{
        char *temp;
        char num;
        char *ret;
        int cidr = 0;

        if (mask < 8 || mask > 30) exit(EXIT_FAILURE); /* mask cannot be less than 8 or more than 30 or less than 1 */

        /* we assume that CIDR is not being used */
        switch (mask) {
                case 8:
                        num = 1;
                        temp = (char *)malloc(sizeof(char) * 11);
                        temp = "255.255.255";
                        break;
                case 16:
                        num = 2;
                        temp = (char *)malloc(sizeof(char) * 7);
                        temp = "255.255";
                        break;
                case 24:
                        num = 3;
                        temp = (char *)malloc(sizeof(char) * 3);
                        temp = "255";
                        break;
                default: /* assume CIDR */
                        cidr = 1;
                        break;
        }

        if (!cidr) {
                if ((ret = get_octets(ip_address, num)) != NULL) {
                       // memcpy(&(*output_buffer), /* start of the output array */
                       //                 &ret, strlen(ret));
                       // memcpy(&(*output_buffer)[strlen(ret)], /* end of the output array */
                       //                 temp, strlen(temp));
                       strcpy(output_buffer, ret);
                       strcpy(&output_buffer[strlen(ret)], temp);
                }
        } else {
                get_cidr_broadcast_addr(ip_address, mask, output_buffer);
        } 
}

void
get_network_id(char *ip_address, char mask, char *output_buffer)
{
        char *ip_addr = (char *)malloc(sizeof(char) * 20);
        strcpy(ip_addr, ip_address);
        unsigned int ip = get_ip_integral_equivalent(ip_addr);
        unsigned int nw_id = ip | mask;
        char *network_id = (char *)malloc(sizeof(char) * 20);

        get_abcd_ip_format(nw_id, network_id);
        strcpy(output_buffer, network_id);
}

unsigned int
get_subnet_cardinality(char mask)
{
        const char bits = 32;

        if (mask < 8 || mask > 30) exit(EXIT_FAILURE);

        /* 2 IPs are reserved for network ID (0) and broadcast address (255) */
        return (unsigned int)pow(2.0, (double)(bits - mask)) - 2;
}

int /* return 0 if true, -1 if false */
check_ip_subnet_membership(char *network_id, char mask, char *check_ip)
{
        char *nw_id = (char *)malloc(sizeof(char) * 20);

        get_network_id(check_ip, mask, nw_id);

        if (strcmp(nw_id, network_id) != 0) return -1;
        else return 0;
}
