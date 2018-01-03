#ifndef padd3_H
#define padd3_H

#include "bmp.h"

BYTE **padd3(BYTE *img, int cols, int rows) //cols = xs+4  rows = ys+4
{

	int i,j,k;
	BYTE **padded_img;
	padded_img =(BYTE **) malloc(rows*sizeof(BYTE *));
	   	/* h ekfrash sizeof(BYTE *) xrhsimopoieitai gia na desmeusoume mnhmh gia 'rows' deiktes , p.x. ean rows=3
		desmeuetai mnhmh gia tous deiktes img[0] , img[1] , img[2] */
	if(padded_img==NULL) exit(1);

	for(i=0;i<rows;i++){
		*(padded_img+i) = (BYTE *) malloc(cols*sizeof(BYTE));  // *(img+i)  is an address not a value
		if(*(padded_img+i)==NULL) exit(1);

	}
	//memset(img,0,rows*cols);

	//First create a white(255) image ::
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
                padded_img[i][j]=255;
        }
    }

	k=0;

	for(i=2;i<rows-2;i++){
		for(j=2;j<cols-2;j++){
			padded_img[i][j]=*(img+(k++));
		}
	}
		// ***** txt file with the numbers of the padded image *******

	char fname1[] = "padded_bayer_crayons_new.txt";
	FILE *f1;
	if((f1=fopen(fname1,"w"))==NULL) exit(1);

	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			fprintf(f1,"%u\t",padded_img[i][j]);
		}
		fprintf(f1,"\r\n");
	}

	fclose(f1);
	return padded_img;
}

#endif
