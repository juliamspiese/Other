#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover image\n");
        return 1;
    }

    //remember forensic image filename
    char *infile = argv[1];

    // open input file
    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //making 512 byte buffer
    const int b = 512;
    unsigned char buffer[b];

    //setting count for jpgs scanned
    int jpg_count = 0;
    //setting array for jpg names
    char jpg_name[50];

    //initializing FILE-type img as NULL
    FILE *img = NULL;

    //reads from input file & writes to output file up until end of input file
    while (!feof(raw_file))
    {
        //reads from input file into butter
        fread(buffer, b, 1, raw_file);

        //checking first four bytes for jpg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
        {
            if (jpg_count > 0)
            {
                //closes any previously opened file
                fclose(img);
            }
            //prints file name
            sprintf(jpg_name, "%03i.jpg", jpg_count);
            //increment count of jpgs scanned
            jpg_count++;
            //create new file
            img = fopen(jpg_name, "w");
            //writes from buffer into output jpg file
            fwrite(buffer, b, 1, img);
        }

        //writes into buffer if jpg file is already open
        else if(jpg_count > 0)
        {
            fwrite(buffer, b, 1, img);
        }
    }
    //closes output and input files
    fclose(img);
    fclose(raw_file);
}
