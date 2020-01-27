#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

int mx=4;
float my=1.1;
int szer=440,wys=540;
int szerGl=400, wysGl=400;

int step=0,rys=0;

extern void krok();
extern void zaznacz();

extern void osobniki();

LRESULT CALLBACK obsluga_kom (HWND,UINT,WPARAM,LPARAM);
void Render();

static HDC hdc;
static HGLRC hrc;
HWND hwnd,anim_hwnd,pocz_hwnd, area_hwnd;
UINT timer;

int anim=0;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,PSTR szCmdLine,int iCmdShow)
{
	MSG msg;

 WNDCLASS okno;
 okno.style=CS_HREDRAW | CS_VREDRAW;
 okno.cbClsExtra		= 0;
 okno.cbWndExtra		= 0;
 okno.hInstance		= hInstance;
 okno.hIcon			= LoadIcon(NULL,IDI_APPLICATION);
 okno.hCursor		= LoadCursor(NULL,IDC_ARROW);
 okno.hbrBackground  =(HBRUSH)(COLOR_BTNFACE+1);
 okno.lpszMenuName	= NULL;     // wska¿nik do menu okna
 okno.lpfnWndProc=obsluga_kom;
 okno.lpszClassName="okienko";

 if(!RegisterClass(&okno)){
			MessageBox(NULL,"Nie uda³o siê zarejestrowaæ klasy okna","B£¥D",MB_ICONERROR);
		}

 hwnd=CreateWindow(	"okienko",     					//nazwa klasy okna
						"Ekstremum funkcji",                      //nag³ówek okna
						WS_OVERLAPPEDWINDOW,            // styl okna
						CW_USEDEFAULT,CW_USEDEFAULT,  // pocz¹tkowa pozycja x,y
						szer,wys,  // pocz¹tkowy rozmiar x,y
						NULL,                           // uchwyt okna nadrzêdnego
						NULL,                           // uchwyt menu okna
						hInstance,                      // uchwyt kopii programu
						NULL);                          // parametry tworzenia


	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        Render();
    }

	return msg.wParam;
}

void SetDCPixelFormat( HDC hDC )
{
    int nPixelFormat;

    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof( PIXELFORMATDESCRIPTOR ),  // struct size
        1,                                // struct version
        PFD_DRAW_TO_WINDOW |              // drawing in window
        PFD_SUPPORT_OPENGL |              // support OpenGL
        PFD_DOUBLEBUFFER,                 // double buffering
        PFD_TYPE_RGBA,                    // RGBA color mode
        8,                                // 8 - bit color mode
        0,0,0,0,0,0,                      // not used to chooose mode
        0,0,                              // not used to chooose mode
        0,0,0,0,0,                        // not used to chooose mode
        16,                               // size of depth buffer
        0,                                // not used to chooose mode
        0,                                // not used to chooose mode
        PFD_MAIN_PLANE,                   // draw on main plane
        0,                                // not used to chooose mode
        0,0,0                             // not used to chooose mode
    };

    nPixelFormat = ChoosePixelFormat( hDC, &pfd );
    SetPixelFormat( hDC, nPixelFormat, &pfd );
}



LRESULT CALLBACK obsluga_kom(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
static PAINTSTRUCT ps;


	switch(message)
	{
		case WM_CREATE:
  
               CreateWindow("BUTTON", "Ruch +1",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,
                     10,10,70,22,
                     (HWND)hwnd,(HMENU)101,
                     GetModuleHandle(NULL),NULL);
               CreateWindow("BUTTON", "Ruch +10",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,
                     10,35,70,22,
                     (HWND)hwnd,(HMENU)102,
                     GetModuleHandle(NULL),NULL);
     anim_hwnd=CreateWindow("BUTTON", "Animuj",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,
                     10,60,70,22,
                     (HWND)hwnd,(HMENU)106,
                     GetModuleHandle(NULL),NULL);
               CreateWindow("BUTTON", "Reset",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,
                     szer-90,10,70,22,
                     (HWND)hwnd,(HMENU)105,
                     GetModuleHandle(NULL),NULL);
               CreateWindow("BUTTON", "Wartoœci",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE,
                     szer-90,35,70,22,
                     (HWND)hwnd,(HMENU)104,
                     GetModuleHandle(NULL),NULL);
     pocz_hwnd=CreateWindow("EDIT","0.5",
                     ES_RIGHT | WS_CHILD |WS_VISIBLE|WS_BORDER,
                     250,10,50,17,
                     (HWND)hwnd,(HMENU)200,
                     GetModuleHandle(NULL),NULL);
               CreateWindow("EDIT","Wartoœæ pocz¹tkowa :",
                     ES_RIGHT | WS_CHILD |WS_VISIBLE|WS_BORDER|WS_DISABLED,
                     90,10,150,17,
                     (HWND)hwnd,(HMENU)200,
                     GetModuleHandle(NULL),NULL);
               CreateWindow("BUTTON", "Tylko aktualna iteracja",
                     BS_PUSHBUTTON|WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
                     90,35,170,22,
                     (HWND)hwnd,(HMENU)210,
                     GetModuleHandle(NULL),NULL);
            area_hwnd=CreateWindow("BUTTON", "",
            		WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
                     10,90,szerGl,wysGl,
                     (HWND)hwnd,NULL,
					 GetModuleHandle(NULL),NULL);



        hdc = GetDC( area_hwnd );
        SetDCPixelFormat( hdc );
        hrc = wglCreateContext( hdc );
        wglMakeCurrent( hdc, hrc );
        break;

        case WM_CLOSE:
          wglMakeCurrent(hdc, NULL);
          wglDeleteContext(hrc);
          PostQuitMessage(0);
        break;

		case WM_PAINT:
        	BeginPaint(hwnd,&ps);

    		EndPaint(hwnd,&ps);
        break;

		case WM_DESTROY:
          wglMakeCurrent(hdc, NULL);
          KillTimer(hwnd,timer);
          wglDeleteContext(hrc);
          PostQuitMessage(0);
        break;
        case WM_TIMER:
            krok();
        break;
        case WM_COMMAND:
        switch(LOWORD(wParam))
        {

            case 101:
                krok();
            break;
            case 102:
               for(int i=0;i<10;i++)
                krok();
            break;
            case 104:
                osobniki();
            break;
            case 105:
                 step=0;
            break;
            case 106:
               if(anim==0)
                {
                 anim=1;
                 SetTimer(hwnd,timer,500,NULL);
                 SetWindowText(anim_hwnd,"Stop");
                }
                else
                {
                 anim=0;
                 KillTimer(hwnd,timer);
                 SetWindowText(anim_hwnd,"Animuj");
                }
            break;
            case 210:
             rys=rys?0:1;
            break;
            }
        break;


 default: return DefWindowProc(hwnd,message,wParam,lParam);
 }
}

void Render()
{
float i,j;
    glViewport(0,0,szerGl,wysGl);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, mx+1,0, my );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_LINES);
     glVertex3f(-1.0f,0.0f,0.0f);
     glVertex3f(mx+1,0.0f,0.0f);
    glEnd();

    glColor3f(1.0f,0.0f,0.0f);

    zaznacz();

    glFlush();
    SwapBuffers(hdc);
}
