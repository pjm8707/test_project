#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "test_src.h"

typedef int BOOL;

#define TRUE 1
#define FALSE 0

typedef struct
{
    const char *name;
    int has_arg;
    int *flag;
    int val;
    const char *help;
} optionExt;

void Help(optionExt *opt, const char *prog_name);
int parseArg (int argc, char **argv, convInfo *pArg);
void swap_nv(void* data, int y_size, int nv21);

int main(int argc, char **argv)
{
    convInfo conv_info;
    int ret = 0, idx = 0;
    unsigned int frame_size = 0, luma_size=0, cb_size=0, chroma_size = 0, bpp = 1;
    FILE* fp_read, *fp_write;
    char* work_buf;
    size_t f_read_size = 0;

    memset(&conv_info, 0x00, sizeof(convInfo));

    ret = parseArg(argc, argv, &conv_info);

    assert(ret == 0);

    if ( conv_info.is_10b == 1 ) 
    {
        bpp = 2;
    }
 
    luma_size = conv_info.input_width * conv_info.input_height * bpp;
    cb_size = ((conv_info.input_width + 1)/2) * ((conv_info.input_height+1)/2) * bpp;
    chroma_size = cb_size * 2;
    frame_size = luma_size + chroma_size;

    if (luma_size == 0 || cb_size == 0)
    {
        return -1;
    }

    printf("luma size : %d cb_size : %d chroma_size : %d \n", luma_size, cb_size, chroma_size);

    work_buf = (char*)malloc(luma_size+1);

    fp_read = fopen(conv_info.input_file, "rb");
    fp_write = fopen(conv_info.output_file, "wb");

    assert(fp_read != NULL);
    assert(fp_write != NULL);
        
    for (idx = 0; idx < conv_info.output_num; idx++)
    {
        f_read_size = fread(work_buf, 1, luma_size, fp_read);
        assert(f_read_size == luma_size);
        fwrite(work_buf, 1, luma_size, fp_write);

        f_read_size = fread(work_buf, 1, chroma_size, fp_read);
        assert(f_read_size == chroma_size);
        swap_nv(work_buf, cb_size, bpp);
        fwrite(work_buf, 1, chroma_size, fp_write);
    }

    free(work_buf);
    fclose(fp_read);
    fclose(fp_write);

    printf("finished \n");

    return ret;
}

void Help(optionExt *opt, const char *prog_name)
{
    //int i;

    printf("------------------------------------------------------------------------------\n");
    printf("%s \n", prog_name);
    printf("\tAll rights reserved by Chips&Media(C)\n");
    printf("------------------------------------------------------------------------------\n");
    printf("-i                          input file path\n");
    printf("-o                          output file path\n");
    printf("-n                          number of output \n");
    printf("-w                          source width \n");
    printf("-h                          source height \n");
    printf("-b                          bitdepth, 0 : 8b , 1 : 10b \n");
    /* 
    for (i = 0;i < MAX_GETOPT_OPTIONS;i++) {
        if (opt[i].name == NULL)
            break;
        VLOG(INFO, "%s", opt[i].help);
    }
    */
}

int parseArg(int argc, char **argv, convInfo *pArg)
{
    int     i;
    char    *s;

    for (i=1; i<argc; i++) {
        s = argv[i];
        if (s[0] == '-') 
        {
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
        } 
        else 
        {
            return -1;
        }
    }
    if (argc == 1 ) 
    {
        Help(NULL, argv[0]);
    }
    return 0;
}

// only for yuv 420
void swap_nv(void* buf, int cb_size, int bpp)
{
    int idx = 0;
    char* cb_st = buf;
    char* cr_st = (char*)(cb_st + cb_size);
    char* temp_buf = NULL, *pos;
    short* pos_two;
    short* cb_st_two = (short*)cb_st;
    short* cr_st_two = (short*)cr_st;

    assert(buf != NULL);

    temp_buf = (char*)malloc(cb_size * 2);

    assert(temp_buf != NULL);
    
    pos = temp_buf;
    pos_two = (short*)temp_buf;

    if (bpp == 1) 
    {
        for (idx = 0; idx < cb_size; idx++) 
        {
            *pos++=*cb_st++;
            *pos++=*cr_st++;
        }
    } 
    else if (bpp == 2) 
    {
        for (idx = 0; idx < (cb_size / bpp); idx++) 
        {
            *pos_two++=*cb_st_two++;
            *pos_two++=*cr_st_two++;
        }
    } 
    else
    {
        assert(1 == 0);
    }
    
    memcpy(buf, temp_buf, cb_size * 2);
    free(temp_buf);
}


