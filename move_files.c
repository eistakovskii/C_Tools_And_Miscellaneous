#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void copy_files(char *src_path, char *dst_path) {
    char search_path[MAX_PATH];
    snprintf(search_path, MAX_PATH, "%s\\*", src_path);

    WIN32_FIND_DATA find_data;
    HANDLE find_handle = FindFirstFile(search_path, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE) {
        printf("Error opening directory: %s\n", src_path);
        return;
    }

    do {
        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0) {
            continue;
        }

        char src_file[MAX_PATH];
        snprintf(src_file, MAX_PATH, "%s\\%s", src_path, find_data.cFileName);

        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            copy_files(src_file, dst_path);
        } else {
            char dst_file[MAX_PATH];
            snprintf(dst_file, MAX_PATH, "%s\\%s", dst_path, find_data.cFileName);

            if (!CopyFile(src_file, dst_file, FALSE)) {
                printf("Error copying file: %s\n", src_file);
            }
        }
    } while (FindNextFile(find_handle, &find_data));

    FindClose(find_handle);
}

int main() {
    char src_path[MAX_PATH];
    printf("Enter the source directory path: ");
    fgets(src_path, MAX_PATH, stdin);
    src_path[strlen(src_path) - 1] = '\0';

    char dst_path[MAX_PATH];
    printf("Enter the destination directory path: ");
    fgets(dst_path, MAX_PATH, stdin);
    dst_path[strlen(dst_path) - 1] = '\0';

    CreateDirectory(dst_path, NULL);
    copy_files(src_path, dst_path);

    printf("Files copied successfully!\n");
    return 0;
}