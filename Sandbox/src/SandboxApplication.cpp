#include "Core/Application.h"



int main() {

	auto app = new LSO::Application;
	app->Run();
	delete app;

	return 0;
}