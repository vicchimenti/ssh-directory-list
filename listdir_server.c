/****
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
#include <stdio.h>
#include <string.h>
#include<rpc/xdr.h>

extern int errno;


readdir_ret *
readdir_1_svc(nametype *argp, struct svc_req *rqstp)
{
	static readdir_ret  result;
	int errnum;
	DIR *dirp;
	struct dirent *dp;
	namelist nl;
	namelist *nlp;

	// xdr_free(xdr_namenode, &xdr_namelist);
	// xdr_free((xdrproc_t)xdr_namelist,(char*)nlp);

	// open and assign directory
	dirp = opendir(*argp);
	if (dirp == (DIR *) NULL) {
		errnum = errno;
		perror("\nopendir failed\n");
	}
	// xdr_free(xdr_readdir_ret, &result);
	// xdr_free((xdrproc_t)xdr_namelist,(char*)nlp);

	nlp = &result.readdir_ret_u.list;
	while (dp = readdir(dirp)) {
		nl = *nlp = (namenode*)
		malloc(sizeof(namenode));
		if (nl == (namenode*) NULL) {
			errnum = EAGAIN;
			closedir(dirp);
			return(&result);
		}
		nl->name = strdup(dp->d_name);
		nlp = &nl->next;
	}

	*nlp = (namelist)NULL;
	errnum = 0;
	closedir(dirp);
	return (&result);
}
