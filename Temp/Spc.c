/* INITIALIZE */
void SpcInit(void){
	int ib;
	switch(P.Spc.Type){
		case NONE:  break;  
		case VARRO:  InitVarro(); break;
		case SPC300: InitSpc300();break;
//THARP		case THARP: InitTimeharp();break;
		case SPC630:  
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) InitSpcm(ib);break;
		case HYDRA: for(ib=0;ib<P.Num.Board;ib++) InitHydra(ib);break;
		case SPC_MHARP: for(ib=0;ib<P.Num.Board;ib++) InitMharp(ib);break;
		case TH260: for(ib=0;ib<P.Num.Board;ib++) InitTH260(ib);break;
		case SPC_SC1000: for(ib=0;ib<P.Num.Board;ib++) InitSC1000(ib);break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) InitSpad(ib);break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) InitNirs(ib);break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) InitLuca(ib);break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) InitSwab(ib);break;
		case TEST: InitTest(); break;
		case DEMO: InitDemo(); break;
		case SPC_BCD: InitBcd(0); break;
		default:;
		}
	}


/* CLOSE SPC */
void SpcClose(void){
	SpcStop(FALSE);
	switch(P.Spc.Type){
		case SPC630:  
		case SPC130: CloseSpcm(); break;
		case HYDRA: CloseHydra(); break;
		case SPC_MHARP: CloseMharp(); break;
		case TH260: CloseTH260(); break;
		case SPC_SC1000: CloseSC1000(); break;
		case SPC_SPADLAB: CloseSpad(); break;
		case SPC_NIRS: CloseNirs(); break;
		case SPC_LUCA: CloseLuca(); break;
		case SPC_SWAB: CloseSwab(); break;
		case DEMO: CloseDemo(); break;
		case SPC_BCD: CloseBcd(); break;
		default:;
		}
	}

	
/* SPC PAUSE */
void SpcPause(void){
	int ib;
	switch(P.Spc.Type){
		case VARRO: CharCommVarro('d'); break; //TODO check
	//	case SILENA: DataStopSilena(); break; //TODO check
		case SPC300: SPCI_pause_measurement(); break;
//THARP		case THARP: TH_StopMeas(); break;  //TODO check
		case SPC630:  
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) SPC_pause_measurement(ib); break;
		case HYDRA: HH_StopMeas(HYDRA_DEV0); break;
		case SPC_MHARP: for(ib=0;ib<P.Num.Board;ib++) StopMharp(ib); break;
		case TH260: TH260_StopMeas(TH260_DEV0); break;
		case SPC_SC1000: for(ib=0;ib<P.Num.Board;ib++) sc_tdc_interrupt2(P.Spc.ScBoard[ib]); break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) PauseSpad(ib); break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) PauseSwab(ib); break;
		default:;
		}
	}
	

/* CLEAR DATA */
void SpcClear(void){
	int ic;

	if(P.Spc.Subtract) for(ic=0;ic<P.Chann.Num;ic++) D.Last[ic]=0;
	switch(P.Spc.Type){
		case VARRO: CharCommVarro('e'); break;
	// 	case SILENA: ClearSilena(); break;
		case SPC300: SPCI_fill_memory(-1,0,0); break;
//THARP		case THARP: TH_ClearHistMem(); break;
		case SPC630:
		case SPC130: ClearSpcm(); break;
		case HYDRA: ClearHydra(); break;
		case SPC_MHARP: ClearMharp(); break;
		case TH260: ClearTH260(); break;
		case SPC_SPADLAB: ClearSpad(); break;
		case SPC_SC1000: ClearSC1000(); break; 
		case SPC_SWAB: ClearSwab(); break;
		case SPC_BCD: ClearBcd(); break;
		default:;
		}
	P.Spc.Zero=TimerN();
	P.Spc.Trash=FALSE;
}


/* DATA IN */
void SpcIn(){
	int ib;
	
	switch(P.Spc.Type){
		case VARRO: CharCommVarro('a'); break;
	//	case SILENA: DataInSilena(); break;
		case SPC300: SPCI_start_measurement(); break;
//THARP		case THARP: TH_StartMeas(); break;
		case SPC630: 
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) SPC_start_measurement(ib); break;
		case HYDRA: HH_StartMeas(HYDRA_DEV0,P.Spc.TimeHydra); break;
		case SPC_MHARP: for(ib=0;ib<P.Num.Board;ib++) StartMharp(ib); break;
		case TH260: TH260_StartMeas(TH260_DEV0,P.Spc.TimeTH260); break;
		case SPC_SC1000: for(ib=0;ib<P.Num.Board;ib++){} break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) StartSpad(ib); break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) StartNirs(ib); break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) StartLuca(ib); break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) StartSwab(ib); break;
		case SPC_BCD: ClearBcd(); break;
		default:;
		}
	P.Spc.Zero=TimerN();
	if(P.Spc.Type!=SPC_SC1000) P.Spc.Started=TRUE;
	}


/* DATA RESTART */
void SpcRestart(void){  //TODO: check
	int ib=0;
	switch(P.Spc.Type){
		case VARRO: CharCommVarro('a'); break;
	//	case SILENA: DataInSilena(); break;
		case SPC300: SPCI_restart_measurement(); break;
//THARP		case THARP: TH_StartMeas(); break;
		case SPC630: 
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) SPC_restart_measurement(ib); break;
		case HYDRA: HH_StartMeas(HYDRA_DEV0,P.Spc.TimeHydra); break;
		case SPC_MHARP: for(ib=0;ib<P.Num.Board;ib++) StartMharp(ib); break;
		case TH260: TH260_StartMeas(TH260_DEV0,P.Spc.TimeHydra); break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) StartSpad(ib); break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) StartNirs(ib); break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) StartLuca(ib); break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) StartSwab(ib); break;
		default:;
		}
	//P.Spc.Zero=TimerN();	  // WARNING: DO YOU NEED TO INSERT THIS?
	}


/* OPTIMIZED DATA CLEAR & DATA IN */
void SpcReset(char Status, char Clear, char Stop){
	if((P.Spc.Type==SPC_NIRS)&&P.Spc.Trash) TrashNirs(); // note Trash clear for SPC_NIRS is inserted here  
	if((P.Spc.Type==SPC_LUCA)&&P.Spc.Trash) TrashLuca(); // note Trash clear for SPC_LUCA is inserted here  
	if(Clear) SpcClear(); 
	if(P.Spc.Trash) SpcOut(FALSE);
	if(Stop||(!P.Spc.Started)) SpcIn();
	if((P.Spc.Type==SPC_SWAB)&&(P.Contest.Run==CONTEST_MEAS)&&(P.Contest.Function==CONTEST_MEAS)) StartFileSwab(); // if not started, start saving file  
	if(Status) SetCtrlVal (hDisplay, DISPLAY_MEASURE, ON);
	P.Spc.Trash=FALSE;
	}



/* DATA SET TIME */
void SpcTime(float Time){ 
	int ib;
	if(P.Wait.Type!=WAIT_SPC) Time *= 2;
	switch(P.Spc.Type){
		case SPC300: SPCI_set_parameter(COLLECT_TIME,Time); break;
//THARP		case THARP: TH_SetMMode(0,1000*Time); break;
		case SPC630: 
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) SPC_set_parameter(ib,COLLECT_TIME,Time); break;
		case HYDRA: P.Spc.TimeHydra = (int) (Time*SEC_2_MILLISEC); break;
		case SPC_MHARP: P.Spc.TimeMharp = (int) (Time*SEC_2_MILLISEC); break;
		case TH260: P.Spc.TimeTH260 = (int) (Time*SEC_2_MILLISEC); break;
		case SPC_SC1000: P.Spc.TimeSC1000 = (int) (Time*SEC_2_MILLISEC); break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) TimeSpad(ib,Time); break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) TimeNirs(ib,Time); break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) TimeLuca(ib,Time); break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) TimeSwab(ib,Time); break;
		case SPC_BCD: TimeBcd(Time); break;
		default:;
		}
	}


/* DATA STOP */
void SpcStop(char Status){
	short ib;
	//**	CalcTime();
	switch(P.Spc.Type){
		case VARRO: CharCommVarro('d'); break;
	//	case SILENA: DataStopSilena(); break;
		case SPC300: SPCI_stop_measurement(); break;
//THARP		case THARP: TH_StopMeas();break;
		case SPC630:
		case SPC130: for(ib=0;ib<P.Num.Board;ib++) SPC_stop_measurement(ib);break;
		case HYDRA: HH_StopMeas(HYDRA_DEV0); break;
		case SPC_MHARP: for(ib=0;ib<P.Num.Board;ib++) MH_StopMeas(ib); break;
		case TH260: TH260_StopMeas(TH260_DEV0); break;
		case SPC_SC1000: break;
		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) StopSpad(ib);break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) StopNirs(ib);break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) StopLuca(ib);break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) StopSwab(ib);break;
		default:;
		}
	CalcTime();
	if(Status) SetCtrlVal (hDisplay, DISPLAY_MEASURE, OFF);
	if(P.Spc.Type!=SPC_SC1000) P.Spc.Started=FALSE;
	}


/* WAIT SPC */
void SpcWait(void){
	short mod_state;
	int mod_state2;
	int ib;
    unsigned char statusmeas;
	switch(P.Spc.Type){
		case NONE:  break;  
		case VARRO: while(CheckAcqVarro()); break;  // check !
	//	case SILENA: do _GetMeasInfo(&realtime,&livetime,&deadtime,&statusmeas);
					 while(statusmeas != SILENA_TIMESTOP); break;
		case SPC300: do SPCI_test_state(&mod_state);
					 while((mod_state & SPC_ARMED) != 0);break;
//THARP		case THARP: while(TH_CTCStatus()==0);
//THARP					TH_StopMeas();break; 
		case SPC630:   
		case SPC130: for(ib=0;ib<P.Num.Board;ib++)
    					do SPC_test_state(ib,&mod_state);
						while((mod_state & SPC_ARMED) != 0);break;
		case HYDRA: for(ib=0;ib<P.Num.Board;ib++)
    					do HH_CTCStatus(HYDRA_DEV0,&mod_state2);
						while(mod_state2==0);break;
		case SPC_MHARP: for (ib = 0; ib < P.Num.Board; ib++) WaitMharp(ib); break;
		case TH260: for(ib=0;ib<P.Num.Board;ib++)
    					do TH260_CTCStatus(TH260_DEV0,&mod_state2);
						while(mod_state2==0);break;
		case SPC_SC1000: //if(P.Spc.ScWait) Delay(MILLISEC_2_SEC*(P.Spc.TimeSC1000*10));
						/*for(ib=0;ib<P.Num.Board;ib++)
    					do  sc_tdc_get_status2(P.Spc.ScBoard[ib],&mod_state2);
						while(mod_state2==0);*/ break;
 		case SPC_SPADLAB: for(ib=0;ib<P.Num.Board;ib++) WaitSpad(ib); break;
		case SPC_NIRS: for(ib=0;ib<P.Num.Board;ib++) WaitNirs(ib); break;
		case SPC_LUCA: for(ib=0;ib<P.Num.Board;ib++) WaitLuca(ib); break;
		case SPC_SWAB: for(ib=0;ib<P.Num.Board;ib++) WaitSwab(ib); break;
		case SPC_BCD: WaitBcd(); break;
		case DEMO:
		case TEST: Delay((P.Contest.Function==CONTEST_OSC?P.Spc.TimeO:P.Spc.TimeM));break;
		default:;
		}
	}


/* TRANSFER DATA FROM SPC INTO MEMORY */
void SpcGet(void){
	switch(P.Spc.Type){
		case VARRO: GetDataVarro(); break;
	//	case SILENA: GetDataSilena(); break;
		case SPC300: GetDataSpc300();break; 
//THARP		case THARP: GetDataTimeharp();break; 
		case SPC630:   
		case SPC130: GetDataSpcm();break;
		case HYDRA: GetDataHydra();break;
		case SPC_MHARP: GetDataMharp(); break;
		case TH260: GetDataTH260();break;
		case SPC_SC1000: GetDataSC1000();break;
		case SPC_SPADLAB: GetDataSpad();break;
		case SPC_NIRS: GetDataNirs();break;
		case SPC_LUCA: GetDataLuca();break;
		case SPC_SWAB: GetDataSwab();break;
		case TEST:  GetDataTest();break;
		case DEMO:  GetDataDemo();break;
		case SPC_BCD: GetDataBcd();break;
		default:;
		}
	}


/* DATA OUT AND PRE-PROCESSING */
void SpcOut(char Status){
	if(P.Spc.Started) CalcTime();
	SpcGet();
	DataCopy();
	if((P.Spc.Type==VARRO)||(P.Spc.Type==SILENA)) DataReverse();
	if((P.Spc.Type==VARRO)||(P.Spc.Type==SILENA)) DataSubtract();
	if(Status) SetCtrlVal (hDisplay, DISPLAY_MEASURE, OFF);
	}


/* SUBTRACT LAST DATA */
void DataSubtract(void){
	short ic;
	D.Curve=D.Data[0][0];
	for(ic=0; ic<P.Chann.Num; ic++){
		D.Curve[ic] -= D.Last[ic];
		D.Last[ic] += D.Curve[ic];
		}
	}  


/* REVERSE DATA */
void DataReverse(void){
	short num = P.Chann.Num;
	int ic;
	T_DATA temp;
	D.Curve=D.Data[0][0];
	for(ic=0;ic<(num/2);ic++){
		temp = D.Curve[ic];
		D.Curve[ic] = D.Curve[num-1-ic];
		D.Curve[num-1-ic] = temp;
		}
	}

	
/* CALCULATE EFFECTIVE TIME */
void CalcTime(void){
	short ib,state;
	double now;
	float meas_time, rem_time;
	double elapsed_time;
	switch (P.Spc.Type){
		case SPC130:
			for(ib=0;ib<P.Num.Board;ib++){
				SPC_test_state(ib,&state);
				SPC_get_actual_coltime(ib, &rem_time);
				SPC_get_parameter(ib, COLLECT_TIME, &meas_time);
				P.Spc.EffTime[ib] = meas_time - rem_time;
				now=TimerN();
			P.Spc.EffTime[0]=now-P.Spc.Zero;
			P.Spc.Zero=now;
				}
			break;
		case HYDRA:
			HH_GetElapsedMeasTime(HYDRA_DEV0,&elapsed_time);
			for(ib=0;ib<P.Num.Board;ib++) P.Spc.EffTime[ib] = elapsed_time;
			break;
		case SPC_MHARP:
			for (ib = 0; ib < P.Num.Board; ib++) {
				MH_GetElapsedMeasTime(ib, &elapsed_time);
				P.Spc.EffTime[ib] = (1.0*elapsed_time)/SEC_2_MILLISEC;
				}
			break;
		case TH260:
			TH260_GetElapsedMeasTime(TH260_DEV0,&elapsed_time);
			for(ib=0;ib<P.Num.Board;ib++) P.Spc.EffTime[ib] = elapsed_time;
			break;
		case SPC_NIRS:
			for(ib=0;ib<P.Num.Board;ib++)
				P.Spc.EffTime[ib]=(double)(P.Spc.Nirs[ib].IntTime)/SEC_2_MILLISEC;
			break;  
		case SPC_LUCA:
			for(ib=0;ib<P.Num.Board;ib++)
				P.Spc.EffTime[ib]=(double)(P.Spc.Luca[ib].IntTime)/SEC_2_MILLISEC;
			break;  
		case SPC_SWAB:
			GetSwabElapsedTime(&elapsed_time);
			for(ib=0;ib<P.Num.Board;ib++) P.Spc.EffTime[ib] = elapsed_time;
			break;  
		default:
			now=TimerN();
			P.Spc.EffTime[0]=now-P.Spc.Zero;
			P.Spc.Zero=now;
			break;
		}
		
	//if((P.Spc.Type!=HYDRA)&&(P.Spc.Type!=HYDRA)){
	//	now=TimerN();
	//	P.Spc.EffTime[0]=now-P.Spc.Zero;
	//	P.Spc.Zero=now;
	//	}
	}


/* COPY CURVE TO DATA */
void DataCopy(void){
	int ib,id;
	long page;
	int ic;
	int is_meas=(P.Contest.Function==CONTEST_MEAS);
	
	if(!is_meas)
		for(ib=0;ib<P.Num.Board;ib++)
			for(id=0;id<P.Num.Det;id++)
				for(ic=0;ic<P.Chann.Num;ic++)
					D.Osc[id+ib*P.Num.Det][ic]=D.Buffer[ib][ic+id*P.Chann.Num];
	else{
		for(ib=0;ib<P.Num.Board;ib++){
			for(id=0;id<P.Num.Det;id++){
				page=P.Filter.Page[P.Acq.Actual][ib][id];
				if(page!=-1){
					P.Page[page].Acq=P.Acq.Actual;
					P.Page[page].TimeNom=P.Spc.TimeM;
					P.Page[page].TimeEff=P.Spc.EffTime[ib];
					for(ic=0;ic<P.Chann.Num;ic++) D.Data[P.Frame.Actual][page][ic]+=D.Buffer[ib][ic+id*P.Chann.Num];
					if(P.Info.SubHeader) CompileSub(P.Ram.Actual,P.Frame.Actual,page);
					}
				}
			}
		}
	}
	

/* UPDATE ALL ACQ INDEXES */
void NewAcq(void){
P.Acq.Actual++;
	if(P.Acq.Actual==P.Acq.Frame){
		P.Frame.Actual=P.Frame.Actual+P.Frame.Dir;
		P.Acq.Actual=0;
	}
	if(P.Frame.Actual==P.Frame.Num){
		P.Ram.Actual++;
		P.Frame.Actual=0;
	} 
}
