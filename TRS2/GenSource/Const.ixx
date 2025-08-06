/* ########################   CONSTANTS   ################################# */

export module Const;

// ADDED CONSTANTS
export constexpr const char* STEP_NONE = "None";

// VERSION
export constexpr const char* MESSAGE_ABOUT = "Copyright: POLITECNICO DI MILANO\nVersion: 18.0\nDate: November 2020";

// TYPE OF DATA
// USE long for TimeHarp, Varro, Silena, USE short for all others SPC boards.
export using T_DATA = unsigned long;
export struct sHeader2;
export using T_HEAD = sHeader2;
export struct sSubHeader1;
export using T_SUB = sSubHeader1;

/* TOOLS */
export constexpr auto SIGNUM = [](auto x) { return (x >= 0) ? 1 : -1; };
export constexpr auto REMINDER = [](auto a, auto b) { return (a - b * static_cast<int>(a / b)); };
export constexpr auto MAX = [](auto a, auto b) { return (a > b ? a : b); };
export constexpr auto MIN = [](auto a, auto b) { return (a < b ? a : b); };
export constexpr auto CEIL = [](auto a, auto b) { return (REMINDER(a, b) == 0 ? a / b : a / b + 1); };

/* GENERAL CONSTANTS */
export constexpr int STRLEN = 128;
export constexpr int PATHLEN = 128;
export constexpr int PACKLENGTH = 6;
export constexpr int SLI = sizeof(long);
export constexpr int SCH = sizeof(char);
export constexpr int ns2ps = 1000;
export constexpr int STRLEN_LONG = 1024;

/* PROTOCOL CONSTANTS */
export constexpr int STRLEN_PROT = 128;
export constexpr int STRLEN_FIBER = 64;
export constexpr int MAX_ROW_PROT = 16;
export constexpr int COL_PROT_SOURCE = 1;
export constexpr int COL_PROT_FIBERS = 2;
export constexpr int COL_PROT_ACQSTART = 3;
export constexpr int COL_PROT_ACQSTOP = 4;
export constexpr int MAX_SUB = 105;
export constexpr int MAX_ROI_SUB = 4;
export constexpr int MAX_ROW_FIBER = 16;
export constexpr int MAX_FIBER = 64;
export constexpr int MAX_SOURCE = 16; //ALE
export constexpr int COL_FIBER_BOARD = 1;
export constexpr int COL_FIBER_DET = 2;
export constexpr int COL_FIBER_FIBERS = 3;
export constexpr int COL_SOURCE_SOURCE = 1;
export constexpr int COL_SOURCE_SWITCH = 2;
export constexpr int COL_SOURCE_CHANN = 3;
export constexpr int COL_MHARP_INPUT_OFFSET = 2; // note: first is the label
export constexpr int COL_MHARP_INPUT_LEVEL = 3;
export constexpr int COL_MHARP_INPUT_EDGE = 4;
export constexpr int COL_MHARP_INPUT_DEADTIME = 5;
export constexpr int MAX_ROW_SOURCE = 16;
export constexpr int MAX_TWITCH = 2;
export constexpr int MAX_CHANN_SWITCH = 2;
export constexpr int GEOM_COORD_CART = 1;
export constexpr int LAYOUT_PARALL = 0;
export constexpr int LAYOUT_SERIAL = 1;

/* PRESENTATION CONSTANTS */
export constexpr int MAX_ROW_PRES_BLOCK = 18;
export constexpr int MAX_ROW_PRES_LOOP = 5;
export constexpr auto COL_BLOCK_DEF_BLOCK = 1;
export constexpr auto COL_BLOCK_DEF_TYPE = 2;
export constexpr auto COL_BLOCK_DEF_START_FRAME = 3;
export constexpr auto COL_BLOCK_DEF_STOP_FRAME = 4;
export constexpr auto COL_BLOCK_DEF_PARAM1 = 5;
export constexpr auto COL_BLOCK_DEF_PARAM2 = 6;
export constexpr auto COL_BLOCK_DEF_PARAM3 = 7;
export constexpr auto COL_BLOCK_SEQUENCE_BLOCK = 1;
export constexpr auto COL_BLOCK_SEQUENCE_REPEAT = 2;
export constexpr auto ROW_LOOP_PARTITION_LOOP3 = 1;
export constexpr auto ROW_LOOP_PARTITION_LOOP2 = 2;
export constexpr auto ROW_LOOP_PARTITION_LOOP1 = 3;
export constexpr auto END_TYPE_POINTER = 3;
export constexpr auto END_LENGTH_POINTER = 0;
export constexpr char END_PARAM1_POINTER = ']';
export constexpr char END_PARAM2_POINTER = ']';
export constexpr char END_PARAM3_POINTER = ']';
export constexpr auto BASELINE_CONST = 0;
export constexpr auto TASK_CONST = 1;
export constexpr auto RECOVERY_CONST = 2;

/* TABLE CONSTANTS */
export constexpr auto MAX_TABLE = 1375;
export constexpr auto STRLEN_TABLE = 20;
export constexpr auto TCHAR = 0;
export constexpr auto TINT = 1;
export constexpr auto TDOUBLE = 2;
export constexpr auto TSTRING = 3;
export constexpr auto CE = 0;
export constexpr auto CT = 1;
export constexpr auto MAX_TTABLE = 13;
export constexpr auto STRLEN_TTABLE = 20;
export constexpr auto MAX_PANEL = 18;

/* FILE CONSTANTS AND ENVIRONMENT SETTINGS */
export constexpr const char* EXTASCII = ".TXT";
export constexpr auto NUMZERO = 4;
export constexpr const char* FILESET = "SET\\TRS.TRS";
export constexpr const char* DIRPROG = "";
export constexpr const char* DIRSETTINGS = "SET";
export constexpr const char* DIR_INI = "INI";
export constexpr const char* EXTSETTINGS = "*.TRS";
export constexpr const char* EXTFILEPOS = ".POS";
export constexpr const char* DIRFILEPOS = "POS";
export constexpr const char* EXTFILETRIM = ".TRM";
export constexpr const char* DIRFILETRIM = "TRM";
export constexpr const char* EXTFILEBREAK = ".BRE";
export constexpr const char* DIRFILEBREAK = "BREAK";

/* LOOP CONSTANTS */
export constexpr auto MAX_LOOP = 5;
export constexpr auto LOOP_NONE = -1;
export constexpr auto LOOP1 = 0;
export constexpr auto LOOP2 = 1;
export constexpr auto LOOP3 = 2;
export constexpr auto LOOP4 = 3;
export constexpr auto LOOP5 = 4;
export constexpr auto MAXBREAK = 1000;	 // Maximum number of lines in file break

/* TIME BASE CONSTANTS */
export constexpr auto TIME_WIN = 0;
export constexpr auto TIME_TIOMAMM = 1;

/* STEPPER CONSTANTS */
export constexpr auto STEP_SIGN_POS = 0;
export constexpr auto STEP_SIGN_NEG = 1;
export constexpr auto WAIT_FALSE = 0;
export constexpr auto WAIT_TRUE = 1;
export constexpr auto NEWP_VEL_CORR = (1.000 / 1.005); // Empirical correction factor for nominal velocity
export constexpr auto NEWP_FAST_RV = 400;		// Ramp Velocity (um/s) #400
export constexpr auto NEWP_SLOW_RV = 100;		// Ramp Velocity (um/s) #100
export constexpr auto NEWP_CONT_RV = 5000;	// Ramp Velocity (um/s) #5000
export constexpr auto NEWP_FAST_XV = 65000;	// Max  Velocity (um/s) #65000
export constexpr auto NEWP_SLOW_XV = 1000;	// Max  Velocity (um/s) #1000
export constexpr auto NEWP_CONT_XV = 100000;	// Max  Velocity (um/s) #100000
export constexpr auto NEWP_FAST_RW = 1000;	// Ramp Width (ms)      #1000
export constexpr auto NEWP_SLOW_RW = 500;		// Ramp Width (ms)		#500
export constexpr auto NEWP_CONT_RW = 500;		// Ramp Width (ms)	    #500
export constexpr auto NEWP_FAST_SV = 4000;	// Set Velocity (um/s)  #40000
export constexpr auto NEWP_SLOW_SV = 200;		// Set Velocity (um/s)  #200
export constexpr auto STEP_EQUAL_POS = 11;		// Maximum number of unchanged pos
export constexpr auto FACTOR_MONO = 1;
export constexpr auto FACTOR_TUNE = 100;
export constexpr auto FACTOR_NEWP = 1;		// Loop Step (um)	#1000
export constexpr auto FACTOR_TIO = 2;	   //Loop Step factor with TIO board
export constexpr auto MAXITERNEWP = 10;    // Maximum number of iterations in MoveNewp to reach Goal
export constexpr auto MAX_STEP = 6;
export constexpr auto LPT1 = 888;	 // PARALLEL PORT ADDRESS (PIN 11,17-25 -> GND)
export constexpr auto STEP_LPT_ON_1 = 0x01;	 // LSB 	-> PIN 2	(Axis1)
export constexpr auto STEP_LPT_ON_2 = 0x08;  // LSB + 3	-> PIN 5	(Axis2)
export constexpr auto STEP_LPT_CW_1 = 0x02;  // LSB + 1	-> PIN 3	(Axis1)
export constexpr auto STEP_LPT_CW_2 = 0x10;	 // LSB + 4	-> PIN 6	(Axis2)
export constexpr auto STEP_LPT_AWO_1 = ~0x04; // LSB + 2	-> PIN 4	(Axis1)
export constexpr auto STEP_LPT_AWO_2 = ~0x20; // LSB + 5	-> PIN 7	(Axis2)
export constexpr auto SLEEP_MONO = 0.002;	 // 0.025 Sleep Time for MONO (s)
export constexpr auto SLEEP_TUNE = 0.008;	 // Sleep Time for TUNE	(s)
export constexpr auto SLEEP_NEWP = 5;
export constexpr auto STEPS_MONO = 1;      // Number of Steps Moto for 1 nm  (nanometer)
export constexpr auto STEPS_TUNE = 8;       // Number of Steps Tune for 0.01 mm  (millimeter)
export constexpr const char* STEPS_NEWP = "000";   // Number of Steps Newp for 1 mm ("0" = *10 steps)
export constexpr auto MAXPOS = 10000;	 // Maximum number of step or switch positions
export constexpr auto EXP_STEP = 1.0;
export constexpr auto SLEEP_MIN_MVIS = 0.005; //0.010
export constexpr auto SLEEP_MAX_MVIS = 0.020; //0.040
export constexpr auto SLEEP_MIN_MNIR = 0.0025; //0.010
export constexpr auto SLEEP_MAX_MNIR = 0.0025; //0.040
export constexpr auto SLEEP_MIN_TUNE = 0.002; //0.002
export constexpr auto SLEEP_MAX_TUNE = 0.002; //0.002
export constexpr auto SPEED = 30;  // Newport velocity (mm/s)

// TIO SPECIFIC CONSTANTS
export constexpr auto STEP_TIO_BOARD1 = 1;		// First Tio Board
export constexpr auto STEP_TIO_BOARD2 = 2;		// Second Tio Board
export constexpr const char* STEP_TIO_PORT0 = "0";		// First Port on Tio
export constexpr const char* STEP_TIO_PORT1 = "1";		// Second Port on Tio
export constexpr auto STEP_TIO_LINE_DIR = 0;		// Digital Line Direction
export constexpr auto STEP_TIO_LINE_ENABLE = 1;		// Digital Line Enable
export constexpr auto STEP_TIO_LINE_HALF = 2;		// Digital Line HalfStep
export constexpr auto STEP_TIO_COUNT_GATE = 1;		// Counter Gate
export constexpr auto STEP_TIO_COUNT_CLOCK = 2;		// Counter Clock
export constexpr auto STEP_TIO_COUNT_COUNT = 3;		// Counter Counter
export constexpr auto HIGH_LEVEL = 1;		// Digital Level High
export constexpr auto LOW_LEVEL = 0;		// Digital Level Low
export constexpr auto STEP_TIO_NUM_LINE = 2;		// Number of Lines used for each Tio Stepper
export constexpr auto STEP_TIO_NUM_COUNT = 3;		// Number of Counters used for each Tio Stepper
export constexpr auto STEP_TIO_MAX_LINE = 8;		// Max lines per Tio Board

// MIO SPECIFIC CONSTANTS
export constexpr auto STEP_MIO_MV_V = 1000;   // Factor to change mV to V
//#define STEP_MIO_BOARD1			 3   // MIO device number

// ADC SPECIFIC CONSTANTS
export constexpr auto POWER_ADC_BOARD = 4;   // ADC device number (same as MIO Board: PCI6024E)
export constexpr auto ADC_FACTOR = 1000000; // conversion factor from Volt to microVolt

// DELAYER_GATE SPECIFIC CONSTANTS
//#define FILEPATH_CALIB      'C:\\Documents and Settings\\Laboratorio\\Desktop\\Copia di Copy (2) of devTrs\\POS'			 // Folder of the calibration file
export constexpr auto N_BIT_DELAYER_GATE = 8;       // Number of bits in imput to delayer
export constexpr auto N_BIT_DELAYER_GATE_COMMAND = 8;
export constexpr auto STEP_DELAYER_GATE = 25;
export constexpr auto SLEEP_DELAYER_GATE = 0.5;
//#define DELAYER_GATE_COM         5

// DELAYER SPECIFIC CONSTANTS
export constexpr auto DELAYER_BAUDRATE = 19200;
export constexpr auto DELAYER_PARITY = 0;
export constexpr auto DELAYER_DATABITS = 8;
export constexpr auto DELAYER_STOPBITS = 1;
export constexpr auto DELAYER_DELTA = 25; 		// stepsize of delayer in ps
export constexpr auto DELAYER_JUMP = 10;		// number of steps to jump to avoid 'if(Actual=Goal) return' for the home
export constexpr auto DELAYER_WAIT = 3;		// wait time (s) to let GatedModule stabilize after delay change


// MICRO SPECIFIC CONSTANTS
export constexpr char MICRO_LCD = 'W';
export constexpr char MICRO_HOLD = 'H';
export constexpr char MICRO_FMIN = 'M';
export constexpr char MICRO_FDELTA = 'A';
export constexpr char MICRO_HOME = 'I';
export constexpr char MICRO_VEL = 'V';
export constexpr char MICRO_GOTO = 'G';
export constexpr char MICRO_TELL = 'T';
export constexpr char MICRO_STOP = 'F';
export constexpr char MICRO_END = 'E';
export constexpr char MICRO_TERM = ';';
export constexpr auto MICRO_GETLENGTH = 16;
export constexpr auto MICRO_HOLD_OFF = 0;
export constexpr auto MICRO_HOLD_MEAS = 1;
export constexpr auto MICRO_HOLD_ON = 2;
export constexpr auto MICRO_LCD_OFF = 0;
export constexpr auto MICRO_LCD_ALL = 1;
export constexpr auto MICRO_LCD_END = 2;
export constexpr auto MICRO_BAUDRATE = 115200;
export constexpr auto MICRO2_BAUDRATE = 2000000; // new micro
export constexpr auto MICRO_PARITY = 0;
export constexpr auto MICRO_DATABITS = 8;
export constexpr auto MICRO_STOPBITS = 1;

// ARDUINO SPECIFIC CONSTANTS
export constexpr char ARD_LCD = 'W';
export constexpr char ARD_HOLD = 'H';
export constexpr char ARD_FMIN = 'M';
export constexpr char ARD_FDELTA = 'A';
export constexpr char ARD_HOME = 'I';
export constexpr char ARD_VEL = 'V';
export constexpr char ARD_GOTO = 'G';
export constexpr char ARD_TELL = 'T';
export constexpr char ARD_STOP = 'F';
export constexpr char ARD_END = 'E';
export constexpr char ARD_TERM = ';';
export constexpr auto ARD_GETLENGTH = 16;
export constexpr auto ARD_HOLD_OFF = 0;
export constexpr auto ARD_HOLD_MEAS = 1;
export constexpr auto ARD_HOLD_ON = 2;
export constexpr auto ARD_LCD_OFF = 0;
export constexpr auto ARD_LCD_ALL = 1;
export constexpr auto ARD_LCD_END = 2;
export constexpr auto ARD_BAUDRATE = 115200;
export constexpr auto ARD_PARITY = 0;
export constexpr auto ARD_DATABITS = 8;
export constexpr auto ARD_STOPBITS = 1;

// ESP300 SPECIFIC CONSTANTS
export constexpr auto ESP300_TERM = 13; // Terminator = Carriage Return
export constexpr auto ESP300_BAUDRATE = 19200;
export constexpr auto ESP300_PARITY = 0;
export constexpr auto ESP300_DATABITS = 8;
export constexpr auto ESP300_STOPBITS = 1;
export constexpr const char* ESP300_VEL = "VA";
export constexpr const char* ESP300_MAXVEL = "VU";
export constexpr const char* ESP300_GOTO = "PA";
export constexpr const char* ESP300_WAIT = "WS";
export constexpr const char* ESP300_TELL = "TP";
export constexpr const char* ESP300_STOP = "ST";
export constexpr const char* ESP300_VER = "VE";
export constexpr const char* ESP300_STATUS = "TS";
export constexpr const char* ESP300_STAGE = "ID";
export constexpr const char* ESP300_QUITPROG = "QP"; // Quit Program mode (just in case)
export constexpr const char* ESP300_TRAJTRAP = "TJ1"; // Define Trapezoidal velocity profile (trajectory)
export constexpr const char* ESP300_TRAJS = "TJ2"; // Define S-Shape velocity profile (trajectory)


// LT900 SPECIFIC CONSTANTS
export constexpr auto LT900_TERM = 13; // Terminator = Carriage Return
export constexpr auto LT900_BAUDRATE = 9600;
export constexpr auto LT900_PARITY = 0;
export constexpr auto LT900_DATABITS = 8;
export constexpr auto LT900_STOPBITS = 1;
export constexpr const char* LT900_RESET = "*RST";
export constexpr const char* LT900_GO0 = "SWITCH:0";
export constexpr const char* LT900_ANS_RESET = "0,OK";
export constexpr const char* LT900_ANS_GO0 = "00,OK";


// CHAM SPECIFIC CONSTANTS
export constexpr auto CHAM_TERM = 13; // Terminator = Carriage Return
export constexpr auto CHAM_BAUDRATE = 19200;
export constexpr auto CHAM_PARITY = 0;
export constexpr auto CHAM_DATABITS = 8;
export constexpr auto CHAM_STOPBITS = 1;
export constexpr const char* CHAM_VEL = "VA";
export constexpr const char* CHAM_GOTO = "PA";
export constexpr const char* CHAM_WAIT = "WS";
export constexpr const char* CHAM_TELL = "TP";
export constexpr const char* CHAM_STOP = "ST";


// PI SPECIFIC CONSTANTS
export constexpr const char* PI_HOME = "DH";
export constexpr const char* PI_VEL = "SV";
export constexpr const char* PI_GOTO = "MA";
export constexpr const char* PI_TELL = "TP";
export constexpr const char* PI_STOP = "AB";
export constexpr char PI_TERM = ';';
export constexpr auto PI_GETLENGTH = 16;
export constexpr auto PI_BAUDRATE = 9600;
export constexpr auto PI_DEVICE = 1;


// AOTF CONSTANTS
export constexpr auto AOTF_FREQ_FACTOR = 1000000; //1E9->HZ, 1E6->KHz, 1E3->MHz
export constexpr auto AOTF_VOLT_FACTOR = 1000;   //1->Volt, 1000->mV


// NKT COMMUNICATIONS CONSTANTS
export constexpr auto NKT_BAUDRATE = 115200;
export constexpr auto NKT_PARITY = 0;
export constexpr auto NKT_DATABITS = 8;
export constexpr auto NKT_STOPBITS = 1;
export constexpr auto NKT_SOT = 0x0D;
export constexpr auto NKT_EOT = 0x0A;
export constexpr auto NKT_SOE = 0x5E;
export constexpr auto NKT_ECC = 0x40;
export constexpr auto NKT_TXBUFFERSIZE = 240;
export constexpr auto NKT_SOURCE = 66;
export constexpr auto NKT_NONE = 0;
export constexpr auto NKT_U8 = 1;
export constexpr auto NKT_U16 = 2;
export constexpr auto NKT_U32 = 3;
export constexpr auto NKT_DESTINATION = 6;
export constexpr auto NKT_READ_REG = 0x04;
export constexpr auto NKT_WRITE_REG = 0x05;
export constexpr auto NKT_LAMBDA_REG = 0x90;
export constexpr auto NKT_POW_REG = 0xB0;
export constexpr auto NKT_LAMBDA_MIN = 0x34;
export constexpr auto NKT_LAMBDA_MAX = 0x35;




// STANDA SPECIFIC CONSTANTS
export constexpr float STANDA_MaxTemp = 70.0f;
export constexpr float STANDA_AccelT = 200.0f;
export constexpr float STANDA_DecelT = 200.0f;
export constexpr float STANDA_BTimeout1 = 500.0f;
export constexpr float STANDA_BTimeout2 = 500.0f;
export constexpr float STANDA_BTimeout3 = 500.0f;
export constexpr float STANDA_BTimeout4 = 500.0f;
export constexpr float STANDA_BTO1P = 100.0f;
export constexpr float STANDA_BTO2P = 200.0f;
export constexpr float STANDA_BTO3P = 300.0f;
export constexpr float STANDA_BTO4P = 600.0f;
export constexpr float STANDA_MinP = 500.0f;
export constexpr float STANDA_BTimeoutR = 500.0f;
export constexpr float STANDA_LoftPeriod = 500.0f;
export constexpr auto STANDA_RTDelta = 200;
export constexpr auto STANDA_RTMinError = 15;
export constexpr float STANDA_EncMult = 2.5f;
export constexpr auto STANDA_MaxLoft = 32;
export constexpr float STANDA_PTimeout = 100.0f;
export constexpr auto STANDA_SynOUTP = 1;
export constexpr auto STANDA_TICSxSTEP = 8;



// MONO SPECIFIC CONSTANTS
export constexpr auto MONO_HOME = 12;
export constexpr auto MONO_VEL = 13;
export constexpr auto MONO_GOTO = 12;
export constexpr auto MONO_READPOS = 29;
export constexpr auto MONO_BAUDRATE = 9600;
export constexpr auto MONO_PARITY = 0;
export constexpr auto MONO_DATABITS = 8;
export constexpr auto MONO_STOPBITS = 1;
export constexpr auto MONO_MASKL = 255;
export constexpr auto MONO_MASKH = 65280;
export constexpr auto MONO_SEC_TO_MIN = 60;
export constexpr auto MONO_NM_TO_AMG = 10;
export constexpr auto MONO_TIMEOUT = 1;
export constexpr auto MONO_TIMEOUT_OFFSET = 0.5;


// MONO_TCP SPECIFIC CONSTANTS
export constexpr auto MONO_TCP_STRLEN = 256;
export constexpr auto MONO_TCP_WAIT_TIME = 1000;
export constexpr auto MONO_TCP_PORT = 1;
export constexpr const char* MONO_IP_ADDRESS_FILE = "M:\\Programs\\ControlloDigikrom\\DigikIp.txt";
export constexpr char MONO_TCP_INIT_COMMAND = 'i';
export constexpr char MONO_TCP_CLOSE_COMMAND = 'c';
export constexpr char MONO_TCP_HOME_COMMAND = 'h';
export constexpr char MONO_TCP_MOVE_COMMAND = 'm';
export constexpr char MONO_TCP_VEL_COMMAND = 'v';
export constexpr char MONO_TCP_TELL_COMMAND = 't';
export constexpr char MONO_TCP_WAIT_COMMAND = 'w';



/* PWM SPECIFIC CONSTANTS */
/* pwm commands */
export constexpr char PWM_ABS_GOTO = 'A';
export constexpr char PWM_REL_GOTO = 'R';
export constexpr char PWM_STOP = 'K';
export constexpr char PWM_SETHOME = 'H';
export constexpr char PWM_SETSPEED = 'S';
export constexpr char PWM_TELL = 'G';
export constexpr char PWM_RESET = 'H';
export constexpr auto PWM_STRLEN = 7;
/* pwm replies  */
export constexpr const char* PWM_READY = "R00000;";
export constexpr const char* PWM_ERROR = "E00000;";
export constexpr const char* PWM_CURPOS = "P+";
/* pwm COMport parameters */
export constexpr auto PWM_BAUDRATE = 38400;
export constexpr auto PWM_PARITY = 0;
export constexpr auto PWM_DATABITS = 8;
export constexpr auto PWM_STOPBITS = 1;
/* pwm limits and resolution */
export constexpr auto PWM_STEP_MAX = 5000;
export constexpr auto PWM_STEP_MIN = 0;
export constexpr auto PWM_FREQ_MAX = 1000;
export constexpr auto PWM_FREQ_MIN = 0;

/* FPM SPECIFIC CONSTANTS */
/* Calibration factor --> power[uW] = FPM_value / FPM_CALIB_FACT   */
export constexpr auto FPM_CALIB_FACT = 2.2665;
/* fpm COMport parameters */
export constexpr auto FPM_BAUDRATE = 9600;
export constexpr auto FPM_PARITY = 0;
export constexpr auto FPM_DATABITS = 8;
export constexpr auto FPM_STOPBITS = 1;
export constexpr auto FPM_STRLEN = 10;
/* fpm commands... */
export constexpr const char* FPM_STOPMEAS = "GN";
export constexpr const char* FPM_GETSINGLE = "GS0";
export constexpr const char* FPM_GETCONT = "GC0";
export constexpr const char* FPM_SETSAMPFREQ = "SF";
/* fpm replies... */
export constexpr const char* FPM_OK = "OK";
export constexpr const char* FPM_ERROR = "ER";
export constexpr auto FPM_EINVALCOM = 1	/* Invalid command */;
export constexpr auto FPM_ELENEXC = 2	/* String too long */;
export constexpr auto FPM_EINVALFREQ = 3	/* Invlaid frequency */;


// SWITCH CONSTANTS
export constexpr auto MAX_SWITCH = 10;
export constexpr auto FIBER_OFF = 0;
export constexpr auto FIBER_1 = 1;
export constexpr auto FIBER_2 = 2;
export constexpr auto FIBER_3 = 3;
export constexpr auto FIBER_4 = 4;
export constexpr auto FIBER_5 = 5;
export constexpr auto FIBER_6 = 6;
export constexpr auto FIBER_7 = 7;
export constexpr auto FIBER_8 = 8;
export constexpr auto FIBER_9 = 9;
export constexpr auto FIBER_II = 0;
export constexpr auto FIBER_X = 1;
export constexpr auto SWITCH_LEONI_BAUDRATE = 57600;
export constexpr auto SWITCH_LEONI_PARITY = 0;
export constexpr auto SWITCH_LEONI_DATABITS = 8;
export constexpr auto SWITCH_LEONI_STOPBITS = 1;
export constexpr auto SWITCH_THORWHEEL_BAUDRATE = 115200;


// SYNC CONSTANT
export constexpr auto SYNC_INPUT = 1;
export constexpr auto SYNC_OUTPUT = 2;
export constexpr auto SYNC_ONE = 1;
export constexpr auto SYNC_TWO = 2;
export constexpr auto SYNC_CONT = 3;
export constexpr auto SYNC_LPT = 2;
export constexpr auto SYNC_USB = 3;



/* IEEE488 CONSTANTS */
export constexpr auto GPIBVARRO = 1;	// Varro Address
export constexpr auto GPIBNEWP = 2;    // Newport Address
export constexpr auto IEEETIMEOUT = 60;      // Timeout for IEEE (s)
export constexpr auto GPIB0 = 0;
export constexpr auto DELAYVARRO = 1;       // Delay before getting data from Varro

/* USER INTERFACE CONSTANTS */
export constexpr const char* PATH_UIR = ".\\Sources\\TRS.UIR";
export constexpr auto NEG = -1;
export constexpr auto MEASURING = 0;
export constexpr auto PROCESSING = 1;
export constexpr auto SETTING = 2;
export constexpr auto FAST = 0;
export constexpr auto SLOW = 1;
export constexpr auto CONT = 0;
export constexpr auto LIGTH = 1;
export constexpr auto EXACT = 2;
export constexpr auto ONLY_FIRST = 3;
export constexpr auto ONLY_SEC = 4;
export constexpr auto REF = 0;
export constexpr auto SIG = 1;
export constexpr auto OFF = 0;
export constexpr auto ON = 1;
export constexpr auto SINGLE = 0;
export constexpr auto OSCILL = 1;
export constexpr auto GENERAL = 0;
export constexpr auto MAMMOT = 1;
export constexpr auto OXYM = 2;
export constexpr auto SPECTRA = 3;
export constexpr auto MEAS = 0;
export constexpr auto SYST = 1;
export constexpr auto REFL = 0;
export constexpr auto TRANSM = 1;
export constexpr auto STEP_SINGLE = 0;
export constexpr auto STEP_MULTI = 1;
export constexpr auto STEP_CONT = 2;
export constexpr auto SWITCH_SINGLE = 0;
export constexpr auto SWITCH_MULTI = 1;
export constexpr auto SWITCH_CONT = 2;
export constexpr auto AXIS1 = 0;
export constexpr auto AXIS2 = 1;
export constexpr auto AXIS3 = 2;
export constexpr auto NONE = 0;
export constexpr auto SWITCH2X2 = 1;
export constexpr auto SWITCH1X4 = 2;
export constexpr auto SWITCH1X9 = 3;
export constexpr auto SHUTTER = 4;
export constexpr auto SWITCH_EOL2x2 = 5;
export constexpr auto SWITCH_LUCA = 6;
export constexpr auto SWITCH_LEONI = 7;
export constexpr auto SWITCH_THORWHEEL = 8;
export constexpr auto LPT = 1;
export constexpr auto NEWP = 2;
export constexpr auto TIO = 3;
export constexpr auto MIO = 4;
export constexpr auto MM4005 = 5;
export constexpr auto MICRO = 6;
export constexpr auto MONO = 7;
export constexpr auto MONO_TCP = 8;
export constexpr auto PI1 = 9;
export constexpr auto FPM = 10;
export constexpr auto PWM = 11;
export constexpr auto DELAYER = 12;
export constexpr auto ADC = 13;
export constexpr auto AOTF_FREQ = 14;
export constexpr auto AOTF_POW = 15;
export constexpr auto DELAYER_GATE = 16;
export constexpr auto STANDA = 17;
export constexpr auto NKT_LAMBDA = 18;
export constexpr auto NKT_POW = 19;
export constexpr auto ESP300 = 20;
export constexpr auto LT900 = 21;
export constexpr auto CHAMALEON = 22;
export constexpr auto MICRO2 = 23;
export constexpr auto STEP_STANDA2 = 24;
export constexpr auto ATT_LUCA = 25;
export constexpr auto BCD_SYNC = 26;
export constexpr auto BCD_PIX = 27;
export constexpr auto DMD_TX = 28;
export constexpr auto ARD_FLOW = 29;
export constexpr auto ARD_STEP = 30;
export constexpr auto VARRO = 1;
export constexpr auto NI_6602 = 5;
export constexpr auto COM = 6;
export constexpr auto NIDAQmx = 7;
export constexpr auto SILENA = 2;
export constexpr auto SPC300 = 3;
export constexpr auto HYDRA = 4;
export constexpr auto SPC630 = 5;
export constexpr auto SPC130 = 6;
export constexpr auto TEST = 7;
export constexpr auto TH260 = 8;
export constexpr auto DEMO = 9;
export constexpr auto SPC_SC1000 = 10;
export constexpr auto SPC_SPADLAB = 11;
export constexpr auto SPC_NIRS = 12;
export constexpr auto SPC_LUCA = 13;
export constexpr auto SPC_SWAB = 14;
export constexpr auto SPC_BCD = 15;
export constexpr auto SPC_MHARP = 16;
export constexpr auto WAIT_DELAY = 0;
export constexpr auto WAIT_TIME = 1;
export constexpr auto WAIT_COUNT = 2;
export constexpr auto WAIT_POS = 3;
export constexpr auto WAIT_SPC = 4;
export constexpr auto WAIT_MARKER = 5;
export constexpr auto BYN = 1;
export constexpr auto ASC = 0;
export constexpr auto MEASURE = 0;
export constexpr auto RETRIEVE = 1;
export constexpr auto ORIGIN = 0;
export constexpr auto PEAK = 1;
export constexpr auto SPECTRUM = 1;
export constexpr auto NUMAXIS = 3;
export constexpr auto NUMGATES = 3;
export constexpr auto HEADLEN = 256;
export constexpr auto SHOWROW = 0;
export constexpr auto COL_TRIS_STEP = 1;
export constexpr auto COL_TRIS_SWITCH = 2;
export constexpr auto COL_TRIS_TRIM = 3;
export constexpr auto COL_ROI_PAGE = 1;
export constexpr auto COL_ROI_FIRST = 2;
export constexpr auto COL_ROI_LAST = 3;
export constexpr auto COL_ROI_AREA = 4;
export constexpr auto COL_ROI_MAX = 5;
export constexpr auto COL_ROI_PEAK = 6;
export constexpr auto COL_ROI_WIDTH = 7;
export constexpr auto COL_VALUE_ROI = 1;
export constexpr auto COL_VALUE_AREA = 2;
export constexpr auto COL_VALUE_WIDTH = 3;
export constexpr auto COL_OSCILL_FIRST = 1;
export constexpr auto COL_OSCILL_LAST = 2;
export constexpr auto COL_OSCILL_FRACT = 3;
export constexpr auto CONT_NONE = 0;
export constexpr auto CONT_STEP = 1;
export constexpr auto CONT_RANGE = 2;
export constexpr auto ROW_BANK_NUM = 1;
export constexpr auto ROW_BANK_ACTUAL = 2;
export constexpr auto ROW_BANK_TIMEB = 3;
export constexpr auto ROW_BANK_TIMET = 4;
export constexpr auto ROW_BANK_TIMEA = 5;


/* CONTEST CONSTANTS */
export constexpr auto CONTEST_MEAS = 0;
export constexpr auto CONTEST_OSC = 1;
export constexpr auto CONTEST_TRIM = 2;
export constexpr auto APPL_GEN = 0;
export constexpr auto APPL_MAMM = 1;
export constexpr auto APPL_MOXY = 2;
export constexpr auto APPL_SPECTRA = 3;

/* SPC CONSTANTS */
export constexpr auto MAX_BOARD = 4;
export constexpr auto MAX_DET = 256;
export constexpr auto MAX_PAGE = 256 * 32;
export constexpr auto MAX_FRAME = 1024;
export constexpr auto MAX_ACQ = 1024;
export constexpr auto MAX_ROW_ROI = 32;
export constexpr auto MAX_PLOT = 16;
export constexpr auto SPC_SHORT = 0;
export constexpr auto SPC_LONG = 1;
export constexpr auto SPC_ALL = -1;
export constexpr auto SPC_BANK_DIM = 128 * 1024;
export constexpr auto SPC_NUM_BANK = 2;
export constexpr auto SPC130_TIMEOUT = 2.5;
export constexpr auto SPC_TIMEDELAY = 1; //60	//secondi
export constexpr const char* LABEL_CFD_LIMIT_LOW = "cfd_limit_low";
export constexpr const char* LABEL_CFD_ZC_LEVEL = "cfd_zc_level";
export constexpr const char* LABEL_SYNC_ZC_LEVEL = "sync_zc_level";
export constexpr const char* LABEL_TAC_GAIN = "tac_gain";
export constexpr const char* LABEL_TAC_OFFSET = "tac_offset";
export constexpr const char* LABEL_TAC_LIMIT_LOW = "tac_limit_low";
export constexpr const char* LABEL_TAC_LIMIT_HIGH = "tac_limit_high";
export constexpr auto INFINITY = 60000;
export constexpr auto MBADR = 0x280;  // i/o port address on which the card is mapped
export constexpr auto MAX_CHANN_SILENA = 8192;   //
export constexpr auto GROUP_SILENA = 0;	    //
export constexpr auto EXTAMPL_SILENA = 1;	//
export constexpr auto REALTIME = 0;	    //
export constexpr auto LIVETIME = 1;	    //
export constexpr auto TIMESCALE = 0;	    // seconds ->0       0.01 seconds ->1
export constexpr auto MAXTIME = 3000;   //
export constexpr auto MBC_TO_PC = 0;	    // from mca to pc->0   from pc to mca->1
export constexpr auto SILENA_TIMESTOP = 3;	    //
export constexpr auto COUNTSTOP = 4;	    //
export constexpr auto CALIB_VARRO = 3.02;   // TAC Lab.Elettronica 6/7/98
export constexpr auto CALIB_SILENA = 2.78;
export constexpr auto CALIB_SPC300 = (97.7 / (4 * 4 * 2));
export constexpr auto CALIB_SPC630 = (50 / 1.024);
export constexpr auto CALIB_SPC130 = (50 / 1.024);
export constexpr auto SPC_MIN_TIME = 0.1;	// minimum acquisition time for count control (s)
export constexpr const char* SPC300_INI_FILE = "SPC300.INI";
export constexpr const char* SPC630_INI_FILE = "SPC630.INI";
export constexpr const char* SPC130_1_INI_FILE = "SPC131.INI";
export constexpr const char* SPC130_2_INI_FILE = "SPC132.INI";
export constexpr const char* SPC130_3_INI_FILE = "SPC133.INI";
export constexpr const char* SPC130_4_INI_FILE = "SPC134.INI";
export constexpr const char* THARP_INI_FILE = "TIMEHARP.INI";
export constexpr auto SPC_NORM_FALSE = 0;
export constexpr auto SPC_NORM_TRUE = 1;
export constexpr auto MAX_COUNTS = 1000000000;

/* HYDRA CONSTANTS */
export constexpr auto HYDRA_BINNING = 0; //you can change this
export constexpr auto HYDRA_SYNC_OFFSET = 0;
export constexpr auto HYDRA_INPUT_OFFSET = -8000;
export constexpr auto HYDRA_OFFSET = 0;
export constexpr auto HYDRA_TACQ = 1000; //Measurement time in millisec, you can change this
export constexpr auto HYDRA_SYNC_DIVIDER = 4; //Note: you must reduce SYNC rate to <12.5 MHz
export constexpr auto HYDRA_SYNC_CFDZEROCROSS = 10; //you can change this
export constexpr auto HYDRA_SYNC_CFDLEVEL = 200; //you can change this
export constexpr auto HYDRA_INPUT_CFDZEROCROSS = 10; //you can change this
export constexpr auto HYDRA_INPUT_CFDLEVEL = 100; //you can change this
export constexpr auto HYDRA_LENCODE = 4; //  Note: HistLen=1024*(2^HYDRA_LENCODE)
export constexpr auto HYDRA_DEV0 = 0; // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
export constexpr auto SEC_2_MILLISEC = 1000; // conversion factor for second to millisecond

/* MHARP CONSTANTS */
export constexpr auto MHARP_DEV0 = 0; // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
export constexpr auto T3HISTBINS = 32768; //=2^15, dtime in T3 mode has 15 bits (w/o binning???)
export constexpr auto MH_SLEEPFORSYNCRATE = 300; // After Init allow 150 ms for valid  count rate readings
export constexpr const char* MH_FILEEXT = "mhbin"; // file extension for MultiHarp Time Tags
export constexpr auto MHARP_SLEEP_THREAD = 0.001; // number of seconds to sleep if FIFO or Buffer not ready
export constexpr auto MHARP_MAX_DET = 16; // Max number of det in input
export constexpr auto MHARP_MAX_BIN = 16384; // Max number of bins
export constexpr auto MHARP_BUFFER_MULT = 4; // Expand the buffer
//export constexpr auto MHARP_SIZE_RING_M = MHARP_BUFFER_MULT * TTREADMAX; // Size of Ring Buffer for Acquisition
//export constexpr auto MHARP_SIZE_RING_A = MHARP_BUFFER_MULT * MHARP_MAX_DET * MHARP_MAX_BIN; // Size of Ring Buffer for Analysis


/* TH260 CONSTANTS */
export constexpr auto TH260_BINNING = 0; //you can change this
export constexpr auto TH260_SYNC_OFFSET = 8600;
export constexpr auto TH260_INPUT_OFFSET = 0;
export constexpr auto TH260_OFFSET = 0;
export constexpr auto TH260_TACQ = 1000; //Measurement time in millisec, you can change this
export constexpr auto TH260_SYNC_DIVIDER = 4; //Note: you must reduce SYNC rate to <12.5 MHz
export constexpr auto TH260_SYNC_CFDZEROCROSS = -10; //you can change this
export constexpr auto TH260_SYNC_CFDLEVEL = -400; //you can change this
export constexpr auto TH260_INPUT_CFDZEROCROSS = -10; //you can change this
export constexpr auto TH260_INPUT_CFDLEVEL = -50; //you can change this
export constexpr auto TH260_LENCODE = 4; //  Note: HistLen=1024*(2^TH260_LENCODE)
export constexpr auto TH260_DEV0 = 0; // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
//++export constexpr auto SEC_2_MILLISEC = 1000; // conversion factor for second to millisecond
export constexpr auto MILLISEC_2_SEC = 1 / 1000; // conversion factor for millisecond to second

/* SC1000 CONSTANTS */
//++export constexpr auto SC1000_TYPE = unsigned long;			// data type of hystogram SC1000 data (non-lin)
export constexpr auto SC1000_TIME_INFINITY = 1000000;       // sec
//++export constexpr auto SC1000_BINDEPTH = BS32;					// max size of the bin (BS32=unsigned int)
export constexpr auto SC1000_LINEARISE = 1;					// 1 = use background file to linearise time scale, 0 = do not linearise
export constexpr auto SC1000_HARDREFOLD = 5;					// hardware refolding using SC and Modulo
export constexpr auto SC1000_NODATAOPERATION = -1;
export constexpr auto SC1000_MAXBIN = 40800;		// max number of channels (bin) in SC1000 // 10 mhz
export constexpr auto SC1000_REBIN = 32;
export constexpr auto SC1000_MAX_COUNT_RATE = 30000000;
export constexpr auto SC1000_MIN_COUNT_RATE = 7000;

/* SPADLAB CONSTANTS */
export constexpr const char* SPADLAB_TDC_WRITE = "\\\\localhost\\MyProcess\\tdc-write";
export constexpr const char* SPADLAB_TRS_WRITE = "\\\\localhost\\myprocess\\trs-write";
export constexpr auto SPADLAB_DATAIN = 1;
export constexpr auto SPADLAB_MAXTIME = 5000; // max wait time to be sent in transmit the DataIn command

/* NIRS CONSTANTS */
export constexpr auto NIRS_HISTLEN = 8192;	   // number of channels per lambda (fixed)
export constexpr auto NIRS_DT = (10000.0 / 1024); // (ps) Time Bin
//++export constexpr auto NIRS_REGLEN = ((int32_t)128);
//++export constexpr auto NIRS_STATLEN = ((uint32_t)3);
export constexpr auto NIRS_DETNUM = 2;
export constexpr auto NIRS_LAMBDA1 = 1;
export constexpr auto NIRS_LAMBDA2 = 2;
export constexpr auto NIRS_LAMBDA12 = 3;

/* LUCA CONSTANTS */
export constexpr auto LUCA_HISTLEN = 8192;	   // number of channels per detector (fixed)
export constexpr auto LUCA_DT = (10000.0 / 1024); // (ps) Time Bin
//++export constexpr auto LUCA_REGLEN = ((int32_t)128);
export constexpr auto LUCA_NUMDET = 2;
//++export constexpr auto LUCA_STATLEN = ((uint32_t)3);
export constexpr auto LUCA_DETNUM = 2;
export constexpr auto LUCA_STOP = 0;
export constexpr auto LUCA_AUTO = 1;
export constexpr auto LUCA_MANUAL = 2;
export constexpr auto LUCA_SHOT = 3;
export constexpr auto LUCA_ATT_ABS = 0;
export constexpr auto LUCA_ATT_INC = 1;
export constexpr auto LUCA_ATT_DEC = 2;
export constexpr auto LUCA_ATT_DB = 3;
export constexpr auto LUCA_ATT_IDLE = 0;
export constexpr auto LUCA_ATT_DONE = 1;
export constexpr auto LUCA_ATT_RUNNING = 2;
export constexpr auto LUCA_ATT_ERROR = 3;
export constexpr const char* LUCA_FILE_HANDLE = "LucaHandle.log";

/* SWAB CONSTANTS */
export constexpr auto SWAB_MAX_DET = 18;		// max number of detectors in SwabianBoard
export constexpr auto SWAB_NONE = 0;		// no detector
export constexpr auto SWAB_SIGN = 1;		// sign detector
export constexpr auto SWAB_SYNC = 2;		// sync detector
export constexpr auto SWAB_REPLAY_SPEED = 1.0;		// replay at SWAB_REPLAY_SPEED*real speed
export constexpr auto SWAB_S2PS = 1E12;	// seconds to ps conversion
export constexpr const char* SWAB_FILEEXT = "ttbin"; // file extension for Time Tags
export constexpr auto SWAB_HIST = 1;		// corresponds to classical TPSF histogram
export constexpr auto SWAB_CORR = 2;		// corresponds to correlation among 2 channels
export constexpr auto SWAB_REAL = 1;		// Real Time Tagger
export constexpr auto SWAB_VIRTUAL = 2;		// Virtual Time Tagger
export constexpr auto COL_SWAB_DETTYPE = 1;		// Column in UIR SWAB Panel Table corressponding to DetType
export constexpr auto COL_SWAB_LEVEL = 2;		// Column in UIR SWAB Panel Table corressponding to DetType
export constexpr auto COL_SWAB_DELAY = 3;		// Column in UIR SWAB Panel Table corressponding to DetType

/* BCD CONSTANTS */
export constexpr auto BCD_MAXBIN = 256;		// LEN of the TDC Array
export constexpr auto BCD_MAXPIX = 2048;	// Maximum size of the Pixel Matrix
export constexpr auto BCD_QUADRANTS = 0b00001111;
export constexpr auto BCD_STEPCOARSE = 1280;	// (ps) Coarse Step of the Gate/delay
export constexpr auto BCD_STEPFINE = 100;		// (ps) Fine Step of the Gate/delay


/* TEST CONSTANTS */
export constexpr auto TEST_MUS = 10.0;
export constexpr auto TEST_MUA = 0.10;
export constexpr auto TEST_RHO = 2.0;
export constexpr auto TEST_V = 0.03 / 1.5;
export constexpr auto TEST_AREA = 1000000;
export constexpr auto TEST_NOISE = 0.1;
export constexpr auto TEST_CALIB = 3.0;


/* TRIMMER CONSTANTS */
export constexpr auto MAX_TRIM = 10;
export constexpr auto TARGET_AREA = 0;
export constexpr auto TARGET_STDEV = 1;
export constexpr auto TARGET_WIDTH = 2;
export constexpr auto TARGET_AREAWIDTH = 3;
export constexpr auto TARGET_MAX_BOARD_AREA = 4;
export constexpr auto TRIM_DIR_NEG = -1;
export constexpr auto TRIM_DIR_POS = 1;
export constexpr auto TRIM_SCAN_MIDDLE = 0;
export constexpr auto TRIM_SCAN_UP = 1;
export constexpr auto TRIM_SCAN_DOWN = 2;
export constexpr auto TRIM_SCAN_RANGE = 3;
export constexpr auto TRIM_WAIT_POS = 0;
export constexpr auto TRIM_WAIT_TIME = 1;
export constexpr auto TRIM_WAIT_SPC = 2;
export constexpr auto INIT_HIGHER = 0;
export constexpr auto INIT_LOWER = 1E20;
export constexpr const char* FNAME_TRIM = "POS\\TRIM";
export constexpr const char* FEXT_TRIM = ".POS";
export constexpr const char* SAVETRIM_TITLE_1 = "DO YOU WANT TO SAVE CHANGES TO FILE ";
export constexpr const char* SAVETRIM_MESSAGE_1 = "You can SAVE CHANGES, SAVE & COPY previous version,\nSAVE CHANGES in a new file specified in the input box";
export constexpr const char* SAVETRIM_TITLE_2 = "SET HOME TO ZERO";
export constexpr const char* SAVETRIM_MESSAGE_2 = "Do you want to set HOME position to ZERO?";

/* ########################  MAMMOT CONSTANTS  ################################# */
export constexpr auto MAMM_VIS = 0;
export constexpr auto MAMM_NIR = 1;
export constexpr auto MAMM_NIR_IDX_MIN_BORDER = 400;
export constexpr auto MAMM_NIR_IDX_MAX_BORDER = 360;
export constexpr auto MAMM_NIR_STEP_MAX = 400;
export constexpr auto MAMM_NUM_BOARD = 2;
export constexpr auto MAMM_NUM_DET = 8; //EDO
export constexpr auto MAMM_NUM_ROW = 240;
export constexpr auto D2 = (char)2;
export constexpr auto X = (char)0;
export constexpr auto Y = (char)1;
export constexpr auto MAMM_DIR_POS = (char)1;
export constexpr auto MAMM_DIR_NEG = (char)-1;
export constexpr auto MAMM_NONE = 0;
export constexpr auto MAMM_ONLY_VIS = 1;
export constexpr auto MAMM_ONLY_NIR = 2;
export constexpr auto MAMM_VIS_AND_NIR = 3;
export constexpr auto MAMM_VIS_OR_NIR = 4;
export constexpr auto MAMM_NUM_LAMBDA = 7;
export constexpr auto MAMM_NORTHWEST_DET = 0;
export constexpr auto MAMM_WEST_DET = 1;
export constexpr auto MAMM_SOUTHWEST_DET = 2;
export constexpr auto MAMM_SOUTH_DET = 3;
export constexpr auto MAMM_SOUTHEAST_DET = 4;
export constexpr auto MAMM_EAST_DET = 5;
export constexpr auto MAMM_NORTHEAST_DET = 6;
export constexpr auto MAMM_NORTH_DET = 7;




/* OMA CONSTANTS  */
/***/
export constexpr auto OMA_NONE = -1;
export constexpr const char* OMA_IP_ADDRESS_FILE = "c:\\Programs\\ControlloOMA\\ipAddress.txt";
/* file contenente l'indirizzo IP del PC su cui � lanciato il programma dell'OMA */
export constexpr auto OMA_PORT = 10000				   /* porta del programma dell'OMA */;
export constexpr auto OMA_ADDRESS_LENGHT = 20					   /* lunghezza dell'array contenetne l'indirizzo IP */;
export constexpr auto OMA_BUFFER_LENGHT = 256					   /* lunghezza buffer */;
export constexpr auto OMA_WAIT_TIME = 1000				   /* tempo d'attesa prima di restituire errore durante una chiamta TCP */;
export constexpr auto OMA_NO_CONNECTION = -12					   /* codice d'errore */;
export constexpr auto OMA_READY_STRING_LENGHT = 6					   /* lunghezza della stringa di "Ready?" */;

/* OPHIR SPECIFIC CONSTANTS */
export constexpr auto OPHIR_NONE = -1;
export constexpr auto OPHIR_BAUDRATE = 9600;
export constexpr auto OPHIR_PARITY = 0;
export constexpr auto OPHIR_DATABITS = 8;
export constexpr auto OPHIR_STOPBITS = 1;
export constexpr auto OPHIR_STRLEN = 10;

/* LABEL CONSTANTS */
export constexpr auto LABEL_MAX = 16;
export constexpr auto LABEL_NAMELEN = 12;
export constexpr auto LABEL_CONTENTLEN = 22;

/* DOSTEP CONSTANTS */
export constexpr auto DOSTEP_MAX = 3;
export constexpr auto DOSTEP_NONE = -1;

/* DISPLAY CONSTANTS */
//export constexpr auto MAX_PLOT = 16;
export constexpr auto COLOR_FULL = 256;
export constexpr auto COLOR_FRACT = 0.5;
export constexpr auto WINDOW_MANUAL = 0;
export constexpr auto WINDOW_REF = 1;
export constexpr auto WINDOW_SIG = 2;
export constexpr auto WINDOW_REFs_SIGs = 3;
export constexpr auto WINDOW_REFSIG_ = 4;
export constexpr auto GRAPH_PLOT = 0;
export constexpr auto GRAPH_ROI = 1;
export constexpr auto GRAPH_LIN = 0;
export constexpr auto GRAPH_LOG = 1;
export constexpr auto MAX_ROW_OSCILL = 2;

/* MOXY CONSTANTS */
export constexpr auto MOXY_NUM_SWITCH = 2;
export constexpr const char* MOXY_END_SWITCH = "N";
export constexpr const char* MOXY_END_COMMAND = "F";
export constexpr const char* MOXY_SET = "S";
export constexpr const char* MOXY_START = "M";
export constexpr const char* MOXY_ABORT = "A";
export constexpr const char* MOXY_GOTO = "P";
export constexpr char MOXY_END = 'O';
export constexpr const char* MOXY_NO_SWITCH = "1";
export constexpr const char* MOXY_SWITCH = "0";
export constexpr auto MOXY_COMPORT = 1;
export constexpr auto MOXY_BAUDRATE = 9600;
export constexpr auto MOXY_PARITY = 0;
export constexpr auto MOXY_DATABITS = 8;
export constexpr auto MOXY_STOPBITS = 1;
export constexpr auto MOXY_OVERHEAD = 0.02;
export constexpr auto SEC_TO_MICROSEC = 1000000;
export constexpr auto MOXY_CHANN_REST = 8;
export constexpr auto MOXY_SWITCH_DELAY = 0.005;

/* GENERAL CONSTANTS */
export constexpr auto FALSE = 0;
export constexpr auto TRUE = 1;
//#define TNONE		 0
//#define TCHAR		 1
//#define TSHORT		 2
//#define TDOUBLE      3
export constexpr auto VER_UNO = 1;
export constexpr auto VER_DUE = 2;
export constexpr auto VER_GEN = 0;
export constexpr auto VER_MAMM = 1;
export constexpr auto VER_MAMM_HEADER = 1;

/* PROFILING CONSTANTS */
export constexpr auto IS_PROFILING = 0;
export constexpr auto PROF_MAX_STRLEN = 20;
export constexpr auto PROF_MAX_ID = 10000;
export constexpr const char* PROF_FILE_NAME = "PROFILING.TXT";

/* ERROR HANDLER CONSTANTS */
export constexpr auto ERR_SPC = 0;
export constexpr auto ERR_MEM = 1;
export constexpr auto ERR_HYDRA = 2;
export constexpr auto ERR_TH260 = 3;
export constexpr auto ERR_SC1000 = 4;
export constexpr auto ERR_GENERIC = 5;
export constexpr auto ERR_SWAB = 6;
export constexpr auto ERR_BCD = 7;
export constexpr auto ERR_MHARP = 8;