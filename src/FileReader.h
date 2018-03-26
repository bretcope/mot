#ifndef GOT_FILE_H
#define GOT_FILE_H


#include <cstdint>
#include "FileContent.h"

const uint32_t MAX_FILENAME_SIZE = 600;     // Windows limit is 260 UTF-16 characters. This more than covers that limit.

/**
 * Attempts to load a file by name.
 * @param filename The name of the file. A copy of this string is made and owned by the returned FileContent.
 * @param maxSize The maximum size of the file to load (in bytes).
 * @param errStream The file stream where to print error messages (e.g. stderr).
 * @param [out] out_content The loaded content, if successful.
 * @return True if the file was loaded successfully.
 */
bool LoadFile(const char* filename, uint32_t maxSize, FILE* errStream, FileContent** out_content);


#endif //GOT_FILE_H
