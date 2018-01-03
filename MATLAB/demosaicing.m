clear all, close all

I = imread('parrots.jpg');

% prosoxh , h .bmp image einai 3 pinakes oi opoioi exoun kai oi 3 ta idia stoixeia 
% afou h eikona  mou einai grayscale , ara krataw mono ton ena pinaka
%I=I(:,:,1);

[y,x]=size(I);

R=uint8(zeros(y,x));
G=uint8(zeros(y,x));
B=uint8(zeros(y,x));

a=4;

ys=y+a;
xs=x+a;

%{
%padding
lines_to_add=ys-y;
columns_to_add=xs-x;
top_lines_to_add=floor(lines_to_add/2);
bottom_lines_to_add=ceil(lines_to_add/2);
left_columns_to_add=floor(columns_to_add/2);
right_columns_to_add=ceil(columns_to_add/2);

padded_im=[zeros(top_lines_to_add, x); I; zeros(bottom_lines_to_add, x)];
% pad columns
I1=[zeros(ys, left_columns_to_add) padded_im  zeros(ys, right_columns_to_add)];
%}


I1=uint8(zeros(ys,xs));

% padding frame with zeros
for l=1:ys
    for k=1:xs
        if((l>2 && l<=(ys-a/2))&& (k>2 && k<=(xs-a/2))) I1(l,k)=I(l-a/2,k-a/2);
        end               
        
    end
end



imshow(I)
figure,imshow(I1)    %the initial image padded with zeros panel 
        
    
for i=3:ys-2
    for j=3:xs-2
        
        
        if(mod(i,2)~=0)     %odd lines  BGBGBG...
            if(mod(j,2)~=0)     %odd col  B
                
                R(i-2,j-2)= (I1(i-1,j-1)+I1(i-1,j+1)+I1(i+1,j-1)+I1(i+1,j+1))/4; 
             
                
                
                if(abs(I1(i-2,j)-I1(i+2,j))<abs(I1(i,j+2)-I1(i,j-2)))   
                     G(i-2,j-2)=(I1(i-1,j)+I1(i+1,j))/2 ;
                elseif (abs(I1(i-2,j)-I1(i+2,j))>abs(I1(i,j+2)-I1(i,j-2)))     
                    G(i-2,j-2)=(I1(i,j+1)+I1(i,j-1))/2 ;
                elseif (abs(I1(i-2,j)-I1(i+2,j))== abs(I1(i,j+2)-I1(i,j-2)))
                  G(i-2,j-2)=(I1(i-1,j)+I1(i+1,j)+I1(i,j+1)+I1(i,j-1))/4;
                end
             
                B(i-2,j-2) = I1(i,j);
                 
                
            elseif(mod(j,2)==0)       %even col G
                
                R(i-2,j-2)= (I1(i-1,j)+I1(i+1,j))/2;
                G(i-2,j-2)= I1(i,j);
                B(i-2,j-2)= (I1(i,j-1)+I1(i,j+1))/2;
                
            end
            
        elseif(mod(i,2)==0)            %even lines     GRGRGR..
            if(mod(j,2)~=0)     %odd col  G
                
                R(i-2,j-2)= (I1(i,j-1)+I1(i,j+1))/2; 
                G(i-2,j-2)= I1(i,j);
                B(i-2,j-2)= (I1(i-1,j)+I1(i+1,j))/2;
                
                
                
            else(mod(j,2)==0)        %even col R
                 R(i-2,j-2)=I1(i,j);
                
                                  
                if(abs(I1(i-2,j)-I1(i+2,j))<abs(I1(i,j+2)-I1(i,j-2))) 
                    G(i-2,j-2)=(I1(i-1,j)+I1(i+1,j))/2 ;
                    
                elseif (abs(I1(i-2,j)-I1(i+2,j))>abs(I1(i,j+2)-I1(i,j-2))) 
                    G(i-2,j-2)=(I1(i,j+1)+I1(i,j-1))/2 ;
                        
                elseif (abs(I1(i-2,j)-I1(i+2,j))== abs(I1(i,j+2)-I1(i,j-2)))
                    G(i-2,j-2)=(I1(i-1,j)+I1(i+1,j)+I1(i,j+1)+I1(i,j-1))/4;
                        
                end
                
                B(i-2,j-2)=(I1(i-1,j-1)+I1(i-1,j+1)+I1(i+1,j-1)+I1(i+1,j+1))/4;
               
                
            end            
        end
    end
end
            
           output(:,:,1)=R; output(:,:,2)=G; output(:,:,3)=B;
                    
          % figure,image(output);
            
           figure,imshow(output)
        