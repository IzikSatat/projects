#include "server_driver.h"
#include "recive_msg_handler.h"

int main(int argc, char *argv[]) {
	myWork::ReciveMessageHandler handler{};
	bool toRun = true;
	myWork::ServerDriver server{1050, toRun, handler};
	server.Run();
	return(0);
}
