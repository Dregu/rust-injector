#pragma once

#include <cstdint>
#include <cstdlib>
#include <string>
#include <string_view>

#include <Windows.h>

using AllocFun = decltype(malloc);

struct FileInfo
{
    void* Data{nullptr};
    int _member_1{0};
    int DataSize{0};
    int AllocationSize{0};
    int _member_4{0};
};
using LoadFileCallback = FileInfo*(const char* file_path, AllocFun alloc_fun);
using ReadFromFileOrig = void(const char* file, void** out_data, size_t* out_data_size);
using ReadFromFileCallback = void(const char* file, void** out_data, size_t* out_data_size, AllocFun alloc_fun, ReadFromFileOrig* orig);
using WriteToFileOrig = void(const char* backup_file, const char* file, void* data, size_t data_size);
using WriteToFileCallback = void(const char* backup_file, const char* file, void* data, size_t data_size, WriteToFileOrig* orig);
using GetImageFilePathCallback = std::string(std::string root_path, std::string relative_path);
using MakeSavePathCallback = std::string (*)(std::string_view script_path, std::string_view script_name);

FileInfo* load_file_as_dds_if_image(const char* file_path, AllocFun alloc_fun);

void register_on_load_file(LoadFileCallback on_load_file);
void register_on_read_from_file(ReadFromFileCallback on_read_from_file);
void register_on_write_to_file(WriteToFileCallback on_write_to_file);
void register_get_image_file_path(GetImageFilePathCallback get_image_file_path);
void register_make_save_path(MakeSavePathCallback make_save_path_callback);

std::string get_image_file_path(std::string root_path, std::string relative_path);

bool create_d3d11_texture_from_file(const char* filename, struct ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
