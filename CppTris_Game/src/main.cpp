#include "Engine/Application.h"

extern Application* CreateApp();

int main(int argc, char* argv[]) {
	Application* app = CreateApp();
	app->Run();
	delete app;

	return 0;
}