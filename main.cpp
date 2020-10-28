/*#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE*/
//#endif
#include<iostream>
#include<fstream>
#include <tchar.h>
#include <windows.h>

using namespace std;
ifstream in("date.in");
ofstream out("date.out");
int verif;

struct nod
{
    char info[100],autor[100], an[10];
    int nr;
    nod *ant, *urm;
};
nod *start,*fin;
char c[100],c2[100],w[1000000],c3[10];
int load,id;
////////////////////////////////////////////////////////////////////////////////

void creare(char d[100],char d2[100],int x,nod *&p,nod *&ultim,char y[10])
{
    if(p==NULL)
    {
        p=new nod;
        p->ant=NULL;
        p->urm=NULL;
        strcpy(p->info,d);
        strcpy(p->autor,d2);
        strcpy(p->an,y);
        p->nr=x;
        ultim=p;
    }
    else
    {
        nod *r;
        r=new nod;
        ultim->urm=r;
        r->ant=ultim;
        r->urm=NULL;
        strcpy(r->info,d);
        strcpy(r->autor,d2);
        r->nr=x;
        strcpy(r->an,y);
        ultim=r;
    }


}

void sortare(nod *prim)
{

    char aux[104];
    for(nod *i =prim; i->urm; i=i->urm)
        for(nod *j=i->urm; j; j=j->urm)
        {
            if(strcmp(i->info,j->info)>0)
            {
                strcpy( aux,i->info);
                strcpy(i->info,j->info);
                strcpy(j->info,aux);
                strcpy( aux,i->autor);
                strcpy(i->autor,j->autor);
                strcpy(j->autor,aux);
                strcpy( aux,i->an);
                strcpy(i->an,j->an);
                strcpy(j->an,aux);
                swap(i->nr,j->nr);
            }

        }
}
int stergere(nod *aux,char w[100])
{

    while(aux!=NULL)
    {
        if(strcmp(aux->info,w)==NULL)
        {

            nod *r=aux;
            aux->ant->urm=r->urm;
            if(aux->urm!=NULL)   aux->urm->ant=r->ant;
            delete r;
            return 1;
        }
        aux=aux->urm;
    }
    return 0;
}

void copiere(char fis1[30],char fis2[30],int x)
{

    char s[100];
    ifstream inq(fis1);
    ofstream outq(fis2);
    inq>>x;
    outq<<x<<endl;
    inq.get();
    while(inq.get(s,100))
    {
        outq<<s<<endl;
        inq.get();
    }
    inq.close();
    outq.close();

}

void caz2()
{
    in>>load;
    int y,i;
    char q[100],q2[100],q3[10];
    id=load+1;
    in>>y;
    in.get();
    in.get(q,200);
    in.get();
    in.get(q2,200);
    in.get();
    in.get(q3,200);
    in.get();

    creare(q,q2,y,start,fin,q3);
    strcpy(w,q);
    strcat(w," de ");
    strcat(w,q2);
    strcat(w," - ");
    strcat(w,q3);
    strcat(w,"\r\n");
    for(i=2; i<=load; i++)
    {
        in>>y;
        in.get();
        in.get(q,200);
        in.get();
        in.get(q2,200);
        in.get();
        in.get(q3,200);
        in.get();
        creare(q,q2,y,start,fin,q3);
        strcat(w,q);
        strcat(w," de ");
        strcat(w,q2);
        strcat(w," - ");
        strcat(w,q3);
        strcat(w,"\r\n");
    }
    sortare(start);
}
void reactualizare()
{
    nod *r;
    r=start;
    strcpy(w,start->info);
    while(r!=NULL)
    {
        if(r==start)
            strcpy(w,start->info);
        else strcat(w,r->info);
        strcat(w," de ");
        strcat(w,r->autor);
        strcat(w," - ");
        strcat(w,r->an);
        strcat(w,"\r\n");
        r=r->urm;
    }

}

//////////////////////////////////////////////////////////////////////////////



HWND adauga,adauga2,sterge,hOut,hOut2,sort_autor,sort_an,adauga3;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HWND textfield, button,button2, button3,button4;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Colectia mea"),       /* Title Text */
               WS_SYSMENU, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1100,                 /* The programs width */
               650,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:

        textfield=CreateWindow("STATIC", "Colectia mea",WS_VISIBLE | WS_CHILD | WS_BORDER, 388,30, 90,20,hwnd,NULL,NULL,NULL);

        button2=CreateWindow("BUTTON","VIZUALIZEAZA COLECTIA",WS_VISIBLE | WS_CHILD| WS_BORDER, 750,100,175,25,hwnd,(HMENU) 2,NULL,NULL);

        button4=CreateWindow("BUTTON","SALVEAZA",WS_VISIBLE | WS_CHILD| WS_BORDER, 120,100,80,25,hwnd,(HMENU) 4,NULL,NULL);


        adauga=CreateWindow("EDIT","Scrie titlul nou",WS_BORDER|WS_CHILD|WS_VISIBLE,20,220,220,20,hwnd,NULL,NULL,NULL);
        adauga2=CreateWindow("EDIT","Scrie numele autorului",WS_BORDER|WS_CHILD|WS_VISIBLE,240,220,200,20,hwnd,NULL,NULL,NULL);
        adauga3=CreateWindow("EDIT","Anul",WS_BORDER|WS_CHILD|WS_VISIBLE,440,220,40,20,hwnd,NULL,NULL,NULL);
        CreateWindow("BUTTON","Adauga",WS_VISIBLE|WS_CHILD|WS_BORDER,480,220,70,20,hwnd,(HMENU) 1,NULL,NULL);

        sort_autor=CreateWindow("EDIT","Filtreaza cartile dupa un autor",WS_BORDER|WS_CHILD|WS_VISIBLE,20,430,420,20,hwnd,NULL,NULL,NULL);
        sort_an=CreateWindow("EDIT","Filtreaza cartile dupa anul aparitiei",WS_BORDER|WS_CHILD|WS_VISIBLE,20,450,420,20,hwnd,NULL,NULL,NULL);
        CreateWindow("BUTTON","Ok",WS_VISIBLE|WS_CHILD|WS_BORDER,440,430,70,20,hwnd,(HMENU) 5,NULL,NULL);
        CreateWindow("BUTTON","Ok",WS_VISIBLE|WS_CHILD|WS_BORDER,440,450,70,20,hwnd,(HMENU) 6,NULL,NULL);

        sterge=CreateWindow("EDIT","Scrie titlul pe care vrei sa-l stergi",WS_BORDER|WS_CHILD|WS_VISIBLE,20,240,420,20,hwnd,NULL,NULL,NULL);
        CreateWindow("BUTTON","Sterge",WS_VISIBLE|WS_CHILD|WS_BORDER,440,240,70,20,hwnd,(HMENU) 3,NULL,NULL);
        hOut=CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE|WS_HSCROLL|WS_VSCROLL, 620,150, 450,200,hwnd,NULL,NULL,NULL);
        hOut2=CreateWindow("EDIT", "",WS_VISIBLE | WS_CHILD | WS_BORDER|ES_AUTOVSCROLL|ES_MULTILINE|WS_HSCROLL|WS_VSCROLL, 620,370, 450,200,hwnd,NULL,NULL,NULL);
        break;


    case WM_COMMAND:

        switch(LOWORD(wParam))
        {


        case 1:


            ::MessageBeep(MB_ICONASTERISK);
            ::MessageBox(hwnd,"Titlul a fost adaugat!","Adauga",MB_OK);
            int g,g2,g3 ;
            g=GetWindowText(adauga,&c[0],100);
            g2=GetWindowText(adauga2,&c2[0],100);
            g3=GetWindowText(adauga3,&c3[0],100);
            creare(c,c2,id,start,fin,c3);
            id++;
            sortare(start);
            reactualizare();
            SetWindowText(hOut,w );
            break;

        case 2:
            verif=1;
            caz2();

            SetWindowText(hOut,w );

            ::MessageBox(hwnd,"Aceasta este colectia ta de pana acum!","Vizualizeaza",MB_OK);
            break;

        case 3:

            int de ;
            de=GetWindowText(sterge,&c[0],200);
            ::MessageBeep(MB_ICONASTERISK);

            if(strcmp(start->info,c)==NULL)
            {
                id--;
                nod *copie=start;
                start=start->urm;
                delete copie;
                ::MessageBox(hwnd,"Titlul a fost sters!","Stergere",MB_OK);
                reactualizare();
                SetWindowText(hOut,w );
            }
            else if( stergere(start,c)==1)

            {
                id--;

                ::MessageBox(hwnd,"Titlul a fost sters!","Stergere",MB_OK);
                reactualizare();
                SetWindowText(hOut,w );
            }
            else
                ::MessageBox(hwnd,"Titlul nu a fost gasit in lista pentru a fi sters!","Stergere",MB_OK);

            break;

        case 4:
            nod *load1,*load2;

            if(start!=NULL)
            {
                load1=start;
                load2=fin;
                if(verif==1)
                    out<<id-1<<endl;
                else out<<id<<endl;
                while(load1!=load2->urm)
                {
                    out<<load1->nr<<endl<<load1->info<<endl<<load1->autor<<endl<<load1->an<<endl;
                    load1=load1->urm;
                }
            }


            copiere("date.out","date.in",load);

            PostQuitMessage (0);


            break;


        case 5:

            nod *r1;
            GetWindowText(sort_autor,&c[0],100);
            r1=start;
            char text[10000];
            int ok2;
            ok2=1;
            while(r1!=NULL)
            {
                if(strcmp(r1->autor,c)==NULL)
                {
                    if(ok2==1)
                    {
                        strcpy(text,r1->info);
                        ok2=0;
                    }
                    else strcat(text,r1->info);
                    strcat(text,"\r\n");
                }
                r1=r1->urm;
            }



            SetWindowText(hOut2,text);

            break;

        case 6:

            nod *r2;
            GetWindowText(sort_an,&c[0],100);
            r2=start;
            char text2[10000];
            int ok3=1;
            while(r2!=NULL)
            {
                if(strcmp(r2->an,c)==NULL)
                {
                    if(ok3==1)
                    {
                        strcpy(text2,r2->info);
                        ok3=0;
                    }
                    else strcat(text2,r2->info);
                    strcat(text2,"\r\n");
                }
                r2=r2->urm;
            }
            SetWindowText(hOut2,text2);
            break;

        }
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

