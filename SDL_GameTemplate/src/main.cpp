#include "Core/Application.h"

extern core::Application* CreateApp();

int main(int argc, char* argv[]) {
	core::Application* app = CreateApp();
	app->Run();
	delete app;

	return 0;
}