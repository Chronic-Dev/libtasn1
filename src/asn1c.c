/*
 *      Copyright (C) 2000,2001 Fabio Fiorina
 *
 * This file is part of GNUTLS.
 *
 * GNUTLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUTLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */


/*****************************************************/
/* File: PkixTabExample.c                            */
/* Description: An example on how to use the         */
/*              'asn1_parser_asn1_file_c' function.  */   
/*****************************************************/

#include <stdio.h>
#include <string.h>
#include "libtasn1.h"

int
main(int argc,char *argv[])
{
  int result;
  char* outfile;
  char errorDescription[MAX_ERROR_DESCRIPTION_SIZE];

  
  if(argc<2||argc>3) {
  	fprintf(stderr, "Usage: %s: input.asn output.c\n", argv[0]);
  	exit(1);
  }
 
  if (argc==3) outfile=argv[2];
  else outfile=NULL;
  
  result=asn1_parser2array( argv[1], outfile, NULL, errorDescription);

  if(result==ASN1_SYNTAX_ERROR){
    printf("PARSE ERROR\n");
    return 1;
  }
  else if(result==ASN1_IDENTIFIER_NOT_FOUND){
    printf("IDENTIFIER NOT FOUND\n");
    return 1;
  }
  else if(result==ASN1_FILE_NOT_FOUND){
    printf("FILE NOT FOUND\n");
    return 1;
  }

     return 0;
}









