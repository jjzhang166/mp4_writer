#include <list>
using namespace std;

class H264_Extractor {
	FILE *fd;
	int file_size;
	unsigned char *h264_data;
	list<int> nalu_list;
	list<int>::iterator it;
public:
	H264_Extractor();
	~H264_Extractor();

	int get_to_list(const char *path);
	int get_sps_pps(char *_sps_pps, int &_sps_pps_len);
};
