#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp_y, *fp_cb, *fp_cr, *fp_out;
    char *fileNm, *fileNm_y, *fileNm_u, *fileNm_v, *p_w, *p_h, *sfn, *pfn, *bpp;
    char read_data[16384];
    int start_frame_num, pic_width, pic_height;
    int pic_size_y, pic_size_c;
    int pos_y, pos_x;
    int processing_num;
    int frame_num;
    int seek_size;
    int bit_depth;

    printf("Frame Cutter. 10bit Support version.\n");
    printf("yuv420_to_yuv420 in_file out_file pic_width pic_height start_frame processing_frame_num bit_depth(8,16)\n");
    fileNm = argv[1];
    fileNm_y = argv[2];
    p_w = argv[3];
    p_h = argv[4];
    sfn = argv[5];
    pfn = argv[6];
    bpp = argv[7];

    start_frame_num = atoi(sfn);
    processing_num = atoi(pfn);
    pic_width = atoi(p_w);
    pic_height = atoi(p_h);
    bit_depth = atoi(bpp);

    if (bit_depth == 16) {
        pic_width = pic_width * 2;
    }

    pic_size_y = pic_width * pic_height;
    pic_size_c = (pic_width/2) * (pic_height/2);

    printf("Pic Size X : Y = %d : %d\n",pic_width, pic_height);
    printf("Pic Size : %d\n",pic_size_y);

    if (fileNm == NULL)
    {
        fprintf(stderr, "read_PPM call error\n");
        return 0;
    }

    fp_y = fopen(fileNm, "rb");
    fp_cb = fopen(fileNm, "rb");
    fp_cr = fopen(fileNm, "rb");
    fp_out = fopen(fileNm_y, "wb");

    /// Start Frame jump
    for (frame_num=0;frame_num<processing_num;frame_num++) {
        seek_size = (pic_size_y + (pic_size_c * 2)) * (start_frame_num + frame_num);
        fseek(fp_y, seek_size, SEEK_SET);
        seek_size = seek_size + pic_size_y;
        fseek(fp_cb, seek_size, SEEK_SET);
        seek_size = seek_size + pic_size_c;
        fseek(fp_cr, seek_size, SEEK_SET);

        /// Y
        for (pos_y=0;pos_y<pic_height;pos_y++) {
            fread(read_data,sizeof(char),pic_width, fp_y);
            fwrite(read_data,sizeof(char),pic_width, fp_out);
        }
        /// Cb, Cr
        for (pos_y=0;pos_y<pic_height/2;pos_y++) {
            for (pos_x=0;pos_x<pic_width/2;pos_x++) {
                fread(read_data,sizeof(char),1, fp_cb);
                fwrite(read_data,sizeof(char), 1, fp_out);
                fread(read_data,sizeof(char),1, fp_cr);
                fwrite(read_data,sizeof(char), 1, fp_out);
            }
        }

    }
    fclose(fp_y);
    fclose(fp_cb);
    fclose(fp_cr);
    fclose(fp_out);
}
