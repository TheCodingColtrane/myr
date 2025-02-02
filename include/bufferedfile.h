#ifndef BUFFERED_FILE_HANDLER_H
#define BUFFERED_FILE_HANDLER_H

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <memory>
#include <algorithm>

class BufferedFileHandler {
public:
      BufferedFileHandler(const std::string& fname) 
        : file_name(fname), write_buffer() {
        write_buffer.reserve(BUFFER_SIZE);
    }
    ~BufferedFileHandler();

    // Delete copy constructor and assignment operator
    BufferedFileHandler(const BufferedFileHandler&) = delete;
    BufferedFileHandler& operator=(const BufferedFileHandler&) = delete;

    // Public interface
    void write(const std::string& data);
    void flush();
    std::string read();

    template<typename Processor>
    void processFileInChunks(Processor processor);

private:
    static const size_t BUFFER_SIZE = 8192; // 8KB buffer
    std::string file_name;
    std::vector<char> write_buffer;
};

#endif // BUFFERED_FILE_HA