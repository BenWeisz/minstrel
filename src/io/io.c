#include "io/io.h"

unsigned char* IO_read_internal(const char* path, unsigned int* size, const unsigned int padding)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		printf("ERROR: Failed to open file: %s\n", path);
		*size = 0;
		return NULL;
	}

	// Jump to the end of the file and read the file size
	int r = fseek(file, 0, SEEK_END);
	if (r == -1)
	{
		printf("ERROR: Failed to seek to the end of the file\n");
		fclose(file);
		*size = 0;
		return NULL;
	}

	long file_size = ftell(file);
	if (file_size == 0)
	{
		// This file is empty, not necessarily an error
		fclose(file);
		*size = 0;
		return NULL;
	}

	// Jump back to the start of the file to read the file data
	r = fseek(file, 0, SEEK_SET);
	if (r == -1)
	{
		printf("ERROR: Failed to seek to the start of the file\n");
		fclose(file);
		*size = 0;
		return NULL;
	}

	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * (file_size + padding));
	if (data == NULL)
	{
		printf("ERROR: Failed to allocate space for data\n");
		fclose(file);
		*size = 0;
		return NULL;
	}

	size_t bytes_read = fread(data, sizeof(unsigned char), file_size, file);
	if (bytes_read != file_size)
	{
		printf("ERROR: Failed to read all of the file contents\n");
		fclose(file);
		*size = 0;
		free(data);
		return NULL;
	}

	*size = bytes_read;

	return data;
}

unsigned char* IO_read_uchar(const char* path, unsigned int* size)
{
	return IO_read_internal(path, size, 0);
}

char* IO_read_char(const char* path)
{
	unsigned int size;
	char* data = IO_read_char_sized(path, &size);
	return data;
}

char* IO_read_char_sized(const char* path, unsigned int* size)
{
	char* data = (char*)IO_read_internal(path, size, 1);
	if (data != NULL)
		data[*size] = '\0';
	return data;
}
