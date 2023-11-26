#include "framework.h"
#include "WindowsProject3.h"
#include"targetver.h"
#include <fstream>
#include <CommDlg.h>
#include <cwchar>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

struct comprador {
    char comName[10];
    char password[10];
    char tel[10];
    char compras[10][160];

}Comprador;

struct eventosS {
    char eventname[40];
    char tipoevento[40];
    int precio;
    int mes;
    int dia;

}Eventos[10];

char Ceventname[40];
char Ctipoevento[40];
int Cprecio;
int Cmes;
int Cdia;

int index;
int rep = 0;

char arch_citas[] = "Citas.dat";
char mensaje[50] = { 0 };
char nombrearchivo[MAX_PATH] = { 0 };
bool _login = true;
char arch_VET[]="VET.dat";
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


INT_PTR CALLBACK sesion(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK eventos(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK venta(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK miscompras(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId){

            case PESTANA_EVENTOS:

                if (_login) {
                    DialogBox(hInst, MAKEINTRESOURCE(PT_EVENTOS), hWnd, eventos);
                }
                else
                {
                    MessageBox(0, "Debe conectarse primero", "ERROR",
                        MB_ICONEXCLAMATION + MB_OK);
                }
                break;

            case PESTANA_MISCOMPRAS:    
                DialogBox(hInst, MAKEINTRESOURCE(PT_MISCOMPRAS), hWnd, miscompras);
                break;

            case PESTANA_PERFIL:    
                DialogBox(hInst, MAKEINTRESOURCE(PT_INICIOSESION), hWnd, sesion);
                break;  

            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK sesion(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    HWND hnomb = GetDlgItem(hDlg, NOMBRE_PTIC);
    HWND hcontra = GetDlgItem(hDlg, CONTRASENA_PTIC);
    HWND htel = GetDlgItem(hDlg, TELEFONO_PTIC);
    HWND hconfirm = GetDlgItem(hDlg, BTN_INGRESAR_PTIC);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        

    case WM_COMMAND: {

        if (LOWORD(wParam) == BTN_INGRESAR_PTIC) {
            char nombre[10];
            char contrasena[10];
            char telefono[10];

            int nlength = GetWindowTextLength(hnomb);
            GetWindowText(hnomb, nombre, nlength + 1);

            int clength = GetWindowTextLength(hcontra);
            GetWindowText(hcontra, contrasena, clength + 1);

            int tlength = GetWindowTextLength(htel);
            GetWindowText(htel, telefono, tlength + 1);
           
            strcpy(Comprador.comName, nombre);
            strcpy(Comprador.password, contrasena);
            strcpy(Comprador.tel, telefono);

            MessageBox(NULL, "Ha sido dado de alta en nuestra página", "TICKET NOOB", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));

        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));

        }

    }

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK eventos(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    if (LOWORD(wParam) == LIST_EVENTOS && HIWORD(wParam) == LBN_SELCHANGE) {
        int index = SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, 0, 0);
        if (index != LB_ERR) {
            SetDlgItemText(hDlg, NOMBRE_PTE, Eventos[index].eventname);
            SetDlgItemText(hDlg, TIPOEVENTO_PTE, Eventos[index].tipoevento);

            char precioStr[10];
            sprintf(precioStr, "%d", Eventos[index].precio);
            SetDlgItemText(hDlg, PRECIO_PTE, precioStr);

            char diaStr[3];
            sprintf(diaStr, "%d", Eventos[index].dia);
            SetDlgItemText(hDlg, DIA_PTE, diaStr);


            strcpy(Ctipoevento, Eventos[index].tipoevento);
            Cprecio = Eventos[index].precio;
            Cmes = Eventos[index].mes;
            Cdia = Eventos[index].dia;

            
        }
    }

    strcpy(Eventos[0].eventname, "Edipo Rey");
    strcpy(Eventos[0].tipoevento, "Obra Teatral");
    Eventos[0].precio = 450;
    Eventos[0].mes = 11;
    Eventos[0].dia = 27;

    strcpy(Eventos[1].eventname, "RPM. Franco Escamilla");
    strcpy(Eventos[1].tipoevento, "Stand Up");
    Eventos[1].precio = 750;
    Eventos[1].mes = 11;
    Eventos[1].dia = 29;

    strcpy(Eventos[2].eventname, "Luis Miguel");
    strcpy(Eventos[2].tipoevento, "Concierto");
    Eventos[2].precio = 1500;
    Eventos[2].mes = 11;
    Eventos[2].dia = 31;

    strcpy(Eventos[3].eventname, "Martin O´Donell");
    strcpy(Eventos[3].tipoevento, "Concierto");
    Eventos[3].precio = 800;
    Eventos[3].mes = 12;
    Eventos[3].dia = 1;

    strcpy(Eventos[4].eventname, "Michael Salvatori");
    strcpy(Eventos[4].tipoevento, "Concierto");
    Eventos[4].precio = 800;
    Eventos[4].mes = 12;
    Eventos[4].dia = 2;

    strcpy(Eventos[5].eventname, "El Fantasma de la Opera");
    strcpy(Eventos[5].tipoevento, "Obra Teatral");
    Eventos[5].precio = 600;
    Eventos[5].mes = 12;
    Eventos[5].dia = 10;

    strcpy(Eventos[6].eventname, "Linkin Park");
    strcpy(Eventos[6].tipoevento, "Concierto");
    Eventos[6].precio = 1300;
    Eventos[6].mes = 12;
    Eventos[6].dia = 13;

    strcpy(Eventos[7].eventname, "Falacia. Ricardo O´Farril");
    strcpy(Eventos[7].tipoevento, "Stand Up");
    Eventos[7].precio = 600;
    Eventos[7].mes = 12;
    Eventos[7].dia = 22;

    strcpy(Eventos[8].eventname, "Carlos Ballarta");
    strcpy(Eventos[8].tipoevento, "Stand Up");
    Eventos[8].precio = 1250;
    Eventos[8].mes = 12;
    Eventos[8].dia = 24;

    strcpy(Eventos[9].eventname, "Chayanne");
    strcpy(Eventos[9].tipoevento, "Concierto");
    Eventos[9].precio = 900;
    Eventos[9].mes = 12;
    Eventos[9].dia = 29;

    char NombresEv[10][40];

    for (int i = 0; i < 10; i++) {
        strcpy(NombresEv[i], Eventos[i].eventname);
    }

    HWND hlist = GetDlgItem(hDlg, LIST_EVENTOS);
    HWND hnom = GetDlgItem(hDlg, NOMBRE_PTE);
    HWND htip = GetDlgItem(hDlg, TIPOEVENTO_PTE);
    HWND hprec = GetDlgItem(hDlg, PRECIO_PTE);
    HWND hmes = GetDlgItem(hDlg, MES_PTE);
    HWND hdia = GetDlgItem(hDlg, DIA_PTE);
    HWND hcomp = GetDlgItem(hDlg, COMPRAR_PTE);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        for (int i = 0; i < 10; i++) {
            SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_ADDSTRING, NULL, (LPARAM)NombresEv[i]);
        }


    case WM_COMMAND: {
        if (LOWORD(wParam) == LIST_EVENTOS && HIWORD(wParam) == LBN_SELCHANGE) {
            int index = SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, NULL, NULL);
            if (index != LB_ERR) {
                char nombreSeleccionado[40];
                SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETTEXT, index, (LPARAM)nombreSeleccionado);
                SetDlgItemText(hDlg, NOMBRE_PTE, nombreSeleccionado);

                int i = 0;
                while (strcmp(Eventos[i].eventname, nombreSeleccionado) != 0) {
                    i++;
                }

                SetDlgItemText(hDlg, TIPOEVENTO_PTE, Eventos[i].tipoevento);

                switch (Eventos[i].mes) {
                case 1:
                    SetDlgItemText(hDlg, MES_PTE, "Enero");
                    break;

                case 2:
                    SetDlgItemText(hDlg, MES_PTE, "Febrero");
                    break;

                case 3:
                    SetDlgItemText(hDlg, MES_PTE, "Marzo ");
                    break;

                case 4:
                    SetDlgItemText(hDlg, MES_PTE, "Abril ");
                    break;

                case 5:
                    SetDlgItemText(hDlg, MES_PTE, "Mayo ");
                    break;

                case 6:
                    SetDlgItemText(hDlg, MES_PTE, "Junio ");
                    break;

                case 7:
                    SetDlgItemText(hDlg, MES_PTE, "Julio ");
                    break;

                case 8:
                    SetDlgItemText(hDlg, MES_PTE, "Agosto ");
                    break;

                case 9:
                    SetDlgItemText(hDlg, MES_PTE, "Septiembre ");
                    break;

                case 10:
                    SetDlgItemText(hDlg, MES_PTE, "Octubre ");
                    break;

                case 11:
                    SetDlgItemText(hDlg, MES_PTE, "Noviembre ");
                    break;

                case 12:
                    SetDlgItemText(hDlg, MES_PTE, "Diciembre ");
                    break;

                }
                strcpy(Ceventname, nombreSeleccionado);

            }
        }

        if (LOWORD(wParam) == COMPRAR_PTE) {
            if (SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, NULL, NULL) == -1) {
                MessageBox(hDlg, "No tienes ningun evento seleccionado", "Error", MB_OK);
            }
            else {
                DialogBox(hInst, MAKEINTRESOURCE(PT_VENTA), hDlg, venta);
            }
        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
        }

    }

    }
    return (INT_PTR)FALSE;

}

INT_PTR CALLBACK venta(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    
    HWND hcant = GetDlgItem(hDlg, CANTIDAD_PTVB);
    HWND hconf = GetDlgItem(hDlg, CONFIRMACION_PTVB);
    HWND hprom = GetDlgItem(hDlg, PROMOCIONES_PTVB);


    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG: {
        HWND hpromo = GetDlgItem(hDlg, PROMOCIONES_PTVB);
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"Sin promoción");
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"10% de descuento");
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"2 x 1");
        

        SendMessage(hpromo, CB_SETCURSEL, 0, 0);

        char precioAC[10];
        sprintf(precioAC, "%d", Cprecio);
        SetDlgItemText(hDlg, PRECIO_PTVB, precioAC);

        char diaAC[3];
        sprintf(diaAC, "%d", Cdia);
        SetDlgItemText(hDlg, DIA_PTVB, diaAC);

        SetDlgItemText(hDlg, EVENTO_PTVB, Ceventname);
        SetDlgItemText(hDlg, TIPOEVENTO_PTVB, Ctipoevento);

        switch (Cmes) {
        case 1:
            SetDlgItemText(hDlg, MES_PTVB, "Enero");
            break;

        case 2:
            SetDlgItemText(hDlg, MES_PTVB, "Febrero");
            break;

        case 3:
            SetDlgItemText(hDlg, MES_PTVB, "Marzo ");
            break;

        case 4:
            SetDlgItemText(hDlg, MES_PTVB, "Abril ");
            break;

        case 5:
            SetDlgItemText(hDlg, MES_PTVB, "Mayo ");
            break;

        case 6:
            SetDlgItemText(hDlg, MES_PTVB, "Junio ");
            break;

        case 7:
            SetDlgItemText(hDlg, MES_PTVB, "Julio ");
            break;

        case 8:
            SetDlgItemText(hDlg, MES_PTVB, "Agosto ");
            break;

        case 9:
            SetDlgItemText(hDlg, MES_PTVB, "Septiembre ");
            break;

        case 10:
            SetDlgItemText(hDlg, MES_PTVB, "Octubre ");
            break;

        case 11:
            SetDlgItemText(hDlg, MES_PTVB, "Noviembre ");
            break;

        case 12:
            SetDlgItemText(hDlg, MES_PTVB, "Diciembre ");
            break;

        }

    }

    case WM_COMMAND: {

        if (LOWORD(wParam) == CONFIRMACION_PTVB) {
            char Tcant[3];
            int itxtlength = GetWindowTextLength(hcant);
            GetWindowText(hcant, Tcant, itxtlength + 1);

            int cantAC = atoi(Tcant);
            
            int monto = 0;
            int MONTO = 0;
            int iva = 0;
            float Miva = 0;
            
            int d10 = 0;
            int d2x1 = 0;

            char prom[20];
            int promlength = GetWindowTextLength(hprom);
            GetWindowText(hprom, prom, promlength + 1);
            
            if (strcmp(prom, "10% de descuento") == 0) {
                monto = cantAC * Cprecio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva * 0.90;
                d10 = 1;
            }
            else if (strcmp(prom, "2 x 1") == 0 and cantAC % 2 == 0 and cantAC >= 2) {
                monto = cantAC * Cprecio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva * 0.5;
                d2x1 = 1;

            }
            else if (strcmp(prom, "Sin promoción") == 0) {
                monto = cantAC * Cprecio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva;
            }
           
            char Liva[5];
            sprintf(Liva, "%d", iva);

            char Lprec[5];
            sprintf(Lprec, "%d", Cprecio);

            char Lmonto[5];
            sprintf(Lmonto, "%d", monto);

            char MONTOI[10];
            sprintf(MONTOI, "%d", MONTO);

            strcpy(Comprador.compras[rep], Ceventname);
            strcat(Comprador.compras[rep], " ... ");
            strcat(Comprador.compras[rep], Tcant);
            strcat(Comprador.compras[rep], " Boletos ...");
            strcat(Comprador.compras[rep], " Precio Unitario: $");
            strcat(Comprador.compras[rep], Lprec);
            strcat(Comprador.compras[rep], " ... IVA: $");
            strcat(Comprador.compras[rep], Liva);
            strcat(Comprador.compras[rep], "... Monto antes de impuestos: $");
            strcat(Comprador.compras[rep], Lmonto);
            strcat(Comprador.compras[rep], " ... Monto Total: $");
            strcat(Comprador.compras[rep], MONTOI);

            if (d10 == 1) {
                strcat(Comprador.compras[rep], " .... descuento 10%");
            }

            if (d2x1 == 1) {
                strcat(Comprador.compras[rep], " .... Boletos 2x1");
            }

            rep++;
            MessageBox(hDlg, "Gracias por su compra, puede verificar su adquisición en la sección Mis Compras", "Compra Exitosa", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));

        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));

        }
        
    }

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK miscompras(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    HWND hlcompras = GetDlgItem(hDlg, COMPRAS_PTMC);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        for (int i = 0; i < 10; i++) {
            SendDlgItemMessage(hDlg, COMPRAS_PTMC, LB_ADDSTRING, NULL, (LPARAM)Comprador.compras[i]);
        }



    case WM_COMMAND: {
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            
        }

    }

    }
    return (INT_PTR)FALSE;
}

