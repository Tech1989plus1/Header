//
//  main.c
//  HW02
//
//  Created by Derrick Marshall on 6/29/17.
//  Copyright © 2017 Derrick Marshall. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFERSIZE 4096

size_t read_char;

int main(int argc, const char * argv[]) {
	
	if(argc != 2){
		printf("Usage: mh FILE\n");
		exit(1);
	}
	
	int fildes = open(argv[1], O_RDONLY);
	
	if(fildes == -1){
		int errsv = errno;
		
		if (errsv == ENOENT)
			printf("No Such File or Directory: %s\n", argv[1]);
		else
			perror("The following error occurred");
		
		exit(1);
	}
	
	char buf[BUFFERSIZE];
	read_char = read(fildes, buf, BUFFERSIZE);
	
	if (read_char == -1) {
		perror("The following error occurred");
		close(fildes);
		exit(1);
	}
	
	int count = 0, list = 0;
	
	while (count < read_char) {
		if(list == 10)
			break;
		else if(buf[count] == '\n')
			list++;
		printf("%c", buf[count]);
		count++;
	}
	
	close(fildes);
	return 0;
}
