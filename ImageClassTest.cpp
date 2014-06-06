// **********************************************************************
// PUCRS/FACIN
// COMPUTAÇÃO GRÁFICA
//
//
// Programa de testes para manipulação de Imagens
//
//  Este programa deve ser compilador junto com a classe "ImageClass",
//  que está implementada no arquivo "ImageClass.cpp"
//
//  - para compilar no Visual C ou Visual Studio acrescente as seguintes
//        bibliotecas:
//      opengl32.lib glu32.lib glaux.lib glut32.lib
//
//  - para compilar no DEVCPP (ou no g++) acrescente as seguintes
//        bibliotecas:
//        -lopengl32 -lglut32 -lglu32 -lglaux
//
//  - para alterar a imagem que é carregada pelo programa, olhe a
//    rotina 'init' e altere a linha:
//       r = Image->Load("    ");
//
// Marcio Sarroglia Pinho
//
// pinho@inf.pucrs.br
// **********************************************************************

#include <iostream>
#include <list>
using namespace std;

#ifdef _MSC_VER

#endif

#ifdef WIN32
#include <windows.h>
#include "GL\glut.h"
#endif

#ifdef __APPLE__
#include <GL/glut.h>
#endif

#include "SOIL/SOIL.h"

#include "ImageClass.h"

ImageClass *Image, *NovaImagem;

#define LIMIAR 10
#define LARGURA_JAN 800
#define ALTURA_JAN 800
/*
Sort an array :) Classic  Bubble Sort
*/
void BubbleSort(int vetor[], int tamanho)
{
  int aux, i, j;

  for(j=tamanho-1; j>=1; j--)
  {
    for(i=0; i<j; i++)
    {
      if(vetor[i]>vetor[i+1])
      {
        aux=vetor[i];
        vetor[i]=vetor[i+1];
        vetor[i+1]=aux;
      }
    }
  }
}
// **********************************************************************
//  void ConvertBlackAndWhite()
//
//
// **********************************************************************
void ConvertBlackAndWhite()
{
    // Tarefa 1:
    //  Mude o valor do LIMIAR para números pequenos como 5 ou 10

	unsigned char r,g,b;
    int x,y;
    int i;
    int preto = 0,branco = 0;
    int ma=100,mi = 0;
    cout << "Iniciou Black & White....";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    int value=150;
    for(x=0;x<Image->SizeX()-1;x++)
    {
        for(y=0;y<Image->SizeY()-1;y++)
        {
            i = Image->GetPointIntensity(x,y);
            //cout<<i<<"\n";

			//Se Preto
            if(i == 0){
                if(  Image->GetPointIntensity(x,y+1) > value &&
                     Image->GetPointIntensity(x+1,y) > value&&
                     Image->GetPointIntensity(x,y-1) > value &&
                     Image->GetPointIntensity(x-1,y) > value){
                      Image->DrawPixel(x, y, 255,255,255);
                      preto++;
                  }
                continue;
            }
            // printf("Intens Fora: %5d\n",i);
            if (i > 30)
            {
              //Preto
                  if(Image->GetPointIntensity(x,y+1) > value &&
                     Image->GetPointIntensity(x+1,y) > value&&
                     Image->GetPointIntensity(x,y-1) > value &&
                     Image->GetPointIntensity(x-1,y) > value){
                      Image->DrawPixel(x, y, 0,0,0);
                      Image->DrawPixel(x+1, y, 0,0,0);
                      Image->DrawPixel(x-1, y, 0,0,0);
                      Image->DrawPixel(x, y+1, 0,0,0);
                      Image->DrawPixel(x, y-1, 0,0,0);
                      preto++;
                  }
              else if(Image->GetPointIntensity(x,y+1) < value &&
                      Image->GetPointIntensity(x+1,y) < value&&
                      Image->GetPointIntensity(x,y-1) < value &&
                      Image->GetPointIntensity(x-1,y) < value){
                          Image->DrawPixel(x, y, 255,255,255);
                          Image->DrawPixel(x+1, y, 255,255,255);
                          Image->DrawPixel(x-1, y, 255,255,255);
                          Image->DrawPixel(x, y+1, 255,255,255);
                          Image->DrawPixel(x, y-1, 255,255,255);
                      }
              else
                Image->DrawPixel(x, y, 255,255,255);
            }
        }
    }
    cout << "Concluiu Black & White.\n";
    cout << "Pretos  : "<<preto<<"\n";
    cout << "Brancos : "<<branco<<"\n";
    cout << "Limiar Max  : "<<ma<<"\n";
    cout << "Limiar Min : "<<mi<<"\n";
}

void refina_TEST(){
    unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Iniciou refinamento....\n";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    int k,j = 0;
    int total = 3;
    int baz [total][total];
    for(x=1;x<Image->SizeX()-1;x++)
    {
        for(y=1;y<Image->SizeY()-1;y++)
        {
            i = Image->GetPointIntensity(x,y);
            int black = 20;
            int white = 200;
            //Se Branco

            if(i > white){
                if(Image->GetPointIntensity(x,y+1) <  black &&
                   Image->GetPointIntensity(x+1,y) <  black&&
                   Image->GetPointIntensity(x,y-1) <  black &&
                   Image->GetPointIntensity(x-1,y) < black){
                   Image->DrawPixel(x, y, 0,0,0);
                }
                else if(Image->GetPointIntensity(x,y+1)   <  black &&
                   Image->GetPointIntensity(x+1,y)   <  black &&
                   Image->GetPointIntensity(x+1,y+1) <  black){
                   Image->DrawPixel(x, y, 0,0,0);
                }

                //cout<<"\nLOL "<<i;

            }
            else{
                if(Image->GetPointIntensity(x,y+1)   > white &&
                        Image->GetPointIntensity(x+1,y)   > white &&
                        Image->GetPointIntensity(x+1,y+1) > white){
                   Image->DrawPixel(x, y, 255,255,255);
                }
               // else
                    //cout<<"\nLOL "<<i;
            }
            /*
            baz[0][1] = Image->GetPointIntensity(x+1,y);
            baz[0][2] = Image->GetPointIntensity(x+2,y);

            baz[1][0] = Image->GetPointIntensity(x,y+1);
            baz[2][0] = Image->GetPointIntensity(x,y+2);
            */

        }
    }
}


void pintaFundo(){
    int x,y;
    int i;
    cout << "Iniciou refinamento....\n";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    int k,j = 0;
    int total = 3;
    int baz [total][total];
    for(x=4;x<Image->SizeX()-4;x++)
    {
        for(y=4;y<Image->SizeY()-4;y++)
        {
            i = Image->GetPointIntensity(x,y);
            int black = 10;
            int white = 200;
            //Se Branco

            if(i > white){
                if(Image->GetPointIntensity(x,y+1) <  black &&
                   Image->GetPointIntensity(x,y+2) <  black &&
                   Image->GetPointIntensity(x,y+3) <  black &&
                   Image->GetPointIntensity(x,y+4) <  black &&
                   Image->GetPointIntensity(x+1,y+1) <  black &&
                   Image->GetPointIntensity(x+2,y+2) <  black &&
                   Image->GetPointIntensity(x+3,y+3) <  black &&
                   Image->GetPointIntensity(x+4,y+4) <  black &&
                   Image->GetPointIntensity(x+1,y) <  black &&
                   Image->GetPointIntensity(x+2,y) <  black &&
                   Image->GetPointIntensity(x+3,y) <  black &&
                   Image->GetPointIntensity(x+4,y) <  black ){
                   Image->DrawPixel(x, y, 0,0,0);
                }
            }
            else{
                if( Image->GetPointIntensity(x,y+1) >  white &&
                    Image->GetPointIntensity(x,y+3) >  white &&
                    Image->GetPointIntensity(x,y+2) >  white &&
                    Image->GetPointIntensity(x,y+4) >  white &&
                    Image->GetPointIntensity(x+1,y+1) >  white &&
                    Image->GetPointIntensity(x+2,y+2) >  white &&
                    Image->GetPointIntensity(x+3,y+3) >  white &&
                    Image->GetPointIntensity(x+4,y+4) >  white &&
                    Image->GetPointIntensity(x+1,y) >  white &&
                    Image->GetPointIntensity(x+2,y) >  white &&
                    Image->GetPointIntensity(x+3,y) >  white &&
                    Image->GetPointIntensity(x+4,y) >  white ){
                    Image->DrawPixel(x, y, 255,255,255);
                }
                if(Image->GetPointIntensity(x,y+1)   > white &&
                        Image->GetPointIntensity(x+1,y)   > white &&
                        Image->GetPointIntensity(x+1,y+1) > white){   }
            }

        }
    }

}
/*
void refina(){
    unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Iniciou refinamento....";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    int baz [3][3];
    for(x=0;x<Image->SizeX()-2;x++)
    {
        for(y=0;y<Image->SizeY()-2;y++)
        {
            i = Image->GetPointIntensity(x,y);
            baz[0][0] = i;
            baz[0][1] = Image->GetPointIntensity(x+1,y);
            baz[0][2] = Image->GetPointIntensity(x+2,y);

            baz[1][0] = Image->GetPointIntensity(x,y+1);
            baz[2][0] = Image->GetPointIntensity(x,y+2);

            //Para cada pixel que pode ser ruido deixar branco

                if(baz[0][0] != baz[0][1] || baz[0][0] != baz[0][2]){

                    if(baz[0][0]!=baz[1][0] || baz[0][0]!=baz[2][0]){
                        Image->DrawPixel(x, y,255,255,255);
                    }
                continue;
                }
                else
                    if(i<150)
                       Image->DrawPixel(x, y,255,255,255);
        }
    }
}
*/
void refina_final(){
    int x,y;
    int i;
    cout << "Iniciou refinamento....\n";
    int k,j = 0;
    int total = 3;
    int baz [total][total];
    for(x=4;x<Image->SizeX()-4;x++)
    {
        for(y=4;y<Image->SizeY()-4;y++)
        {
            i = Image->GetPointIntensity(x,y);
            int black = 20;
            int white = 150;
            //Se Branco

            if(i < black){
                if(Image->GetPointIntensity(x,y+1) >  white &&
                   Image->GetPointIntensity(x,y+2) >  white &&
                   Image->GetPointIntensity(x,y+3) >  white &&
                   Image->GetPointIntensity(x+1,y+1) >  white &&
                   Image->GetPointIntensity(x+2,y+2) >  white &&
                   Image->GetPointIntensity(x+3,y+3) >  white &&
                   Image->GetPointIntensity(x+1,y) >  white &&
                   Image->GetPointIntensity(x+2,y) >  white &&
                   Image->GetPointIntensity(x+3,y) >  white ){
                       Image->DrawPixel(x,y,0,0,0);
                   }
                   else{
                    Image->DrawPixel(x,y,255,255,255);

                    Image->DrawPixel(x,y+1,255,255,255);
                    Image->DrawPixel(x,y+2,255,255,255);
                    Image->DrawPixel(x,y+3,255,255,255);
                    Image->DrawPixel(x,y+4,255,255,255);

                    Image->DrawPixel(x+1,y+1,255,255,255);
                    Image->DrawPixel(x+2,y+2,255,255,255);
                    Image->DrawPixel(x+3,y+3,255,255,255);
                    Image->DrawPixel(x+4,y+4,255,255,255);

                    Image->DrawPixel(x+1,y,255,255,255);
                    Image->DrawPixel(x+2,y,255,255,255);
                    Image->DrawPixel(x+3,y,255,255,255);
                    Image->DrawPixel(x+4,y,255,255,255);

                   }
            }
            /*else{
                if( Image->GetPointIntensity(x,y+1) >  white &&
                    Image->GetPointIntensity(x,y+3) >  white &&
                    Image->GetPointIntensity(x,y+2) >  white &&
                    Image->GetPointIntensity(x,y+4) >  white &&
                    Image->GetPointIntensity(x+1,y+1) >  white &&
                    Image->GetPointIntensity(x+2,y+2) >  white &&
                    Image->GetPointIntensity(x+3,y+3) >  white &&
                    Image->GetPointIntensity(x+4,y+4) >  white &&
                    Image->GetPointIntensity(x+1,y) >  white &&
                    Image->GetPointIntensity(x+2,y) >  white &&
                    Image->GetPointIntensity(x+3,y) >  white &&
                    Image->GetPointIntensity(x+4,y) >  white ){
                    Image->DrawPixel(x, y, 255,255,255);
                }
                if(Image->GetPointIntensity(x,y+1)   > white &&
                        Image->GetPointIntensity(x+1,y)   > white &&
                        Image->GetPointIntensity(x+1,y+1) > white){
                   //Image->DrawPixel(x, y, 255,255,255);
                }*/
               // else
                    //cout<<"\nLOL "<<i;
            }
            /*
            baz[0][1] = Image->GetPointIntensity(x+1,y);
            baz[0][2] = Image->GetPointIntensity(x+2,y);

            baz[1][0] = Image->GetPointIntensity(x,y+1);
            baz[2][0] = Image->GetPointIntensity(x,y+2);
            */

        }
    }

// **********************************************************************
//  void ConvertBlackAndWhite()
//
//
// **********************************************************************
void ConvertBlackAndWhite2()
{
    // Tarefa 1:
    //  Mude o valor do LIMIAR para números pequenos como 5 ou 10

	unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Iniciou Black & White....";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    int loop = 0;
    int next_left,next_up;
    //Parte 1, white to black
    for(x=0;x<Image->SizeX()-5;x++)
    {
        for(y=0;y<Image->SizeY()-5;y++)
        {
            i = Image->GetPointIntensity(x,y);
			//Image->ReadPixel(x,y,r,g,b);

            // printf("Intens Fora: %5d\n",i);

            if(i < LIMIAR&&
               Image->GetPointIntensity(x+1,y)< LIMIAR&&
               Image->GetPointIntensity(x+2,y)< LIMIAR&&
               Image->GetPointIntensity(x+3,y)< LIMIAR&&
               Image->GetPointIntensity(x+4,y)< LIMIAR&&
               Image->GetPointIntensity(x+5,y)< LIMIAR&&

               Image->GetPointIntensity(x+1,y+1)< LIMIAR&&
               Image->GetPointIntensity(x+2,y+2)< LIMIAR&&
               Image->GetPointIntensity(x+3,y+3)< LIMIAR&&
               Image->GetPointIntensity(x+4,y+4)< LIMIAR&&
               Image->GetPointIntensity(x+5,y+5)< LIMIAR&&

               Image->GetPointIntensity(x,y+1)< LIMIAR&&
               Image->GetPointIntensity(x,y+2)< LIMIAR&&
               Image->GetPointIntensity(x,y+3)< LIMIAR&&
               Image->GetPointIntensity(x,y+4)< LIMIAR&&
               Image->GetPointIntensity(x,y+5)< LIMIAR){
                    Image->DrawPixel(x, y,0,0,255);
               }

/*
            if (i < LIMIAR)
            {
                Image->DrawPixel(x, y,255,0,255);
            }
*/			else{
                Image->DrawPixel(x, y, 0,0,0);
			}
        }
    }
        //refina();
            cout << "Concluiu Magic.\n";

    }


void Numero2()
{
	unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Tirando marcas de metal...";
    //Parte 1, white to black
    for(x=0;x<Image->SizeX()-2;x++)
    {
        for(y=0;y<Image->SizeY()-2;y++)
        {
            i = Image->GetPointIntensity(x,y);
            int up = Image->GetPointIntensity(x,y+1);
            int up2 = Image->GetPointIntensity(x,y+2);
            int left = Image->GetPointIntensity(x+1,y);
            int left2 = Image->GetPointIntensity(x+2,y);
            int corner = Image->GetPointIntensity(x+1,y+1);
            int corner21 = Image->GetPointIntensity(x+2,y+1);
            int corner12 = Image->GetPointIntensity(x+1,y+2);
            int corner2 = Image->GetPointIntensity(x+2,y+2);
            int low = 10;
            int high = 100;
            bool okay=
            up>low       && up<high&&
            up2>low      && up2<high&&
            left>low     && left<high&&
            left2>low    && left2<high&&
            corner>low   && corner<high&&
            corner2>low  && corner2<high&&
            corner12>low && corner12<high&&
            corner21>low && corner21<high;
            // printf("Intens Fora: %5d\n",i);

            int white = 150;
            if(i>low&&i<high){
                    //cout<<i<<"\n";
                    Image->DrawPixel(x, y,255,255,255);
            }
            else {
                if( okay == true){
                    Image->DrawPixel(x, y,255,255,255);
                }
                else{
                    Image->DrawPixel(x,y,0,0,0);
                }
            }
        }
    }
}


void vertical(int valor){
	unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Vertical ...\n";
    // 5 em 5 pixels
    int loop=0, n = valor,white = 0,black = 0,other= 0;

    int    buffer[n];
    //Parte 1, white to black

    for(x=0;x<Image->SizeX();x++)
    {
        for(y=0;y<Image->SizeY()-n;y+=n)
        {
            black = 0;
            white = 0;
            other= 0;
            for(loop = 0; loop<n;loop++){
                int aux = Image->GetPointIntensity(x,y+loop);
                if(aux < 20)
                    black++;
                else if(aux>150)
                    white++;
                else
                    other++;
                buffer[loop] = aux;
            }
            if(white>= n*0.8){
                for(loop = 0; loop<n;loop++){
                    Image->DrawPixel(x,y+loop,255,255,255);
                    //Image->DrawPixel(x,y+loop,0,0,255);
                }
            }
            else{
                for(loop = 0; loop<n;loop++){
                    Image->DrawPixel(x,y+loop,0,0,0);
                    //Image->DrawPixel(x,y+loop,255,0,0);
                }
            }
        }
    }

}

void verticalParte2(int valor){

    unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Vertical Parte 2...\n";
    // quadrado de 9 pixeis

    int low = 20;
    int high = 100;
    int loop=0,loop1=0, n = valor,white = 0,black = 0,other= 0;

    int    buffer[n][n],pos_black[n][n],pos_white[n][n];

    //Parte 1, white to black
    int last_x=0,last_y=0;
    for(x=0;x<=Image->SizeX();x+=n)
    {   last_x=x;
        if((n+x)>Image->SizeX()){
            //n--;
            //x--;
            continue;
        }
        for(y=0;y<=Image->SizeY();y+=n)
        {
            last_y=y;
            if((n+y)>Image->SizeY()){
                //n--;
                //y--;
                continue;
            }
            //Clean Buffer
            for(loop1=0;loop1<n;loop1++){
                for(loop=0;loop<n;loop++){
                    buffer[loop1][loop]=-2;
                }
            }
            black = 0;
            white = 0;
            other = 0;
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){
                    int aux = Image->GetPointIntensity(x+loop1,y+loop);

                        if(aux < low){
                            black++;
                            pos_black[loop1][0] = x+loop1;
                            pos_black[loop1][loop]=y+loop;
                            buffer[loop1][loop] = 0;
                        }
                        //white = -1
                        else if(aux>high){
                            white++;
                            pos_white[loop1][0]=x+loop1;
                            pos_white[loop1][loop]=y+loop;
                            buffer[loop1][loop] = -1;
                        }
                        else if(aux>45 && aux<70){
                            other++;
                            buffer[loop1][loop] = aux;
                        }
                }
            }

            if(other>(n*n)*0.25){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                        Image->DrawPixel(loop1+x,loop+y,255,255,255);
                    }
                }
            }
            else{
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                        Image->DrawPixel(x+loop1,y+loop,0,0,0);
                    }
                }
            }
        }

    }
    cout<<n<<" N \n";
    cout<<Image->SizeX()<<" "<<Image->SizeY()<<"\n";
    cout<<last_x<<" "<<last_y<<"\n";
}


void SobrepoeImage(){
    int x,y;
    int i;
    cout << "\nSobrepoe";
    // quadrado de 9 pixeis
    int loop,n = 100;
    int buffer[n];

    for(x=n;x<Image->SizeX();x++)
    {
        for(y=n;y<Image->SizeY();y++)
        {
            int black = 0;
            int white = 0;
            for(loop = 0;loop<n;loop++){
                int aux = Image->GetPointIntensity(x-loop,y);
                if(aux < 20)
                    black++;
                else if(aux>100)
                    white++;
                buffer[loop] = aux;
            }

            if(black>=n*0.9&&white>=n*0.1){
                for(loop = 0; loop<n;loop++){
                    NovaImagem->DrawPixel(x-loop,y,25,70,200);
                }

            }
            else if (white>=n*0.9){
                for(loop = 0; loop<n;loop++){
                    NovaImagem->DrawPixel(x-loop,y,255,0,0);
                }
            }
        }
    }
}


//OLD
void horizontal(int valor){
	unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Horizontal...";
    // 5 em 5 pixels
    int loop=0, n = valor,white = 0,black = 0,other= 0;

    int    buffer[n];
    //Parte 1, white to black

    for(x=0;x<Image->SizeX()-n;x+=n)
    {
        for(y=0;y<Image->SizeY();y++)
        {
            black = 0;
            white = 0;
            other= 0;
            for(loop = 0; loop<n;loop++){
                int aux = Image->GetPointIntensity(x+loop,y);
                if(aux < 20)
                    black++;
                else if(aux>150)
                    white++;
                else
                    other++;
                buffer[loop] = aux;
            }
            if(white>= n*0.8){
                for(loop = 0; loop<n;loop++){
                    Image->DrawPixel(x+loop,y,255,255,255);
                }
            }
            else{
                for(loop = 0; loop<n;loop++){
                    Image->DrawPixel(x+loop,y,0,0,0);
                }
            }
        }
    }
}
//OLD
void Refina(int valor){
    int x,y;
    int i;
    cout << "Vertical Pinta se tem mais branco do que preto...\n";
    // quadrado de n^2 pixeis
    int loop=0,loop1=0, n = valor,white,black,other;

    int    buffer[n][n];
    int totalPixels = 0;

    bool pintando = false;
    int sequencia = 0;

    //Parte 1, white to black
    for(x=0;x<Image->SizeX()-n;x+=n)
    {
        for(y=0;y<Image->SizeY()-n;y+=n)
        {

            //Clean Buffer
            for(loop1=0;loop1<n;loop1++){
                for(loop=0;loop<n;loop++){
                    buffer[loop1][loop]=-2;
                }
            }
            black = 0;
            white = 0;
            other = 0;
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){

                    int aux = Image->GetPointIntensity(x+loop1,y+loop);
                        //preto
                        if(aux <= 10){
                            black++;
                            buffer[loop1][loop] = 0;
                        }
                        //white
                        else if(aux>150){
                            white++;
                            buffer[loop1][loop] = -1;
                        }
                        //intensidade da dentina
                        else if(aux>42 && aux<100){
                            other++;
                            buffer[loop1][loop] = aux;
                        }
                }
            }
            //se muito branco pinta de preto
            if(white>(n*n)*0.01){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,0,0,0);
                    }
                }
            }
            //se muito others pinta de branco
            else if(other>=(n*n)*0.35){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            totalPixels++;
                            Image->DrawPixel(loop1+x,loop+y,255,255,255);
                    }
                }
            }
            else{
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,0,0,0);
                    }
                }
            }
        }

    }
    cout<<totalPixels<<" pixeis de dentina";

}

void LimpaRuido(int valor){
    int x,y;
    int i;
    cout << "Limpa aquele ruido do fundo...\n";
    // quadrado de n^2 pixeis
    int loop=0,loop1=0, n = valor,white,black,other;

    int    buffer[n][n];
    int    big_buffer_left[n][2*n];
    int    big_buffer_up[2*n][n];
    //Parte 1, white to black

    for(x=0;x<Image->SizeX()-n;x+=2*n)
    {
        for(y=0;y<Image->SizeY()-n;y+=2*n)
        {
            int soma_buffer = 0,soma_big_buffer_up,soma_big_buffer_left=0;

            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){
                    soma_buffer += Image->GetPointIntensity(x+loop1,y+loop);
                }
            }
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<2*n;loop++){
                    soma_big_buffer_left += Image->GetPointIntensity(x+loop1,y+loop);
                }
            }
            for(loop1 = 0;loop1<2*n;loop1++){
                for(loop = 0; loop<n;loop++){
                    soma_big_buffer_up += Image->GetPointIntensity(x+loop1,y+loop);
                }
            }
            if((soma_big_buffer_left==0 || soma_big_buffer_up==0)&&soma_buffer==0)
                continue;
            if(soma_big_buffer_left<= soma_buffer+((2*n)*0.3)*40){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,255,255,255);
                    }
                }
            }
            if(soma_big_buffer_up<= soma_buffer+((2*n)*0.3)*40){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,25,0,150);
                    }
                }
            }

        }
    }
}

void pintaMatrixPreto(int x1,int x2, int y1,int y2){
    int x_range = x1,x_range_final=x2;
    int y_range = y1,y_range_final=y2;
    int r= rand()%255,g=rand()%255,b=rand()%255;

    int totalPixels = 0;
    while(x_range<x_range_final){
        while(y_range<y_range_final){
                //orange change later to white
                NovaImagem->DrawPixel(x_range,y_range,r,g,b);
                //NovaImagem->DrawPixel(x_range,y_range,0,0,0);
                Image->DrawPixel(x_range,y_range,0,0,0);
                totalPixels++;
            y_range++;
        }
        y_range=y1;
        x_range++;
    }
}

void pintaMatrixFundo(int x1,int x2, int y1,int y2){
    unsigned char ra,ga,ba;
    int x_range = x1,x_range_final=x2;
    int y_range = y1,y_range_final=y2;
    int r= rand()%255,g=rand()%255,b=rand()%255;
    int totalPixels = 0;
    while(x_range<x_range_final){
        while(y_range<y_range_final){
                //orange change later to white
                Image->ReadPixel(x_range,y_range,ra,ga,ba);
                if(ra>200&&ga>200&&ba>200){

                }else{
                    //NovaImagem->DrawPixel(x_range,y_range,r,255,0);
                    Image->DrawPixel(x_range,y_range,96,96,96);
                    //NovaImagem->DrawPixel(x_range,y_range,0,0,0);
                    //Image->DrawPixel(x_range,y_range,r,g,b);
                }
                totalPixels++;
            y_range++;
        }
        y_range=y1;
        x_range++;
    }
}

bool MaisBranco(int x1,int x2, int y1,int y2){
    unsigned char r,g,b;
    int total_teste = (x2-x1)*(y2-y1);
    int x_range = x1,x_range_final=x2;
    int y_range = y1,y_range_final=y2;
    int white = 0,total = 0;
    while(x_range<x_range_final){
        //cout<<x_range<<" "<<y_range<<"\n";
        while(y_range<y_range_final){
            Image->ReadPixel(x_range,y_range,r,g,b);
            if(r>200&&g>200&&b>200){
                white++;
            }
            total++;
            //cout<<total<<" \n";
            //cada pixel
            y_range++;
        }
        y_range=y1;
        x_range++;
    }
    //cout<<total<<"total \n";
    //cout<<white<<" white\n";
    if(white == 0){
        return false;
    }
    if(white>= total * 0.3){
        //cout<<"\nx1: "<<x1<<" x2: "<<x2<<" y1: "<<y1<<" y2: "<<y2<<"total: "<<total<<" white: "<<white<<endl;
        //cout<<"Tudo Branco";
        return true;
    }
    return false;
}

int quantidade_Branco(int x1,int x2, int y1,int y2){
    unsigned char r,g,b;
    int x_range = x1,x_range_final=x2;
    int y_range = y1,y_range_final=y2;
    int white = 0,total = 0;
    while(x_range<x_range_final){
        //cout<<x_range<<" "<<y_range<<"\n";
        while(y_range<y_range_final){
            Image->ReadPixel(x_range,y_range,r,g,b);
            if(r>200&&g>200&&b>200){
                white++;
            }
            total++;
            //cout<<total<<" \n";
            //cada pixel
            y_range++;
        }
        y_range=y1;
        x_range++;
    }
    return white;
}

struct areaPintar
{
    int valor;
    int x_range;
    int y_range;
    int x_range_final;
    int y_range_final;

};


void pintaNovaImagem(){
    unsigned char r,g,b;
    int x_range = 0,x_range_final=2000;
    int y_range = 0,y_range_final=2000;
    int totalPixels = 0;
    int dentina = 0 , canal = 0;
    while(x_range<x_range_final){
        while(y_range<y_range_final){
            Image->ReadPixel(x_range,y_range,r,g,b);
            if(Image->GetPointIntensity(x_range,y_range)>200){
                NovaImagem->DrawPixel(x_range,y_range,255,0,0);
                dentina++;
            }
            else if(Image->GetPointIntensity(x_range,y_range)>50){
                Image->ReadPixel(x_range,y_range,r,g,b);
                if(NovaImagem->GetPointIntensity(x_range,y_range)<10){
                    NovaImagem->DrawPixel(x_range,y_range,0,255,0);
                    canal++;
                }
            }
            y_range++;
        }
        y_range=0;
        x_range++;
    }
    cout<<"\nDentina : "<<dentina;
    cout<<"\nCanal: "<<canal;
}

void pintaComMedia(int valor){
    cout<<"\nComecou\n";
    int x_range = 0,x_range_final   = 2000;
    int y_range = 0, y_range_final  = 2000 ;
    int valor_media = 0;
    bool x_fail = false,y_fail=false;
    std::list<areaPintar> pontos;

    int x2=0, y2 = 0;


    while(x_range<=x_range_final){
        if(x_range+valor>=2000&&x_fail==false){
            x2 = 2000;
            x_range = 2000-valor;
            x_fail = true;
        }else{
            if(x_fail==true)
                break;
            x2 = x_range+valor;
        }
        while(y_range<=y_range_final){
            if(y_range+valor>=2000&&y_fail==false){
                y2 = 2000;
                y_range=2000-valor;
                y_fail=true;
            }else{
                if(y_fail==true)
                    break;
                y2 = y_range+valor;
            }
            int porcento = (valor*valor);
            bool mediaBranco = MaisBranco(x_range,x2,y_range,y2);
            if(mediaBranco == false){
                //cout<<x_range << " "<<y_range << " \n";
                areaPintar aux;
                aux.x_range=x_range;
                aux.x_range_final=x2;
                aux.y_range=y_range;
                aux.y_range_final=y2;
                pontos.push_back(aux);
                //pintaMatrixPreto(valor,x_range,x2,y_range,y2);
            }
            y_range+=valor;
        }
        y_range=0;
        y_fail=false;
        x_range+=valor;
    }

     cout<<"Acabou algoritimo\n";
     cout<<"Comecou a pintar algoritimo\n";
     std::list<areaPintar>::iterator it;
     for(it = pontos.begin(); it != pontos.end(); it++) {
        pintaMatrixPreto(it->x_range,it->x_range_final,it->y_range,it->y_range_final);
    }


}


std::list<areaPintar> pontos;

void pintaRecursivo(int x1,int x2, int y1,int y2){

    if((x2-x1)<=70&&(y2-y1)<=70){
        if(MaisBranco(x1,x2,y1,y2)==false)
        {
            pintaMatrixPreto(x1,x2,y1,y2);
        }
        return;
    }
    //cout<<"\nx1 "<<x1<<" x2 "<<x2<<"y1 "<<y1<<" y2 "<<y2;
    //1 ->  0 1000 0 1000
    pintaRecursivo(x1,(x2+x1)/2,y1,(y2+y1)/2);

    //2-> 1000 2000 0 1000
    pintaRecursivo((x1+x2)/2,x2,y1,(y2+y1)/2);
    //3-> 1000 2000 1000 2000
    pintaRecursivo((x1+x2)/2,x2,(y2+y1)/2,y2);

    //4->0 1000 1000 2000
    pintaRecursivo(x1,(x2+x1)/2,(y1+y2)/2,y2);

}


void pintaFundoRecursivo(int x1,int x2, int y1,int y2){

    int varia_x = x2-x1, varia_y = y2-y1;

    if(varia_x<=500&&varia_y<=500){
        int white = quantidade_Branco(x1,x2,y1,y2);
        if(white<(varia_y*varia_y)*0.9 && white > 0)
        {
            pintaMatrixFundo(x1,x2,y1,y2);
        }
        return;
    }
    //cout<<"\nx1 "<<x1<<" x2 "<<x2<<"y1 "<<y1<<" y2 "<<y2;
    //1 ->  0 1000 0 1000
    pintaFundoRecursivo(x1,(x2+x1)/2,y1,(y2+y1)/2);

    //2-> 1000 2000 0 1000
    pintaFundoRecursivo((x1+x2)/2,x2,y1,(y2+y1)/2);
    //3-> 1000 2000 1000 2000
    pintaFundoRecursivo((x1+x2)/2,x2,(y2+y1)/2,y2);

    //4->0 1000 1000 2000
    pintaFundoRecursivo(x1,(x2+x1)/2,(y1+y2)/2,y2);

}

void FiltroDeMediana(int valor){
    int x,y;
    int i;
    cout << "Filtro de Mediana\n";

    // quadrado de n^2 pixeis
    int loop=0,loop1=0, n = valor;

    int    buffer[n][n];
    int    buffer2array[n*n];
    //Fill Buffer

    for(x=0;x<Image->SizeX()-n;x+=n)
    {
        for(y=0;y<Image->SizeY()-n;y+=n)
        {
            int mediana = 0;
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){

                    buffer[loop1][loop] = Image->GetPointIntensity(x+loop1,y+loop);
                }
            }
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){
                    buffer2array[loop1*n + loop] = buffer[loop1][loop];
                }
            }

            BubbleSort(buffer2array,n*n);

            mediana += buffer2array[(n*n)/2];
            if(n*n%2==0){
                mediana += buffer2array[((n*n)/2)+1];
            }
            else
                mediana += buffer2array[(n*n)/2];

           //Draw pixels with the average
            for(loop1=0;loop1<n;loop1++){
                for(loop=0;loop<n;loop++){
                        Image->DrawPixel(loop1+x,loop+y,mediana,mediana,mediana);
                }
            }
        }
    }

}



void PintaFundoBranco(int valor){
    int x,y;
    int i;
    cout << "Vertical Parte 3...\n";
    // quadrado de 9 pixeis
    int loop=0,loop1=0, n = valor,white = 0,black = 0,other= 0;

    int    buffer[n][n];

    int contador = 0;
    for(x=0;x<Image->SizeX()-n;x+=n)
    {
        for(y=0;y<Image->SizeY()-n;y+=n)
        {

            //Clean Buffer
            for(loop1=0;loop1<n;loop1++){
                for(loop=0;loop<n;loop++){
                    buffer[loop1][loop]=-2;
                }
            }

            black = 0;
            white = 0;
            other= 0;
            for(loop1 = 0;loop1<n;loop1++){
                for(loop = 0; loop<n;loop++){

                    int aux = Image->GetPointIntensity(x+loop1,y+loop);

                        if(aux < 40){
                            black++;
                            buffer[loop1][loop] = 0;
                        }
                        //white = -1
                        else if(aux>150){
                            white++;
                            buffer[loop1][loop] = -1;
                        }
                        else{
                            other++;
                            buffer[loop1][loop] = aux;
                        }
                }
            }


            if(white>=(n*n)*0.9){
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,255,255,255);
                    }
                }
            }
            else{
                for(loop1=0;loop1<n;loop1++){
                    for(loop=0;loop<n;loop++){
                            Image->DrawPixel(loop1+x,loop+y,0,0,0);
                    }
                }
            }

        }

    }

}

//OLD
void Numero4(){
    unsigned char r,g,b;
    int x,y;
    int i;
    cout << "Pintando o fundo...";
    //Parte 1, white to black
    for(x=0;x<Image->SizeX()-1;x++)
    {
        for(y=0;y<Image->SizeY()-1;y++)
        {
            i = Image->GetPointIntensity(x,y);
            // printf("Intens Fora: %5d\n",i);
            int low = 70;
            int high = 100;
            int white = 150;
            if(i<low){
                    //cout<<i<<"\n";
                    if(Image->GetPointIntensity(x+1,y)>low&&
                       Image->GetPointIntensity(x+1,y+1)>low&&
                       Image->GetPointIntensity(x,y+1)>low)
                        Image->DrawPixel(x, y,96,96,96);
                    else
                        Image->DrawPixel(x, y,255,255,255);
            }
        }
    }
}

void Pos_Refinamento()
{
    int x,y;
    int i;
    cout << "Pos refinamento....";
    //NovaImagem->DrawPixel(20, 1,100,255,0,0 );
    //Parte 1, white to black
    for(x=0;x<Image->SizeX();x++)
    {
        for(y=0;y<Image->SizeY();y++)
        {
            i = Image->GetPointIntensity(x,y);
			//Image->ReadPixel(x,y,r,g,b);

            // printf("Intens Fora: %5d\n",i);
            if (i>160)
            {
                Image->DrawPixel(x, y,255,255,255);
            }

			else{
                Image->DrawPixel(x, y, 0,0,0);

			}
        }
    }
        //refina();
            cout << "Concluiu Magic.\n";

}

void pintaInterior(){
    unsigned char r,g,b;
    unsigned char r_fundo=20,g_fundo=150,b_fundo=20;

    int x,y;
    int i;
    cout << "\nSobrepoe";
    // quadrado de 9 pixeis
    int loop,loop2,n = 4,m=10;
    int buffer[n][m];
    int x_red,y_red;
    int x_red_final,y__final;
    bool pode_pintar = false,pintando=false;

    for(x=0;x<Image->SizeX();x++)
    {
        for(y=0;y<Image->SizeY();y++)
        {
                Image->ReadPixel(x,y,r,g,b);
                    if(r==255&&g==255&&b==255){
                        if(pintando== false)
                        {
                            pode_pintar= true;
                            x_red = x - loop;
                            y_red = y;
                        }
                    }
                    if(r<10&&g<10&&b<10){
                        if(pode_pintar==true){
                            pintando = true;
                            x_red_final =  x - loop;
                            y__final = y;
                        }
                    }
                    Image->DrawLineV(x_red,y_red,y__final,r_fundo,g_fundo,b_fundo);

        }
    }
}
// **********************************************************************
//  void init(void)
//  Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void)
{

    Image = new ImageClass();
    int r;

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // Fundo de tela preto

    r = Image->Load("775.png");


    if (!r){
        cout << ("Imagem nao foi carregada!\n");
        exit(1);
    }

    else
        cout << ("Imagem carregada!\n");

    // Instacia o objeto que irá exibir a nova imagem
    // Caso precise alterar o tamanho da nova imagem, mude os parâmetros
    // da construtura, na chamada abaixo
    NovaImagem = new ImageClass(Image->SizeX(), Image->SizeY(), Image->Channels());
    NovaImagem->Load("775.png");
}

// **********************************************************************
//  void reshape( int w, int h )
//  trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    gluOrtho2D(0,w,0,h);

    // Set the clipping volume
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}
// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
// Ajusta o ZOOM da imagem para que apareca na metade da janela
    float zoomH = (glutGet(GLUT_WINDOW_WIDTH)/2.0)/Image->SizeX();
    float zoomV = (glutGet(GLUT_WINDOW_HEIGHT)/2.0)/Image->SizeY();
    Image->SetZoomH(zoomH);
    Image->SetZoomV(zoomV);

// posiciona a imagem nova na metada da direita da janela
    NovaImagem->SetPos(glutGet(GLUT_WINDOW_WIDTH)/2, 0);

// Ajusta o ZOOM da imagem para que apareca na metade da janela
    NovaImagem->SetZoomH(zoomH);
    NovaImagem->SetZoomV(zoomV);

// Desenha uma Linha Vermelha
    //Image->DrawLine(0,0,1000,1000, 255,0,0);
// Coloca as imagens na tela
    Image->Display();
    NovaImagem->Display();

// Mostra a tela OpenGL
    glutSwapBuffers();
}


// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
    switch ( key )
    {
        case 27: // Termina o programa qdo  a tecla ESC for pressionada
            NovaImagem->Delete();
            Image->Delete();
            exit ( 0 );
        break;

        case 'a':
            init();
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case 't':
            vertical(20);
            horizontal(20);
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case 'y':
            verticalParte2(40);
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case 'c':
            //SobrepoeImage();
            cout<<"\nComecou";
            pintaFundoRecursivo(0,2000,0,2000);
            cout<<"\nAcabou";
            //pintaInterior();
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case 'x':
            //SobrepoeImage();
            cout<<"\nPintando nova imagem";
            pintaNovaImagem();
            //cout<<"Acabou";
            //pintaInterior();
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case '1':
            //antigo
            PintaFundoBranco(100);
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case '4':
            Refina(20);
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        /*Lixo hahaha nao adiantou muito*/
        case '5':
            //FiltroDeMedia(4);
            //FiltroDeMediana(25);
            pintaComMedia(20);
            //LimpaRuido(25);
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        case 'z':
            cout<<"\nComecou";
            pintaRecursivo(0,2000,0,2000);
            cout<<"\nAcabou";
            glutPostRedisplay();    // obrigatório para redesenhar a tela
        break;
        default:
        break;
    }
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
    switch ( a_keys )
    {
        case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
        break;
        case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...

        break;
        default:
        break;
    }
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{
    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (10,10);

    // Define o tamanho da janela gráfica do programa
    glutInitWindowSize  ( LARGURA_JAN, ALTURA_JAN);
    glutCreateWindow    ( "Image Loader" );

    init ();

    glutDisplayFunc ( display );
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    //glutIdleFunc ( display );

    glutMainLoop ( );

    cout << "FIM" << endl;

    return 0;
}


