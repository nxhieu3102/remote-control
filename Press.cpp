// Nguyễn Xuân Hiếu
#include <iostream>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

using namespace std;

int main()
{
    const char *dev_path = "/dev/input/event1"; // Path to keyboard device file
    int fd = open(dev_path, O_RDONLY);
    if (fd < 0) {
        std::cerr << "Could not open device file." << std::endl;
        return 1;
    }

    while (1) {
        struct input_event ev;
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n == sizeof(ev)) {
            if (ev.type == EV_KEY && ev.value == 1) {
                std::cout << "Key " << ev.code << " was pressed." << std::endl;
            }
        }
    }

    close(fd);
    return 0;
}