#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <list>
using namespace std;

#include "mp4_extractor.h"

#define DEBUG 1
#define DEFAULT_FILE_SIZE 20*1024*1024

H264_Extractor::H264_Extractor():
				fd(NULL),
				file_size(0),
				h264_data(NULL)
{

}

int H264_Extractor::get_to_list(const char *file) {
	fd = fopen(file, "r");
	if(fd == NULL) {
		printf("Error when opening file\n");
		return -1;
	}

	fseek(fd, 0, SEEK_END);
	file_size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	h264_data = (unsigned char *)malloc(file_size*sizeof(unsigned char));
	fread(h264_data, file_size, sizeof(unsigned char), fd);

	unsigned char *src = h264_data;
        for(int i=0; i<file_size; i++) {
            if( (src[i] == 0x0) && (src[i+1] == 0x0)) {
                if(src[i+2] == 0x01) {

                }else if((src[i+2] == 0x0) && (src[i+3] == 0x01)) {
                    nalu_list.push_back(i);
                    i+=3;
                }
            }
        }
        nalu_list.push_back(file_size);

#ifdef DEBUG
	int count = 0;
	for(it = nalu_list.begin(); it!=nalu_list.end(); count++, ++it) {
	    printf("NALU LIST -->  Count: %d   Value: %d\n", count, *it);
	}
#endif
        return nalu_list.size();
}

int H264_Extractor::get_sps_pps(char *_sps_pps, int &_sps_pps_len) {

	return 0;
}
