#include "wavedata.h"

const string WaveData::id = "data";

WaveData::WaveData()
{
	m_bytes = "";
}

Data *
WaveData::encode() const
{
	cout << "ENTREI ENCODE" << endl;
	
	const int ID_LENGTH = 4;
	const int SIZE_LENGTH = 4;
	const int HEADER_LENGTH = ID_LENGTH + SIZE_LENGTH;
	
	uint32_t encoded_size = size(); 
	
	cout << encoded_size << endl;
	
	uint32_t total_size = encoded_size + HEADER_LENGTH;
	
	uint8_t *bytes = new uint8_t[total_size];
	
	if (bytes == 0)
		return 0;
	
	uint32_t offset = 0;
	
	memcpy(bytes + offset, WaveData::id.c_str(), ID_LENGTH);
	offset += ID_LENGTH;
	
	memcpy(bytes + offset, &encoded_size, SIZE_LENGTH);
	offset += SIZE_LENGTH;
	
	memcpy(bytes + offset, m_bytes.c_str(), encoded_size);
	offset += encoded_size; 
	
	Data *data = new Data();
	data->set(bytes, total_size);
	
	return data;
}

uint32_t 
WaveData::decode(const Data& data, uint32_t offset)
{
	cout << "ENTREI DENCODE" << endl;
	
	const uint8_t *iterator = data.bytes(offset);
	uint32_t decoded = 0;
	
	// Read id
	char buffer[5];
	memcpy(buffer, iterator + decoded, 4);
	buffer[4] = 0;
	
	if (memcmp(buffer, WaveData::id.c_str(), 4))
		return 0;
	
	decoded += 4;
	
	uint32_t size;
	memcpy(&size, iterator + decoded, 4);
	decoded += 4;
	
	char *temp_char = new char[size + 1]; 
	temp_char[size] = 0;
	
	memcpy(temp_char, iterator + decoded, size);
	decoded += size;
	
	string temp_string(temp_char);
	
	m_bytes = temp_string;
	
	delete [] temp_char;
	
	return decoded;
}

uint32_t 
WaveData::size() const
{
	return m_bytes.size();
}


void 
WaveData::print(ostream& os) const
{
	os << "\tID: " << WaveData::id << endl;
	os << "\tsize: " << size() << endl;
	os << "\t\tdata: [" << m_bytes << "]" << endl;
}
