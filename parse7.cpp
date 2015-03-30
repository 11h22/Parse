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
  char Regularalphabet[27];
  int RegAlphaNum[27];
  char cipher[27];
  int ciphernumsent[27];
  char dcipher[27];
  int dciphernumsent[27];
  double letterfreq[27];
  double eletterfreq[27];
  float letterfreqfromwiki[27];
  double matrix[27][27];
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
  strncpy(Regularalphabet," abcdefghijklmnopqrstuvwxyz",27);
  for (int i=0;i<27;i++){
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
  for (int i=0;i<27;i++){
    RegAlphaNum[i]=0;
    ciphernumsent[i]=0;
    dciphernumsent[i]=0;
    letterfreq[i]=0;
    eletterfreq[i]=0;
    letterfreqfromwiki[i]=0;
    for (int j=0;j<27;j++){
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
	i++;
	j++;
      }
      fclose (pFile);
    }
  }
  else {
    while(c!='\n') {
      c = getc(stdin);
      if (i==0){
	c=' ';
      }
      str = (char*)realloc(str,j*sizeof(char));
      numsent = (int*)realloc(numsent,j*sizeof(int));
      str[i] = c;
      numsent[i]=c;
      i++;
      j++;
    }
  }
  str = (char*)realloc(str,j*sizeof(char));
  numsent = (int*)realloc(numsent,j*sizeof(int));
  str[i]='\0';   
  numsent[i]=0;
  strlen=i;
  //printf ("%s",str);
  printf("Length of string is : %d\n",strlen);
  for (int i=0;i<strlen;i++){
    if (numsent[i]>64&&numsent[i]<91){
      numsent[i]=numsent[i]-64;
    }
    else if (numsent[i]>96&&numsent[i]<123){
      numsent[i]=numsent[i]-96;
    }
    else {
      numsent[i]=0;
    }
  }
}
/*void readfromfile(){
  FILE * pFileR;//binary
  pFileR = fopen ("/home/o/Parse/InputText.bin", "r");
  fread (MemR , sizeof(int), games*17, pFileR);
  fclose (pFileR);
}
void Writetofile(){
  FILE * pFileW;
  pFileW = fopen ("/home/o/Parse/InputText.bin", "w");
  fwrite (MemW , sizeof(int), games*17, pFile);//binary
  fclose (pFileW);
  }*/
void Text::PrintStrings(bool a,bool b,bool c) const{
  cout<<"Printing:"<<endl;
  if (a){
    cout<<"Text:"<<endl;
    printf ("%s", str);
  }
  if (b){
    cout<<"Alphabet:"<<endl;
    printf ("%s \n", Regularalphabet);
  }
  if (c){
    cout<<"Normal:"<<endl;
    for (int i=0;i<strlen;i++){
      cout<<numsent[i]<<" ";
    }
  }
  cout<<endl;
}
void Text::GetKey(){
  strncpy(cipher," nopqrstuvwxyzabcdefghijklm",27);
}
void Text::GetKeynum(){
  for (int i=0;i<27;i++){
    ciphernumsent[i]=cipher[i];
  }
  for (int i=0;i<27;i++){
    if (ciphernumsent[i]>96){
      ciphernumsent[i]=ciphernumsent[i]-96;
    }
      else {
      ciphernumsent[i]=0;
    }
  }
}
void Text::DoIt(){
  estr = (char*)malloc(sizeof(char[strlen+1]));
  enumsent = (int*)malloc(sizeof(int[strlen+1]));
  memcpy(estr,str,sizeof(char[strlen+1]));
  memcpy(enumsent,numsent,sizeof(int[strlen+1]));
  for (int i=0;i<strlen;i++){
    enumsent[i]=ciphernumsent[numsent[i]]; 
  }
  for (int i=0;i<strlen;i++){
    if (enumsent[i]==0){
      estr[i]=' ';
    }
    else {
      estr[i]=Regularalphabet[enumsent[i]];
    }
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
  for (int i=0;i<28;i++){
    letterfreq[i]=letterfreq[i]/(strlen-1);
    eletterfreq[i]=eletterfreq[i]/(strlen-1);
  }
  FILE * pFileR;
  pFileR = fopen ("/home/o/Parse/freq.text", "r");
  letterfreqfromwiki[0]=0;
  for (int i=1;i<27;i++){
    fscanf(pFileR,"%f",&letterfreqfromwiki[i]);
  }
  fclose (pFileR);
  //cout<<endl<<"Frequency English\tFrequency of plaintext\tFrequency of Cipher"<<endl;
  for (int i=0;i<27;i++){
    //cout<<Regularalphabet[i]<<"\t"<<letterfreqfromwiki[i]<<"\t\t"<<letterfreq[i]*100<<"\t\t"<<eletterfreq[i]*100<<endl;
  }
}
void Text::Matrix(){
  double bestchance[27]={0};
  int plain=0;
  int ciph=0;
  for (int i=0;i<27;i++){
    //cout<<Regularalphabet[i]<<"\t";
    for (int j=0;j<27;j++){
      if (i==0 || j==0){
	matrix[i][j]=0;
      }
      else {
	matrix[i][j]=((double)eletterfreq[i]*100)-letterfreqfromwiki[j];
	if (matrix[i][j]<0){
	  matrix[i][j]=matrix[i][j]*(-1);
	}
      }
      //matrix[i][j]=double(int(matrix[i][j]*10+0.5))/10;//loss of accuracy by rounding to the nearest tenth
      //cout<<matrix[i][j]<<"\t";
    }
    //cout<<endl; 
  }
  FILE * pFile;
  pFile = fopen ("/home/o/Parse/cipherfreq.text", "w");
  for (int i=0;i<27;i++){
    for (int j=0;j<27;j++){
      fprintf(pFile,"%f\t",matrix[i][j]);
    }
    fprintf(pFile,"\n");
  }
  fclose (pFile);
  //cout<<"Initial Best Guesses"<<endl;
  //cout<<"Cipher to English  Minimum difference in frequencies"<<endl;
  for (int i=1;i<27;i++){
    bestchance[i]=matrix[i][1];
    plain=i;
    for (int j=1;j<26;j++){
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
  char alpha1[27];
  char alpha2[27];
  char alpha3[27];
  strncpy(alpha1,Regularalphabet,27);
  strncpy(alpha2,Regularalphabet,27);
  strncpy(alpha3,Regularalphabet,27);
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
  for (int i=0;i<27;i++){
    //cout<<alpha1[i]<<"\t\t"<<letterfreqfromwiki[i]<<"\t\t"<<alpha2[i]<<"\t\t"<<letterfreq[i]*100<<"\t"<<alpha3[i]<<"\t\t"<<eletterfreq[i]*100<<endl;
  }
  //cout<<"Cipher to English  Minimum difference in frequencies"<<endl;
  for (int i=1;i<27;i++){
    for (int j=1;j<26;j++){
      if (matrix[i][j]<1.5){
	//cout<<Regularalphabet[i]<<" to  "<<Regularalphabet[j]<<" "<<matrix[i][j]<<endl;
      }
    }
  }
}
void Text::CaesarBreak(){
  double cmatrix[27][27]={0};
  double summedpercentages[27][2]={0};
  double swap[2]={0};
  for (int i=1;i<27;i++){
    for (int j=1;j<26;j++){
      if (matrix[i][j]<1.5){
	cmatrix[i][j]=matrix[i][j];
	//cout<<Regularalphabet[i]<<" to  "<<Regularalphabet[j]<<" "<<matrix[i][j]<<endl;
      }
    }
  }
  FILE * pFile;
  pFile = fopen ("/home/o/Parse/cipherfreqsortedfiltered.text", "w");
  for (int i=0;i<27;i++){
    for (int j=0;j<27;j++){
      fprintf(pFile,"%f\t",cmatrix[i][j]);
    }
    fprintf(pFile,"\n");
  }
  fclose (pFile);
  for (int i=0;i<27;i++){ //to be used for data analysis
    for (int j=26;j>-1;j--){
      //cout<<(j+i+1)%27<<" ";
      summedpercentages[(j+i+1)%27][0]=summedpercentages[(j+i+1)%27][0]+matrix[i][j];
      summedpercentages[(j+i+1)%27][1]=j;
    }
    //cout<<endl;
  }
  cout<<endl<<endl;
  /*for (int i=26;i>-1;i--){ //easier to read
    for (int j=26;j>-1;j--){
      cout<<(j+i+1)%27<<" ";
    }
    cout<<endl;
    }*/
  for (int i=0;i<27;i++){
    for (int j=0;j<27;j++){
      if (summedpercentages[j][0] > summedpercentages[j+1][0]) {
        swap[0] = summedpercentages[j][0];
        summedpercentages[j][0] = summedpercentages[j+1][0];
        summedpercentages[j+1][0] = swap[0];
        swap[1] = summedpercentages[j][1];
        summedpercentages[j][1] = summedpercentages[j+1][1];
        summedpercentages[j+1][1] = swap[1];
      }
    }
  }
  //y=x+13;
  cout<<"Summed percentages on all lines with slope 1"<<endl<<"The 2nd number is the yintercept"<<endl;
  dciphernumsent[0]=(int)summedpercentages[1][1];
  for (int i=0;i<27;i++){
   dciphernumsent[i]=(i+dciphernumsent[0])%27;
   cout<<summedpercentages[i][0]<<"\t"<<summedpercentages[i][1]<<"\t"<<dciphernumsent[i]<<"\t"<<Regularalphabet[dciphernumsent[i]]<<endl;
  }
}
void Text::Decrypt(){
  dstr = (char*)malloc(sizeof(char[strlen+1]));
  dnumsent = (int*)malloc(sizeof(int[strlen+1]));
  memcpy(dstr,estr,sizeof(char[strlen+1]));
  memcpy(dnumsent,enumsent,sizeof(int[strlen+1]));


  for (int i=0;i<strlen;i++){
    dnumsent[i]=dciphernumsent[numsent[i]]; 
  }
  for (int i=0;i<strlen;i++){
    if (dnumsent[i]==0){
      dstr[i]=' ';
    }
    else {
      dstr[i]=Regularalphabet[enumsent[i]];
    }
  }
  /*
  strncpy(cipher," nopqrstuvwxyzabcdefghijklm",27);
  for (int i=0;i<27;i++){
    ciphernumsent[i]=cipher[i];
  }
  for (int i=0;i<27;i++){
    if (ciphernumsent[i]>96){
      ciphernumsent[i]=ciphernumsent[i]-96;
    }
      else {
      ciphernumsent[i]=0;
      }
  }*/
}
int main(){
  Text *GO= new Text();
  GO->Initialize();
  GO->GetSent();
  GO->GetKey();
  GO->GetKeynum();
  GO->DoIt();
  GO->PrintStrings(1,0,0,1);
  GO->Frequency();
  GO->Matrix();
  GO->LookatFrequency();
  GO->CaesarBreak();
  delete GO;
}
  /*fgets(word1, 100, stdin);*/
