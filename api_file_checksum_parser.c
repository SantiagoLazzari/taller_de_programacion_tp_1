#include "api_file_checksum_parser.h"

int file_checksum_parser_init(file_checksum_parser_t *self, char *filename,int block_size) {
  self->filename = filename;
  self->block_size = block_size;

  return 0;
}

int file_checksum_parser_checksum_at_index(file_checksum_parser_t *self, checksum_t *checksum, char *buffer, unsigned long index) {
  FILE *fp = fopen(self->filename,"r");

  fseek(fp, index, SEEK_SET);

  char character;

  for (int index = 0 ; index < self->block_size ; index++) {
    character = fgetc(fp);
    printf("%c\n", character);
    if(feof(fp))
      return 1;
    buffer[index] = character;
  }

  checksum_init(checksum, buffer, self->block_size);

  fclose(fp);
  return 0;
}