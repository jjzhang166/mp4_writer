#include <stdio.h>
#include <iostream>

#include <mp4.h>
#include "mp4_extractor.h"
using namespace std;

#define FILE_PATH "/home/liwei/Desktop/720p_1930kbs_30帧.264"

int main() {
	H264_Extractor *extractor = new H264_Extractor();
	int ret = extractor->get_to_list(FILE_PATH);
	return 0;
}
