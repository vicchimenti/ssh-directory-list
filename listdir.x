/***
* Victor Chimenti
* CPSC 5520 19FQ
* HW2 - A Simple Directory Listing Service
* listdir.x
* Last Modified: 20191007
*
*
*/



/***
* listdir.x
*
*/
const MAXLEN = 255;
typedef string nametype<MAXLEN>;
typedef struct namenode* namelist;

/***
* directory list node
*
*/
struct namenode {
	nametype name;
	namelist next;
};

/***
* union result switch
*
*/
union readdir_ret switch(int err) {
	case 0:
		namelist list;
	default:
		void;
};

/***
* IDL program declaration
*
*/
program DIR_LIST_PROG {
	version DIR_LIST_VERS {
		readdir_ret READDIR(nametype)=1;
	}=1;
}=0x20000026;

