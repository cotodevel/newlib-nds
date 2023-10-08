#include "typedefsTGDS.h"
#include <unistd.h>

void abort(){
	exit(-10000);
	while(1==1){}	//no return function marked as no return
}