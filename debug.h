#include <stdio.h>
#include <errno.h>
#include <string.h>

#define Error_on     1
#define Warning_on   1
#define Info_on      1

/*
#define Debug_error(msg...)   do{if(Error_on)  {printf("ERROR--    %s|%s|%d: ",__FILE__,__FUNCTION__,__LINE__);printf(msg);}}while(0)
#define Debug_warning(msg...) do{if(Warning_on){printf("WARNING--  %s|%s|%d: ",__FILE__,__FUNCTION__,__LINE__);printf(msg);}}while(0)
#define Debug_info(msg...)    do{if(Info_on)   {printf("INFO--     %s|%s|%d: ",__FILE__,__FUNCTION__,__LINE__);printf(msg);}}while(0)
#define Debug_strerror()	  printf("errno:%s\n",strerror(errno))
*/
#define Debug_error(...)   do{if(Error_on)  {printf("[E] %s|%d: ",__FUNCTION__,__LINE__);printf(__VA_ARGS__);fflush(stdout);}}while(0)
#define Debug_warning(...) do{if(Warning_on){printf("[W] %s|%d: ",__FUNCTION__,__LINE__);printf(__VA_ARGS__);fflush(stdout);}}while(0)
#define Debug_info(...)    do{if(Info_on)   {printf("[I] %s|%d: ",__FUNCTION__,__LINE__);printf(__VA_ARGS__);fflush(stdout);}}while(0)
#define Debug_strerror()	  printf("errno:%s\n",strerror(errno))
		
