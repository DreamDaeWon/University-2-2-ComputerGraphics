#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"
#include <iostream>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/GL.h>
#include <tchar.h>

struct WGL_WindowData { HDC hDC; };






class DW_imgui_Manager
{
public:
	DW_imgui_Manager(HWND hWnd, HDC hdc);

	~DW_imgui_Manager();

public:

	void Imgui_Initialize();

	void Tick();

	void Render();

private:
	void Update();

	void CleanupDeviceWGL(HWND hWnd, WGL_WindowData* data);

	bool CreateDeviceWGL(HWND hWnd, WGL_WindowData* data);


	HWND hwnd{};
	HDC hdc{};
	bool done{};

	MSG msg{};

	ImGuiIO* io;


	HGLRC  g_hRC{};
	WGL_WindowData   g_MainWindow;

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

};