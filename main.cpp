#include "my_client.h"

int main(int argc, char* argv[])
{
    if (argc < 4) {
        exit(-1);
    }
    stringstream ss{argv[1]};
    auto name_ = "ZHENYA " + ss.str();
    ss.clear();
    uint port_ = atoi(argv[2]);

    uint period = atoi(argv[3]);
    MyClient myClient(name_, port_, period);
    while (true) {

        myClient.run();
        this_thread::sleep_for(chrono::seconds(period));
    }
    return 0;
}
