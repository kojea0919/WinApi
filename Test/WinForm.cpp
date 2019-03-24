// WinForm.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WinForm.h"

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


//-------------------------------------------------
//WinMain의 인자값
//hInstance : 프로그램의 인스턴스 핸들
//hPrevInstance : NULL
//lpCmdLine : 실행시 실행파일 이외의 인자 커맨드 라인
//nCmdShow : 창 표시 방법 
//ex) SW_SHOW = 일반표시
//	  SW_SHOWMAXIMIZE = 최대화 표시
//	  SW_SHOWMINIMIzE = 최소화 표시
//우리는 사실상 메시지를 처리하는 WndProc함수를 봐야한다.
//-------------------------------------------------
//APIENTRY -> __stdcall 호출규약
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    MSG msg;
	HWND hWnd;

	WNDCLASSEXW wcex;
	//-------------------------------------
	//WNDCLASSEXW구조체
	//이 구조체를 적절하게 초기화한 후
	//RegisterClassEx()함수를 호출하여
	//윈도우 클래스를 등록하게 된다.
	//즉 WNDCLASSEXW구조체는 우리가 만들고자
	//하는 윈도우에 따라 적당한 값을 setting하기
	//위해서 존재하는 구조체이다.
	//모든 인자값을 아는 것보다 필요할 때 마다
	//찾아서 값을 정하도록 하자.
	//--------------------------------------

	wcex.cbSize = sizeof(WNDCLASSEX);//이 구조체의 사이즈

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	//------------------------------------------------------
	//CS_DBLCLKS : 마우스 더블클릭 메시지
	//CS_DROPSHADOW : 윈도우에 그림자
	//CS_HREDRAW, CS_VREDRAW : 가로 세로 사이즈 변경시 다시 그림
	//------------------------------------------------------

	wcex.lpfnWndProc = WndProc;
	//------------------------------
	//메시지를 처리할 프로시저 함수 포인터
	//------------------------------

	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;//추가 사용자 공간?

	wcex.hInstance = hInstance;//WinMain을 통해 들어온 Instance핸들 값
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINFORM));//
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);//기본 커서 핸들
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINFORM);

	wcex.lpszClassName = L"ClassName_990";
	//---------------------------------
	//이번에 등록되는 클래스의 이름
	//---------------------------------
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);
	//-------------------------------------------------------
	//위에서 초기화된 정보를 가지고 윈도우를 setting 해준다.
	//-------------------------------------------------------


	hWnd = CreateWindowW(L"ClassName_990", L"Caption", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	//-------------------------------------------------------
	//RegisterClassEx함수를 통해서 setting된 윈도우를 실제로
	//생성해주는 함수
	//-------------------------------------------------------

	if (!hWnd)//열리지 않으면 false
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);//윈도우를 화면에 보여준다.

	UpdateWindow(hWnd);
	//---------------------------------------------------
	//윈도우가 처음 생성된 후 WM_PAINT 메시지를 발생시켜
	//화면을 업데이트 해주기 위한 용도
	//---------------------------------------------------


    // 기본 메시지 루프입니다.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);//
	}
	//////////////////////////////////////////////////////

	//-----------------------------------------------------------
	//GetMessage함수
	//메시지 큐에서 메시지를 읽어들인후 구조체 msg를 초기화한다.
	//읽어들인 메시지가 WM_QUIT일 경우에 false를 return
	//나머지 세개의 인수는 읽어들일 메시지의 범위를 지정하는데
	//잘 사용되지 않는다.
	//-----------------------------------------------------------

	//-----------------------------------------------------------
	//TranslateMessage함수
	//키보드 입력 메시지를 가공한다.
	//예를들면 A키를 누를후 떼었다면
	//키보드의 눌림, 떨어짐이 연속적으로 발생함을 보고 
	//A문자가 입력되었다는 메시지를 만들어 낸다.
	//-----------------------------------------------------------

	//-----------------------------------------------------------
	//DispatchMessage함수
	//메시지 큐에서 꺼낸 메시지를 프로그램의 메시지 처리 함수로
	//전달한다. 내부적으로 WndProc함수를 호출한다. 
	//-----------------------------------------------------------

    return (int) msg.wParam;
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//----------------------------------------------
	//message의 종류
	//WM_QUIT : 프로그램을 끝낼 떄 발생하는 메시지
	//WM_LBUTTONDOWM : 마우스의 좌측 버튼을누를 경우 발생
	//WM_CHAR : 키보드로부터 문자가 입력될 때 발생
	//WM_PAINT : 화면을 다시 그려야 할 필요가 있을 떄 발생
	//WM_DESTROY : 윈도우가 메모리에서 파괴될 때 발생
	//WM_CREATE : 윈도우가 처음 만들어질 때 발생
	//----------------------------------------------
	
	//여기서 DESTROY를 자세히 살펴보자
	//윈도우가 메모리에서 파괴될 때 발생한다고 적혀있다.
	//윈도우지 어플리케이션이 아니다 즉

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
        PostQuitMessage(0);//여기서 WM_QUIT메시지를 보낸다.
		//이것을 처리할 때 그때 while문을 빠져나오면서
		//어플리케이션이 종료한다.
		//만약 PostQuitMessage함수를 주석처리로 막았다면
		//윈도우는 꺼졌지만 프로세스는 꺼지지 않고
		//block상태로 유지될 것이다.
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


//-----------------------------------------
//여러가지 중요한 기능들
//도구 -> Spy++ -> 로그클릭(무슨 msg가 나는지 보여준다.)
//도구 -> Spy++ -> 망원경클릭(해당 윈도우 어플리케이션에 대한 정보를 Capture)

