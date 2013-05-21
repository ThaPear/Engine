#include "Engine.h"

int main(int _NArgs, char *_Args[])
{
	if(Engine::Init(_NArgs, _Args))
	{
		Engine::Run();
		Engine::Terminate();
	}
	else
	{
		printf("Engine initialization failed.\n");
	}

	// TODO: Remove 1 second delay.
	printf("Exiting in 1 second.\n");
	Sleep(1000);
}