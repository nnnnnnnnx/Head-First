#include "NanStream.cpp"
#include<iostream>
unsigned short buff[20];

using namespace nans;
using namespace std;

int main() {

	buff[0] = 1;
	buff[1] = 2;
	buff[2] = 3;
	buff[3] = 1;
	buff[4] = 2;
	buff[5] = 3;
	std::cout << nans::checksum(buff, 3) << std::endl;
	std::cout << nans::checksum(buff + 3, 3) << std::endl;
	string buf;
	uint32_t x = 544;
	cout << x << endl;
	nans::write7BitEncoded(x, buf);
	int len;
	uint32_t value;
	const char* cstr = buf.c_str();
	nans::read7BitEncoded(cstr, len, value);
	cout << value << endl;

	std::string outbuf;
	BinaryStreamWriter writeStream(&outbuf);
	int32_t i1 = 2;
	int32_t i2 = 4;
	string ss = "abcde";
	const char* sss = "gafa";
	int64_t i3 = 60;
	int64_t i4 = 8;
	cout << i1 << endl << i2 << endl << ss << endl;
	printf("%s\n", sss);
	cout << i3 << endl;
	cout << i4 << endl;
	writeStream.WriteInt32(i1);
	writeStream << i2;
	writeStream << ss;
	writeStream.WriteCString(sss, strlen(sss));
	writeStream.WriteInt64(i3);
	writeStream.WriteInt64(i4);
	cout << "WRITESTREAM:<<<" << endl;
	cout << outbuf << " " << outbuf.size() << endl;
	cout << writeStream.GetData() << " " << writeStream.GetSize() << endl;
	printf("%sg\n", outbuf.c_str());
	BinaryStreamReader readStream(outbuf.c_str(), (size_t)outbuf.size());
	i1 = 0, i2 = 0, ss = "a", i3 = -1, i4 = 0;
	readStream.ReadInt32(i1);
	printf("%d\n", i1);
	readStream >> i2;
	printf("%d\n", i2);
	size_t ll;
	readStream >> (&ss);
	cout << ss << "" << ss.size() << endl;
	char ssss[10];
	ll = -1;
	bool ok = readStream.ReadCString(ssss, 1000, ll);
	cout << ok << endl;
	ssss[ll] = '\0';
	printf("%s %d\n", ssss, ll);
	readStream.ReadInt64(i3);
	cout << i3 << endl;
	readStream.ReadInt64(i4);
	cout << i4 << endl;

	return 0;
}
