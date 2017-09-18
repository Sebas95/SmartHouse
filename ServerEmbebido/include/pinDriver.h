
#define ECHO "echo "
#define MORE_THAN " > "
#define PATH_EXPORT "/sys/class/gpio/export"
#define PATH "/sys/class/gpio/gpio"
#define DIRECTION "/direction"
#define VALUE "/value"

#define PIN_LIGHT_1 3
#define PIN_LIGHT_2 5
#define PIN_LIGHT_3 7
#define PIN_LIGHT_4 8
#define PIN_LIGHT_5 10

#define PIN_DOOR_1 11
#define PIN_DOOR_2 18
#define PIN_DOOR_3 13
#define PIN_DOOR_4 4

void init();
void setPin(short,char);
void writePin(short,short);
void writePinChar(char,char);
void exportPin(short);
short readPin(short);
void writeAllPinsLights(short);
short doorPinMapper(short);
short lightPinMapper(char);