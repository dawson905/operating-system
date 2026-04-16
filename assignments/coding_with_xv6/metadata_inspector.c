#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

void inspect_file(const char* filepath) {
struct stat file_stat;

printf("Inspecting: %s\n", filepath);

if(stat(filepath, &file_stat) == -1) {
printf("Error: could not access file.\n");
return;
}

printf("Size: %ld bytes\n", (long)file_stat.st_size);

if(S_ISDIR(file_stat.st_mode)) {
printf("Type: directory\n");
} else if(S_ISREG(file_stat.st_mode)) {
printf("Type: regular file\n");
} else {
printf("Type: other\n");
}
}

int main() {
FILE *f = fopen("test.txt", "w");
if(f) {
fputs("Hello File System!", f);
fclose(f);
}

inspect_file("test.txt");
inspect_file(".");
inspect_file("does_not_exist.bin");

return 0;
}
