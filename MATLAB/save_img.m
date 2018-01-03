    clear all, close all

    I = imread('rgb.bmp');
    
    I=I(:,:,1);

    [y,x]=size(I);
    
	[filename,pathname]=uiputfile('*.h','Save the input image');  
	fid=fopen([pathname,filename],'w');
    
    fprintf(fid,'#define xs %d\n',x);
    
    fprintf(fid,'#define ys %d\n',y);
    
    fprintf(fid,'#define N %d\r\n\n\n',x*y);
    fprintf(fid,'unsigned char a[N] = {');
    %fprintf(fid,'a = (unsigned short *) malloc(N*sizeof(unsigned char));\n\n');
       
    for i=1:y
        fprintf(fid,'\r\n');
        if(i==y)
            for j=1:x-1
                fprintf(fid,'%d,\t',I(i,j));
            end                
            fprintf(fid,'%d',I(i,j+1));
        else
            for j=1:x
                fprintf(fid,'%d,\t',I(i,j));
            end     
        end
       
    end
        
    fprintf(fid,'};');
    
    fclose(fid);
    
             
      
    
    
	