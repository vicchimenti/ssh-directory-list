/*****
 * Victor Chimenti
 * CPSC 5520 19FQ
 * Distributed Systems
 * Directory List Service - Client
 * listdir_client.c
 * Last Modified: 20191012
 *
 * 
 *
 */


#include "listdir.h"
#include <stdio.h>
#include <errno.h>
#include <rpc/rpc.h>

extern int errno;

void
dir_list_prog_1(char *host, char *argument)
{
	CLIENT *clnt;
	readdir_ret  *result_1;
	nametype  readdir_1_arg;
	namelist nl;

#ifndef	DEBUG
	clnt = clnt_create (host, DIR_LIST_PROG, DIR_LIST_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	
	// assign arg	
	readdir_1_arg = argument;
	errno = 0;
	
	// call server
	result_1 = readdir_1(&readdir_1_arg, clnt);
	if (result_1 == (readdir_ret *) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		if (errno != 0) {
			perror(argument);
			exit(1);
		} else {
			// print server response
			for (nl = result_1->readdir_ret_u.list;
				nl = nl->next;) {
					printf("\n%s\n", nl->name);
				}
		}
	}
	
#ifndef	DEBUG
	clnt_freeres(clnt, (xdrproc_t)xdr_readdir_ret, (char*)result_1);
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	// create host info
	char *host;
	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	
	// check for path input in argument list
	if (argc < 3) {
		// post error message
		perror("\nToo few arguments; requires two args, using default cwd\n");
	} else {
		// call list function with user arg
		dir_list_prog_1 (host, argv[2]);
	}

exit (0);
}

