/*              Copyright (C) 2002 Fabio Fiorina
 *
 * This file is part of LIBASN1.
 *
 * The LIBTASN1 library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public   
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include <int.h>
#include "errors.h"
#ifdef STDC_HEADERS
# include <stdarg.h>
#endif


#define LIBTASN1_ERROR_ENTRY(name) \
	{ #name, name }

struct libtasn1_error_entry {
	const char *name;
	int  number;
};
typedef struct libtasn1_error_entry libtasn1_error_entry;

static libtasn1_error_entry error_algorithms[] = {
	LIBTASN1_ERROR_ENTRY( ASN1_SUCCESS ),
	LIBTASN1_ERROR_ENTRY( ASN1_FILE_NOT_FOUND ),
	LIBTASN1_ERROR_ENTRY( ASN1_ELEMENT_NOT_FOUND ),
	LIBTASN1_ERROR_ENTRY( ASN1_IDENTIFIER_NOT_FOUND ),
	LIBTASN1_ERROR_ENTRY( ASN1_DER_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_VALUE_NOT_FOUND ),
	LIBTASN1_ERROR_ENTRY( ASN1_GENERIC_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_VALUE_NOT_VALID ),
	LIBTASN1_ERROR_ENTRY( ASN1_TAG_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_TAG_IMPLICIT ),
	LIBTASN1_ERROR_ENTRY( ASN1_ERROR_TYPE_ANY ),
	LIBTASN1_ERROR_ENTRY( ASN1_SYNTAX_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_MEM_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_MEM_ALLOC_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_DER_OVERFLOW ),
	LIBTASN1_ERROR_ENTRY( ASN1_NAME_TOO_LONG ),
	LIBTASN1_ERROR_ENTRY( ASN1_ARRAY_ERROR ),
	LIBTASN1_ERROR_ENTRY( ASN1_ELEMENT_NOT_EMPTY ),
	{0}
};

#define LIBTASN1_ERROR_LOOP(b) \
        const libtasn1_error_entry *p; \
                for(p = error_algorithms; p->name != NULL; p++) { b ; }

#define LIBTASN1_ERROR_ALG_LOOP(a) \
                        LIBTASN1_ERROR_LOOP( if(p->number == error) { a; break; } )



/**
  * libtasn1_perror - prints a string to stderr with a description of an error
  * @error: is an error returned by a libasn1 function. 
  *
  * This function is like perror(). The only difference is that it accepts an 
  * error returned by a libasn1 function. 
  **/
void libtasn1_perror(asn1_retCode error)
{
	const char *ret = NULL;

	/* avoid prefix */
	LIBTASN1_ERROR_ALG_LOOP(ret =
			      p->name + sizeof("ASN1_") - 1);

	_libtasn1_log( "LIBTASN1 ERROR: %s\n", ret);
	
}


/**
  * libtasn1_strerror - Returns a string with a description of an error
  * @error: is an error returned by a libtasn1 function.
  *
  * This function is similar to strerror(). The only difference is that it 
  * accepts an error (number) returned by a libasn1 function. 
  **/
const char* libtasn1_strerror(asn1_retCode error)
{
	const char *ret = NULL;

	/* avoid prefix */
	LIBTASN1_ERROR_ALG_LOOP(ret =
			      p->name + sizeof("ASN1_") - 1);

	return ret;
}

/* this function will output a message.
 */
#ifdef LIBTASN1_DEBUG
void _libtasn1_log( const char *fmt, ...) {
 va_list args;
 char str[MAX_LOG_SIZE];

 va_start(args,fmt);
 vsprintf( str,fmt,args); /* Flawfinder: ignore */
 va_end(args);   

 fprintf(stderr, str);

 return;
}
#else /* not DEBUG */
# ifndef C99_MACROS

/* Without C99 macros these functions have to
 * be called. This may affect performance.
 */
void _libtasn1_null_log( void* x, ...) { return; }
# endif /* C99_MACROS */
#endif /* DEBUG */
