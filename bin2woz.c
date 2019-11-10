/************************************************************
 * Binary to Wozmon                                         *
 ************************************************************
 * @file bin2woz.c
 * @author Matthias Arndt <marndt@asmsoftware.de>
 * @copyright ASM Software http://www.asmsoftware.de/
 ************************************************************
 * @brief   dump binary file in Wozmon monitor format
 * @details Data is displayed <address>: <data1> ... <dataN>
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

typedef struct
{
    void * data;
    uint16_t address;
    uint16_t nr_of_bytes;
} BinFile;


static void dump_data_record(uint16_t address, uint8_t * datasrc, uint8_t nr_bytes)
{
    if(nr_bytes > 0)
    {
        printf("%04X:", address);

        while(nr_bytes-- > 0)
        {
            printf(" %02X", *datasrc++);
        }
        putchar(13);
        putchar(10);
    }

    return;
}

static void dump_file(BinFile * self)
{
    uint8_t nr_of_bytes_in_record;
    uint8_t * data = (uint8_t *)self->data;
    uint16_t byte_offset = 0;

    while(self->nr_of_bytes > 0)
    {
        nr_of_bytes_in_record = min(self->nr_of_bytes, 8);
        dump_data_record(self->address, &data[byte_offset], nr_of_bytes_in_record);
        self->address += nr_of_bytes_in_record;
        byte_offset += nr_of_bytes_in_record;

        self->nr_of_bytes -= nr_of_bytes_in_record;
    }
}

int main(int argc, char *argv[])
{
    int retval = -1;
    FILE *fp;
    BinFile binfile;
    unsigned int tmp_addr;

    if(argc != 3)
    {
        printf("Usage: %s <start address> <input file>\n", argv[0]);
    }
    else
    {
        sscanf(argv[1], "%4x", &tmp_addr);

        if(tmp_addr > 0xFFFF)
        {
            printf("Error: bogus loading address!\n");

            return -2;
        }

        binfile.address = (uint16_t)tmp_addr;

        fp = fopen(argv[2], "rb");

        if(fp != NULL)
        {
            fseek(fp, 0L, SEEK_END);
            binfile.nr_of_bytes = min(0x10000, ftell(fp));
            fseek(fp, 0L, SEEK_SET);

            binfile.data = malloc(binfile.nr_of_bytes);

            if(binfile.data == NULL)
            {
                printf("ERROR: malloc failed!\n");
                retval = -4;
            }
            else
            {
                fread(binfile.data, binfile.nr_of_bytes, 1, fp);
                retval = 0;
                dump_file(&binfile);
            }


            fclose(fp);
        }
        else
        {
            printf("ERROR: Could not open input file!\n");
            retval = -3;
        }

    }

    return retval;
}
