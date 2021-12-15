#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_src.h"

typedef int BOOL;

#define TRUE 1
#define FALSE 0


int parseArg (int argc, char **argv, convInfo *pArg);

int main(int argc, char **argv)
{
    convInfo conv_info;
    int ret = 0;
    unsigned int frame_size = 0;
    unsigned int luma_size=0;
    unsigned int cb_size=0;
    unsigned int bpp = 1;
    FILE* fp_data;

    if ( conv_info.is_10b == 1 ) 
    {
        bpp = 2;
    }

    memset(&conv_info, 0x00, sizeof(convInfo));

    ret = parseArg(argc, argv, &conv_info);
 
    luma_size = conv_info.input_width * conv_info.input_height * bpp;
    cb_size = ((conv_info.input_width + 1)/2) * ((conv_info.input_height+1)/2) * bpp; 
    frame_size = luma_size + cb_size;

    if (luma_size == 0 || cb_size == 0)
    {
        return -1;
    }

    fp_data = fopen(conv_info.input_file, "rb");

    return 0;
}

int parseArg(int argc, char **argv, convInfo *pArg)
{
    int     i;
    char    *s;
    for (i=1; i<argc; i++) {
        s = argv[i];
        if (s[0] == '-') {
            switch (s[1]) {
            case 'i':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return 1;
                pArg->input_file = strdup(argv[i]);
                break;
            case 'o':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return -1;
                pArg->output_file = strdup(argv[i]);
                break;
            case 'w':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return -1;
                pArg->input_width = atoi(strdup(argv[i]));
                break;
            case 'h':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return -1;
                pArg->input_height = atoi(strdup(argv[i]));
                break;
            case 'b':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return -1;
                pArg->is_10b = atoi(strdup(argv[i]));
                break;
            case 'n':
                if (s[2] != 0)
                    return -1;
                i++;
                if (i == argc)
                    return -1;
                pArg->output_num = atoi(strdup(argv[i]));
                break;
            default:
                return -1;
            }
        } else
            return -1;
    }
    return 0;
}

