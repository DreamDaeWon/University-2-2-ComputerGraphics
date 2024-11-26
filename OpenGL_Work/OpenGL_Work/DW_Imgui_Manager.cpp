#include "DW_Imgui_Manager.h"


DW_imgui_Manager::DW_imgui_Manager(HWND hWnd, HDC hdc)
{
    hwnd = hWnd;

    g_MainWindow.hDC = hdc;

    Imgui_Initialize();
}

DW_imgui_Manager::~DW_imgui_Manager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void DW_imgui_Manager::Imgui_Initialize()
{
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    // Create application window
    ///ImGui_ImplWin32_EnableDpiAwareness();
    // Initialize OpenGL

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // 업데이트 OS 마우스 포지션

    // Setup Platform/Renderer backends
    //ImGui_ImplWin32_InitForOpenGL(hwnd);
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL3_Init();
}


// Helper functions
bool DW_imgui_Manager::CreateDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    HDC hDc = ::GetDC(hWnd);
    PIXELFORMATDESCRIPTOR pfd = { 0 };
    pfd.nSize = sizeof(pfd);    
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;

    const int pf = ::ChoosePixelFormat(hDc, &pfd);
    if (pf == 0)
        return false;
    if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
        return false;
    ::ReleaseDC(hWnd, hDc);

    data->hDC = ::GetDC(hWnd);
    if (!g_hRC)
        g_hRC = wglCreateContext(data->hDC);
    return true;
}


void DW_imgui_Manager::Update()
{

}

void DW_imgui_Manager::CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data)
{
    wglMakeCurrent(nullptr, nullptr);
    ::ReleaseDC(hWnd, data->hDC);
}


void DW_imgui_Manager::Tick()
{
    //MSG msg;
    //while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    //{
    //    ::TranslateMessage(&msg);
    //    ::DispatchMessage(&msg);
    //    if (msg.message == WM_QUIT)
    //        done = true;
    //}
    //if (::IsIconic(hwnd))
    //{
    //    ::Sleep(10);
    //    return;
    //}


    //if (io->WantCaptureMouse)
         //return;
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("TOOL_BOX");
    if (ImGui::Button("Click Me"))
        ImGui::Text("Button was clicked!");
    ImGui::End();

    // RENDER 
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DW_imgui_Manager::Render()
{

    // 렌더링


}

