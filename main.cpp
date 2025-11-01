#include <string.h>
#include "Goban.hpp"
#include "NetworkGoban.hpp"

int main(int argc, const char *argv[])
{
	if(argc < 2){
		fprintf(stderr,"Usage:%s <local|network>\n",argv[0]);
		return -1;
	}

	if(strcmp(argv[1],"local") == 0){
		Goban goban("tiechui","cuihua");
		goban.run();
	}else if(strcmp(argv[1],"network") == 0){
		NetworkGoban networkGoban("tiechui","cuihua");
		networkGoban.run();
	}else{
		fprintf(stderr,"Unknown mode\n");
	}

	return 0;
}
