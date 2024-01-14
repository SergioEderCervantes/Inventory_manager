#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        MessageBoxW(hwnd, L"¡Buah chaval esto es otro nivel maribel!", L"Ventana Emergente", MB_OK | MB_ICONINFORMATION);
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main()
{
    // Registro de la clase de la ventana
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"VentanaEmergenteClass";

    RegisterClassW(&wc);

    // Creación de la ventana
    HWND hwnd = CreateWindowExW(0, L"VentanaEmergenteClass", L"Ventana Emergente", 0, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (hwnd == NULL)
    {
        MessageBoxW(NULL, L"Fallo al crear la ventana", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Bucle de mensajes
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
