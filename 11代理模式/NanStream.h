#ifndef __NAN_STREAM_H__
#define __NAN_STREAM_H__

#include<stdlib.h>
#include<sys/types.h>
#include<string>
#include<sstream>
#include<stdint.h>

namespace nans
{
	enum
	{
		TEXT_PACKLEN_LEN = 4,
		TEXT_PACKAGE_MAXLEN = 0xffff,
		BINARY_PACKLEN_LEN = 2,
		BINARY_PACKAGE_MAXLEN = 0xffff,

		TEXT_PACKLEN_LEN_2 = 6,
		TEXT_PACKAGE_MAXLEN_2 = 0xffffff,

		BINARY_PACKLEN_LEN_2 = 4,               //4字节头长度
		BINARY_PACKAGE_MAXLEN_2 = 0x10000000,   //包最大长度是256M,足够了

		CHECKSUM_LEN = 2,
	};

	//计算校验和 
	unsigned short checksum(const unsigned short* buffer, int size);
	//将一个4字节的整形数值压缩成1~5个字节
	void write7BitEncoded(uint32_t value, std::string& buf);
	//讲一个8字节的整形数值编码成1~10个字节
	void write7BitEncoded(uint64_t value, std::string& buf);
	//将一个1~5个字节的字符数组值还原成4字节的整型值
	void read7BitEncoded(const char* buf, uint32_t len, uint32_t& value);
	//将一个1~10个字节的值还原成4字节的整型值
	void read7BitEncoded(const char* buf, uint32_t len, uint64_t& value);

	class BinaryStreamReader final
	{
	public:
		BinaryStreamReader(const char* ptr, size_t len);
		~BinaryStreamReader() = default;

		virtual const char* GetData() const;
		virtual size_t GetSize() const;
		bool IsEmpty() const;

		bool ReadString(std::string* str, size_t maxlen, size_t& outlen);
		BinaryStreamReader& operator>>(std::string* str);

		bool ReadCString(char* str, size_t strlen, size_t& len);
		BinaryStreamReader& operator>>(char* str);

		bool ReadCCString(const char** str, size_t maxlen, size_t& outlen);
		BinaryStreamReader& operator>>(const char** str);

		bool ReadInt32(int32_t& i);
		BinaryStreamReader& operator>>(int32_t& i);

		bool ReadInt64(int64_t& i);
		BinaryStreamReader& operator>>(int64_t& i);

		bool ReadShort(short& i);
		BinaryStreamReader& operator>>(short& i);

		bool ReadChar(char& c);
		BinaryStreamReader& operator>>(char& c);

		bool ReadDouble(double& d);
		BinaryStreamReader& operator>>(double& d);

		size_t ReadAll(char* szBuffer, size_t iLen) const;
		bool IsEnd() const;
		const char* GetCurrent() const { return cur; }

	public:
		bool ReadLength(size_t& len);
		bool ReadLengthWithoutOffset(size_t& headlen, size_t& outlen);

	private:
		BinaryStreamReader(const BinaryStreamReader&) = delete;
		BinaryStreamReader& operator=(const BinaryStreamReader&) = delete;

	private:
		const char* const ptr;
		const size_t      len;
		const char* cur;
	};

	class BinaryStreamWriter final
	{
	public:
		BinaryStreamWriter(std::string* data);
		~BinaryStreamWriter() = default;

		virtual const char* GetData() const;
		virtual size_t GetSize() const;

		bool WriteCString(const char* str, size_t len);
		BinaryStreamWriter& operator<<(const char* str);

		bool WriteString(const std::string& str);
		BinaryStreamWriter& operator<<(const std::string& str);

		bool WriteDouble(double value, bool isNULL = false);
		BinaryStreamWriter& operator<<(double value);

		bool WriteInt64(int64_t value, bool isNULL = false);
		BinaryStreamWriter& operator<<(int64_t value);

		bool WriteInt32(int32_t i, bool isNULL = false);
		BinaryStreamWriter& operator<<(int32_t i);

		bool WriteShort(short i, bool isNULL = false);
		BinaryStreamWriter& operator<<(short i);

		bool WriteChar(char c, bool isNULL = false);
		BinaryStreamWriter& operator<<(char c);

		size_t GetCurrentPos() const { return m_data->length(); }
		void Flush();
		void Clear();

	private:
		BinaryStreamWriter(const BinaryStreamWriter&) = delete;
		BinaryStreamWriter& operator=(const BinaryStreamWriter&) = delete;

	private:
		std::string* m_data;
	};
}




#endif
