/* ########################   TEST DATA SIMULATING SPC   ######################## */

/* INIT TEST */
void InitTest(void){
	int ret;
	char message[STRLEN];
	
	}

/* TRANSFER DATA FROM TEST */	
void GetDataTest(void){
	double *dataD;
	double mua,mus,r,v,area,value,timeA,t;
	int ib,id,ic,il;
	int delta=P.Chann.Num/2;
	dataD = calloc (P.Chann.Num, sizeof(*dataD));
	for(ib=0;ib<P.Num.Board;ib++)
		for(id=0;id<P.Num.Det;id++){
			for(il=0;il<2;il++){
				mus=TEST_MUS/(P.Num.Det*P.Num.Board*(il/0.3+1/0.3))*(1+2*(id+ib*P.Num.Det));
				mua=TEST_MUA/(P.Num.Det*P.Num.Board*(il/0.3+1/0.3))*(1+2*(id+ib*P.Num.Det));
				r=TEST_RHO;
				v=TEST_V;
				for(ic=0;ic<delta;ic++){
					t=(ic+0.5)*P.Spc.Factor;
					dataD[ic+il*delta]=(pow(t,-5/2)/mus)*exp(-mua*v*t)*exp(-(3*r*r*mus)/(4*v*t));
					}
				area=0;
				}
			for(ic=0;ic<P.Chann.Num;ic++)
				area+=dataD[ic];
			for(ic=0;ic<P.Chann.Num;ic++){
				timeA=(P.Contest.Function==CONTEST_OSC?P.Spc.TimeO:P.Spc.TimeM);
				value=(TEST_AREA*timeA/area*dataD[ic]);
				value*=(1-TEST_NOISE+(2*TEST_NOISE*rand())/RAND_MAX);
				D.Buffer[ib][ic+id*P.Chann.Num] = (T_DATA) value;
				}
		
			}
	free(dataD);
	}
	
