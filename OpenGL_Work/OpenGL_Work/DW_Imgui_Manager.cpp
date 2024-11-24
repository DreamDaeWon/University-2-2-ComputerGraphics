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

    // Create application window
    ///ImGui_ImplWin32_EnableDpiAwareness();
    // Initialize OpenGL

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    
    io = &(ImGui::GetIO());

    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    // 업데이트 OS 마우스 포지션
   
    ImGui::StyleColorsDark();



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
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io->Framerate, io->Framerate);
    ImGui::End();

    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            show_another_window = false;
        ImGui::End();
    }


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
   
}

void DW_imgui_Manager::Render()
{

    // 렌더링


}

