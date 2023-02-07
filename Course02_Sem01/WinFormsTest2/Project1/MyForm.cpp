#include "MyForm.h"
#include <Windows.h>

using namespace Project1;

void main(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);  
    Application::Run(gcnew MyForm);
}