// WinAPI_GalsPainc_Proj.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI_GalsPainc_Proj.h"

#define MAX_LOADSTRING 100

// >> : 사용자 정의 함수
#pragma comment(lib, "msimg32.lib")
RECT rectView;
HBITMAP hDoubleBufferImage, hDoubleBufferImage2;
void DrawDoubleBuffering(HWND hWnd, HDC hdc, CCircle& cir, std::list<CLine>& cl);


// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPIGALSPAINCPROJ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIGALSPAINCPROJ));

    MSG msg;

    DWORD dwPrevCount = GetTickCount();

    DWORD dwAccCount = 0;
    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            int iTime = GetTickCount();

            if (msg.message == WM_QUIT)
            {
                break;
            }

            if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            dwAccCount += (GetTickCount() - iTime);
        }

        // 메세지가 발생하지 않는 대부분의 시간
        else
        {
            DWORD dwCurCount = GetTickCount();
            if (dwPrevCount - dwCurCount > 1000)
            {
                float fRatio = (float)dwAccCount / 1000.f;

                wchar_t szBuff[50] = {};
                wsprintf(szBuff, L"비율 : %f", fRatio);
                SetWindowText(hWnd, szBuff);
            }

            // Game 코드 수행
            // 디자인 패턴(설계 유형)

        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIGALSPAINCPROJ));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIGALSPAINCPROJ);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

#define timer_ID_1 1

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    using namespace std;
    HDC hdc;
    PAINTSTRUCT ps;
    static bool isLeft = false;
    static bool isRight = false;
    static bool isUp = false;
    static bool isDown = false;
    static bool lineLeft = false;
    static bool lineRight = false;
    static bool lineUp = false;
    static bool lineDown = false;
    static POINT cursor = { 10, 10 };
    static list<CLine> cl;
    static list<CLine>::iterator it = cl.begin();
    static CCircle cir(cursor);

    switch (message)
    {
    case WM_CREATE:
        GetClientRect(hWnd, &rectView);
        SetTimer(hWnd, timer_ID_1, 10, NULL);
        break;
    case WM_TIMER:
        if (wParam == timer_ID_1)
        {
            if (isLeft)
            {
                cursor.x -= 5;
            }
            else if (isRight)
            {
                cursor.x += 5;
            }
            else if (isUp)
            {
                cursor.y -= 5;
            }
            else if (isDown)
            {
                cursor.y += 5;
            }

            cir.Update(&rectView, cursor);
            if (lineLeft || lineRight || lineUp || lineDown)
            {
                (*it).SetEnd(cursor);
            }
            InvalidateRect(hWnd, NULL, FALSE);
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_KEYDOWN:
    {
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            isLeft = true;
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            isRight = true;
        }
        else if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            isUp = true;
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            isDown = true;
        }

        if (GetAsyncKeyState(VK_SPACE) & 0x8000)
        {
            if (GetAsyncKeyState(VK_LEFT) & 0x8000)
            {
                if (!lineLeft)
                {
                    lineLeft = true;
                    cl.push_back(CLine(cursor));
                    it = prev(cl.end());
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
            {
                if (!lineRight)
                {
                    lineRight = true;
                    cl.push_back(CLine(cursor));
                    it = prev(cl.end());
                }
            }
            else if (GetAsyncKeyState(VK_UP) & 0x8000)
            {
                if (!lineUp)
                {
                    lineUp = true;
                    cl.push_back(CLine(cursor));
                    it = prev(cl.end());
                }
            }
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
            {
                if (!lineDown)
                {
                    lineDown = true;
                    cl.push_back(CLine(cursor));
                    it = prev(cl.end());
                }
            }
        }
    }
    break;
    case WM_KEYUP:
    {
        if (wParam == VK_LEFT)
        {
            isLeft = false;
            lineLeft = false;
        }
        else if (wParam == VK_RIGHT)
        {
            isRight = false;
            lineRight = false;
        }
        else if (wParam == VK_UP)
        {
            isUp = false;
            lineUp = false;
        }
        else if (wParam == VK_DOWN)
        {
            isDown = false;
            lineDown = false;
        }

        if (wParam == VK_SPACE)
        {
            lineLeft = false;
            lineRight = false;
            lineUp = false;
            lineDown = false;
        }
    }
    break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            DrawDoubleBuffering(hWnd, hdc, cir, cl);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        KillTimer(hWnd, timer_ID_1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void DrawDoubleBuffering(HWND hWnd, HDC hdc, CCircle& cir, std::list<CLine>& lines)
{
    HDC hMemDC, hMemDC2;
    HBITMAP hOldBitmap, hOldBitmap2;
    HBRUSH hBrush, oldBrush;

    hMemDC = CreateCompatibleDC(hdc);
    if (hDoubleBufferImage == NULL)
    {
        hDoubleBufferImage = CreateCompatibleBitmap(hdc,
            rectView.right, rectView.bottom);
    }
    hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hMemDC, &rectView, hBrush); // 배경색 채우기
    DeleteObject(hBrush);

    hMemDC2 = CreateCompatibleDC(hMemDC);
    if (hDoubleBufferImage2 == NULL)
    {
        hDoubleBufferImage2 = CreateCompatibleBitmap(hdc,
            rectView.right, rectView.bottom);
    }
    hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hDoubleBufferImage2);

    hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hMemDC2, &rectView, hBrush); // 배경색 채우기
    DeleteObject(hBrush);

    hBrush = CreateSolidBrush(RGB(0, 255, 0));
    oldBrush = (HBRUSH)SelectObject(hMemDC2, hBrush);
    cir.Draw(hMemDC2);
    SelectObject(hMemDC2, oldBrush);
    DeleteObject(hBrush);  
    
    HPEN hPen, oldPen;
    hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    oldPen = (HPEN)SelectObject(hMemDC2, hPen);
    for (auto cl : lines)
    {
        cl.Draw(hMemDC2);
    }
    SelectObject(hMemDC2, oldPen);
    DeleteObject(hPen);

    BitBlt(hMemDC, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, SRCCOPY);
    SelectObject(hMemDC2, hOldBitmap2);
    DeleteDC(hMemDC2);

    BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
    SelectObject(hMemDC, hOldBitmap);
    DeleteDC(hMemDC);
}