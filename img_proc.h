#ifndef img_processing_H
#define img_processing_H

#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "bmp.h"

BYTE *Bayer2RGB(BYTE *b,int rows,int cols,int prows,int pcols)
{
	int x1=cols+pcols;
	int y1=rows+prows;
	int i,j,k,l;
	  	
	BYTE *Buffer;  	
	Buffer = (BYTE *) malloc(3*cols*rows*sizeof(BYTE));
	if(Buffer==NULL) exit(1); 
			  	  
	k = 0;
		
	// Demosaicing - Bayer to RGB -- Adaptive method
	
  for (i=y1-3;i>=2; i--) {
 	
 	 	
    // padding bytes should remain 0's, shouldn't have to re-clear them.
    for (j=2;j<=x1-3;j++) {
    	                
    	
		if( i & 1 ) { // Odd line BGBGBG .... BG
        	if( j & 1 ) {// R         
          		*(Buffer+(k++)) = (*(b + j + x1*i ));  // R
          		
				if(abs(*(b + j + x1*(i-2))-*(b + j + x1*(i+2))) < abs(*(b + (j+2) + x1*i)-*(b + (j-2) + x1*i)))
				{
					*(Buffer+(k++)) = (*(b + j + x1*(i-1)) + *(b + j + x1*(i+1)) )>>1;  // G
				}else if (abs(*(b + j + x1*(i-2))-*(b + j + x1*(i+2))) > abs(*(b + (j+2) + x1*i)-*(b + (j-2) + x1*i)))
				{
					*(Buffer+(k++)) = (*(b + (j-1) + x1*i) + *(b + (j+1) + x1*i) )>>1;  // G
				}else
				{
					*(Buffer+(k++)) = ( *(b + j + x1*(i-1)) + *(b + j + x1*(i+1)) + *(b + (j-1) + x1*i) + *(b + (j+1) + x1*i) )>>2;  // G
				}
          		
		  		
		  		*(Buffer+(k++))  = ( *(b + (j-1) + x1*(i-1)) + *(b + (j+1) + x1*(i-1)) + *(b + (j-1) + x1*(i+1))+ *(b + (j+1) + x1*(i+1)) )>>2; // B
			} else { // G
 
          		*(Buffer+(k++)) = (*(b + (j-1) + i*x1) + *(b + j+1 + i*x1) )>>1;  // R
          		*(Buffer+(k++)) = (*(b + j + i*x1));  // G
          		*(Buffer+(k++)) = (*(b + j + (i-1)*x1) + *(b + j + (i+1)*x1) )>>1;  // B
		  	
        	}
        
		} else { // Even line       GRGRGRGR....GR

        	if( j & 1 ) {// G 
			         
          		*(Buffer+(k++)) = (*(b + j + (i-1)*x1) + *(b + j + (i+1)*x1) )>>1;  // R
          		*(Buffer+(k++)) = (*(b + j + i*x1));  // G
          		*(Buffer+(k++)) = (*(b + (j-1) + i*x1) + *(b + j+1 + i*x1) )>>1;  // B
          
        	} else { // B
 		        *(Buffer+(k++)) = (*(b + (j-1) + x1*(i-1)) + *(b + (j+1) + x1*(i-1)) + *(b + (j-1) + x1*(i+1))+ *(b + (j+1) + x1*(i+1)) )>>2; // R
 		        
          		if(abs(*(b + j + x1*(i-2))-*(b + j + x1*(i+2))) < abs(*(b + (j+2) + x1*i)-*(b + (j-2) + x1*i)))
				{
					*(Buffer+(k++)) = (*(b + j + x1*(i-1)) + *(b + j + x1*(i+1)) )>>1;  // G
				}else if (abs(*(b + j + x1*(i-2))-*(b + j + x1*(i+2))) > abs(*(b + (j+2) + x1*i)-*(b + (j-2) + x1*i)))
				{
					*(Buffer+(k++)) = (*(b + (j-1) + x1*i) + *(b + (j+1) + x1*i) )>>1;  // G
				}else
				{
					*(Buffer+(k++)) = ( *(b + j + x1*(i-1)) + *(b + j + x1*(i+1)) + *(b + (j-1) + x1*i) + *(b + (j+1) + x1*i) )>>2;  // G
				}
				
          		*(Buffer+(k++)) = (*(b + j + x1*i));  // B
		
			}
		}
		
	}
	    	
	
}

return Buffer;
	
}

void EdgeDetection(unsigned char *rgb, int rows, int cols)
{
    printf("Sobel Edge Detection...\n");
    //Edge Detection via Sobel Mask
    int i, j, Gx, Gy, G;
    int rgb_size = 3*rows*cols;
    int z[9];//z1,z2,z3,z4,z5,z6,z7,z8,z9;
    
    for(i=0;i<rgb_size-8;i++) {

        for(j=0;j<9;j++)    z[j]=*(rgb+i+j);
        
        Gx=(z[6]+2*z[7]+z[8])-(z[0]+2*z[1]+z[2]);
        Gy=(z[2]+2*z[5]+z[8])-(z[0]+2*z[3]+z[6]);
        G = (abs(Gx) + abs(Gy))/2;
        
        *(rgb+i) = G;
    }
        
}

void updown2(unsigned char *rgb, int rows, int cols)
{
    int rgb_size=3*rows*cols;
    int i;
    unsigned char r_tmp, g_tmp, b_tmp;
    //RED COMPONENT ::
    for(i=0;i<(rgb_size/2)-1;i+=3) {
        r_tmp = *(rgb+rgb_size-i);
        *(rgb+rgb_size-i) = *(rgb+i);
        *(rgb+i) = r_tmp;
    }
    //GREEN COMPONENT ::
    for(i=1;i<(rgb_size/2)-1;i+=3) {
        g_tmp = *(rgb+rgb_size-i-1);
        *(rgb+rgb_size-i-1) = *(rgb+i);
        *(rgb+i) = g_tmp;
    }
    //BLUE COMPONENT ::
    for(i=2;i<(rgb_size/2)-1;i+=3) {
        b_tmp = *(rgb+rgb_size-i-2);
        *(rgb+rgb_size-i-2) = *(rgb+i);
        *(rgb+i) = b_tmp;
    }
}    


void gammaCor(unsigned char *rgb, int rows, int cols, float a)
{
	int rgb_size = 3*rows*cols;
	int i;
	float r,g,b;
	for(i=0;i<rgb_size-2;i+=3) {
		r = *(rgb+i);
		g = *(rgb+i+1);	
		b = *(rgb+i+2);	

		r = pow(r, (float)(1/a));
		*(rgb+i) = 255*r;

		g = pow(g, (float)(1/a));
		*(rgb+i+1) = 255*g;

		b = pow(g, (float)(1/a));
		*(rgb+i+2) = 255*b;
		
		*(rgb+i) = (*(rgb+i)>255) ? 255 : *(rgb+i);
		*(rgb+i) = (*(rgb+i)<0) ? 0 : *(rgb+i);
		*(rgb+i+1) = (*(rgb+i+1)>255) ? 255 : *(rgb+i+1);
		*(rgb+i+1) = (*(rgb+i+1)<0) ? 0 : *(rgb+i+1);
		*(rgb+i+2) = (*(rgb+i+2)>255) ? 255 : *(rgb+i+2);
		*(rgb+i+2) = (*(rgb+i+2)<0) ? 0 : *(rgb+i+2);
	}
}


//This function inverses image colors --> Color Inversion(works) -->
void inverse(unsigned char *rgb, int rows, int cols) //
{
    printf("Negative effect...\n");
    int rgb_size = 3*rows*cols;
    int i;
    for(i=0; i<rgb_size-2; i+=3) {
        *(rgb+i) = 255 - *(rgb+i);
        *(rgb+i+1) = 255 - *(rgb+i+1);
        *(rgb+i+2) = 255 - *(rgb+i+2);

        *(rgb+i) = (*(rgb+i)>255) ? 255 : *(rgb+i);
        *(rgb+i+1) = (*(rgb+i+1)>255) ? 255 : *(rgb+i+1);
        *(rgb+i+2) = (*(rgb+i+2)>255) ? 255 : *(rgb+i+2);

        *(rgb+i) = (*(rgb+i)<0) ? 0 : *(rgb+i);
        *(rgb+i+1) = (*(rgb+i+1)<0) ? 0 : *(rgb+i+1);
        *(rgb+i+2) = (*(rgb+i+2)<0) ? 0 : *(rgb+i+2);

    }

}

void extra_solarize(unsigned char *rgb, int rows, int cols) 
{
	int rgb_size = 3*rows*cols;
	int i, T, idx;
	for(i=0;i<rgb_size-2;i+=3) {
            
                idx = rand()%4;
		if(idx==1) { 
			T = *(rgb+i);
		} else if(idx==2) {
			T = *(rgb+i+1);
		} else {
			T = *(rgb+i+2);
		}
		
		*(rgb+i) = (*(rgb+i)<T) ? (255-*(rgb+i)) : (*(rgb+i));
		*(rgb+i+1) = (*(rgb+i+1)<T) ? (255-*(rgb+i+1)) : (*(rgb+i+1));
		*(rgb+i+2) = (*(rgb+i+2)<T) ? (255-*(rgb+i+2)) : (*(rgb+i+2));
		
		*(rgb+i) = (*(rgb+i)<0) ? 0 : *(rgb+i);
		*(rgb+i) = (*(rgb+i)>255) ? 255 : *(rgb+i);
		*(rgb+i+1) = (*(rgb+i+1)<0) ? 0 : *(rgb+i+1);
		*(rgb+i+1) = (*(rgb+i+1)>255) ? 255 : *(rgb+i+1);
		*(rgb+i+2) = (*(rgb+i+2)<0) ? 0 : *(rgb+i+2);
		*(rgb+i+2) = (*(rgb+i+2)>255) ? 255 : *(rgb+i+2);
	}
}

//This function does not work absolutely correct this very moment -->
void binarize(unsigned char *rgb, int rows, int cols)
{
    printf("Image Binarization...\n");
    //int idx = rand()%(rows*cols);	//Random number between 0-(rows*cols)-1
    //int T = *(rgb+idx);
    int i,j,sum=0,T;
    int rgb_size = 3*rows*cols;
    int r,g,b;
	for(i=0;i<rgb_size;i++) {
		sum += *(rgb+i);
	}
	T = sum/rgb_size;
	printf("Mean value = %d\n", T);
    
    for(j=0;j<rgb_size-2;j++) {
        r = *(rgb+j);
        g = *(rgb+j+1);
        b = *(rgb+j+2);
        
    	*(rgb+j)   = (r+g+b)/3;
	}
	
	for(i=0; i<rgb_size-2;i++) 
            *(rgb+i)   = (*(rgb+i)>T)    ? 255 : 0; 
}

//This function works correctly -->
void RGB2YCbCr(unsigned char *rgb, int rows, int cols)
{
    int rgb_size = 3*rows*cols;
    unsigned long long int r,g,b,i;
    for(i=0; i<rgb_size-2; i+=3) {
        r = *(rgb+i);
        g = *(rgb+i+1);
        b = *(rgb+i+2);
        
        *(rgb+i) = ((b*3726 + g*19235 + r*9798)>>15);  // einai /2^15 ousiastika p.x. --> Y = 0.299R + 0.587G + 0.114B
        *(rgb+i+1) = ((b*2664 - g*10856 - r*5528)>>15) +128;
        *(rgb+i+2) = ((-b*2664 - g*13720 + r*16384)>>15) +128;
    }
}

void YCbCr2RGB(unsigned char *rgb, int rows, int cols)
{
    int rgb_size = 3*rows*cols;
    unsigned long long int Y, Cb, Cr, rr, gg, bb, i;
    for(i=0;i<rgb_size-2;i+=3) {
        Y = *(rgb+i);
        Cb = *(rgb+i+1);
        Cr = *(rgb+i+2);
        
        rr = ((Cr*45941)>>15) + Y - 179;
        gg = ((-Cr*23499 - Cb*11277)>>15) + Y + 136;
        bb = ((Cb*58065)>>15) + Y - 227;
        
        rr = (rr>255) ? 255 : rr;
        rr = (rr<0) ? 0 : rr;
        
        gg = (gg>255) ? 255 : gg;
        gg = (gg<0) ? 0 : gg;
        
        bb = (bb>255) ? 255 : bb;
        bb = (bb<0) ? 0 : bb;
        
        *(rgb+i) = rr;
        *(rgb+i+1) = gg;
        *(rgb+i+2) = bb;
    }
}      

void Color_Saturation(unsigned char *rgb, float k, int rows, int cols)
{
  int rgb_size = 3*rows*cols;
  int i;
  int b,g,r;
  float temp;
  int temp_b,temp_g,temp_r;

	for (i=0; i<rgb_size-2; i+=3)	{

		b = *(rgb+i);
		g = *(rgb+i + 1);
		r = *(rgb+i + 2);

		temp = 3736*(1-k)*b + 19235*(1-k)*g + (9798+22970*k)*r;
		temp_b = temp; temp_b = temp_b>>15;
        	temp = 3736*(1-k)*b + (19235+13533*k)*g + 9798*(1-k)*r;
		temp_g = temp; temp_g = temp_g>>15;
		temp = (3736+29032*k)*b + 19235*(1-k)*g + 9798*(1-k)*r;
		temp_r = temp; temp_r = temp_r>>15;



		temp_b = (temp_b >255) ? 255 : temp_b;
		temp_b = (temp_b <0) ? 0 : temp_b;
		temp_g = (temp_g >255) ? 255 : temp_g;
		temp_g = (temp_g <0) ? 0 : temp_g;
		temp_r = (temp_r >255) ? 255 : temp_r;
		temp_r = (temp_r <0) ? 0 : temp_r;

	    	*(rgb+i) = temp_b;
		*(rgb+i + 1) = temp_g ;
		*(rgb+i + 2) = temp_r;

	}
}

void WhiteBalance(unsigned char *rgb, int rows, int cols)
{
  int i, rgb_size;
  rgb_size = 3*rows*cols;
  float bavg,gavg,ravg,b_mul,g_mul,r_mul,maxavg,temp_b, temp_g,temp_r;

    for (i=0; i<rgb_size-2; i+=3) {
            bavg += *(rgb+i);
            gavg += *(rgb+i + 1);
            ravg += *(rgb+i + 2);
    }
    bavg = bavg/rgb_size;
    gavg = gavg/rgb_size;
    ravg = ravg/rgb_size;

    maxavg = (gavg >= bavg) ? gavg : bavg;
    maxavg = (maxavg < ravg) ? ravg : maxavg;
    b_mul = maxavg/bavg;
    g_mul = maxavg/gavg;
    r_mul = maxavg/ravg;

    for (i=0; i<rgb_size-2; i+=3) {
            temp_b = *(rgb+i)*b_mul;
            temp_g =*(rgb+i + 1)*g_mul;
            temp_r = *(rgb+i + 2)*r_mul;

            temp_b = (temp_b >255) ? 255 : temp_b;
            temp_g = (temp_g >255) ? 255 : temp_g;
            temp_r = (temp_r >255) ? 255 : temp_r;

            *(rgb+i ) = temp_b;
            *(rgb+i + 1) =  temp_g;
            *(rgb+i + 2) = temp_r;
        }
}


void ColorCorrection(unsigned char *rgb,int rows, int cols) 
{
  int i;
  int rgb_size = 3*rows*cols;
  int b,g,r;
  float temp_b, temp_g,temp_r;

    for (i=0; i<rgb_size-2; i+=3) {

            b = *(rgb+i);
            g = *(rgb+i + 1);
            r = *(rgb+i + 2);
            temp_b = (40206*b - 4129*g - 3310*r)>>15;
            temp_g = (-1671*b + 59671*g - 28574*r)>>15;
            temp_r = (-1671*b - 3080*g + 41550*r)>>15;

            temp_b = (temp_b >255) ? 255 : temp_b;
            temp_b = (temp_b <0) ? 0 : temp_b;
            temp_g = (temp_g >255) ? 255 : temp_g;
            temp_g = (temp_g <0) ? 0 : temp_g;
            temp_r = (temp_r >255) ? 255 : temp_r;
            temp_r = (temp_r <0) ? 0 : temp_r;

            *(rgb+i) = temp_b;
            *(rgb+i+1) = temp_g;
            *(rgb+i+2) = temp_r;
    }
}

void Sepia(unsigned char *rgb, int rows, int cols)
{
    int rgb_size=3*rows*cols;
    int i;
    int r,g,b;
    
    for(i=0;i<rgb_size-2;i+=3) {
        r = *(rgb+i);
        g = *(rgb+i+1);
        b = *(rgb+i+2);
                
        *(rgb+i) = (r* .393) + (g* .769) + (b* .189);
        *(rgb+i+1) = (r* .349) + (g* .686) + (b* .168);
        *(rgb+i+2) = (r* .272) + (g* .534) + (b* .131);
    /*    
        *(rgb+i) = (*(rgb+i)>255) ? 255 : *(rgb+i);
        *(rgb+i+1) = (*(rgb+i+1)>255) ? 255 : *(rgb+i+1);
        *(rgb+i+2) = (*(rgb+i+2)>255) ? 255 : *(rgb+i+2);
        
        *(rgb+i) = (*(rgb+i)<0) ? 0 : *(rgb+i);
        *(rgb+i+1) = (*(rgb+i+1)<0) ? 0 : *(rgb+i+1);
        *(rgb+i+2) = (*(rgb+i+2)<0) ? 0 : *(rgb+i+2);
    
    */
    }
}

#endif // img_processing_H


