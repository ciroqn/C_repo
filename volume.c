// Modifies the volume of an audio file. In the terminal the syntax is './volume input_file.txt output_file.txt {volume_factor}'

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Store header form input in at address, &buffer
    uint8_t buffer[HEADER_SIZE];
    fread(&buffer, HEADER_SIZE, 1, input);
    fwrite(&buffer, HEADER_SIZE, 1, output);

    // Read samples from input file and write updated data to output file
    // Declare sample with type 'int16_t' i.e. 16-bit sample (2 bytes), which
    // is what each sample in the WAV file contains
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input) != 0)
    {
        // Multiply each sample by the factor given in terminal
        sample *= factor;
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
