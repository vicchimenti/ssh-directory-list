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
// #include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

readdir_ret *
readdir_1_svc(nametype *argp, struct svc_req *rqstp)
{
	static readdir_ret  result;
	DIR *dirp;
	struct dirent *dp;
	namelist nl;
	namelist *nlp;

	// xdr_free(xdr_namenode, &xdr_namelist);
	// debugging print
	printf("\nClient arg received: %s\n", *argp);

	// open and assign directory
	dirp = opendir(*argp);
	if (dirp == (DIR *) NULL) {
		result.errno = errno;
		return (%result);
	}
	xdr_free(xdr_readdir_result, &result);

	nlp = #ret.xdr_readdir_result_u.list;
	while (dp = readdir(dirp)) {
		nl = *nlp = (namenode*)
		malloc(sizeof(namenode));
		if (nl == (namenode*) NULL) {
			result.errno = EAGAIN;
			closedir(dirp);
			return(&result);
		}
		nl->name = strdup(d->d_name);
		nlp = &nl->next;
	}

	*nlp = (namelist)NULL;
	result.errno = 0;
	closedir(dirp);


	// if ((dirp = opendir(".")) == NULL) {
	// 	perror ("\nopendir() error\n");
	// 	(void) printf("Could not find client supplied directory: %s\n", *argp);
	// } else {
	// 	while((dp = readdir(dirp)) != NULL) {
	// 		// debugging print
	// 		printf("\nDirectory Entry specified by client: %s\n", dp->d_name);
	// 		// xdr_namenode->name = dp->d_name;
	// 		// xdr_namenode = xdr_namenode->next;
	// 	}
	// 	result = (readdir_ret)*dirp;
	// 	closedir(dirp);
	// }


	return &result;
}
