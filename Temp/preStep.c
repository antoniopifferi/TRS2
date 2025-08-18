/* ########################   STEPPER PROCEDURES   ######################## */
void InitStep(char Step){
	P.Step[Step].Moving = FALSE;
	switch(P.Step[Step].Type){
		case MICRO:  InitMicro(Step); break;
		case MONO:	InitMono(Step); break;
		default:;
		}
	if(P.Step[Step].Mode==STEP_CONT) SetVel(Step,fabs(P.Step[Step].Delta/(P.Spc.TimeM*P.Loop[P.Step[Step].Loop].Num)));
	else SetVel(Step, P.Step[Step].Freq);
	}

void CloseStep(char Step){
	switch(P.Step[Step].Type){
		case MICRO: CloseMicro(Step); break;
		case MONO: CloseMono(Step); break;
		default:;
		}
	}

void MoveStep(long *Actual,long Goal,char Step,char Wait,char Status){
	char dir;
	long delta;
	int is;
	char on = FALSE;
	if (*Actual==Goal) return;
	P.Step[Step].Moving = TRUE;
	delta=Goal-*Actual;
	dir=(delta>0?1:-1);
	P.Step[Step].Dir=dir;
	Goal=(dir>0?min(Goal,P.Step[Step].Max):max(Goal,P.Step[Step].Min));
	if(Status) SetCtrlVal (hDisplay, DISPLAY_MOVE, ON);
	switch (P.Step[Step].Type){
		case MICRO: MoveMicro(Step,Goal,Wait); break;
		case MONO: MoveMono(Step,Goal,Wait); break;
		default:;
		}
	P.Spc.Trash=TRUE;
	if(Wait) return;	
	//if(Status) SetCtrlVal (hDisplay, P.Step[Step].Control, (P.Step[Step].Actual/(1.0*P.Step[Step].Factor)));//TODO: Check for TRIM
	P.Step[Step].Moving = FALSE;
	if(Status){
		for(is=0;is<MAX_STEP;is++)
			if(P.Step[is].Step)
				on |= P.Step[is].Moving;
		if(!on) SetCtrlVal (hDisplay, DISPLAY_MOVE, OFF);
		}
	}


// #### MICROCHIP STEPPER ####
	
void InitMicro(char Step){
	int ret,open;
	char message[STRLEN];
	int com=P.Step[Step].Com;
	int micro_baudrate=(P.Step[Step].Type==MICRO2?MICRO2_BAUDRATE:MICRO_BAUDRATE);
	sprintf(message,"Initializing MICRO Stepper #%d on COM%d",Step+1,com);
    SetCtrlVal (hDisplay, DISPLAY_MESSAGE,message);
	open=OpenComConfig(com,NULL,micro_baudrate,MICRO_PARITY,MICRO_DATABITS,MICRO_STOPBITS,0,-1);
	FlushInQ (com);
	FlushOutQ (com);
    
    TalkMicro(Step,MICRO_LCD,P.Step[Step].Lcd,&ret);
    TalkMicro(Step,MICRO_HOLD,P.Step[Step].Hold,&ret);
    TalkMicro(Step,MICRO_FMIN,P.Step[Step].FreqMin,&ret);
	TalkMicro(Step,MICRO_VEL,(int) P.Step[Step].Freq,&ret);
	TalkMicro(Step,MICRO_FDELTA,P.Step[Step].FreqDelta,&ret);
    SetCtrlVal (hDisplay, DISPLAY_MESSAGE," PASSED\n");
	}

void CloseMicro(char Step){
	int ret;
	int com=P.Step[Step].Com;
    TalkMicro(Step,MICRO_END,0,&ret);
	FlushInQ (com);
	FlushOutQ (com);
	CloseCom (com);
	}

void MoveMicro(char Step,long Goal,char Wait){
	int ret;
	int com=P.Step[Step].Com;
	if(Goal==P.Step[Step].Actual) return;
    TalkMicro(Step, MICRO_GOTO, Goal,&ret);
	if(Wait) WaitMicro(Step,Goal);
	}

void TalkMicro(char Step, char Command, long Value, long *Answer){
	unsigned char *pChar;
	unsigned char Command4Char[4];
	unsigned short shortValue=(unsigned short)Value;
	char *pChar2;
	int com=P.Step[Step].Com;
	switch (P.Step[Step].Type) {
		case MICRO:
			pChar = (unsigned char*) &shortValue;
			Command4Char[0]=pChar[0];
			Command4Char[1]=pChar[1];
			Command4Char[2]=0;
			Command4Char[3]=(unsigned char) Command;
			ComWrt(com,(const char*)Command4Char,4);
			GetMicro(com,Answer);
			break;
		case MICRO2:
			pChar2 = (char*) &Value;
			pChar2[3] = (char) Command;
			ComWrt(com,pChar2,4);
			GetMicro(com,Answer);
			break;
		}
	return;	
	}

void GetMicro(int Com,long *Answer){
	char *pChar;
	pChar = (char*) Answer;
	while(ComRd (Com,pChar,4)<4);
	}
