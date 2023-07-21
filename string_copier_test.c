// usng pointers to copy strings

// extract data from address 'pointed' to by the pointers by using dereference char, *

#include<stdio.h>
#include<string.h>
 
void copy(char* dst, char* src){
  while (*src != '\0') {
    // obtain char pointed to by src and copy it to dst
    *dst = *src;
    // increment both pointers for next iteration
    src++;
    dst++;
  }
  // after loop, set last char to terminating char
  *dst = '\0';
}
 
int main(){
  char srcString[] = "This is the string to be copied and stored in dstString.";
 
  // initialise str that is as long as srcString
  char dstString[strlen(srcString)+1];

  // test copy function
  copy(dstString, srcString);

  printf("%s", dstString);

}
