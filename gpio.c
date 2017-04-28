
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "gpio.h"

int gpio_check_num(int gpio_num)
{
	if(!(GPIO_MIN_NUMBER <= gpio_num && gpio_num <= GPIO_MAX_NUMBER))
		return 0;
	return -1;
}

int gpio_open(int gpio_num)
{
	int fd = 0;
	int len = 0;
	const char *file_path = "/sys/class/gpio/export";
	char num_string[100];

	if(gpio_check_num(gpio_num)) return -1;
	fd = open(file_path, O_WRONLY);
	if(fd < 0) {
		return -1;
	}
	len = sprintf(num_string, "%d", gpio_num);
	write(fd, num_string, len);
	close(fd);
	return 0;
}

int gpio_close(int gpio_num)
{
	int fd = 0;
	int len = 0;
	const char *file_path = "/sys/class/gpio/unexport";
	char num_string[100];

	if(gpio_check_num(gpio_num)) return -1;
	fd = open(file_path, O_WRONLY);
	if(fd < 0) return -1;
	len = sprintf(num_string, "%d", gpio_num);
	write(fd, num_string, len);
	close(fd);
	return 0;
}

int gpio_setmode(int gpio_num, int mode)
{
	int fd = 0;
	int len = 0;
	char mode_string[100];
	char file_path[100];

	if(gpio_check_num(gpio_num)) return -1;
	len = sprintf(file_path, "/sys/class/gpio/gpio%d/direction", gpio_num);
	fd = open(file_path, O_WRONLY);
	if(fd < 0) return -1;
	len = sprintf(mode_string, "%d", gpio_num);
	write(fd, mode_string, len);
	close(fd);
	return 0;
}

int gpio_write_value(int gpio_num, int value)
{
	int fd = 0;
	int len = 0;
	char file_path[100];
	char num_string[100];

	if(gpio_check_num(gpio_num)) return -1;
	len = sprintf(file_path, "/sys/class/gpio/gpio%d/value", gpio_num);
	fd = open(file_path, O_WRONLY);
	if(fd < 0) return -1;
	if(value == 1)
		write(fd, "1", 2);
	else
		write(fd, "0", 2);
	close(fd);
	return 0;
}

int gpio_read_value(int gpio_num)
{
	int fd = 0;
	int len = 0;
	int value;
	char file_path[100];
	char buf[1024];

	if(gpio_check_num(gpio_num)) return -1;
	len = sprintf(file_path, "/sys/class/gpio/gpio%d/value", gpio_num);
	fd = open(file_path, O_RDONLY);
	if(fd < 0) return -1;
	len = read(fd, buf, sizeof(buf));
	if(len == -1) return -1;
	close(fd);
	value = atoi(buf);
	return value;
}

int gpio_write(int gpio_num, int value)
{
	if(!gpio_open(gpio_num)) return -1;
	if(!gpio_write_value(gpio_num, value)) return -1;
	if(!gpio_close(gpio_num)) return -1;
	return 0;
}

int gpio_read(int gpio_num)
{
	int value;

	if(!gpio_open(gpio_num)) return -1;
	value = gpio_read_value(gpio_num);
	if(value < 0) return -1;
	if(!gpio_close(gpio_num)) return -1;
	return value;
}

