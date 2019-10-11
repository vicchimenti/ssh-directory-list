/*****
 * Victor Chimenti
 * CPSC 5520 19FQ
 * Distributed Systems
 * Directory List Service - Client
 * listdir_client.c
 * Last Modified: 20191007
 *
 * 
 *
 */


#include "listdir.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>


void
dir_list_prog_1(char *host, char *argument)
{
	CLIENT *clnt;
	readdir_ret  *result_1;
	nametype  readdir_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, DIR_LIST_PROG, DIR_LIST_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	
	// assign arg	
	readdir_1_arg = argument;

	// debugging
	printf("\nReady to pass arg to server: %s\n", readdir_1_arg);

	// call server
	result_1 = readdir_1(&readdir_1_arg, clnt);
	if (result_1 == (readdir_ret *) NULL) {
		clnt_perror (clnt, "call failed");
	} else {
		printf("\nReceived echo from server: %s\n", result_1);
	}
#ifndef	DEBUG
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

	// get current working directory with debugging
	char cwd[MAXLEN];
	if(getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd() error");
	else
		printf("\nCurrent Working Directory: %s\n", cwd);
	
	// check for path input in argument list
	if (argc < 3) {
		dir_list_prog_1(host, cwd);
		perror("\nToo few arguments; requires two args, using default cwd\n");
	} else {
		// call list function with user arg
		dir_list_prog_1 (host, argv[2]);
	}

exit (0);
}
