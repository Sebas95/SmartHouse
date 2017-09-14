
#define ECHO "echo "
#define MORE_THAN " > "
#define PATH_EXPORT "/sys/class/gpio/export"
#define PATH "/sys/class/gpio/gpio"
#define DIRECTION "/direction"
#define VALUE "/value"

void init();
void setPin(short,char);
void writePin(short,short);
void writePinChar(char,char);
void exportPin(short);
short readPin(short);