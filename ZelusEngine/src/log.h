#pragma once

#include <ImGui/imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include<iostream>

//Surpress warning for strlen, strcpy and the like which are 'unsafe'
#pragma warning (disable: 4996)

class Log
{

private:
	char inputBuf[256];
	ImVector<char*> items;
	ImVector<const char*> commands; 
	ImVector<char*> history;
	int historyPos;    // -1: new line, 0..History.Size-1 browsing history.
	ImGuiTextFilter filter;
	bool autoScroll;
	bool scrollToBottom;

public: 
	void StartUp();
	void ShutDown();

	// Helper Functions
	static int Stricmp(const char* str1, const char* str2); 
	static int Strnicmp(const char* str1, const char* str2, int n); 
	static char* Strdup(const char* str); 
	static void Strtrim(char* str);

	void ClearLog();
	void AddLog(const char* fmt, ...)IM_FMTARGS(2);
	void Draw(const char* title, bool* p_open);
	void ExecCommand(const char* command_line);
	
	static int TextEditCallbackStub(ImGuiInputTextCallbackData* data);
	int TextEditCallback(ImGuiInputTextCallbackData* data);

};

