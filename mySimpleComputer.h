#define flag_count 5
#define memory_count 100
#define regP 0x1 //переполнение при выполнении операции
#define regM 0x2 //ошибка выхода за границы памяти
#define regO 0x4 //ошибка деления на 0
#define regT 0x8 //игнорирование тактовых импульсов
#define regE 0x10 //указана неверная команда
int sc_accumulator;
int Counter;
extern int memory[memory_count];
extern int flag[flag_count];
char flags;
int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int registe_r, int value);
int sc_regGet (int registe_r, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
