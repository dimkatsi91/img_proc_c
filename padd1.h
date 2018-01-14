#ifndef padd_H
#define padd_H

#include "bmp.h"


BYTE *padd(BYTE *img, int rows, int cols, int prows, int pcols)
{
	int new_cols = cols + pcols;
	int new_rows = rows + prows;
	
	BYTE *p_img;
	
	p_img = (BYTE *) malloc (new_cols*new_rows*sizeof(BYTE));
	
	int i,j=0,k=0;
	
	for(i=0;i<new_cols*new_rows;i++)
	{		
		if(i<2*new_cols || i>=new_cols*new_rows-2*new_cols) 
		{
			*(p_img+i)=255;
			
		}
		else
		{
			if(j>=2 && j<new_cols-2)	
			{
				*(p_img+i)=*(img+(k++));
			}	
			else
			{
				*(p_img+i)=255;
			}
			j++;
		}		
			
		if(j==new_cols) {j=0;}	
	}
	
	
	
	/*	
	// ***** txt file with the numbers of the padded image *******
	
	char fname1[] = "padded_bayer_crayons.txt";
	
	FILE *f1;
	
	if((f1=fopen(fname1,"w"))==NULL) exit(1);
	
	
	j=0;
	
	for(i=0;i<new_cols*new_rows;i++)
	{
		fprintf(f1,"%u\t",*(p_img+i));
	
		j++;	
		if(j==new_cols)
	 {
			fprintf(f1,"\r\n");
			j=0;
		}
	}
	
	fclose(f1);
	*/
	return p_img;
}

#endif  //padd_H



