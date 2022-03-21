#include <windows.h>
#include <stdio.h>
#include <tchar.h> 

#include "resource.h"

  HWND w_hMainWnd, wnd;
  
  LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{ 

	char szClassName[] = ("OWNERDRAW");
	MSG msg;
	WNDCLASSEX wc;	

	wc.cbSize        = sizeof(wc);		
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.hIcon         = 0;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = szClassName;
	wc.hIconSm       = 0;


	if (!RegisterClassEx(&wc)) 
	{
		MessageBox(NULL, _T("Cannot register class"), _T("Error"), MB_OK);
		return 0;
	}


	w_hMainWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, szClassName,"OWNERDRAW",WS_SYSMENU | WS_MINIMIZEBOX 
		,300, 300, 330, 330,
		(HWND)NULL,(HMENU)NULL,(HINSTANCE)hInstance,0);


	wnd = CreateWindow(_T("BUTTON"),0, BS_OWNERDRAW | WS_CHILD | WS_VISIBLE, 
										50, 50, 250, 250,w_hMainWnd, (HMENU)NULL, hInstance, NULL);
	 
	ShowWindow(w_hMainWnd, nCmdShow);
	UpdateWindow(w_hMainWnd);							 

	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// ownerdraw button
	static HBITMAP no_active;
	static HBITMAP in_focus;
	static HBITMAP select;
	// стили

	LPDRAWITEMSTRUCT pdis;
	static BITMAP bm_owner;
	static HDC hMemDcFrame,hDC_owner; 
	static HBRUSH hbrush;
	
	switch (msg)
	{	
		case WM_DRAWITEM:
		{	 
			pdis = (LPDRAWITEMSTRUCT) lParam;
			hDC_owner = CreateCompatibleDC(pdis->hDC);

			 switch (pdis->itemAction)
			 {	
				case ODA_FOCUS:
					if (pdis->itemState & ODS_FOCUS)	
						SelectObject(hDC_owner,in_focus);
					else
						SelectObject(hDC_owner,no_active);
					break;
				case ODA_SELECT:
					if (pdis->itemState & ODS_SELECTED)
						SelectObject(hDC_owner,select);
					break;
				default:  
					SelectObject(hDC_owner,no_active);   
					break;   
			} 
		
			FillRect(pdis->hDC, &pdis->rcItem, hbrush);
			BitBlt(pdis->hDC, 0,0, bm_owner.bmWidth, bm_owner.bmHeight, hDC_owner,0,0, SRCCOPY);
		
			FrameRect(pdis->hDC,&pdis->rcItem,(HBRUSH)GetStockObject(BLACK_BRUSH) );

			DeleteDC(hDC_owner);
			return true;
		
		} 	

		case WM_CREATE:
			// инициализация

			no_active = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BITMAP1));
			in_focus = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BITMAP2));
			select = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BITMAP3));

			GetObject( no_active, sizeof(bm_owner), (LPSTR)&bm_owner);
	 	    break;
		
		
		case WM_DESTROY:
				
				PostQuitMessage(0);	
			break;

		case WM_SETCURSOR:  // отслеживание фокуса ввода для курсора мыши
				if ((HWND)wParam == wnd)	
				{	
					SetFocus(wnd);
					DeleteObject(hbrush);
					hbrush = CreatePatternBrush(in_focus);
				}

				else if ((HWND)wParam != wnd) 
				{
					SetFocus(w_hMainWnd);
					DeleteObject(hbrush);
					hbrush = CreatePatternBrush(no_active);
				}
				return false;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}