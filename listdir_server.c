/*
 * Victor Chimenti
 * CPSC 5520 19FQ
 * Distributed Systems
 * Directory List Service - Server
 * listdir_server.c
 * Last Modified: 20191011
 *
 *
 *
 */



#include "listdir.h"
#include <errno.h>
#include <dirent.h>
// #include <rpc/rpc.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

readdir_ret *
readdir_1_svc(nametype *argp, struct svc_req *rqstp)
{
	static readdir_ret  result;
	DIR *dirp;
	struct dirent *dp;

	// xdr_free(xdr_namenode, &xdr_namelist);
	// debugging print
	printf("\nClient arg received: %s\n", *argp);

	// open and assign directory
	if ((dirp = opendir("/")) == NULL) {
		perror ("\nopendir() error\n");
		(void) printf("Could not find client supplied directory: %s\n", *argp);
	} else {
		while((dp = readdir(dirp)) != NULL) {
			printf("\nDirectory Entry specified by client: %s\n", dp->d_name);
		}
		closedir(dirp);
	}

	// // process argument passed from client
	// do {
	// 	errno = 0;
	// 	if ((dp = readdir(dirp)) != NULL) {
	// 		if (strcmp(dp->d_name, *argp) != 0) { continue; }
	// 			// troubleshooting print
	// 			(void) printf("\nDirectory Entry specified by client: %s\n", *argp);
	// 			(void) closedir(dirp);
	// 		}
	// } while (dp != NULL);

	// // process any errno
	// if (errno !=0) {
	// 	perror("Error reading directory");
	// } else {
	// 	(void) printf("Could not find client supplied directory: %s\n", *argp);
	// }

	// (void) closedir(dirp);

	// return result is not yet assigned
	return &result;
}
