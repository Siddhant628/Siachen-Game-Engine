#include "pch.h"

// Pointer to the swap chain interface (A pointer to the series of buffers which take turns being rendered)
IDXGISwapChain *g_pSwapChain;
// Pointer to the Direct 3D device interface (A virtual representation of the video adapter)
ID3D11Device *g_pDevice;
// Pointer to the Direct 3D device context (This object is used to render graphics and to determine how they will be rendered, manages the GPU)
ID3D11DeviceContext *g_pDeviceContext;
// Pointer to a location in video memory where we need to render (holds all the information about the render target)
ID3D11RenderTargetView *g_pBackBuffer;

// Initializes Direct 3D and prepares it for use
void InitD3D(HWND hWnd);
// Closes Direct 3D and releases memory for windows
void CleanD3D(void);
// This is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// Render a single frame
void RenderFrame(void);

// Execution starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
	HWND hWnd;								// The handle for the window, filled by a function
	WNDCLASSEX wc;							// This struct holds information for the window class

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	
	// Fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// Register the window class (1/3 step of building a window)
	RegisterClassEx(&wc);

	RECT wr = { 0, 0, 1280, 720 };							// Set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);		// Adjust the size

	// Create the window and use the result as the handle (2/3 step of building a window)
	hWnd = CreateWindowEx(NULL, L"WindowClass1", L"SiachenGameEngine", WS_OVERLAPPEDWINDOW, 0, 0, wr.right - wr.left, wr.bottom - wr.top, NULL, NULL, hInstance, NULL);

	// Display the window on the screen (3/3 step of building a window)
	ShowWindow(hWnd, nCmdShow);

	InitD3D(hWnd);

	MSG msg = { 0 };	// This struct holds Windows event messages

	// Enter the infinite message loop
	while (TRUE)
	{
		// Handle any messages waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		// Game loop code goes here
		else
		{
			RenderFrame();
		}
	}
	CleanD3D();
	// Return this part of the WM_QUIT message to Windows
	return (int)msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Sort through and find what code to run for the message given
	switch (message)
	{
		// This message is read when the window is closed
		case WM_DESTROY:
		{
			// Close the application entirely
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}
										
void InitD3D(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd;								// Create a struct to store information about the swap chain
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	// Fill the swap chain description struct
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;

	// Create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &g_pSwapChain, &g_pDevice, NULL, &g_pDeviceContext);

	// The above code initialized Direct3D, from here onwards we set the render targets

	// Get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// Use the back buffer address to create the render target
	g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pBackBuffer);
	pBackBuffer->Release();

	// Set the render target as the back buffer
	g_pDeviceContext->OMSetRenderTargets(1, &g_pBackBuffer, NULL);

	// Render targets are set, now we set the viewport

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 1280;
	viewport.Height = 720;

	g_pDeviceContext->RSSetViewports(1, &viewport);
}

void CleanD3D()
{
	// Close and release all COM objects
	g_pSwapChain->Release();
	g_pBackBuffer->Release();
	g_pDevice->Release();
	g_pDeviceContext->Release();
}

void RenderFrame(void)
{
	float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };

	g_pDeviceContext->ClearRenderTargetView(g_pBackBuffer, color);				// Clear the back buffer and set it to a specific color
	
	// Do 3D rendering on the back buffer here

	g_pSwapChain->Present(0, 0);												// Switch the back buffer and the front buffer
}