#include <stdio.h>
#include <iostream>
extern "C" {
#include <mp4v2/mp4v2.h>
}
#include "mp4_writer.h"
#include "mp4_extractor.h"
using namespace std;

#define FILE_PATH "/home/liwei/Desktop/720p_1930kbs_30帧.264"
#define MP4_FILE_PATH "/home/liwei/Desktop/test.mp4"
#define MP4_FPS 30

int main() { H264_Extractor *extractor = new H264_Extractor();
	extractor->get_to_list(FILE_PATH);
	extractor->get_sps_pps();

#if 0
	MP4FileHandle mp4_file = MP4CreateEx("/home/liwei/Desktop/test.mp4", 0, 1, 1, 0, 0, 0, 0);
	if(mp4_file == MP4_INVALID_FILE_HANDLE) {
		printf("Create mp4 file failed\n");
		return -1;
	}

	MP4SetTimeScale(mp4_file, 90000);
	MP4TrackId video = MP4AddH264VideoTrack(mp4_file, 90000, 90000/25, 1280, 720, extractor->sps[1], extractor->sps[2], extractor->sps[3], 3);
	if(video == MP4_INVALID_TRACK_ID) {
		printf("Create video track failed\n");
		return -1;
	}
	MP4AddH264SequenceParameterSet(mp4_file, video, extractor->sps, 26);
	MP4AddH264PictureParameterSet(mp4_file, video, extractor->pps, 5);
#endif

	Mp4_Writer *writer = new Mp4_Writer(1280, 720);
	writer->SetMp4FileName(MP4_FILE_PATH);
	writer->SetMp4Fps(MP4_FPS);
	writer->DoStartRecord();

	unsigned char *payload_data;
	unsigned int payload_size;
	unsigned int time_stamp;
	while( (payload_data = extractor->get_frame(payload_size, time_stamp)) != NULL ) {
		writer->WriteEncodedVideoFrame(payload_data, payload_size, time_stamp);
		extractor->release_frame(&payload_data);
	}
	writer->DoStopRecord();
	return 0;
}
