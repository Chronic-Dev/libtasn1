/*************************************************/
/* File: x509_der.h                              */
/* Description: list of exported object by       */
/*   "x509_der.c"                                */
/*************************************************/

#ifndef _GNUTLS_DER_H
#define _GNUTLS_DER_H

#include "asn1.h"

#define UNIVERSAL        0x00
#define APPLICATION      0x40
#define CONTEXT_SPECIFIC 0x80
#define PRIVATE          0xC0
#define STRUCTURED       0x20


void
_asn1_octet_der(unsigned char *str,int str_len,unsigned char *der,int *der_len);

int
_asn1_get_octet_der(unsigned char *der,int *der_len,unsigned char *str,int str_size, int *str_len);

void
_asn1_bit_der(unsigned char *str,int bit_len,unsigned char *der,int *der_len);

int
_asn1_get_bit_der(unsigned char *der,int *der_len,unsigned char *str, int str_size, int *bit_len);

int 
asn1_create_der(node_asn *root,char *name,unsigned char *der,int *len);

int 
asn1_get_der(node_asn *root,unsigned char *der,int len);

int 
asn1_get_start_end_der(node_asn *root,unsigned char *der,int len,char *name_element,int *start, int *end);

unsigned long
_asn1_get_length_der(unsigned char *der,int  *len);

void
_asn1_length_der(unsigned long len,unsigned char *ans,int *ans_len);

char *
_asn1_ltostr(long v,char *str);

#endif





