

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <algorithm>
#include "../include/bufferedfile.h"


template<typename Processor>
void BufferedFileHandler::processFileInChunks(Processor processor) {
    std::ifstream file(file_name, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Cannot open file for processing: " + file_name);
        }

        std::vector<char> buffer(BUFFER_SIZE);
        while (file) {
            file.read(buffer.data(), BUFFER_SIZE);
            std::streamsize bytes_read = file.gcount();
            
            if (bytes_read > 0) {
                processor(buffer.data(), bytes_read);
            }
        }
}

BufferedFileHandler::~BufferedFileHandler()
{
    flush();
}

void BufferedFileHandler::write(const std::string &data)
{
    if (write_buffer.size() + data.size() >= BUFFER_SIZE)
    {
        flush();
    }
    write_buffer.insert(write_buffer.end(), data.begin(), data.end());
}

void BufferedFileHandler::flush()
{
    if (write_buffer.empty())
        return;

    std::ofstream file(file_name, std::ios::app | std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("Cannot open file for writing: " + file_name);
    }

    file.write(write_buffer.data(), write_buffer.size());
    write_buffer.clear();
    file.close();
}

std::string BufferedFileHandler::read()
{
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if (!file)
    {
        throw std::runtime_error("Cannot open file for reading: " + file_name);
    }

    auto file_size = file.tellg();
    file.seekg(0);

    std::string buffer;
    buffer.resize(file_size);

    // Read in chunks
    const size_t chunk_size = BUFFER_SIZE;
    size_t bytes_read = 0;

    while (bytes_read < file_size)
    {
        size_t remaining = file_size - bytes_read;
        size_t current_chunk_size = std::min(chunk_size, remaining);

        file.read(&buffer[bytes_read], current_chunk_size);
        bytes_read += current_chunk_size;
    }

    return buffer;
}
