// Precompiled header file incudes the Windows and Direct 3D header files
#include "pch.h"
#include "SList.h"
// TODO Lookup
//#include <d3dx11.h>
//#include <d3dx10.h>

// Global declarations (The first step of actually coding Direct3D is to create these three COM (Component Object Model) objects and initialize them)
IDXGISwapChain *g_pSwapChain;								// Pointer to the swap chain interface (A pointer to the series of buffers which take turns being rendered)
ID3D11Device *g_pDevice;									// Pointer to the Direct 3D device interface (A virtual representation of the video adapter)
ID3D11DeviceContext *g_pDeviceContext;						// Pointer to the Direct 3D device context (This object is used to render graphics and to determine how they will be rendered, manages the GPU)

ID3D11RenderTargetView *g_pBackBuffer;						// Pointer to a location in video memory where we need to render (holds all the information about the render target)

// Function prototypes
void InitD3D(HWND hWnd);																// Initializes Direct 3D and prepares it for use
void CleanD3D(void);																	// Closes Direct 3D and releases memory for windows
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);		// This is the main message handler for the program
void RenderFrame(void);																	// Render a single frame

// WINAPI reverses the order in which the parameters are passed. They're normally passed from right to left, but with WINAPI, they are passed from left to right.

// Execution starts here
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//UNREFERENCED_PARAMETER(nCmdShow);
	
	// The handle for the window, filled by a function
	HWND hWnd;
	// This struct holds information for the window class
	WNDCLASSEX wc;

	// Clear out the window class for use
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

	// TODO Set appropriate resolution
	RECT wr = { 0, 0, 1280, 720 };							// Set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // Adjust the size

	// Create the window and use the result as the handle (2/3 step of building a window)
	hWnd = CreateWindowEx
	(
		NULL,
		L"WindowClass1",					// Name of the window class
		L"SiachenGameEngine",				// Title of the window
		WS_OVERLAPPEDWINDOW,				// Window style
		0,									// X-position of the window
		0,									// Y-position of the window
		wr.right - wr.left,					// Width of the window
		wr.bottom - wr.top,					// Height of the window
		NULL,								// We have no parent window, NULL
		NULL,								// We aren't using menus, NULL
		hInstance,							// Application handle
		NULL								// Used with multiple windows, NULL
	);

	// Display the window on the screen (3/3 step of building a window)
	ShowWindow(hWnd, nCmdShow);

	// Setup and initialize Direct3D
	InitD3D(hWnd);

	// This struct holds Windows event messages
	MSG msg = {0};

	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);							// Translate keystroke messages into the right format
			DispatchMessage(&msg);							// Send the message to the WindowProc function
			if (msg.message == WM_QUIT)						// Check to see if it's time to quit
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
	// Cleanup DirectX and COM Objects
	CleanD3D();

	// Demonstrating SList class
	SiachenGameEngine::SList myList(10);

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
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));			// Clear this struct for use

	// Fill the swap chain description struct
	scd.BufferCount = 1;                                    // One back buffer, and there is one front buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // Use 32-bit color
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // How swap chain is to be used
	scd.OutputWindow = hWnd;                                // The window to be used
	scd.SampleDesc.Count = 4;                               // How many Multisample Anti-Aliasing (MSAA)
	scd.Windowed = TRUE;                                    // Windowed or full-screen mode

	// Create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain
	(
		NULL,						// Let DXGI handle finding the best graphics card
		D3D_DRIVER_TYPE_HARDWARE,	// Only systems with hardware(graphics card) for Dx11 will be able to run this game
		NULL,						// Not using since this is slow
		NULL,						// Flags for making Direct3D behave in a certain way, not needed
		NULL,						// Not getting into specific features of the hardware, may be used to notify Direct3D about requirements that the hardware meets
		NULL,						// Number of feature levels in the list above
		D3D11_SDK_VERSION,			// Notifies which version of DirectX you worked on
		&scd,						// A pointer to the swap chain description object
		&g_pSwapChain,				// A pointer to a pointer to the swap chain object
		&g_pDevice,					// A pointer to a pointer to the device object
		NULL,						// A pointer to a feature level variable
		&g_pDeviceContext			// A pointer to the device context object
	);

	// The above code initialized Direct3D, from here onwards we set the render targets
	

	// Get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;				//An object that stores a flat image (2D Texture)
	g_pSwapChain->GetBuffer
	(
		0,										// Number of the back buffer to get
		__uuidof(ID3D11Texture2D),				// A number identifying the ID3D11Texture2D COM object, different COM objects can be identified by using similar IDs
		(LPVOID*)&pBackBuffer					// Pointer to the flat image (a void pointer since we could have had other type of object)
	);

	// Use the back buffer address to create the render target
	g_pDevice->CreateRenderTargetView
	(
		pBackBuffer,							// Pointer to the texture
		NULL,									// A struct that describes the render target
		&g_pBackBuffer							// Pointer to the COM object
	);

	pBackBuffer->Release();						// Frees all memory and closes all threads used by a COM object (not required anymore)

	// Set the render target as the back buffer
	g_pDeviceContext->OMSetRenderTargets
	(
		1,										// Number of render targets
		&g_pBackBuffer,							// Pointer to a list of render target objects
		NULL
	);

	// Render targets are set, now we set the viewport

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	// TODO Set width and height of the viewport
	viewport.Width = 1280;
	viewport.Height = 720;

	g_pDeviceContext->RSSetViewports
	(
		1,										// The number of viewports
		&viewport								// Pointer to the list of viewports
	);
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