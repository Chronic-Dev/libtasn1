/*
 *      Copyright (C) 2002 Fabio Fiorina
 *
 * This file is part of LIBASN1.
 *
 * LIBASN1 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * LIBASN1 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */


/*****************************************************/
/* File: Test_parser.c                               */
/* Description: Test sequences for these functions:  */
/*     asn1_parser_asn1,                             */   
/*****************************************************/

#include <stdio.h>
#include <string.h>
#include "libtasn1.h"

typedef struct{
  int lineNumber;
  char *line;
  int  errorNumber;
  char *errorDescription;
} test_type;

char fileCorrectName[]="Test_parser.asn";
char fileErroredName[]="Test_parser_ERROR.asn";

#define _FILE_ "Test_parser_ERROR.asn"

test_type test_array[]={
  /* Test DEFINITIONS syntax */
  {5,"TEST_PARSER2 { } DEFINITIONS IMPLICIT TAGS ::= BEGIN int1 ::= INTEGER END",
   ASN1_SYNTAX_ERROR,_FILE_":6: parse error near 'TEST_PARSER'"},
  {6,"TEST_PARSER { }",ASN1_SUCCESS,""},

  /* Test MAX_NAME_SIZE (128) */
  {12,"a1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567 ::= INTEGER",
   ASN1_SUCCESS,""},
  {12,"a12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678 ::= INTEGER",
   ASN1_NAME_TOO_LONG,_FILE_":12: name too long (more than 128 characters)"},

  /* Test 'check identifier' function */
  {12,"ident1 ::= ident2   ident2 ::= INTEGER",
   ASN1_SUCCESS,""},
  {12,"ident1 ::= ident2",
   ASN1_IDENTIFIER_NOT_FOUND,_FILE_":: identifier 'ident2' not found"},
  {12,"obj1 OBJECT IDENTIFIER ::= {pkix 0 5 4}    "
      "pkix OBJECT IDENTIFIER ::= {1 2}",
   ASN1_SUCCESS,""},
  {12,"obj1 OBJECT IDENTIFIER ::= {pkix 0 5 4}",
   ASN1_IDENTIFIER_NOT_FOUND,_FILE_":: identifier 'pkix' not found"},

  /* Test INTEGER */
  {14,"int1 INTEGER OPTIONAL,",ASN1_SUCCESS,""},
  {14,"int1 INTEGER DEFAULT 1,",ASN1_SUCCESS,""},
  {14,"int1 INTEGER DEFAULT -1,",ASN1_SUCCESS,""},
  {14,"int1 INTEGER DEFAULT v1,",ASN1_SUCCESS,""},
  {14,"int1 [1] INTEGER,",ASN1_SUCCESS,""},
  {14,"int1 [1] EXPLICIT INTEGER,",ASN1_SUCCESS,""},
  {14,"int1 [1] IMPLICIT INTEGER,",ASN1_SUCCESS,""},
  {12,"Integer ::= [1] EXPLICIT INTEGER {v1(-1), v2(1)}",ASN1_SUCCESS,""},
  {12,"Integer ::= INTEGER {v1(0), v2}",
   ASN1_SYNTAX_ERROR,_FILE_":12: parse error near '}'"},
  {12,"Integer ::= INTEGER {v1(0), 1}",
   ASN1_SYNTAX_ERROR,_FILE_":12: parse error near '1'"},
  {12,"const1 INTEGER ::= -1",ASN1_SUCCESS,""},
  {12,"const1 INTEGER ::= 1",ASN1_SUCCESS,""},
  {12,"const1 INTEGER ::= v1",
   ASN1_SYNTAX_ERROR,_FILE_":12: parse error near 'v1'"},
  {16," generic generalstring",
   ASN1_IDENTIFIER_NOT_FOUND,_FILE_":: identifier 'generalstring' not found"},  


  /* end */
  {0}
};

char
readLine(FILE *file,char *line)
{
  char c;

  while(((c=fgetc(file))!=EOF) && (c!='\n')){
    *line=c;
    line++;
  }

  *line=0;

  return c;
}


void
createFile(int lineNumber,char *line)
{
  FILE *fileIn,*fileOut;
  char lineRead[1024];
  int fileInLineNumber=0;

  fileIn=fopen(fileCorrectName,"r");
  fileOut=fopen(fileErroredName,"w");

  while(readLine(fileIn,lineRead) != EOF){
    fileInLineNumber++;
    if(fileInLineNumber==lineNumber)
      fprintf(fileOut,"%s\n",line);
    else
      fprintf(fileOut,"%s\n",lineRead);
  }

  fclose(fileOut);
  fclose(fileIn);
}


int 
main(int argc,char *argv[])
{
  asn1_retCode result;
  ASN1_TYPE definitions=ASN1_TYPE_EMPTY;
  char errorDescription[MAX_ERROR_DESCRIPTION_SIZE];
  test_type *test;
  int errorCounter=0,testCounter=0;

  printf("\n\n/****************************************/\n");
  printf(    "/*     Test sequence : Test_parser      */\n");
  printf(    "/****************************************/\n\n");


  result=asn1_parser2tree(fileCorrectName,&definitions,errorDescription);

  if(result!=ASN1_SUCCESS){
    printf("File '%s' not correct\n",fileCorrectName);
    libtasn1_perror(result);
    printf("ErrorDescription = %s\n\n",errorDescription);
    exit(1);
  }

  /* Only for Test */
  /* asn1_visit_tree(stdout,definitions,"TEST_PARSER",ASN1_PRINT_ALL); */

  /* Clear the definitions structures */
  asn1_delete_structure(&definitions);


  test=test_array;

  while(test->lineNumber != 0){
    testCounter++;

    createFile(test->lineNumber,test->line);

    result=asn1_parser2tree(fileErroredName,&definitions,errorDescription);
    asn1_delete_structure(&definitions);

    if((result != test->errorNumber) || 
       (strcmp(errorDescription,test->errorDescription))){
      errorCounter++;
      printf("ERROR N. %d:\n",errorCounter);
      printf("  Line %d - %s\n",test->lineNumber,test->line);
      printf("  Error expected: %s - %s\n",libtasn1_strerror(test->errorNumber),
             test->errorDescription);
      printf("  Error detected: %s - %s\n\n",libtasn1_strerror(result),
             errorDescription);
    }
 
    test++;
  }


  printf("Total tests : %d\n",testCounter);
  printf("Total errors: %d\n",errorCounter);

  exit(0);
}







