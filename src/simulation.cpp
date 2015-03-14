
#include "simulation.h"


int  celluar[20];
bool flag=true;//use this flag to distinguish the mode 1&2 with mode 3

double current_time, time_last_event;
/*Static data*/
double call_interval_mean;
double car_speed_mean;
double call_duration_mean;


int call_blocked;
int call_droped;
int call_simulated;
int call_siumlation_required;

/*config data*/
int  channel_celluar_number;
int  channel_handshake;
bool  is_hand_shake_model;

/*pop event data*/
struct node current_event;



void startSimulation(){

   /* run the simulation while more delays are still needed */
	initialize();
   while (call_simulated < call_siumlation_required) 
   {
     /* determine the next event */
       update_info();
	   
	   
	   timing();

     /* update time-average statistical accumulators */
     

     /* invoke the appropriate event function */
	   switch (current_event.evenType)
     {
	 case CALL_BEGIN:  
		        callArrive();
                break;
	 case CALL_DRIVEIN: 
		        callDriveIn();
                break;
	 case CALL_DRIVEOUT:
		        callDriveOut();
				break;
	 case CALL_END:
		        callEnd();
				break;
	 default:
		     break;
		       
     }
	   for(int i=0;i<20;i++){
		   printf("%d  ",celluar[i]);
	   }
	   getchar();
	
   }

}
void update_info(void){
	;
}
void callDriveIn(void){
	celluar[current_event.event_location]++;
}
void callDriveOut(void){
	celluar[current_event.event_location]--;
}
void callEnd(void){
	celluar[current_event.event_location]--;
}


void initialize(void) /* initialization function */
{

   current_time = 0.0;


   
   time_last_event = 0.0;
   call_simulated=0;
   call_siumlation_required=1000;
   call_droped=0;
   call_blocked=0;
   for(int i=0;i<20;i++){
	   celluar[i]=0;
   }
   
   /* initialise the statistical data */
       call_interval_mean=0.66427256;
	   call_duration_mean=119;
	   car_speed_mean=89.98472287;

	   is_hand_shake_model=false;
	   
	   //channel_celluar_number=10;
	   //channel_handshake=0;
       /* initialise event list. Since no customers are present, the departure
      (service completion) event is eliminated from consideration */
	  
	  
	  addAArrivalEvent((current_time+expon(call_interval_mean)),CALL_BEGIN,(int)(randno(1)*20),randno(1)*2,(int)(randno(1)*2),carSpeed(car_speed_mean),expon(119.0));

}
double carSpeed(double car_speed){
	return  car_speed;
}
void timing(void) /* timing function */
{
   int i;
   double min_time_next_event = 1.0e+29;
   
   
   current_event=popAEvent();
   /* determine the event type of the next event to occur */
   
   /*get the imformation of call's derection*/

   min_time_next_event=current_event.time;
   time_last_event=current_time;
   current_time = min_time_next_event;
}

void callArrive(void) /* Arrival event function */
{

	celluar[current_event.event_location]++;
    addAArrivalEvent((current_time+expon(call_interval_mean)),CALL_BEGIN,(int)(randno(1)*20),randno(1)*2,(int)(randno(1)*2),carSpeed(car_speed_mean),expon(119.0));
	call_simulated++;
	double time_cross_celluar;
	time_cross_celluar=2.0/current_event.car_speed*3600;
	int celluar_coverd=0;	
	double distance_after_next_celluar;
	double next_event_time;
  switch (current_event.car_direction)
  {

	case CAR_ATOB:
	  /*Check the culluar number coverd must bigger than 1, so that we can make the first count*/
	  
	  distance_after_next_celluar=current_event.call_duration/3600*current_event.car_speed-(2-current_event.event_initial_point);
	  	
	  if(distance_after_next_celluar>0){
			 
			 next_event_time=(2-current_event.event_initial_point)/current_event.car_speed*3600;
			 if((current_event.event_location+1)<20){
			 addAEvent(next_event_time+current_event.time,CALL_DRIVEIN,current_event.event_location+1);
			 }
			 addAEvent(next_event_time+current_event.time,CALL_DRIVEOUT,current_event.event_location);
			 
			 celluar_coverd=distance_after_next_celluar/2+1;
			 if(celluar_coverd>0){
				 for(int i=1;i<celluar_coverd;i++){
					 next_event_time+=2.0/current_event.car_speed*3600;
					 if((current_event.event_location+i+1)<20){
					 addAEvent(next_event_time+current_event.time,CALL_DRIVEIN,current_event.event_location+1+i);
					 }
					 if((current_event.event_location+i)<20){
					 addAEvent(next_event_time+current_event.time,CALL_DRIVEOUT,current_event.event_location+i);
					 }
				 }
			 }
		 }
	  if((current_event.event_location+celluar_coverd)<20){
	  addAEvent(current_event.time+current_event.call_duration,CALL_END,current_event.event_location+celluar_coverd);
	  }
	  break;

  case CAR_BTOA:
	  /*Check the culluar number coverd must bigger than 1, so that we can make the first count*/
	  
	  distance_after_next_celluar=current_event.call_duration/3600*current_event.car_speed-current_event.event_initial_point;
	  
	  if(distance_after_next_celluar>0){
			 
			 next_event_time=(current_event.event_initial_point)/current_event.car_speed*3600;
			 if((current_event.event_location-1)>-1){
			 addAEvent(next_event_time+current_event.time,CALL_DRIVEIN,current_event.event_location-1);
			 }
			 addAEvent(next_event_time+current_event.time,CALL_DRIVEOUT,current_event.event_location);
			 
			 celluar_coverd=distance_after_next_celluar/2+1;
			 if(celluar_coverd>0){
				 for(int i=1;i<celluar_coverd;i++){
					 next_event_time+=2.0/current_event.car_speed*3600;
					 if((current_event.event_location-i-1)>-1){
					 addAEvent(next_event_time+current_event.time,CALL_DRIVEIN,current_event.event_location-1-i);
					 }
					 if((current_event.event_location-i)>-1){
					 addAEvent(next_event_time+current_event.time,CALL_DRIVEOUT,current_event.event_location-i);
					 }
				 }
			 }
		 }
	  if((current_event.event_location-celluar_coverd)>-1){
	  addAEvent(current_event.time+current_event.call_duration,CALL_END,current_event.event_location-celluar_coverd);
	  }

		break;

  default:
	  break;
  }

  
}


double expon(double mean) /* exponential variate generation function */
{
  double u;

  /* generate a U(0,1) random veriate */
  u = randno(1);

  /* return an exponential random variate with mean "mean" */
  return -mean*log(u);
}

