typedef int BOOL;

typedef struct {
    char*   input_file;
    char*   output_file;
    int     input_width;
    int     input_height;
    BOOL    is_10b;
    int     output_num;      
} convInfo;