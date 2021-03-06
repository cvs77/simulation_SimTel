#include"eventList.h"
vector<node> evenList;
int sortTime(const struct node p1,const struct node p2){
	return p1.time>p2.time;
}
void addAEvent(double nextTime,int eventType,int event_location){
	struct node tep;
	tep.time=nextTime;
	tep.evenType=eventType;
	tep.event_location=event_location;
	evenList.push_back(tep);
}
void addAArrivalEvent(double nectTime       ,int eventType, int event_locaiton,double event_initial_point,int car_directon,double car_speed,double call_duration){
	 struct node tep;
	tep.time=nectTime;
	tep.evenType=eventType;
	tep.event_location=event_locaiton;
	tep.event_initial_point=event_initial_point;
	tep.car_direction=car_directon;
	tep.call_duration=call_duration;
	tep.car_speed=car_speed;
	evenList.push_back(tep);
}
struct node popAEvent(){

/*  the case when event list is empty*/
	if(evenList.size()==0){
		printf("Even list is empty. Mission close unnormally");
		exit(1);
	}
	std::sort(evenList.begin(),evenList.end(),sortTime);//sort the list by sortTime function which is designed by us
	struct node h;
	h=evenList.back();//get the smallest timeSpace of nest even
	evenList.pop_back();// delete this node from the list
	
	return h;

}
void clear_list(void){
	evenList.clear();
}
