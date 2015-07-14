#include <vector>
using namespace std;

class H264_Extractor {
	FILE *fd;
	int file_size;
	int frame_index;
	unsigned char *h264_data;
	std::vector<int> nalu_list;
	std::vector<int>::iterator it;
public:
	H264_Extractor();
	~H264_Extractor();

	int get_to_list(const char *path);
	int get_sps_pps();
	unsigned char *get_frame(int &payload_size, unsigned int &time_stamp);
	void release_frame(unsigned char **buf);
public:
       	unsigned char *sps, *pps, *sps_pps;
};
