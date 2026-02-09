#include "Win32Window.h"
LRESULT windowProcedure(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);
Win32Window::Win32Window(const char* name, unsigned int width, unsigned int height)
{
	input = {};
	WNDCLASSA mWindowClass = {};
	mWindowClass.lpfnWndProc = windowProcedure;
	mWindowClass.lpszClassName = "ClassName";
	mWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	mWindowClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassA(&mWindowClass);

	mWindowHandle = CreateWindowA(mWindowClass.lpszClassName, name, WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, NULL, this);

	mDeviceContextHandle = GetDC(mWindowHandle);

	renderState.height = height;
	renderState.width = width;

	int bufferSize = height * width * sizeof(unsigned int);

	if (renderState.screenBuffer)VirtualFree(renderState.screenBuffer, 0, MEM_RELEASE);
	renderState.screenBuffer = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	bufferSize = height * width * sizeof(float);
	if (renderState.depthBuffer)VirtualFree(renderState.depthBuffer, 0, MEM_RELEASE);
	renderState.depthBuffer = (float*)VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	bitmapInfo.bmiHeader.biSize = sizeof(bitmapInfo.bmiHeader);
	bitmapInfo.bmiHeader.biWidth = renderState.width;
	bitmapInfo.bmiHeader.biHeight = renderState.height;
	bitmapInfo.bmiHeader.biBitCount = 32;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;

}
Win32Window::~Win32Window() {
	ReleaseDC(mWindowHandle, mDeviceContextHandle);
	DestroyWindow(mWindowHandle);
}


LRESULT windowProcedure(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	Win32Window* pWindow = nullptr;
	if ((msg != WM_NCCREATE)) {
		pWindow = reinterpret_cast<Win32Window*>(GetWindowLongPtr(window, GWLP_USERDATA));
	}
	switch (msg) {
	case WM_NCCREATE: {
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pWindow = reinterpret_cast<Win32Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
	}break;
	case WM_CLOSE:
	case WM_DESTROY: {
		RenderState* renderStateU = pWindow->getRenderState();
		if (renderStateU->screenBuffer)VirtualFree(renderStateU->screenBuffer, 0, MEM_RELEASE);
		if (renderStateU->depthBuffer)VirtualFree(renderStateU->depthBuffer, 0, MEM_RELEASE);
		DestroyWindow(window);
		return result;
	}break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(window, &rect);
		RenderState* renderStateU = pWindow->getRenderState();
		renderStateU->width = rect.right - rect.left;
		renderStateU->height = rect.bottom - rect.top;

		int bufferSize = renderStateU->width * renderStateU->height * sizeof(unsigned int);

		if (renderStateU->screenBuffer)VirtualFree(renderStateU->screenBuffer, 0, MEM_RELEASE);
		renderStateU->screenBuffer = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		int dBufferSize = renderStateU->width * renderStateU->height * sizeof(float);
		if (renderStateU->depthBuffer)VirtualFree(renderStateU->depthBuffer, 0, MEM_RELEASE);
		renderStateU->depthBuffer = (float*)VirtualAlloc(0, dBufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		pWindow->bitmapInfo.bmiHeader.biSize = sizeof(pWindow->bitmapInfo.bmiHeader);
		pWindow->bitmapInfo.bmiHeader.biWidth = renderStateU->width;
		pWindow->bitmapInfo.bmiHeader.biHeight = renderStateU->height;
		pWindow->bitmapInfo.bmiHeader.biBitCount = 32;
		pWindow->bitmapInfo.bmiHeader.biPlanes = 1;
		pWindow->bitmapInfo.bmiHeader.biCompression = BI_RGB;

		return 0;
	}break;
	default: {
		return DefWindowProcA(window, msg, wParam, lParam);
	}
	}
	return DefWindowProcA(window, msg, wParam, lParam);
}

void Win32Window::processMessages() {
	//reset input before processing messages
	for (int i = 0; i < Buttons::BUTTON_COUNT; i++) {
		input.buttons->isDown = false;
	}
	MSG message;
	while (PeekMessage(&message, mWindowHandle, 0, 0, PM_REMOVE)) {
		switch (message.message) {
		case WM_KEYUP:
		case WM_KEYDOWN: {
			u32 vk_code = (u32)message.wParam;
			bool isDown = ((message.lParam & (1 << 31)) == 0);
#define process_messages(b,vk)\
case vk:{\
input.buttons[b].changed = (isDown != input.buttons[b].isDown);\
input.buttons[b].isDown = isDown;\
}break;
			switch (vk_code) {
				process_messages(BUTTON_UP, VK_UP)
					process_messages(BUTTON_DOWN, VK_DOWN)
					process_messages(BUTTON_LEFT, VK_LEFT)
					process_messages(BUTTON_RIGHT, VK_RIGHT)
					process_messages(BUTTON_SPACE, VK_SPACE)
					process_messages(BUTTON_ESC, VK_ESCAPE)
					process_messages(BUTTON_SHIFT, VK_SHIFT)
					process_messages(BUTTON_CTRL, VK_CONTROL)
					process_messages(BUTTON_A, 'A')
					process_messages(BUTTON_B, 'B')
					process_messages(BUTTON_C, 'C')
					process_messages(BUTTON_D, 'D')
					process_messages(BUTTON_F, 'F')
					process_messages(BUTTON_G, 'G')
					process_messages(BUTTON_L, 'L')
					process_messages(BUTTON_M, 'M')
					process_messages(BUTTON_N, 'N')
					process_messages(BUTTON_P, 'P')
					process_messages(BUTTON_Q, 'Q')
					process_messages(BUTTON_R, 'R')
					process_messages(BUTTON_S, 'S')
					process_messages(BUTTON_T, 'T')
					process_messages(BUTTON_V, 'V')
					process_messages(BUTTON_W, 'W')
					process_messages(BUTTON_X, 'X')
					process_messages(BUTTON_Z, 'Z')
			}
		}break;
		case WM_LBUTTONDOWN: {
			input.buttons[MOUSE_BUTTON_LEFT].changed = !(input.buttons[MOUSE_BUTTON_LEFT].isDown);
			input.buttons[MOUSE_BUTTON_LEFT].isDown = true;

		}break;
		case WM_LBUTTONUP: {
			input.buttons[MOUSE_BUTTON_LEFT].changed = input.buttons[MOUSE_BUTTON_LEFT].isDown;
			input.buttons[MOUSE_BUTTON_LEFT].isDown = false;

		}break;
		case WM_RBUTTONDOWN: {
			input.buttons[MOUSE_BUTTON_RIGHT].changed = !(input.buttons[MOUSE_BUTTON_RIGHT].isDown);
			input.buttons[MOUSE_BUTTON_RIGHT].isDown = true;

		}break;
		case WM_RBUTTONUP: {
			input.buttons[MOUSE_BUTTON_RIGHT].changed = input.buttons[MOUSE_BUTTON_RIGHT].isDown;
			input.buttons[MOUSE_BUTTON_RIGHT].isDown = false;

		}break;
		default: {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		}
	}
}

void Win32Window::swapBuffers()
{
	StretchDIBits(mDeviceContextHandle, 0, renderState.height - 1, renderState.width, -renderState.height, 0, 0, renderState.width, renderState.height, renderState.screenBuffer, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
}

void Win32Window::addConsole() const
{
	AllocConsole();
	std::freopen("CONOUT$", "w", stdout);
}

void Win32Window::removeConsole() const {
	FreeConsole();
	std::fclose(stdout);
}