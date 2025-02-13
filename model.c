#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int max_seq_length;
    int vocab_size;
    int rounded_vocab_size;
    int num_layers;
    int num_heads;
    int channels;

} GPTConfig;


// the parameters of the model
#define NUM_PARAMETER_TENSORS 16
typedef struct {
    float* wte; // (V, C)
    float* wpe; // (maxT, C)
    float* ln1w; // (L, C)
    float* ln1b; // (L, C)
    float* qkvw; // (L, 3*C, C)
    float* qkvb; // (L, 3*C)
    float* attprojw; // (L, C, C)
    float* attprojb; // (L, C)
    float* ln2w; // (L, C)
    float* ln2b; // (L, C)
    float* fcw; // (L, 4*C, C)
    float* fcb; // (L, 4*C)
    float* fcprojw; // (L, C, 4*C)
    float* fcprojb; // (L, C)
    float* lnfw; // (C)
    float* lnfb; // (C)
} ParameterTensors;



// Function to load the GPT-2 model in binary format

struct {
    unsigned char *data;
    long size;
    int num_layers;
    int num_heads;
    int hidden_size;
} GPT2Model;




void load_gpt2_model(const char *file_path, struct GPT2Model *model) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to hold the model
    unsigned char *model_data = (unsigned char *)malloc(file_size);
    if (model_data == NULL) {
        fprintf(stderr, "Error: Could not allocate memory\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Read the model data into memory
    size_t read_size = fread(model_data, 1, file_size, file);
    if (read_size != file_size) {
        fprintf(stderr, "Error: Could not read file %s\n", file_path);
        free(model_data);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Close the file
    fclose(file);

    // Use the model data (this is just a placeholder, actual usage will depend on your application)
    printf("GPT-2 model loaded successfully, size: %ld bytes\n", file_size);

    // Free the allocated memory
    free(model_data);
}

int main() {
    const char *model_path = "gpt2_124M.bin";
    GPT2Model model;
    load_gpt2_model(model_path, &model);

    // Use the model data (this is just a placeholder, actual usage will depend on your application)
    printf("GPT-2 model loaded successfully, size: %ld bytes\n", model.size);

    // Free the allocated memory
    free(model.data);


    return 0;
}