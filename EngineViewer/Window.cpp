
#include <Windows.h>
#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <string>
#include <vector>

#include "Geometry_local.h"
#include "RaptorState.h"
#include "IDM.h"

// Forward declaration for message handling
LRESULT CALLBACK HandleMessages(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

std::vector<RaptorUI> EngineUIList{};
std::vector<RaptorUI> EngineUIList_Stage2{};

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
    // Register the window class
    const wchar_t CLASS_NAME[] = L"Basic";

    WNDCLASS wc = { };

    wc.lpfnWndProc = HandleMessages;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Initialize GDI+
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Create the window
    HWND hwnd = CreateWindowExW(
        0,                              
        CLASS_NAME,                     
        L"Raptor Viewer",    
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,

        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 600,

        NULL,         
        NULL,       
        hInstance,  
        NULL       
    );

    
    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    std::vector<Point> EngineUILocations = ComputeLocus(31, 10, 1);
    DWORD IdIncrement = 1;

    for (const auto& Point : EngineUILocations) {
        HWND raptorEngine = CreateWindowExW(
            0,
            L"Static",
            NULL,
            WS_CHILD | SS_NOTIFY | SS_OWNERDRAW,

            (85 + Point.x) * 3, (70 + Point.y) * 3 + 40, 15 * 3, 15 * 3,

            hwnd,         
            (HMENU)IdIncrement,
            hInstance,  
            NULL        
        );

        RaptorUI EngineUI;
        EngineUI.Identifier = IdIncrement;
        EngineUI.WindowHandle = raptorEngine;

        EngineUIList.push_back(EngineUI);

        IdIncrement++;
        ShowWindow(raptorEngine, nCmdShow);
    }

    EngineUILocations = ComputeLocus(55, 20, 1);
    for (const auto& Point : EngineUILocations) {
        HWND raptorEngine = CreateWindowExW(
            0,
            L"Static",
            NULL,
            WS_CHILD | SS_NOTIFY | SS_OWNERDRAW,

            (85 + Point.x) * 3, (70 + Point.y) * 3 + 40, 15 * 3, 15 * 3,

            hwnd,          
            (HMENU)IdIncrement,       
            hInstance,  
            NULL        
        );

        RaptorUI EngineUI;
        EngineUI.Identifier = IdIncrement;
        EngineUI.WindowHandle = raptorEngine;

        EngineUIList.push_back(EngineUI);

        IdIncrement++;
        ShowWindow(raptorEngine, nCmdShow);
    }

    EngineUILocations = ComputeLocus(11, 3, -1);
    for (const auto& Point : EngineUILocations) {
        HWND raptorEngine = CreateWindowExW(
            0,
            L"Static",
            NULL,
            WS_CHILD | SS_NOTIFY | SS_OWNERDRAW,

            (85 + Point.x) * 3, (70 + Point.y) * 3 + 40, 15 * 3, 15 * 3,

            hwnd,          
            (HMENU)IdIncrement,       
            hInstance,  
            NULL        
        );

        RaptorUI EngineUI;
        EngineUI.Identifier = IdIncrement;
        EngineUI.WindowHandle = raptorEngine;

        EngineUIList.push_back(EngineUI);

        IdIncrement++;
        ShowWindow(raptorEngine, nCmdShow);
    }

    EngineUILocations = ComputeLocus(10, 3, 1);
    for (const auto& Point : EngineUILocations) {
        HWND raptorEngine = CreateWindowExW(
            0,
            L"Static",
            NULL,
            WS_CHILD | SS_NOTIFY | SS_OWNERDRAW,

            (85 + Point.x) * 3 + 600, (70 + Point.y) * 3 + 40, 15 * 3, 15 * 3,

            hwnd,          
            (HMENU)IdIncrement,       
            hInstance,  
            NULL       
        );

        RaptorUI EngineUI;
        EngineUI.Identifier = IdIncrement;
        EngineUI.WindowHandle = raptorEngine;

        EngineUIList_Stage2.push_back(EngineUI);

        IdIncrement++;
        ShowWindow(raptorEngine, nCmdShow);
    }

    EngineUILocations = ComputeLocus(30, 3, -1);
    for (const auto& Point : EngineUILocations) {
        HWND raptorEngine = CreateWindowExW(
            0,
            L"Static",
            NULL,
            WS_CHILD | SS_NOTIFY | SS_OWNERDRAW,

            (85 + Point.x) * 3 + 585, (70 + Point.y) * 3 + 25, 15 * 5, 15 * 5,

            hwnd,
            (HMENU)IdIncrement,
            hInstance,
            NULL
        );

        RaptorUI EngineUI;
        EngineUI.Identifier = IdIncrement;
        EngineUI.WindowHandle = raptorEngine;

        EngineUIList_Stage2.push_back(EngineUI);

        IdIncrement++;
        ShowWindow(raptorEngine, nCmdShow);
    }

    // Run the message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Free GDI+ 
    Gdiplus::GdiplusShutdown(gdiplusToken);

    return 0;
}

LRESULT CALLBACK HandleMessages(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));

        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_DRAWITEM:
    {
        
        LPDRAWITEMSTRUCT DrawingInformation = reinterpret_cast<LPDRAWITEMSTRUCT>(lParam);
        
        Gdiplus::Graphics GDIGraphicsContext(DrawingInformation->hDC);
    
        int UIIndex = GetUIFromIdentifier(EngineUIList, (DWORD)wParam);
        if (UIIndex < 0) {
            UIIndex = GetUIFromIdentifier(EngineUIList_Stage2, (DWORD)wParam);
        }

        RaptorUI* UIEngine = &EngineUIList[UIIndex];
        if (UIEngine->Enabled) {
            Gdiplus::SolidBrush WhiteFill(Gdiplus::Color(255, 255, 255));

            GDIGraphicsContext.FillEllipse(
                &WhiteFill,
                (INT)DrawingInformation->rcItem.left,
                (INT)DrawingInformation->rcItem.top,
                (INT)(DrawingInformation->rcItem.right - DrawingInformation->rcItem.left),
                (INT)(DrawingInformation->rcItem.bottom - DrawingInformation->rcItem.top)
            );
        }
        else {
            Gdiplus::Pen WhiteColor(Gdiplus::Color(255, 255, 255, 255), 4);

            GDIGraphicsContext.Clear(Gdiplus::Color(0, 0, 0));
            GDIGraphicsContext.DrawEllipse(
                &WhiteColor,
                (INT)DrawingInformation->rcItem.left,
                (INT)DrawingInformation->rcItem.top,
                (INT)(DrawingInformation->rcItem.right - DrawingInformation->rcItem.left - 4),
                (INT)(DrawingInformation->rcItem.bottom - DrawingInformation->rcItem.top - 4)
            );
        }

        return TRUE;
    }
    case WM_COMMAND:
    {
        if (HIWORD(wParam) == STN_CLICKED) {
            DWORD Identifier = LOWORD(wParam);
            HWND UIHandle = (HWND)lParam;

            int UIIndex = GetUIFromIdentifier(EngineUIList, (DWORD)wParam);
            if (UIIndex < 0) {
                UIIndex = GetUIFromIdentifier(EngineUIList_Stage2, (DWORD)wParam);
            }

            RaptorUI* UIElement = &EngineUIList[UIIndex];
            UIElement->Enabled = (UIElement->Enabled ? false : true);

            HDC ControlDrawContext = GetDC(UIHandle);

            RECT WindowDimensions;
            GetClientRect(UIHandle, &WindowDimensions);

            Gdiplus::Graphics GDIGraphicsContext(ControlDrawContext);
            if (UIElement->Enabled) {
                Gdiplus::SolidBrush WhiteFill(Gdiplus::Color(255, 255, 255));

                GDIGraphicsContext.FillEllipse(
                    &WhiteFill,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top)
                );
            }
            else {
                Gdiplus::Pen WhiteColor(Gdiplus::Color(255, 255, 255), 4);

                GDIGraphicsContext.Clear(Gdiplus::Color(0, 0, 0));

                GDIGraphicsContext.DrawEllipse(
                    &WhiteColor,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left - 4),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top - 4)
                );
            }


            ReleaseDC(UIHandle, ControlDrawContext);
        };
        
        if (LOWORD(wParam) == IDM_START_STAGE_ONE) {
            for (int i = 0; i < EngineUIList.size(); i++) {
                RaptorUI* EngineUI = &EngineUIList[i];

                EngineUI->Enabled = true;

                HDC ControlDrawContext = GetDC(EngineUI->WindowHandle);

                RECT WindowDimensions;
                GetClientRect(EngineUI->WindowHandle, &WindowDimensions);

                Gdiplus::SolidBrush WhiteFill(Gdiplus::Color(255, 255, 255));


                Gdiplus::Graphics GDIGraphicsContext(ControlDrawContext);

                Gdiplus::Status stat = GDIGraphicsContext.FillEllipse(
                    &WhiteFill,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top)
                );



                ReleaseDC(EngineUI->WindowHandle, ControlDrawContext);
                
            }
        }
        else if (LOWORD(wParam) == IDM_STOP_STAGE_ONE) {
            for (int i = 0; i < EngineUIList.size(); i++) {
                RaptorUI* EngineUI = &EngineUIList[i];
                EngineUI->Enabled = false;

                HDC ControlDrawContext = GetDC(EngineUI->WindowHandle);

                RECT WindowDimensions;
                GetClientRect(EngineUI->WindowHandle, &WindowDimensions);

                Gdiplus::Graphics GDIGraphicsContext(ControlDrawContext);
                Gdiplus::Pen WhiteColor(Gdiplus::Color(255, 255, 255), 4);

                GDIGraphicsContext.Clear(Gdiplus::Color(0, 0, 0));

                GDIGraphicsContext.DrawEllipse(
                    &WhiteColor,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left - 4),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top - 4)
                );

                ReleaseDC(EngineUI->WindowHandle, ControlDrawContext);
            }
        }
        else if (LOWORD(wParam) == IDM_START_STAGE_TWO) {
            for (int i = 0; i < EngineUIList_Stage2.size(); i++) {
                RaptorUI* EngineUI = &EngineUIList_Stage2[i];
                EngineUI->Enabled = true;

                HDC ControlDrawContext = GetDC(EngineUI->WindowHandle);

                RECT WindowDimensions;
                GetClientRect(EngineUI->WindowHandle, &WindowDimensions);

                Gdiplus::SolidBrush WhiteFill(Gdiplus::Color(255, 255, 255));


                Gdiplus::Graphics GDIGraphicsContext(ControlDrawContext);

                Gdiplus::Status stat = GDIGraphicsContext.FillEllipse(
                    &WhiteFill,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top)
                );

                ReleaseDC(EngineUI->WindowHandle, ControlDrawContext);
            } 
        }
        else if (LOWORD(wParam) == IDM_STOP_STAGE_TWO) {
            for (int i = 0; i < EngineUIList_Stage2.size(); i++) {
                RaptorUI* EngineUI = &EngineUIList_Stage2[i];
                EngineUI->Enabled = false;

                HDC ControlDrawContext = GetDC(EngineUI->WindowHandle);

                RECT WindowDimensions;
                GetClientRect(EngineUI->WindowHandle, &WindowDimensions);

                Gdiplus::Graphics GDIGraphicsContext(ControlDrawContext);
                Gdiplus::Pen WhiteColor(Gdiplus::Color(255, 255, 255), 4);

                GDIGraphicsContext.Clear(Gdiplus::Color(0, 0, 0));

                GDIGraphicsContext.DrawEllipse(
                    &WhiteColor,
                    (INT)WindowDimensions.left,
                    (INT)WindowDimensions.top,
                    (INT)(WindowDimensions.right - WindowDimensions.left - 4),
                    (INT)(WindowDimensions.bottom - WindowDimensions.top - 4)
                );

                ReleaseDC(EngineUI->WindowHandle, ControlDrawContext);
            }
        }

        return 0;
    }

    case WM_CONTEXTMENU:
    {
        
        int xCoordinate = LOWORD(lParam);
        int yCoordinate = HIWORD(lParam);

        if (xCoordinate > 0) {
            HMENU DisplayShortcutMenu = CreatePopupMenu();

            AppendMenuW(DisplayShortcutMenu, MF_STRING, IDM_START_STAGE_ONE, L"Start Stage 1");
            AppendMenuW(DisplayShortcutMenu, MF_STRING, IDM_STOP_STAGE_ONE, L"End Stage 1");

            AppendMenuW(DisplayShortcutMenu, MF_STRING, IDM_START_STAGE_TWO, L"Start Stage 2");
            AppendMenuW(DisplayShortcutMenu, MF_STRING, IDM_STOP_STAGE_TWO, L"End Stage 2");

            TrackPopupMenu(
                DisplayShortcutMenu,
                TPM_LEFTALIGN | TPM_TOPALIGN,
                xCoordinate,
                yCoordinate,
                0,
                hwnd,
                NULL
            );
        }
        return 0;

    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);

    }
    
}