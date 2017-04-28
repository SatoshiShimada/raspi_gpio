
#define GPIO_MIN_NUMBER 2
#define GPIO_MAX_NUMBER 27

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define GPIO_IN 0
#define GPIO_OUT 1

int gpio_check_num(int);
int gpio_open(int);
int gpio_close(int);
int gpio_setmode(int, int);
int gpio_write_value(int, int);
int gpio_read_value(int);

int gpio_write(int, int);
int gpio_read(int);

