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
        int old = 0; /* hold the index of the last period */

        int sz = strlen(ip_address);
        char *temp = (char *)malloc(sizeof(char)
                        * 3 /* size of each octet */
                        * num /* number of octets */
                        + (num - 1) /* space for periods */
                        );

        if (num > 3) return NULL; /* error handling; there can only be 3 periods in an ip address */

        /* j is incremented for each octet
         * the while loop breaks when num octets are found */
        while (j != num) {
                for (; i < strlen(ip_address); i++) {
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

        while (i >= 0) {
                ip += atoi(strtok(NULL, ".")) * (int)pow(256.0, (double)(i));
                i--;
        }
        return ip;
}

char *
decimal_to_dotted_ipv4(unsigned int ip_address)
{
        printf("Starting %s\n", __func__); /* debug */
        char *ip_addr;
        char *octet;
        int oct;
        int i;
        /* the max value of ip address can be
         * 255 * (256**3) + 255 * (256*2) + 255 * 256 + 255 */
        if (ip_address < 0 || ip_address > 4278386175) exit(EXIT_FAILURE);
        i = 0;

        ip_addr = (char *)malloc(sizeof(char) * 20);
        octet = (char *)malloc(sizeof(char) * 3);

        /* the first octet */
        oct = (int)(ip_address / pow(256.0, 3.0));
        sprintf(octet, "%d", oct);
        memcpy(ip_addr, octet, strlen(octet));
        i += strlen(octet);
        memcpy(&ip_addr[i], ".", 1);
        i++;
        /* the second octet */
        ip_address -= (oct * (int)pow(256.0, 3.0));
        oct = (int)(ip_address / pow(256.0, 2.0));
        sprintf(octet, "%d", oct);
        memcpy(&ip_addr[i], octet, strlen(octet));
        i += strlen(octet);
        memcpy(&ip_addr[i], ".", 1);
        i++;
        /* the third octet */
        ip_address -= (oct * (int)pow(256.0, 2.0));
        oct = (int)(ip_address / 256);
        sprintf(octet, "%d", oct);
        memcpy(&ip_addr[i], octet, strlen(octet));
        i += strlen(octet);
        memcpy(&ip_addr[i], ".", 1);
        i++;
        /* the final octet */
        ip_address -= oct * 256;
        sprintf(octet, "%d", ip_address);
        memcpy(&ip_addr[i], octet, strlen(octet));

        return ip_addr;
}


void
get_cidr_broadcast_addr(char *ip_address, char mask, char **output_buffer)
{
        int i = 0;
        unsigned int ip = 0;
        char *ip_int;
        if (mask < 8 || mask > 30) exit(EXIT_FAILURE);

        ip = get_ip_integral_equivalent(ip_address);
        ip_int = decimal_to_dotted_ipv4(ip | mask);

        memcpy(&(*output_buffer), &ip_int, strlen(ip_int));
}

void
get_broadcast_address(char *ip_address, char mask, char **output_buffer)
{
        int i = 0;
        int sz = strlen(ip_address);
        char* temp;
        char num;
        char *ret = NULL;
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
                        memcpy(&(*output_buffer), /* start of the output array */
                                        &ret, strlen(ret));
                        memcpy(&(*output_buffer)[strlen(ret)], /* end of the output array */
                                        temp, strlen(temp));
                }
        } else {
                get_cidr_broadcast_addr(ip_address, mask, output_buffer);
        }
        
}
