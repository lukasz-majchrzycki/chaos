#include <windows.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>

extern int mx,my;
extern HWND hwnd,pocz_hwnd;
extern int step,rys;

const double dt=0.001;
const double ile=mx/dt;    //400

const int maxp=30;

double pocz=0.5;

double T[4000][30];

void first()
{
int i;
char str[10];
GetWindowText(pocz_hwnd,str,GetWindowTextLength(pocz_hwnd)+1);
pocz=atof(str);

 for(i=0;i<ile;i++)
  T[i][0]=pocz;

}

void krok()
{
 if(step!=0)
 {
 if(step>=maxp) {
                 SendMessage(hwnd,WM_COMMAND,106,0);
                 return;
                }
 int i;
 double j;

  for(i=0,j=dt;i<ile;i++,j+=dt)
   T[i][step]=j*T[i][step-1]*(1.0-T[i][step-1]);

 }
 else first();

 step++;
}


void zaznacz()
{
int i,k,kp;
double j;

if(rys) kp=step-1;
else kp=1;
 for(k=kp;k<step;k++)
 {
 glBegin(GL_LINE_STRIP);
  for(i=0,j=dt;i<ile;i++,j+=dt)
  {

    if(2*k/maxp<0.5)
     glColor3f(1.0f,(float)2*k/maxp,0.0f);
    else
     glColor3f(0.0f,(float)2*k/maxp,0.0f);

     glVertex3f(j,T[i][k],0.0f);
   }
   glEnd();
  }

}

void osobniki()
{
char str[500];
   sprintf(str,"x=%f\ty=%f",0.0,T[0][step-1]);
   for(int i=40;i<ile;i+=400)
    sprintf(str,"%s\nx=%f\ty=%f",str,i*dt,T[i][step-1]);

   MessageBox(NULL, str , "Chaos",MB_OK);
}
