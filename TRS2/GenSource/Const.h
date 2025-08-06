#ifndef CONST_H
#define CONST_H

/* ########################   CONSTANTS   ################################# */


// ADDED CONSTANTS
#define STEP_NONE "None"

// VERSION
#define MESSAGE_ABOUT   "Copyright: POLITECNICO DI MILANO\nVersion: 18.0\nDate: November 2020"

// TYPE OF DATA
// USE long for TimeHarp, Varro, Silena, USE short for all others SPC boards.
#define T_DATA unsigned long
#define T_HEAD struct sHeader2
#define T_SUB struct sSubHeader1

/* TOOLS */
#define SIGNUM(x)	 ((x>=0) ? 1:-1)
#define REMINDER(a,b)  	(a-b*(int)(a/b))
#define MAX(a,b)	(a>b?a:b)
#define MIN(a,b)	(a<b?a:b)
#define CEIL(a,b)	(REMINDER(a,b)==0?a/b:a/b+1)

/* GENERAL CONSTANTS */
#define STRLEN 		  128
#define PATHLEN		  128
#define PACKLENGTH 	  6
#define SLI           sizeof(long)
#define SCH           sizeof(char)
#define ns2ps         1000
#define STRLEN_LONG	  1024


/* PROTOCOL CONSTANTS */
#define STRLEN_PROT	 		128
#define STRLEN_FIBER		64
#define MAX_ROW_PROT		16
#define COL_PROT_SOURCE		1
#define COL_PROT_FIBERS		2
#define COL_PROT_ACQSTART	3
#define COL_PROT_ACQSTOP	4
#define MAX_SUB		 		105
#define MAX_ROI_SUB			4
#define MAX_ROW_FIBER		16
#define MAX_FIBER			64
#define MAX_SOURCE		    16 //ALE
#define COL_FIBER_BOARD		1
#define COL_FIBER_DET		2
#define COL_FIBER_FIBERS	3
#define COL_SOURCE_SOURCE	1
#define COL_SOURCE_SWITCH	2
#define COL_SOURCE_CHANN	3
#define COL_MHARP_INPUT_OFFSET		2 // note: first is the label
#define COL_MHARP_INPUT_LEVEL		3
#define COL_MHARP_INPUT_EDGE		4
#define COL_MHARP_INPUT_DEADTIME	5
#define MAX_ROW_SOURCE		16
#define MAX_TWITCH		2
#define MAX_CHANN_SWITCH	2
#define GEOM_COORD_CART		1
#define LAYOUT_PARALL		0
#define LAYOUT_SERIAL		1

/* PRESENTATION CONSTANTS */
#define MAX_ROW_PRES_BLOCK			18
#define MAX_ROW_PRES_LOOP			MAX_LOOP
#define COL_BLOCK_DEF_BLOCK			1
#define COL_BLOCK_DEF_TYPE			2
#define COL_BLOCK_DEF_START_FRAME	3
#define COL_BLOCK_DEF_STOP_FRAME	4
#define COL_BLOCK_DEF_PARAM1		5
#define COL_BLOCK_DEF_PARAM2		6
#define COL_BLOCK_DEF_PARAM3		7
#define COL_BLOCK_SEQUENCE_BLOCK	1
#define COL_BLOCK_SEQUENCE_REPEAT	2
#define ROW_LOOP_PARTITION_LOOP3	1
#define ROW_LOOP_PARTITION_LOOP2	2
#define ROW_LOOP_PARTITION_LOOP1	3
#define END_TYPE_POINTER			3
#define END_LENGTH_POINTER			0
#define END_PARAM1_POINTER			']'
#define END_PARAM2_POINTER			']'
#define END_PARAM3_POINTER			']'
#define BASELINE_CONST				0
#define TASK_CONST					1
#define RECOVERY_CONST				2

/* TABLE CONSTANTS */
#define MAX_TABLE		1375
#define STRLEN_TABLE	20
#define TCHAR			0
#define TINT			1
#define TDOUBLE			2
#define	TSTRING			3
#define CE				0
#define CT				1
#define MAX_TTABLE		13
#define STRLEN_TTABLE	20
#define MAX_PANEL		18

/* FILE CONSTANTS AND ENVIRONMENT SETTINGS */
#define EXTASCII      ".TXT"
#define NUMZERO 	  4
#define FILESET		"SET\\TRS.TRS"
#define DIRPROG		""
#define DIRSETTINGS   "SET"
#define DIR_INI      "INI"
#define EXTSETTINGS   "*.TRS"
#define EXTFILEPOS	  ".POS"
#define DIRFILEPOS	  "POS"
#define EXTFILETRIM	  ".TRM"
#define DIRFILETRIM	  "TRM"
#define EXTFILEBREAK  ".BRE"
#define DIRFILEBREAK  "BREAK"

/* LOOP CONSTANTS */
#define MAX_LOOP		5
#define LOOP_NONE	   -1
#define LOOP1			0
#define LOOP2			1
#define LOOP3			2
#define LOOP4			3
#define LOOP5			4
#define MAXBREAK		1000	 // Maximum number of lines in file break

/* TIME BASE CONSTANTS */
#define TIME_WIN		0
#define TIME_TIOMAMM	1

/* STEPPER CONSTANTS */
#define STEP_SIGN_POS	0
#define STEP_SIGN_NEG	1
#define WAIT_FALSE		0
#define WAIT_TRUE		1
#define NEWP_VEL_CORR	(1.000/1.005) // Empirical correction factor for nominal velocity
#define NEWP_FAST_RV	400		// Ramp Velocity (um/s) #400
#define NEWP_SLOW_RV	100		// Ramp Velocity (um/s) #100
#define NEWP_CONT_RV	5000	// Ramp Velocity (um/s) #5000
#define NEWP_FAST_XV	65000	// Max  Velocity (um/s) #65000
#define NEWP_SLOW_XV	1000	// Max  Velocity (um/s) #1000
#define NEWP_CONT_XV	100000	// Max  Velocity (um/s) #100000
#define NEWP_FAST_RW	1000	// Ramp Width (ms)      #1000
#define NEWP_SLOW_RW	500		// Ramp Width (ms)		#500
#define NEWP_CONT_RW	500		// Ramp Width (ms)	    #500
#define NEWP_FAST_SV	4000	// Set Velocity (um/s)  #40000
#define NEWP_SLOW_SV	200		// Set Velocity (um/s)  #200
#define STEP_EQUAL_POS	11		// Maximum number of unchanged pos
#define FACTOR_MONO	   1
#define FACTOR_TUNE    100
#define FACTOR_NEWP    1		// Loop Step (um)	#1000
#define FACTOR_TIO     2	   //Loop Step factor with TIO board
#define MAXITERNEWP	   10    // Maximum number of iterations in MoveNewp to reach Goal
#define MAX_STEP	   6

#define LPT1 		   888	 // PARALLEL PORT ADDRESS (PIN 11,17-25 -> GND)
#define STEP_LPT_ON_1  0x01	 // LSB 	-> PIN 2	(Axis1)
#define STEP_LPT_ON_2  0x08  // LSB + 3	-> PIN 5	(Axis2)
#define STEP_LPT_CW_1  0x02  // LSB + 1	-> PIN 3	(Axis1)
#define STEP_LPT_CW_2  0x10	 // LSB + 4	-> PIN 6	(Axis2)
#define STEP_LPT_AWO_1 ~0x04 // LSB + 2	-> PIN 4	(Axis1)
#define STEP_LPT_AWO_2 ~0x20 // LSB + 5	-> PIN 7	(Axis2)

#define SLEEP_MONO 	   0.002	 // 0.025 Sleep Time for MONO (s)
#define SLEEP_TUNE 	   0.008	 // Sleep Time for TUNE	(s)
#define SLEEP_NEWP     5
#define STEPS_MONO	   1      // Number of Steps Moto for 1 nm  (nanometer)
#define STEPS_TUNE	   8       // Number of Steps Tune for 0.01 mm  (millimeter)
#define STEPS_NEWP	   "000"   // Number of Steps Newp for 1 mm ("0" = *10 steps)
#define MAXPOS	   	   10000	 // Maximum number of step or switch positions
#define EXP_STEP	   1.0
#define SLEEP_MIN_MVIS 0.005 //0.010
#define SLEEP_MAX_MVIS 0.020 //0.040
#define SLEEP_MIN_MNIR 0.0025 //0.010
#define SLEEP_MAX_MNIR 0.0025 //0.040
#define SLEEP_MIN_TUNE 0.002 //0.002
#define SLEEP_MAX_TUNE 0.002 //0.002
#define SPEED          30  // Newport velocity (mm/s)

// TIO SPECIFIC CONSTANTS
#define STEP_TIO_BOARD1			1		// First Tio Board
#define STEP_TIO_BOARD2			2		// Second Tio Board
#define STEP_TIO_PORT0			"0"		// First Port on Tio
#define STEP_TIO_PORT1			"1"		// Second Port on Tio
#define STEP_TIO_LINE_DIR		 0		// Digital Line Direction
#define STEP_TIO_LINE_ENABLE	 1		// Digital Line Enable
#define STEP_TIO_LINE_HALF		 2		// Digital Line HalfStep
#define STEP_TIO_COUNT_GATE		 1		// Counter Gate
#define STEP_TIO_COUNT_CLOCK	 2		// Counter Clock
#define STEP_TIO_COUNT_COUNT	 3		// Counter Counter
#define HIGH_LEVEL		 		 1		// Digital Level High
#define LOW_LEVEL		 		 0		// Digital Level Low
#define STEP_TIO_NUM_LINE	 	 2		// Number of Lines used for each Tio Stepper
#define STEP_TIO_NUM_COUNT		 3		// Number of Counters used for each Tio Stepper
#define STEP_TIO_MAX_LINE		 8		// Max lines per Tio Board

// MIO SPECIFIC CONSTANTS
#define STEP_MIO_MV_V			 1000   // Factor to change mV to V
//#define STEP_MIO_BOARD1			 3   // MIO device number

// ADC SPECIFIC CONSTANTS
#define POWER_ADC_BOARD			 4   // ADC device number (same as MIO Board: PCI6024E)
#define ADC_FACTOR				 1000000 // conversion factor from Volt to microVolt

// DELAYER_GATE SPECIFIC CONSTANTS
//#define FILEPATH_CALIB      'C:\\Documents and Settings\\Laboratorio\\Desktop\\Copia di Copy (2) of devTrs\\POS'			 // Folder of the calibration file
#define N_BIT_DELAYER_GATE       8       // Number of bits in imput to delayer
#define N_BIT_DELAYER_GATE_COMMAND    8
#define STEP_DELAYER_GATE        25
#define SLEEP_DELAYER_GATE       0.5
//#define DELAYER_GATE_COM         5

// DELAYER SPECIFIC CONSTANTS
#define DELAYER_BAUDRATE 	19200
#define DELAYER_PARITY 		0
#define DELAYER_DATABITS	8
#define DELAYER_STOPBITS	1
#define DELAYER_DELTA		25 		// stepsize of delayer in ps
#define DELAYER_JUMP		10		// number of steps to jump to avoid 'if(Actual=Goal) return' for the home
#define DELAYER_WAIT		3		// wait time (s) to let GatedModule stabilize after delay change


// MICRO SPECIFIC CONSTANTS
#define MICRO_LCD		'W'
#define MICRO_HOLD		'H'
#define MICRO_FMIN		'M'
#define MICRO_FDELTA	'A'
#define MICRO_HOME		'I'
#define MICRO_VEL		'V'
#define MICRO_GOTO		'G'
#define MICRO_TELL		'T'
#define MICRO_STOP		'F'
#define MICRO_END		'E'
#define MICRO_TERM		';'
#define MICRO_GETLENGTH	16
#define MICRO_HOLD_OFF	0
#define MICRO_HOLD_MEAS	1
#define MICRO_HOLD_ON	2
#define MICRO_LCD_OFF	0
#define MICRO_LCD_ALL	1
#define MICRO_LCD_END	2
#define MICRO_BAUDRATE 	115200
#define MICRO2_BAUDRATE 2000000 // new micro
#define MICRO_PARITY 	0
#define MICRO_DATABITS	8
#define MICRO_STOPBITS	1

// ARDUINO SPECIFIC CONSTANTS
#define ARD_LCD		'W'
#define ARD_HOLD	'H'
#define ARD_FMIN	'M'
#define ARD_FDELTA	'A'
#define ARD_HOME	'I'
#define ARD_VEL		'V'
#define ARD_GOTO	'G'
#define ARD_TELL	'T'
#define ARD_STOP	'F'
#define ARD_END		'E'
#define ARD_TERM	';'
#define ARD_GETLENGTH	16
#define ARD_HOLD_OFF	0
#define ARD_HOLD_MEAS	1
#define ARD_HOLD_ON		2
#define ARD_LCD_OFF		0
#define ARD_LCD_ALL		1
#define ARD_LCD_END		2
#define ARD_BAUDRATE 	115200
#define ARD_PARITY 		0
#define ARD_DATABITS	8
#define ARD_STOPBITS	1

// ESP300 SPECIFIC CONSTANTS
#define ESP300_TERM		13 // Terminator = Carriage Return
#define ESP300_BAUDRATE 19200
#define ESP300_PARITY 	0
#define ESP300_DATABITS	8
#define ESP300_STOPBITS	1
#define ESP300_VEL		"VA"
#define ESP300_MAXVEL	"VU"
#define ESP300_GOTO		"PA"
#define ESP300_WAIT		"WS"
#define ESP300_TELL		"TP"
#define ESP300_STOP		"ST"
#define ESP300_VER		"VE"
#define ESP300_STATUS	"TS"
#define ESP300_STAGE	"ID"
#define ESP300_QUITPROG	"QP" // Quit Program mode (just in case)
#define ESP300_TRAJTRAP	"TJ1" // Define Trapezoidal velocity profile (trajectory)
#define ESP300_TRAJS	"TJ2" // Define S-Shape velocity profile (trajectory)


// LT900 SPECIFIC CONSTANTS
#define LT900_TERM		13 // Terminator = Carriage Return
#define LT900_BAUDRATE  9600
#define LT900_PARITY 	0
#define LT900_DATABITS	8
#define LT900_STOPBITS	1
#define LT900_RESET		"*RST"
#define LT900_GO0		"SWITCH:0"
#define LT900_ANS_RESET		"0,OK"
#define LT900_ANS_GO0		"00,OK"


// CHAM SPECIFIC CONSTANTS
#define CHAM_TERM		13 // Terminator = Carriage Return
#define CHAM_BAUDRATE 19200
#define CHAM_PARITY 	0
#define CHAM_DATABITS	8
#define CHAM_STOPBITS	1
#define CHAM_VEL		"VA"
#define CHAM_GOTO		"PA"
#define CHAM_WAIT		"WS"
#define CHAM_TELL		"TP"
#define CHAM_STOP		"ST"


// PI SPECIFIC CONSTANTS

#define PI_HOME		"DH"
#define PI_VEL		"SV"
#define PI_GOTO		"MA"
#define PI_TELL		"TP"
#define PI_STOP		"AB"

#define PI_TERM		';'

#define PI_GETLENGTH	16

#define PI_BAUDRATE 	9600

#define PI_DEVICE	1


// AOTF CONSTANTS
#define AOTF_FREQ_FACTOR 1000000 //1E9->HZ, 1E6->KHz, 1E3->MHz
#define AOTF_VOLT_FACTOR 1000   //1->Volt, 1000->mV


// NKT COMMUNICATIONS CONSTANTS

#define NKT_BAUDRATE	115200
#define NKT_PARITY		0
#define NKT_DATABITS	8
#define NKT_STOPBITS	1
#define NKT_SOT 		0x0D
#define NKT_EOT 		0x0A
#define NKT_SOE 		0x5E
#define NKT_ECC 		0x40
#define NKT_TXBUFFERSIZE 240
#define NKT_SOURCE		66
#define NKT_NONE		0
#define NKT_U8			1
#define NKT_U16			2
#define NKT_U32			3
#define NKT_DESTINATION 6
#define NKT_READ_REG	0x04
#define NKT_WRITE_REG	0x05
#define NKT_LAMBDA_REG	0x90
#define NKT_POW_REG		0xB0
#define NKT_LAMBDA_MIN	0x34
#define NKT_LAMBDA_MAX	0x35




// STANDA SPECIFIC CONSTANTS
#define STANDA_MaxTemp 70.0f
#define STANDA_AccelT 200.0f
#define STANDA_DecelT 200.0f
#define STANDA_BTimeout1 500.0f
#define STANDA_BTimeout2 500.0f
#define STANDA_BTimeout3 500.0f
#define STANDA_BTimeout4 500.0f
#define STANDA_BTO1P 100.0f
#define STANDA_BTO2P 200.0f
#define STANDA_BTO3P 300.0f
#define STANDA_BTO4P 600.0f
#define STANDA_MinP 500.0f
#define STANDA_BTimeoutR 500.0f
#define STANDA_LoftPeriod 500.0f
#define STANDA_RTDelta 200
#define STANDA_RTMinError 15
#define STANDA_EncMult 2.5f
#define STANDA_MaxLoft 32
#define STANDA_PTimeout 100.0f
#define STANDA_SynOUTP 1
#define STANDA_TICSxSTEP 8



// MONO SPECIFIC CONSTANTS
#define MONO_HOME		12
#define MONO_VEL		13
#define MONO_GOTO		12
#define MONO_READPOS    29
#define MONO_BAUDRATE 	9600
#define MONO_PARITY 	0
#define MONO_DATABITS	8
#define MONO_STOPBITS	1
#define MONO_MASKL		255
#define MONO_MASKH      65280
#define MONO_SEC_TO_MIN	60
#define MONO_NM_TO_AMG	10
#define	MONO_TIMEOUT	1
#define MONO_TIMEOUT_OFFSET	0.5


// MONO_TCP SPECIFIC CONSTANTS
#define MONO_TCP_STRLEN		256
#define MONO_TCP_WAIT_TIME	1000
#define MONO_TCP_PORT		1
#define	MONO_IP_ADDRESS_FILE		"M:\\Programs\\ControlloDigikrom\\DigikIp.txt"
#define MONO_TCP_INIT_COMMAND		'i'
#define MONO_TCP_CLOSE_COMMAND		'c'
#define MONO_TCP_HOME_COMMAND		'h'
#define MONO_TCP_MOVE_COMMAND		'm'
#define MONO_TCP_VEL_COMMAND		'v'
#define MONO_TCP_TELL_COMMAND		't'
#define MONO_TCP_WAIT_COMMAND		'w'



/* PWM SPECIFIC CONSTANTS */
/* pwm commands */
#define PWM_ABS_GOTO	'A'
#define PWM_REL_GOTO	'R'
#define PWM_STOP        'K'
#define PWM_SETHOME     'H'
#define PWM_SETSPEED    'S'
#define PWM_TELL		'G'
#define PWM_RESET		'H'
#define PWM_STRLEN		 7
/* pwm replies  */
#define PWM_READY       "R00000;"
#define PWM_ERROR       "E00000;"
#define PWM_CURPOS      "P+"
/* pwm COMport parameters */
#define PWM_BAUDRATE 	38400
#define PWM_PARITY		0
#define PWM_DATABITS	8
#define PWM_STOPBITS	1
/* pwm limits and resolution */
#define PWM_STEP_MAX		5000
#define PWM_STEP_MIN		0
#define PWM_FREQ_MAX		1000
#define PWM_FREQ_MIN		0

/* FPM SPECIFIC CONSTANTS */
/* Calibration factor --> power[uW] = FPM_value / FPM_CALIB_FACT   */
#define FPM_CALIB_FACT 2.2665
/* fpm COMport parameters */
#define FPM_BAUDRATE 	9600
#define FPM_PARITY	0
#define FPM_DATABITS	8
#define FPM_STOPBITS	1
#define FPM_STRLEN	10
/* fpm commands... */
#define FPM_STOPMEAS	"GN"
#define FPM_GETSINGLE	"GS0"
#define FPM_GETCONT	"GC0"
#define FPM_SETSAMPFREQ	"SF"
/* fpm replies... */
#define FPM_OK		"OK"
#define FPM_ERROR	"ER"
#define FPM_EINVALCOM	1	/* Invalid command */
#define FPM_ELENEXC	2	/* String too long */
#define FPM_EINVALFREQ	3	/* Invlaid frequency */


// SWITCH CONSTANTS
#define MAX_SWITCH	 10
#define FIBER_OFF    0
#define FIBER_1      1
#define FIBER_2      2
#define FIBER_3      3
#define FIBER_4      4
#define FIBER_5      5
#define FIBER_6      6
#define FIBER_7      7
#define FIBER_8      8
#define FIBER_9      9
#define FIBER_II     0
#define FIBER_X      1

#define SWITCH_LEONI_BAUDRATE	57600
#define SWITCH_LEONI_PARITY		0
#define SWITCH_LEONI_DATABITS	8
#define SWITCH_LEONI_STOPBITS	1

#define SWITCH_THORWHEEL_BAUDRATE	115200


// SYNC CONSTANT
#define SYNC_INPUT   1
#define SYNC_OUTPUT  2
#define SYNC_ONE	 1
#define SYNC_TWO	 2
#define SYNC_CONT	 3
#define SYNC_LPT	 2
#define SYNC_USB	 3



/* IEEE488 CONSTANTS */
#define GPIBVARRO	   1	// Varro Address
#define GPIBNEWP       2    // Newport Address
#define IEEETIMEOUT    60      // Timeout for IEEE (s)
#define GPIB0          0
#define DELAYVARRO     1       // Delay before getting data from Varro

/* USER INTERFACE CONSTANTS */
#define PATH_UIR	".\\Sources\\TRS.UIR"
#define NEG			 -1
#define MEASURING	 0
#define PROCESSING   1
#define SETTING		 2
#define FAST		 0
#define SLOW	 	 1
#define CONT		 0
#define LIGTH		 1
#define EXACT		 2
#define ONLY_FIRST	 3
#define ONLY_SEC	 4
#define REF   		 0
#define SIG   		 1
#define OFF			 0
#define ON           1
#define SINGLE       0
#define OSCILL       1
#define GENERAL      0
#define MAMMOT       1
#define OXYM 	     2
#define SPECTRA		 3
#define MEAS		 0
#define SYST		 1
#define REFL		 0
#define TRANSM		 1
#define STEP_SINGLE	 0
#define STEP_MULTI	 1
#define STEP_CONT	 2
#define SWITCH_SINGLE	 0
#define SWITCH_MULTI	 1
#define SWITCH_CONT  	 2
#define AXIS1 	     0
#define AXIS2 		 1
#define AXIS3		 2
#define NONE		 0
#define SWITCH2X2	 1
#define SWITCH1X4	 2
#define SWITCH1X9	 3
#define SHUTTER 	 4
#define SWITCH_EOL2x2 5
#define SWITCH_LUCA  6
#define SWITCH_LEONI 7
#define SWITCH_THORWHEEL 8

#define LPT			 1
#define NEWP	 	 2
#define TIO			 3
#define MIO			 4
#define MM4005		 5
#define MICRO		 6
#define MONO		 7
#define MONO_TCP     8
#define PI1   		 9
#define FPM			10
#define PWM 		11
#define DELAYER		12
#define ADC	        13
#define AOTF_FREQ	14
#define AOTF_POW	15
#define DELAYER_GATE 16
#define STANDA		 17
#define NKT_LAMBDA	18
#define NKT_POW		19
#define ESP300		20
#define LT900		21
#define CHAMALEON	22
#define MICRO2		23
#define STEP_STANDA2	24
#define ATT_LUCA		25
#define BCD_SYNC	26
#define BCD_PIX		27
#define DMD_TX		28
#define ARD_FLOW	29
#define ARD_STEP	30

#define VARRO		 1
#define NI_6602	     5
#define COM          6
#define NIDAQmx      7
#define SILENA		 2
#define SPC300		 3
#define HYDRA	     4
#define SPC630       5
#define SPC130       6
#define TEST		 7
#define TH260		 8
#define DEMO		 9
#define SPC_SC1000		 10
#define SPC_SPADLAB		 11
#define SPC_NIRS		 12
#define SPC_LUCA		 13
#define SPC_SWAB		 14
#define SPC_BCD			 15
#define SPC_MHARP		 16

#define WAIT_DELAY	 0
#define WAIT_TIME	 1
#define WAIT_COUNT	 2
#define WAIT_POS     3
#define WAIT_SPC     4
#define WAIT_MARKER	 5
#define BYN		     1
#define ASC			 0
#define MEASURE 	 0
#define RETRIEVE 	 1
#define ORIGIN		 0
#define PEAK		 1
#define SPECTRUM	 1
#define NUMAXIS		 3
#define NUMGATES	 3
#define HEADLEN		 256
#define SHOWROW		 0
#define COL_TRIS_STEP	 1
#define COL_TRIS_SWITCH	 2
#define COL_TRIS_TRIM	 3
#define COL_ROI_PAGE	 1
#define COL_ROI_FIRST	 2
#define COL_ROI_LAST	 3
#define COL_ROI_AREA	 4
#define COL_ROI_MAX		 5
#define COL_ROI_PEAK	 6
#define COL_ROI_WIDTH	 7
#define COL_VALUE_ROI	 1
#define COL_VALUE_AREA	 2
#define COL_VALUE_WIDTH	 3
#define COL_OSCILL_FIRST 1
#define COL_OSCILL_LAST  2
#define COL_OSCILL_FRACT 3
#define CONT_NONE	0
#define CONT_STEP	1
#define CONT_RANGE	2
#define ROW_BANK_NUM	1
#define ROW_BANK_ACTUAL	2
#define ROW_BANK_TIMEB	3
#define ROW_BANK_TIMET	4
#define ROW_BANK_TIMEA	5


/* CONTEST CONSTANTS */
#define CONTEST_MEAS 0
#define CONTEST_OSC	 1
#define CONTEST_TRIM 2
#define APPL_GEN	0
#define APPL_MAMM	1
#define APPL_MOXY	2
#define APPL_SPECTRA 3

/* SPC CONSTANTS */
#define MAX_BOARD	4
#define MAX_DET		256
#define MAX_PAGE	256*32
#define MAX_FRAME	1024
#define MAX_ACQ		1024
#define MAX_ROW_ROI	32
#define MAX_PLOT	16
#define SPC_SHORT	0
#define SPC_LONG	1
#define SPC_ALL		-1
#define SPC_BANK_DIM	128*1024
#define SPC_NUM_BANK	2
#define SPC130_TIMEOUT	2.5
#define SPC_TIMEDELAY	1 //60	//secondi

#define LABEL_CFD_LIMIT_LOW	  "cfd_limit_low"
#define LABEL_CFD_ZC_LEVEL      "cfd_zc_level"
#define LABEL_SYNC_ZC_LEVEL     "sync_zc_level"
#define LABEL_TAC_GAIN          "tac_gain"
#define LABEL_TAC_OFFSET        "tac_offset"
#define LABEL_TAC_LIMIT_LOW     "tac_limit_low"
#define LABEL_TAC_LIMIT_HIGH    "tac_limit_high"


#define INFINITY	 60000
#define MBADR	     0x280  // i/o port address on which the card is mapped
#define MAX_CHANN_SILENA	     8192   //
#define GROUP_SILENA    0	    //
#define EXTAMPL_SILENA	1	//
#define REALTIME	 0	    //
#define LIVETIME	 1	    //
#define TIMESCALE    0	    // seconds ->0       0.01 seconds ->1
#define MAXTIME	     3000   //
#define MBC_TO_PC    0	    // from mca to pc->0   from pc to mca->1
#define SILENA_TIMESTOP     3	    //
#define COUNTSTOP    4	    //
#define CALIB_VARRO  3.02   // TAC Lab.Elettronica 6/7/98
#define CALIB_SILENA  2.78
#define CALIB_SPC300 (97.7/(4*4*2))
#define CALIB_SPC630 (50/1.024)
#define CALIB_SPC130 (50/1.024)
#define SPC_MIN_TIME 0.1	// minimum acquisition time for count control (s)
#define SPC300_INI_FILE "SPC300.INI"
#define SPC630_INI_FILE "SPC630.INI"
#define SPC130_1_INI_FILE "SPC131.INI"
#define SPC130_2_INI_FILE "SPC132.INI"
#define SPC130_3_INI_FILE "SPC133.INI"
#define SPC130_4_INI_FILE "SPC134.INI"
#define THARP_INI_FILE "TIMEHARP.INI"
#define SPC_NORM_FALSE		0
#define SPC_NORM_TRUE		1
#define MAX_COUNTS			1000000000

/* HYDRA CONSTANTS */
#define HYDRA_BINNING 	0 //you can change this
#define HYDRA_SYNC_OFFSET	0
#define HYDRA_INPUT_OFFSET	-8000
#define HYDRA_OFFSET	0
#define HYDRA_TACQ		1000 //Measurement time in millisec, you can change this
#define HYDRA_SYNC_DIVIDER	4 //Note: you must reduce SYNC rate to <12.5 MHz
#define HYDRA_SYNC_CFDZEROCROSS	10 //you can change this
#define HYDRA_SYNC_CFDLEVEL		200 //you can change this
#define HYDRA_INPUT_CFDZEROCROSS		10 //you can change this
#define HYDRA_INPUT_CFDLEVEL			100 //you can change this
#define HYDRA_LENCODE			4 //  Note: HistLen=1024*(2^HYDRA_LENCODE)
#define HYDRA_DEV0		0 // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
#define SEC_2_MILLISEC	1000 // conversion factor for second to millisecond

/* MHARP CONSTANTS */
#define MHARP_DEV0		0 // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
#define T3HISTBINS 32768 //=2^15, dtime in T3 mode has 15 bits (w/o binning???)
#define MH_SLEEPFORSYNCRATE 300 // After Init allow 150 ms for valid  count rate readings
#define MH_FILEEXT		"mhbin" // file extension for MultiHarp Time Tags
#define MHARP_SLEEP_THREAD 0.001 // number of seconds to sleep if FIFO or Buffer not ready
#define	MHARP_MAX_DET	16 // Max number of det in input
#define	MHARP_MAX_BIN	16384 // Max number of bins
#define MHARP_BUFFER_MULT 4 // Expand the buffer
#define MHARP_SIZE_RING_M MHARP_BUFFER_MULT*TTREADMAX // Size of Ring Buffer for Acquisition
#define MHARP_SIZE_RING_A MHARP_BUFFER_MULT*MHARP_MAX_DET*MHARP_MAX_BIN // Size of Ring Buffer for Analysis


/* TH260 CONSTANTS */
#define TH260_BINNING 	0 //you can change this
#define TH260_SYNC_OFFSET	8600
#define TH260_INPUT_OFFSET	0
#define TH260_OFFSET	0
#define TH260_TACQ		1000 //Measurement time in millisec, you can change this
#define TH260_SYNC_DIVIDER	4 //Note: you must reduce SYNC rate to <12.5 MHz
#define TH260_SYNC_CFDZEROCROSS	-10 //you can change this
#define TH260_SYNC_CFDLEVEL		-400 //you can change this
#define TH260_INPUT_CFDZEROCROSS		-10 //you can change this
#define TH260_INPUT_CFDLEVEL			-50 //you can change this
#define TH260_LENCODE			4 //  Note: HistLen=1024*(2^TH260_LENCODE)
#define TH260_DEV0		0 // Use just 1 Device, the software can control more than 1 device (i.e. many HydraHarp) (Board = Channel, not Device)
#define SEC_2_MILLISEC	1000 // conversion factor for second to millisecond
#define MILLISEC_2_SEC	1/1000 // conversion factor for millisecond to second

/* SC1000 CONSTANTS */
#define SC1000_TYPE unsigned long			// data type of hystogram SC1000 data (non-lin)
#define SC1000_TIME_INFINITY 1000000       // sec
#define SC1000_BINDEPTH BS32					// max size of the bin (BS32=unsigned int)
#define SC1000_LINEARISE  1					// 1 = use background file to linearise time scale, 0 = do not linearise
#define SC1000_HARDREFOLD  5					// hardware refolding using SC and Modulo
#define SC1000_NODATAOPERATION -1
#define SC1000_MAXBIN	40800		// max number of channels (bin) in SC1000 // 10 mhz
#define SC1000_REBIN 32
#define SC1000_MAX_COUNT_RATE 30000000
#define SC1000_MIN_COUNT_RATE 7000

/* SPADLAB CONSTANTS */
#define SPADLAB_TDC_WRITE  "\\\\localhost\\MyProcess\\tdc-write"
#define SPADLAB_TRS_WRITE  "\\\\localhost\\myprocess\\trs-write"
#define SPADLAB_DATAIN  1
#define SPADLAB_MAXTIME  5000 // max wait time to be sent in transmit the DataIn command

/* NIRS CONSTANTS */
#define NIRS_HISTLEN  8192	   // number of channels per lambda (fixed)
#define NIRS_DT	(10000.0/1024) // (ps) Time Bin
#define NIRS_REGLEN ((int32_t) 128)
#define NIRS_STATLEN ((uint32_t) 3)
#define NIRS_DETNUM	2
#define NIRS_LAMBDA1  1
#define NIRS_LAMBDA2  2
#define NIRS_LAMBDA12 3

/* LUCA CONSTANTS */
#define LUCA_HISTLEN  8192	   // number of channels per detector (fixed)
#define LUCA_DT	(10000.0/1024) // (ps) Time Bin
#define LUCA_REGLEN ((int32_t) 128)
#define LUCA_NUMDET	2
#define LUCA_STATLEN ((uint32_t) 3)
#define LUCA_DETNUM	2
#define LUCA_STOP	0
#define LUCA_AUTO	1
#define LUCA_MANUAL	2
#define LUCA_SHOT	3
#define LUCA_ATT_ABS	0
#define LUCA_ATT_INC	1
#define LUCA_ATT_DEC	2
#define LUCA_ATT_DB		3
#define LUCA_ATT_IDLE	0
#define LUCA_ATT_DONE	1
#define LUCA_ATT_RUNNING 2
#define LUCA_ATT_ERROR	3
#define LUCA_FILE_HANDLE "LucaHandle.log"

/* SWAB CONSTANTS */
#define SWAB_MAX_DET		18		// max number of detectors in SwabianBoard
#define SWAB_NONE			0		// no detector
#define SWAB_SIGN			1		// sign detector
#define SWAB_SYNC			2		// sync detector
#define SWAB_REPLAY_SPEED	1.0		// replay at SWAB_REPLAY_SPEED*real speed
#define SWAB_S2PS			1E12	// seconds to ps conversion
#define SWAB_FILEEXT		"ttbin" // file extension for Time Tags
#define SWAB_HIST			1		// corresponds to classical TPSF histogram
#define SWAB_CORR			2		// corresponds to correlation among 2 channels
#define SWAB_REAL			1		// Real Time Tagger
#define SWAB_VIRTUAL		2		// Virtual Time Tagger
#define COL_SWAB_DETTYPE	1		// Column in UIR SWAB Panel Table corressponding to DetType
#define COL_SWAB_LEVEL		2		// Column in UIR SWAB Panel Table corressponding to DetType
#define COL_SWAB_DELAY		3		// Column in UIR SWAB Panel Table corressponding to DetType

/* BCD CONSTANTS */
#define BCD_MAXBIN			256		// LEN of the TDC Array
#define BCD_MAXPIX			2048	// Maximum size of the Pixel Matrix
#define BCD_QUADRANTS		0b00001111
#define BCD_STEPCOARSE		1280	// (ps) Coarse Step of the Gate/delay
#define BCD_STEPFINE		100		// (ps) Fine Step of the Gate/delay


/* TEST CONSTANTS */
#define TEST_MUS	10.0
#define TEST_MUA	0.10
#define TEST_RHO	2.0
#define TEST_V		0.03/1.5
#define TEST_AREA	1000000
#define TEST_NOISE	0.1
#define TEST_CALIB	3.0


/* TRIMMER CONSTANTS */
#define MAX_TRIM			10
#define TARGET_AREA		0
#define TARGET_STDEV	1
#define TARGET_WIDTH	2
#define TARGET_AREAWIDTH 3
#define TARGET_MAX_BOARD_AREA 4
#define TRIM_DIR_NEG	-1
#define TRIM_DIR_POS	1
#define TRIM_SCAN_MIDDLE	0
#define TRIM_SCAN_UP		1
#define TRIM_SCAN_DOWN		2
#define TRIM_SCAN_RANGE		3
#define TRIM_WAIT_POS	 0
#define TRIM_WAIT_TIME	 1
#define TRIM_WAIT_SPC	 2
#define INIT_HIGHER		0
#define INIT_LOWER		1E20
#define FNAME_TRIM		"POS\\TRIM"
#define FEXT_TRIM		".POS"
#define SAVETRIM_TITLE_1	"DO YOU WANT TO SAVE CHANGES TO FILE "
#define SAVETRIM_MESSAGE_1	"You can SAVE CHANGES, SAVE & COPY previous version,\nSAVE CHANGES in a new file specified in the input box"
#define SAVETRIM_TITLE_2	"SET HOME TO ZERO"
#define SAVETRIM_MESSAGE_2	"Do you want to set HOME position to ZERO?"

/* ########################  MAMMOT CONSTANTS  ################################# */

#define	MAMM_VIS			0
#define	MAMM_NIR			1
#define	MAMM_NIR_IDX_MIN_BORDER	400
#define	MAMM_NIR_IDX_MAX_BORDER	360
#define MAMM_NIR_STEP_MAX   400
#define	MAMM_NUM_BOARD		2
#define MAMM_NUM_DET		8 //EDO
#define	MAMM_NUM_ROW		240
#define D2				(char) 2
#define X				(char) 0
#define Y				(char) 1
#define MAMM_DIR_POS	(char) 1
#define MAMM_DIR_NEG	(char) -1
#define MAMM_NONE			0
#define MAMM_ONLY_VIS		1
#define MAMM_ONLY_NIR		2
#define MAMM_VIS_AND_NIR	3
#define MAMM_VIS_OR_NIR		4
#define MAMM_NUM_LAMBDA		7
#define MAMM_NORTHWEST_DET	0
#define MAMM_WEST_DET		1
#define MAMM_SOUTHWEST_DET	2
#define MAMM_SOUTH_DET		3
#define MAMM_SOUTHEAST_DET	4
#define MAMM_EAST_DET		5
#define MAMM_NORTHEAST_DET	6
#define MAMM_NORTH_DET		7




/* OMA CONSTANTS  */
/***/
#define OMA_NONE					-1
#define OMA_IP_ADDRESS_FILE			"c:\\Programs\\ControlloOMA\\ipAddress.txt"
/* file contenente l'indirizzo IP del PC su cui � lanciato il programma dell'OMA */
#define OMA_PORT					10000				   /* porta del programma dell'OMA */
#define OMA_ADDRESS_LENGHT			20					   /* lunghezza dell'array contenetne l'indirizzo IP */
#define OMA_BUFFER_LENGHT			256					   /* lunghezza buffer */
#define OMA_WAIT_TIME				1000				   /* tempo d'attesa prima di restituire errore durante una chiamta TCP */
#define OMA_NO_CONNECTION			-12					   /* codice d'errore */
#define OMA_READY_STRING_LENGHT		6					   /* lunghezza della stringa di "Ready?" */

/* OPHIR SPECIFIC CONSTANTS */
#define OPHIR_NONE		-1
#define OPHIR_BAUDRATE 	9600
#define OPHIR_PARITY	       0
#define OPHIR_DATABITS	   8
#define OPHIR_STOPBITS	   1
#define OPHIR_STRLEN	      10

/* LABEL CONSTANTS */
#define LABEL_MAX		16
#define LABEL_NAMELEN	12
#define LABEL_CONTENTLEN 22

/* DOSTEP CONSTANTS */
#define DOSTEP_MAX		3
#define DOSTEP_NONE		-1

/* DISPLAY CONSTANTS */
#define MAX_PLOT		16
#define COLOR_FULL		256
#define COLOR_FRACT		0.5
#define WINDOW_MANUAL	0
#define WINDOW_REF		1
#define WINDOW_SIG		2
#define WINDOW_REFs_SIGs	3
#define WINDOW_REFSIG_	4
#define GRAPH_PLOT		0
#define GRAPH_ROI		1
#define GRAPH_LIN		0
#define GRAPH_LOG		1
#define MAX_ROW_OSCILL	2

/* MOXY CONSTANTS */
#define MOXY_NUM_SWITCH		2
#define MOXY_END_SWITCH		"N"
#define MOXY_END_COMMAND	"F"
#define MOXY_SET			"S"
#define MOXY_START			"M"
#define MOXY_ABORT			"A"
#define MOXY_GOTO			"P"
#define MOXY_END			'O'
#define MOXY_NO_SWITCH		"1"
#define MOXY_SWITCH			"0"
#define MOXY_COMPORT 		1
#define MOXY_BAUDRATE 		9600
#define MOXY_PARITY 		0
#define MOXY_DATABITS 		8
#define MOXY_STOPBITS 		1
#define MOXY_OVERHEAD 		0.02
#define SEC_TO_MICROSEC		1000000
#define MOXY_CHANN_REST		8
#define MOXY_SWITCH_DELAY	0.005

/* GENERAL CONSTANTS */
#define FALSE   	 0
#define TRUE    	 1
//#define TNONE		 0
//#define TCHAR		 1
//#define TSHORT		 2
//#define TDOUBLE      3
#define VER_UNO		 1
#define VER_DUE		 2
#define VER_GEN		 0
#define VER_MAMM	 1
#define VER_MAMM_HEADER 1

/* PROFILING CONSTANTS */
#define IS_PROFILING 0
#define PROF_MAX_STRLEN	20
#define PROF_MAX_ID		10000
#define PROF_FILE_NAME	"PROFILING.TXT"

/* ERROR HANDLER CONSTANTS */
#define ERR_SPC		0
#define ERR_MEM		1
#define ERR_HYDRA		2
#define ERR_TH260		3
#define ERR_SC1000	4
#define ERR_GENERIC	5
#define ERR_SWAB	6
#define ERR_BCD 	7
#define ERR_MHARP	8



#endif // CONST_H
