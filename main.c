#include "bmp.h"
#include "crayons.h"
//#include "parrots.h"
#include "padd.h"
#include "img_processing.h"

int main()
{
        int imgdataoffset = 14 + 40;     // file header size + bitmap header size
 
        int imgdatasize= 3*xs*ys;
   
        int filesize = imgdataoffset + imgdatasize;
         
        HTLM_bmp_H HTLM_bmp_h;
  
        HTLM_bmp_h.bmfh.bfType = 0x4d42;	//"BM"
        HTLM_bmp_h.bmfh.bfSize = filesize;
        HTLM_bmp_h.bmfh.bfReserved1 = 0;
        HTLM_bmp_h.bmfh.bfReserved2 = 0;
        HTLM_bmp_h.bmfh.bfOffBits = imgdataoffset;

        HTLM_bmp_h.bmih.biSize = 40;
        HTLM_bmp_h.bmih.biWidth = xs;
        HTLM_bmp_h.bmih.biHeight = ys;
        HTLM_bmp_h.bmih.biPlanes = 0;
        HTLM_bmp_h.bmih.biBitCount = 24;
        HTLM_bmp_h.bmih.biCompression = 0;
        HTLM_bmp_h.bmih.biSizeImage = 0;  //imgdatasize;
        HTLM_bmp_h.bmih.biXPelsPerMeter = 0;
        HTLM_bmp_h.bmih.biYPelsPerMeter = 0;
        HTLM_bmp_h.bmih.biClrUsed = 0; //1 << 24;	//ColorsUsed = 1 << BitsPerPixel;
        HTLM_bmp_h.bmih.biClrImportant = 0;
  
	
	char fname[]= "crayons.bmp";
	
	FILE *fp;

	if((fp=fopen(fname,"wb"))==NULL)	{printf("error , can not open image\n"); exit(1);}
	
	
	fwrite(&HTLM_bmp_h.bmfh.bfType,sizeof(WORD),1,fp);
	fwrite(&HTLM_bmp_h.bmfh.bfSize,sizeof(DWORD),1,fp);
	fwrite(&HTLM_bmp_h.bmfh.bfReserved1,sizeof(WORD),1,fp);
	fwrite(&HTLM_bmp_h.bmfh.bfReserved2,sizeof(WORD),1,fp);
	fwrite(&HTLM_bmp_h.bmfh.bfOffBits,sizeof(DWORD),1,fp);
	
	fwrite(&HTLM_bmp_h.bmih.biSize,sizeof(DWORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biWidth,sizeof(LONG),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biHeight,sizeof(LONG),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biPlanes,sizeof(WORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biBitCount,sizeof(WORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biCompression,sizeof(DWORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biSizeImage,sizeof(DWORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biXPelsPerMeter,sizeof(LONG),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biYPelsPerMeter,sizeof(LONG),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biClrUsed,sizeof(DWORD),1,fp);
	fwrite(&HTLM_bmp_h.bmih.biClrImportant,sizeof(DWORD),1,fp);
	
	fseek(fp,HTLM_bmp_h.bmfh.bfOffBits,SEEK_SET);
			
	BYTE *b;	
			
	b = padd(a,ys,xs,4,4);	//Padding frame with white cells (value 255)	
	
	BYTE *Buff;
			
	//memset(Buff,0,3*xs*ys); //filling the empty Buff with zeros
	
	Buff = Bayer2RGB(b,ys,xs,4,4); //	cols =xs	 rows=ys
	
	//inverse(Buff,ys,xs);
	//extra_solarize(Buff,ys,xs);
	//RGB2YCbCr(Buff,ys,xs);
	//YCbCr2RGB(Buff,xs,ys);
	//Color_Saturation(Buff,0.5,ys,xs);
	//WhiteBalance(Buff,ys,xs);
	//ColorCorrection(Buff,ys,xs);
	//Sepia(Buff,ys,xs);
      
    //binarize(Buff,ys,xs);
    //EdgeDetection(Buff, xs, ys);
        
    updown2(Buff,xs,ys);
	
  	fwrite(Buff,sizeof(BYTE),3*xs*ys,fp); 
        fseek(fp,0,SEEK_CUR);	
	  	
  			
	fclose(fp);
	
	
	free(b);
	free(Buff);
	
	return 0;
	
}
