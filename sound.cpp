#include "sound.h"

Sound::Sound()
{
	m_position = -1;
	m_buffer = 0;
	m_size = 0;
}
	
uint8_t *
Sound::buffer() const
{
	return m_buffer;
}
	
int 
Sound::size() const
{
	return m_size;
}

void
Sound::setBuffer(uint8_t *buf)
{
	m_buffer = buf;
}

void
Sound::setSize(int size)
{
	m_size = size;
}
