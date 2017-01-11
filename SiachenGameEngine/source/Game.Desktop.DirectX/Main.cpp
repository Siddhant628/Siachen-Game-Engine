// Precompiled header file incudes the Windows and Direct 3D header files
#include "pch.h"

// TODO Lookup
//#include <d3dx11.h>
//#include <d3dx10.h>



// Global declarations (The first step of actually coding Direct3D is to create these three COM (Component Object Model) objects and initialize them)
IDXGISwapChain *g_pSwapChain;								// Pointer to the swap chain interface (A pointer to the series of buffers which take turns being rendered)
ID3D11Device *g_pDevice;									// Pointer to the Direct 3D device interface (A virtual representation of the video adapter)
ID3D11DeviceContext *g_pDeviceContext;						// Pointer to the Direct 3D device context (This object is used to render graphics and to determine how they will be rendered, manages the GPU)


// Function prototypes
void InitD3D(HWND hWnd);									// Initializes Direct 3D and prepares it for use
void CleanD3D(void);										// Closes Direct 3D and releases memory for windows

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
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
		NULL,						/*Let DXGI handle finding the best graphics card*/ 
		D3D_DRIVER_TYPE_HARDWARE	/*Only systems with hardware(graphics card) for Dx11 will be able to run this game*/, 
		NULL,						/*Not using since this is slow*/
		NULL,						/*Flags for making Direct3D behave in a certain way, not needed*/
		NULL,						/*Not getting into specific features of the hardware, may be used to notify Direct3D about requirements that the hardware meets*/
		NULL,						/*Number of feature levels in the list above*/
		D3D11_SDK_VERSION,			/*Notifies which version of DirectX you worked on*/
		&scd,						/*A pointer to the swap chain description object*/
		&g_pSwapChain,				/*A pointer to a pointer to the swap chain object*/
		&g_pDevice,					/*A pointer to a pointer to the device object*/
		NULL,						/*A pointer to a feature level variable*/
		&g_pDeviceContext			/*A pointer to the device context object*/
	);
}

void CleanD3D()
{
	// Close and release all COM objects
	g_pSwapChain->Release();
	g_pDevice->Release();
	g_pDeviceContext->Release();
}

