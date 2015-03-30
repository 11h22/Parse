#include <stdio.h>
#include <iostream>
#include <stdlib.h>    
#include <time.h>  
#include <string.h>
using namespace std;

class Text{
  int strlen; 
  char *str;
  int *numsent;
  char *estr;
  int *enumsent;
  char *dstr;
  int *dnumsent;
  char Regularalphabet[26];
  int RegAlphaNum[26];
  char cipher[26];
  int ciphernumsent[26];
  char dcipher[26];
  int dciphernumsent[26];
  double letterfreq[26];
  double eletterfreq[26];
  float letterfreqfromwiki[26];
  double matrix[26][26];
public:
  Text();
  ~Text();
  void Initialize();
  void GetSent();
  void PrintStrings(bool a,bool b, bool c) const;
  void GetKey();
  void GetKeynum();
  void DoIt();
  void PrintStrings(bool a,bool b,bool c,bool d) const;
  void Frequency();
  void LookatFrequency();
  void Matrix();
  void CaesarBreak();
  void Decrypt();
}; 
Text::Text(){
  strncpy(Regularalphabet,"abcdefghijklmnopqrstuvwxyz",26);
  for (int i=0;i<26;i++){
    RegAlphaNum[i]=Regularalphabet[i];
  }
}
Text::~Text(){
  cout<<"Cleaning up memory"<<endl;
  free(str);
  free(numsent);
  free(estr);
  free(enumsent);
  free(dstr);
  free(dnumsent);
  cout<<"Ended Text Cleanly"<<endl;
}
void Text::Initialize(){
  strlen=0; 
  numsent=0;
  enumsent=0;
  dnumsent=0;
  for (int i=0;i<26;i++){
    RegAlphaNum[i]=0;
    ciphernumsent[i]=0;
    dciphernumsent[i]=0;
    letterfreq[i]=0;
    eletterfreq[i]=0;
    letterfreqfromwiki[i]=0;
    for (int j=0;j<26;j++){
      matrix[i][j]=0;
    }
  }
}
void Text::GetSent(){
  char c=' '; 
  int i=0,j=1;
  bool a=0;
  int b=0;
  str = (char*)malloc(sizeof(char));
  numsent = (int*)malloc(sizeof(int));
  cout<<"Input text from:"<<endl<<"0 for stdin   1 for file"<<endl;
  scanf("%i",&b);
  if (b!=0){
    a=1;
  }
  else {
    a=0;
  }
  printf("Enter String : ");
  if (a){
    //i=0,j=1;
    FILE * pFile;
    pFile=fopen ("/home/o/Parse/input.text","r");
    if (pFile==NULL) {
      perror ("Error opening file");
    }
    else{
      while(c!=EOF) {
	if(c=='\n'){
	  c=' ';
	}
	c = getc(pFile);
	str = (char*)realloc(str,j*sizeof(char));
	numsent = (int*)realloc(numsent,j*sizeof(int));
	str[i] = c;
	numsent[i]=c;
	if (numsent[i]>64&&numsent[i]<91){ //ascii to more readable form a=1,b=2...
	  numsent[i]=numsent[i]-65;
	}
	else if (numsent[i]>96&&numsent[i]<123){//deal with capital letters
	  numsent[i]=numsent[i]-97;
	}
	else { //get rid of spaces
	  numsent[i]=0;
	  i--;
	  j--;
	}
	i++;
	j++;
      }
      fclose (pFile);
    }
  }
  else {
    while(c!='\n') {
      c = getc(stdin);
      /*if (i==0){
	c=' ';
	}*/
      str = (char*)realloc(str,j*sizeof(char));
      numsent = (int*)realloc(numsent,j*sizeof(int));
      str[i] = c;
      numsent[i]=c;
      if (c!='\n'){
	if (numsent[i]>64&&numsent[i]<91){ //ascii to more readable form a=1,b=2...
	  numsent[i]=numsent[i]-65;
	}
	else if (numsent[i]>96&&numsent[i]<123){//deal with capital letters
	  numsent[i]=numsent[i]-97;
	}
	else { //get rid of spaces
	  numsent[i]=0;
	  i--;
	  j--;
	}
      }
      i++;
      j++;
    }
  }
  str = (char*)realloc(str,j*sizeof(char));
  numsent = (int*)realloc(numsent,j*sizeof(int));
  str[i]='\0';   
  numsent[i]=0;
  strlen=j;
  /*printf ("%s\n",str);
  for (int i=0;i<strlen;i++){
    printf("%d ",numsent[i]);
    }*/
  printf("Length of string is : %d\n",strlen);
}
void Text::PrintStrings(bool a,bool b,bool c) const{
  cout<<"Printing:"<<endl;
  if (a){
    cout<<"Text:"<<endl;
    printf ("%s\n", str);
  }
  if (b){
    cout<<"Alphabet:"<<endl;
    printf ("%s \n", Regularalphabet);
  }
  if (c){
    cout<<"Normal:"<<endl;
    for (int i=0;i<strlen-1;i++){
      cout<<numsent[i]<<" ";
    }
  }
  cout<<endl;
}
void Text::GetKey(){
  strncpy(cipher,"nopqrstuvwxyzabcdefghijklm",26);
}
void Text::GetKeynum(){
  for (int i=0;i<26;i++){
    ciphernumsent[i]=cipher[i];
  }
  for (int i=0;i<26;i++){
    if (ciphernumsent[i]>96){
      ciphernumsent[i]=ciphernumsent[i]-97;
    }
      else {
      ciphernumsent[i]=0;
    }
    //cout<<ciphernumsent;
  }
}
void Text::DoIt(){
  estr = (char*)malloc(sizeof(char[strlen+1]));
  enumsent = (int*)malloc(sizeof(int[strlen+1]));
  memcpy(estr,str,sizeof(char[strlen]));
  memcpy(enumsent,numsent,sizeof(int[strlen]));
  for (int i=0;i<strlen;i++){
    enumsent[i]=ciphernumsent[numsent[i]]; 
  }
  for (int i=0;i<strlen;i++){
    estr[i]=Regularalphabet[enumsent[i]];
  }
}
void Text::PrintStrings(bool a,bool b,bool c,bool d) const{
  cout<<"Printing:"<<endl;
  if (d){
    if (a){
      cout<<"Text:"<<endl;
      printf ("%s\n", estr);
    }
    if (b){
      cout<<"Alphabet:"<<endl;
      printf ("%s \n", cipher);
    }
    if (c){
      cout<<"ASCII:"<<endl;
      for (int i=0;i<strlen;i++){
	cout<<enumsent[i]<<" ";
      }
      cout<<endl;
    }
  }
}
void Text::Frequency(){
  for (int i=0;i<strlen;i++){
    if (numsent[i]!=0){
      letterfreq[numsent[i]]++;
    }
    if (enumsent[i]!=0){
      eletterfreq[enumsent[i]]++;
    }
  }
  for (int i=0;i<26;i++){
    letterfreq[i]=letterfreq[i]/(strlen);
    eletterfreq[i]=eletterfreq[i]/(strlen);
  }
  FILE * pFileR;
  pFileR = fopen ("/home/o/Parse/freq.text", "r");
  letterfreqfromwiki[0]=0;
  for (int i=0;i<26;i++){
    fscanf(pFileR,"%f",&letterfreqfromwiki[i]);
  }
  fclose (pFileR);
  //cout<<endl<<"Frequency English\tFrequency of plaintext\tFrequency of Cipher"<<endl;
  for (int i=0;i<26;i++){
    //cout<<Regularalphabet[i]<<"\t"<<letterfreqfromwiki[i]<<"\t\t"<<letterfreq[i]*100<<"\t\t"<<eletterfreq[i]*100<<endl;
  }
}
void Text::Matrix(){
  double bestchance[26]={0};
  int plain=0;
  int ciph=0;
  for (int i=0;i<26;i++){
    //cout<<Regularalphabet[i]<<"\t";
    for (int j=0;j<26;j++){
      /*if (i==0 || j==0){
	matrix[i][j]=0;
	}*/
      //else {
	matrix[i][j]=((double)eletterfreq[i]*100)-letterfreqfromwiki[j];
	if (matrix[i][j]<0){
	  matrix[i][j]=matrix[i][j]*(-1);
	}
	//}
      //matrix[i][j]=double(int(matrix[i][j]*10+0.5))/10;//loss of accuracy by rounding to the nearest tenth
      //cout<<matrix[i][j]<<"\t";
    }
    //cout<<endl; 
  }
  FILE * pFile;
  pFile = fopen ("/home/o/Parse/cipherfreq.text", "w");
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      fprintf(pFile,"%f\t",matrix[i][j]);
    }
    fprintf(pFile,"\n");
  }
  fclose (pFile);
  //cout<<"Initial Best Guesses"<<endl;
  //cout<<"Cipher to English  Minimum difference in frequencies"<<endl;
  for (int i=0;i<26;i++){
    bestchance[i]=matrix[i][1];
    plain=i;
    for (int j=0;j<25;j++){
      if (bestchance[i]>matrix[i][j+1]){
	bestchance[i]=matrix[i][j+1];
	ciph=j+1;
      }
    }
    //cout<<Regularalphabet[plain]<<" to  "<<Regularalphabet[ciph]<<" "<<bestchance[i]<<endl;
  }
}
void Text::LookatFrequency(){
  float swap[3]={0};
  char cswap[3];
  char alpha1[26];
  char alpha2[26];
  char alpha3[26];
  strncpy(alpha1,Regularalphabet,26);
  strncpy(alpha2,Regularalphabet,26);
  strncpy(alpha3,Regularalphabet,26);
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      if (letterfreqfromwiki[j] < letterfreqfromwiki[j+1]) {
        swap[0] = letterfreqfromwiki[j];
        letterfreqfromwiki[j] = letterfreqfromwiki[j+1];
        letterfreqfromwiki[j+1] = swap[0];
        cswap[0] = alpha1[j];
        alpha1[j] = alpha1[j+1];
        alpha1[j+1] = cswap[0];
      }
      if (letterfreq[j] < letterfreq[j+1]) {
        swap[1] = letterfreq[j];
        letterfreq[j] = letterfreq[j+1];
        letterfreq[j+1] = swap[1];
        cswap[1] = alpha2[j];
        alpha2[j] = alpha2[j+1];
        alpha2[j+1] = cswap[1];
      }
      if (eletterfreq[j] < eletterfreq[j+1]) {
        swap[2] = eletterfreq[j];
        eletterfreq[j] = eletterfreq[j+1];
        eletterfreq[j+1] = swap[2];
        cswap[2] = alpha3[j];
        alpha3[j] = alpha3[j+1];
        alpha3[j+1] = cswap[2];
      }
    }
  }	   
  //cout<<"Sorted English Frequencies\tSorted Input Frequencies\tSorted Cipher Frequencies"<<endl;
  for (int i=0;i<26;i++){
    //cout<<alpha1[i]<<"\t\t"<<letterfreqfromwiki[i]<<"\t\t"<<alpha2[i]<<"\t\t"<<letterfreq[i]*100<<"\t"<<alpha3[i]<<"\t\t"<<eletterfreq[i]*100<<endl;
  }
  //cout<<"Cipher to English  Minimum difference in frequencies"<<endl;
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      if (matrix[i][j]<1.5){
	//cout<<Regularalphabet[i]<<" to  "<<Regularalphabet[j]<<" "<<matrix[i][j]<<endl;
      }
    }
  }
}
void Text::CaesarBreak(){
  double cmatrix[26][26]={0};
  double summedpercentages[26][2]={0};
  double swapd=0;
  int swapi=0;
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      if (matrix[i][j]<1.5){
	cmatrix[i][j]=matrix[i][j];
	//cout<<Regularalphabet[i]<<" to  "<<Regularalphabet[j]<<" "<<matrix[i][j]<<endl;
      }
    }
  }
  FILE * pFile;
  pFile = fopen ("/home/o/Parse/cipherfreqsortedfiltered.text", "w");
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      fprintf(pFile,"%f\t",cmatrix[i][j]);
    }
    fprintf(pFile,"\n");
  }
  fclose (pFile);
  for (int i=0;i<26;i++){ //to be used for data analysis
    for (int j=25;j>-1;j--){
      //cout<<(j+i+1)%26<<" ";
      summedpercentages[(j+i+1)%26][0]=summedpercentages[(j+i+1)%26][0]+matrix[i][j];
      summedpercentages[(j+i+1)%26][1]=j;
    }
    //cout<<endl;
  }
  cout<<endl<<endl;
  /*for (int i=25;i>-1;i--){ //easier to read
    for (int j=25;j>-1;j--){
      cout<<(j+i+1)%26<<" ";
    }
    cout<<endl;
    }*/
  for (int i=0;i<26;i++){
    cout<<summedpercentages[i][0]<<"\t"<<summedpercentages[i][1]<<endl;
  }
  for (int i=0;i<26;i++){
    for (int j=0;j<26;j++){
      if (summedpercentages[j][0] < summedpercentages[j+1][0]) {
        swapd = summedpercentages[j][0];
        summedpercentages[j][0] = summedpercentages[j+1][0];
        summedpercentages[j+1][0] = swapd;
        swapi = summedpercentages[j][1];
        summedpercentages[j][1] = summedpercentages[j+1][1];
        summedpercentages[j+1][1] = swapi;
      }
    }
  }
  //y=x+13;
  cout<<"Summed percentages on all lines with slope 1"<<endl<<"The 2nd number is the yintercept"<<endl;
  dciphernumsent[0]=summedpercentages[25][1];
  for (int i=0;i<26;i++){
    dciphernumsent[i]=((i+dciphernumsent[0])%26);
    cout<<summedpercentages[i][0]<<"\t"<<summedpercentages[i][1]<<"\t"<<dciphernumsent[i]<<"\t"<<Regularalphabet[dciphernumsent[i]]<<endl;
  }
}
void Text::Decrypt(){
  dstr = (char*)malloc(sizeof(char[strlen]));
  dnumsent = (int*)malloc(sizeof(int[strlen]));
  memcpy(dstr,estr,sizeof(char[strlen]));
  memcpy(dnumsent,enumsent,sizeof(int[strlen]));
  printf("%d\n",strlen);
  for (int i=0;i<strlen;i++){
    dnumsent[i]=dciphernumsent[(enumsent[i]+3)%26];//suspicious +3 
  }
  for (int i=0;i<strlen;i++){
    dstr[i]=Regularalphabet[dnumsent[i]];
  }
  printf("%s\n",dstr);
}
int main(){
  Text *GO= new Text();
  GO->Initialize();
  GO->GetSent();
  GO->PrintStrings(0,0,0);
  GO->GetKey();
  GO->GetKeynum();
  GO->DoIt();
  GO->PrintStrings(1,0,0,1);
  GO->Frequency();
  GO->Matrix();
  GO->LookatFrequency();
  GO->CaesarBreak();
  GO->Decrypt();
  delete GO;
}
  /*fgets(word1, 100, stdin);*/
