#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	int i, j, flag = 0;
	char option;
	int arr[800][800];
	
	if (argc < 2)
		exit(-1);

	option = getopt(argc, argv, "12");

    while (option != -1) {
        switch (option) {
            case '1':
                flag = 0;
                break;
            case '2':
                flag = 1;
                break;
            default:
                fprintf(stderr, "Error in key usage\n");
                exit (-1);
        }
        option = getopt(argc, argv, "12");
    }

    for (i = 0; i < 800; i++)
    	for (j = 0; j < 800; j++) {
    		if (flag)
    			arr[j][i] = rand();
    		else
    			arr[i][j] = rand();
    	}


	return 0;
}