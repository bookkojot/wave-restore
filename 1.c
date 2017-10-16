#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


int main(){


int width=704;
int height=576;

uint8_t *rgb=malloc(width*height*3);
FILE *in=fopen("frame.raw","r");
fread(rgb,1,width*height*3,in);

int q,w;

for(w=0;w<height;w++){
uint64_t sum=0;
uint8_t *pos=rgb+w*width*3+10*3;
for(q=10;q<width;q++){
sum+=*pos++;
sum+=*pos++;
sum+=*pos++;
}
int move=sum/30000;
printf("moving line by %d\n",move);
if(move<width){
memmove(rgb+w*width*3+move*3,rgb+w*width*3,(width-move)*3);
}
int add=150-(sum/2000);
printf("add %d\n",add);


pos=rgb+w*width*3;
int sample;
for(q=0;q<width;q++){
sample=*pos;
sample+=add;
if(sample<0){sample=0;}
if(sample>255){sample=255;}
*pos++=sample;

sample=*pos;
sample+=add;
if(sample<0){sample=0;}
if(sample>255){sample=255;}
*pos++=sample;

sample=*pos;
sample+=add;
if(sample<0){sample=0;}
if(sample>255){sample=255;}
*pos++=sample;


}


}


FILE *out=fopen("frame2.raw","w");
fwrite(rgb,1,width*height*3,out);
fclose(out);

return 0;
}
