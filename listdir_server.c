/****
 * Victor Chimenti
 * CPSC 5520 19FQ
 * Distributed Systems
 * Directory List Service - Server
 * listdir_server.c
 * Last Modified: 20191013
 *
 *
 *
 */



#include "listdir.h"
#include <errno.h>
#include <dirent.h>
#include <string.h>

extern int errno;
extern char *strdup();


readdir_ret *
readdir_1_svc(nametype *argp, struct svc_req *rqstp)
{
	// initialize local variables
	static readdir_ret  result;
	int errnum;
	DIR *dirp;
	struct dirent *dp;
	namelist nl = NULL;
	namelist *nlp = NULL;

	// open and assign directory
	dirp = opendir(*argp);
	if (dirp == (DIR *) NULL) {
		errnum = errno;
		perror("\nopendir failed\n");
	}

	// stream directory and assign linked list
	nlp = &result.readdir_ret_u.list;
	while (dp = readdir(dirp)) {
		nl = *nlp = (namenode*)malloc(sizeof(namenode));
		if (nl == (namenode*) NULL) {
			errnum = EAGAIN;
			closedir(dirp);
			return(&result);
		}
		nl->name = strdup(dp->d_name);
		nlp = &nl->next;
	}

	// close directory and return result
	*nlp = (namelist)NULL;
	errnum = 0;
	closedir(dirp);

	// free memory
	done:
	 	(void)xdr_free((xdrproc_t)xdr_namelist,(char*)nlp);
	done_no_free:
	
	return (&result);
}
