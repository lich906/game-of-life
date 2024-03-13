#include <iostream>
#include "core/core.h"

int main()
{
	std::cout << "Hello World!\n";

	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Game of life");

	app->Run();
}
