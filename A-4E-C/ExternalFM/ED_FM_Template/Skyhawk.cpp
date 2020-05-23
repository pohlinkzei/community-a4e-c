// ED_FM_Template.cpp : Defines the exported functions for the DLL application.
//#include "ED_FM_Utility.h"
#include "stdafx.h"
//#include "A-4_Aero.h"
#include "Skyhawk.h"
#include <Math.h>
#include <stdio.h>
#include <string>
#include "Vec3.h"
#include "Input.h"
#include "FlightModel.h"
#include "Airframe.h"

//============================ Skyhawk Statics ============================//
static Skyhawk::Input s_input;
static Skyhawk::Airframe s_airframe(s_input);
static Skyhawk::FlightModel s_fm(s_input, s_airframe);


//========================================================================//

double  throttle		  = 0;
double  stick_roll		  = 0;
double  stick_pitch		  = 0;

double  internal_fuel     = 0;
double  fuel_consumption_since_last_time  = 0;
double s_mass = 0;
Vec3 s_pos;

double mach_table[] = {
	0,	
	0.2,
	0.4,
	0.6,
	0.7,
	0.8,
	0.9,
	1,	
	1.05,
	1.1,
	1.2,
	1.3,
	1.5,
	1.7,
	1.8,
	2,	
	2.2,
	2.5,
	3.9,
};

double cx0[] =
{
	0.0165,
	0.0165,
	0.0165,
	0.0165,
	0.0170,
	0.0178,
	0.0215,
	0.0310,
	0.0422,
	0.0440,
	0.0432,
	0.0423,
	0.0416,
	0.0416,
	0.0416,
	0.0410,
	0.0395,
};

double Cya[] = {
	   0.077,	
	   0.077,	
	   0.077,	
	   0.080,	
	   0.083,	
	   0.087,	
	   0.091,	
	   0.094,	
	   0.094,	
	   0.091,	
	   0.085,	
	   0.068,	
	   0.051,	
	   0.043,	
	   0.037,	
	   0.036,	
	   0.033,	
};

double B[] ={
	0.1,	
	0.1,	
	0.1,	 
	0.094,	
	0.094,	
	0.094,	
	0.11,	
	0.15,	
	0.15,	
	0.14,	
	0.17,	
	0.23,	
	0.23,	
	0.08,	
	0.16,	
	0.25,	
	0.35,	
};

double B4[] ={
	0.032,	
	0.032,	 
	0.032,	
	0.043,	
	0.045,	
	0.048,	
	0.050,	
	0.1,	
	0.1,	
	0.1,	
	0.096,	
	0.09,	
	0.38,	
	2.5,	
	3.2,	
	4.5,	
	6.0,	
};

double CyMax[] = {
	1.6,
	1.6,
	1.6,
	1.5,
	1.45,
	1.4,
	1.3,
	1.2,
	1.1,
	1.05,
	1.0,
	0.9,
	0.7,
	0.55,
	0.4,
	0.4,
	0.4,
};

namespace Skyhawk
{

}



void add_local_force(const Vec3 & Force, const Vec3 & Force_pos)
{
	/*common_force += Force;
	Vec3 delta_pos = Force_pos - center_of_gravity;
	Vec3 delta_moment = cross(delta_pos, Force);
	common_moment += delta_moment;*/
}


void simulate_fuel_consumption(double dt)
{
	fuel_consumption_since_last_time =  10 * throttle * dt; //10 kg persecond
	if (fuel_consumption_since_last_time > internal_fuel)
		fuel_consumption_since_last_time = internal_fuel;
	internal_fuel -= fuel_consumption_since_last_time;
}

void ed_fm_add_local_force(double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z)
{
	x = s_fm.getForce().x;
	y = s_fm.getForce().y;
	z = s_fm.getForce().z;

	pos_x = s_fm.getCOM().x;
	pos_y = s_fm.getCOM().y;
	pos_z = s_fm.getCOM().z;
}

void ed_fm_add_global_force(double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z)
{
	/*y = s_mass * 9.81;
	Vec3 pos = s_pos - s_fm.getCOM();
	pos_x = pos.x;
	pos_y = pos.y;
	pos_z = pos.z;*/
}

void ed_fm_add_global_moment(double & x,double &y,double &z)
{

}

void ed_fm_add_local_moment(double & x,double &y,double &z)
{
	x = s_fm.getMoment().x;
	y = s_fm.getMoment().y;
	z = s_fm.getMoment().z;
}

void ed_fm_simulate(double dt)
{
	s_airframe.airframeUpdate(dt);
	s_fm.calculateForcesAndMoments(dt);
	/*common_force = Vec3();
	common_moment = Vec3();

	

	Vec3 airspeed = velocity_world_cs - wind;
	printf("vx: %lf vy: %lf vz: %lf\n", airspeed.x, airspeed.y, airspeed.z);

	double V_scalar = sqrt(airspeed.x * airspeed.x + airspeed.y * airspeed.y + airspeed.z * airspeed.z);
	double q = (0.5 * atmosphere_density * V_scalar * V_scalar) * 1.0;
	Skyhawk::APars params(q, aoa, beta, 0.0, rx);
	Skyhawk::calculate(params, 0.0, stick_roll, stick_pitch, 0.0, throttle, center_of_gravity);

	common_force = Skyhawk::netForce;
	common_moment = Skyhawk::netMoment;*/
	

	//common_force  = Vec3();
	//common_moment = Vec3();

	////common_moment -= Vec3(rx*10000.0, 0, 0);

	//Vec3 airspeed;

	//airspeed.x = velocity_world_cs.x - wind.x;
	//airspeed.y = velocity_world_cs.y - wind.y;
	//airspeed.z = velocity_world_cs.z - wind.z;

	//
	//Vec3 thrust_pos(-5.0,0,0);
	//Vec3 thrust(throttle * 38000, 0 , 0);

	//double V_scalar =  sqrt(airspeed.x * airspeed.x + airspeed.y * airspeed.y + airspeed.z * airspeed.z);

	//double Mach		= V_scalar/ speed_of_sound;

	//double CyAlpha_ = lerp(mach_table,Cya  ,sizeof(mach_table)/sizeof(double),Mach);
	//double Cx0_     = lerp(mach_table,cx0  ,sizeof(mach_table)/sizeof(double),Mach);
	//double CyMax_   = lerp(mach_table,CyMax,sizeof(mach_table)/sizeof(double),Mach);
	//double B_	    = lerp(mach_table,B    ,sizeof(mach_table)/sizeof(double),Mach);
	//double B4_	    = lerp(mach_table,B4   ,sizeof(mach_table)/sizeof(double),Mach);


	//double Cy  = (CyAlpha_ * 57.3) * aoa;
	//if (fabs(aoa) > 90/57.3)
	//	Cy = 0;
	//if (Cy > CyMax_)
	//	Cy = CyMax_;

	//double Cx  = 0.05 + B_ * Cy * Cy + B4_ * Cy * Cy * Cy * Cy;

	//double q	   =  0.5 * atmosphere_density * V_scalar * V_scalar;
	//const double S = 25;
	//double Lift =  Cy * q * S;
	//double Drag =  Cx * q * S;
	//
	//Vec3 aerodynamic_force(-Drag , Lift , 0 );
	//Vec3 aerodynamic_force_pos(0.0,0,0);

	//add_local_force(aerodynamic_force,aerodynamic_force_pos);
	//add_local_force(thrust			 ,thrust_pos);

	//Vec3 rudder(0, 0, -0.5*beta * CyAlpha_ * 57.3 * q * S);
	//Vec3 rudderPos(-5, 0, 0);

	//Vec3 elevator(0, - 0.2 * stick_pitch * CyAlpha_ * q * S, 0);
	//Vec3 elevatorPos(-5, 0, 0);

	//Vec3 aileron_left (0 , 0.1 * 0.05 * (CyAlpha_ * 57.3) * (stick_roll) * q * S , 0 );
	//Vec3 aileron_right(0 ,-0.1 * 0.05 * (CyAlpha_ * 57.3) * (stick_roll) * q * S , 0 );

	//Vec3 aileron_left_pos(0,0,-5.0);
	//Vec3 aileron_right_pos(0,0, 5.0);


	//add_local_force(aileron_left ,aileron_left_pos);
	//add_local_force(aileron_right,aileron_right_pos);
	//add_local_force(rudder, rudderPos);
	//add_local_force(elevator, elevatorPos);

	//simulate_fuel_consumption(dt);
}

void ed_fm_set_atmosphere(double h,//altitude above sea level
							double t,//current atmosphere temperature , Kelwins
							double a,//speed of sound
							double ro,// atmosphere density
							double p,// atmosphere pressure
							double wind_vx,//components of velocity vector, including turbulence in world coordinate system
							double wind_vy,//components of velocity vector, including turbulence in world coordinate system
							double wind_vz //components of velocity vector, including turbulence in world coordinate system
						)
{
	s_fm.setAtmosphericParams(ro, a, Vec3(wind_vx, wind_vy, wind_vz));

	/*wind.x = wind_vx;
	wind.y = wind_vy;
	wind.z = wind_vz;

	atmosphere_density = ro;
	speed_of_sound     = a;*/
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_mass_state (double mass,
									double center_of_mass_x,
									double center_of_mass_y,
									double center_of_mass_z,
									double moment_of_inertia_x,
									double moment_of_inertia_y,
									double moment_of_inertia_z
									)
{
	s_mass = mass;
	s_fm.setCOM(Vec3(center_of_mass_x, center_of_mass_y, center_of_mass_z));

	/*center_of_gravity.x  = center_of_mass_x;
	center_of_gravity.y  = center_of_mass_y;
	center_of_gravity.z  = center_of_mass_z;*/
}
/*
called before simulation to set up your environment for the next step
*/
void ed_fm_set_current_state (double ax,//linear acceleration component in world coordinate system
							double ay,//linear acceleration component in world coordinate system
							double az,//linear acceleration component in world coordinate system
							double vx,//linear velocity component in world coordinate system
							double vy,//linear velocity component in world coordinate system
							double vz,//linear velocity component in world coordinate system
							double px,//center of the body position in world coordinate system
							double py,//center of the body position in world coordinate system
							double pz,//center of the body position in world coordinate system
							double omegadotx,//angular accelearation components in world coordinate system
							double omegadoty,//angular accelearation components in world coordinate system
							double omegadotz,//angular accelearation components in world coordinate system
							double omegax,//angular velocity components in world coordinate system
							double omegay,//angular velocity components in world coordinate system
							double omegaz,//angular velocity components in world coordinate system
							double quaternion_x,//orientation quaternion components in world coordinate system
							double quaternion_y,//orientation quaternion components in world coordinate system
							double quaternion_z,//orientation quaternion components in world coordinate system
							double quaternion_w //orientation quaternion components in world coordinate system
							)
{
	s_fm.setWorldVelocity(Vec3(vx, vy, vz));
	s_pos = Vec3(px, py, pz);
	/*
	velocity_world_cs.x = vx;
	velocity_world_cs.y = vy;
	velocity_world_cs.z = vz;*/
}


void ed_fm_set_current_state_body_axis(double ax,//linear acceleration component in body coordinate system
	double ay,//linear acceleration component in body coordinate system
	double az,//linear acceleration component in body coordinate system
	double vx,//linear velocity component in body coordinate system
	double vy,//linear velocity component in body coordinate system
	double vz,//linear velocity component in body coordinate system
	double wind_vx,//wind linear velocity component in body coordinate system
	double wind_vy,//wind linear velocity component in body coordinate system
	double wind_vz,//wind linear velocity component in body coordinate system

	double omegadotx,//angular accelearation components in body coordinate system
	double omegadoty,//angular accelearation components in body coordinate system
	double omegadotz,//angular accelearation components in body coordinate system
	double omegax,//angular velocity components in body coordinate system
	double omegay,//angular velocity components in body coordinate system
	double omegaz,//angular velocity components in body coordinate system
	double yaw,  //radians
	double pitch,//radians
	double roll, //radians
	double common_angle_of_attack, //AoA radians
	double common_angle_of_slide   //AoS radians
	)
{
	s_fm.setPhysicsParams(common_angle_of_attack, common_angle_of_slide, Vec3(yaw, pitch, roll), Vec3(omegax, omegay, omegaz), Vec3(omegadotx, omegadoty, omegadoty));


	//aoa = common_angle_of_attack;
	//beta = common_angle_of_slide;
	//rx = omegax;
	//ry = omegay;
	//rz = omegaz;
}
/*
input handling
*/
void ed_fm_set_command
(
	int command,
	float value
)
{
	switch (command)
	{
	case Skyhawk::Control::PITCH:
		s_input.pitch() = value;
		break;
	case Skyhawk::Control::ROLL:
		s_input.roll() = value;
		break;
	case Skyhawk::Control::YAW:
		s_input.yaw() = value;
		break;
	case Skyhawk::Control::THROTTLE:
		s_input.throttle() = value;
		break;
	case Skyhawk::Control::GEAR_DOWN:
		s_input.gear() = Skyhawk::Input::GearPos::DOWN;
		break;
	case Skyhawk::Control::GEAR_UP:
		s_input.gear() = Skyhawk::Input::GearPos::UP;
		break;
	case Skyhawk::Control::GEAR_TOGGLE:
		s_input.gear() = s_input.gear() == Skyhawk::Input::GearPos::DOWN ? Skyhawk::Input::GearPos::UP : Skyhawk::Input::GearPos::DOWN;
		break;
	case Skyhawk::Control::BRAKE:
		s_input.brakeLeft() = value;
		s_input.brakeRight() = value;
		break;
	case Skyhawk::Control::LEFT_BRAKE:
		s_input.brakeLeft() = value;
		break;
	case Skyhawk::Control::RIGHT_BRAKE:
		s_input.brakeRight() = value;
		break;
	case Skyhawk::Control::FLAPS_UP:
		s_input.flaps() = 0.0;
		break;
	case Skyhawk::Control::FLAPS_DOWN:
		s_input.flaps() = 1.0;
		break;
	case Skyhawk::Control::FLAPS_TOGGLE:
		s_input.flaps() = s_input.flaps() > 0.5 ? 0.0: 1.0;
	case Skyhawk::Control::AIRBRAKE_EXTEND:
		s_input.airbrake() = 1.0;
		break;
	case Skyhawk::Control::AIRBRAKE_RETRACT:
		s_input.airbrake() = 0.0;
		break;
	default:
		printf("number %d: %lf\n", command, value);
	}
}
/*
	Mass handling 

	will be called  after ed_fm_simulate :
	you should collect mass changes in ed_fm_simulate 

	double delta_mass = 0;
	double x = 0;
	double y = 0; 
	double z = 0;
	double piece_of_mass_MOI_x = 0;
	double piece_of_mass_MOI_y = 0; 
	double piece_of_mass_MOI_z = 0;
 
	//
	while (ed_fm_change_mass(delta_mass,x,y,z,piece_of_mass_MOI_x,piece_of_mass_MOI_y,piece_of_mass_MOI_z))
	{
	//internal DCS calculations for changing mass, center of gravity,  and moments of inertia
	}
*/
bool ed_fm_change_mass  (double & delta_mass,
						double & delta_mass_pos_x,
						double & delta_mass_pos_y,
						double & delta_mass_pos_z,
						double & delta_mass_moment_of_inertia_x,
						double & delta_mass_moment_of_inertia_y,
						double & delta_mass_moment_of_inertia_z
						)
{
	if (fuel_consumption_since_last_time > 0)
	{
		delta_mass		 = fuel_consumption_since_last_time;
		delta_mass_pos_x = -1.0;
		delta_mass_pos_y =  1.0;
		delta_mass_pos_z =  0;

		delta_mass_moment_of_inertia_x	= 0;
		delta_mass_moment_of_inertia_y	= 0;
		delta_mass_moment_of_inertia_z	= 0;

		fuel_consumption_since_last_time = 0; // set it 0 to avoid infinite loop, because it called in cycle 
		// better to use stack like structure for mass changing 
		return true;
	}
	else 
	{
		return false;
	}
}
/*
	set internal fuel volume , init function, called on object creation and for refueling , 
	you should distribute it inside at different fuel tanks
*/
void   ed_fm_set_internal_fuel(double fuel)
{
	internal_fuel = fuel;
}
/*
	get internal fuel volume 
*/
double ed_fm_get_internal_fuel()
{
	return internal_fuel;
}
/*
	set external fuel volume for each payload station , called for weapon init and on reload
*/
void  ed_fm_set_external_fuel (int	 station,
								double fuel,
								double x,
								double y,
								double z)
{

}
/*
	get external fuel volume 
*/
double ed_fm_get_external_fuel ()
{
	return 0;
}

void ed_fm_set_draw_args (EdDrawArgument * drawargs,size_t size)
{
	drawargs[28].f   = (float)throttle;
	drawargs[29].f   = (float)throttle;

	if (size > 616)
	{	
		drawargs[611].f = drawargs[0].f;
		drawargs[614].f = drawargs[3].f;
		drawargs[616].f = drawargs[5].f;
	}

	drawargs[LEFT_AILERON].f = -s_airframe.aileron();
	drawargs[RIGHT_AILERON].f = s_airframe.aileron();

	drawargs[LEFT_ELEVATOR].f = s_airframe.elevator();
	drawargs[RIGHT_ELEVATOR].f = s_airframe.elevator();

	drawargs[RUDDER].f = -s_airframe.rudder();

	drawargs[LEFT_FLAP].f = s_airframe.getFlapsPosition();
	drawargs[RIGHT_FLAP].f = s_airframe.getFlapsPosition();

	drawargs[LEFT_SLAT].f = s_airframe.getSlatsPosition();
	drawargs[RIGHT_SLAT].f = s_airframe.getSlatsPosition();

	drawargs[AIRBRAKE].f = s_airframe.getSpeedBrakePosition();

	s_airframe.setSpoilerPosition((drawargs[LEFT_SPOILER].f + drawargs[RIGHT_SPOILER].f)/2.0);

	drawargs[HOOK].f = s_airframe.getHookPosition();

	/*drawargs[LEFT_GEAR].f = s_airframe.getGearPosition();
	drawargs[RIGHT_GEAR].f = s_airframe.getGearPosition();
	drawargs[NOSE_GEAR].f = s_airframe.getGearPosition();
	drawargs[LEFT_GEAR_SHOCK].f = s_airframe.getGearPosition();
	drawargs[RIGHT_GEAR_SHOCK].f = s_airframe.getGearPosition();
	drawargs[NOSE_GEAR_SHOCK].f = s_airframe.getGearPosition();*/

}


void ed_fm_configure(const char * cfg_path)
{

}

double test_gear_state = 0;
double ed_fm_get_param(unsigned index)
{


	switch (index)
	{
	case ED_FM_SUSPENSION_0_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_1_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_2_GEAR_POST_STATE:
	case ED_FM_SUSPENSION_0_DOWN_LOCK:
	case ED_FM_SUSPENSION_1_DOWN_LOCK:
	case ED_FM_SUSPENSION_2_DOWN_LOCK:
	case ED_FM_SUSPENSION_0_UP_LOCK:
	case ED_FM_SUSPENSION_1_UP_LOCK:
	case ED_FM_SUSPENSION_2_UP_LOCK:
		return s_airframe.getGearPosition();
	case ED_FM_ANTI_SKID_ENABLE:
	case ED_FM_CAN_ACCEPT_FUEL_FROM_TANKER:
		return 1.0;
	case ED_FM_ENGINE_1_CORE_RPM:
	case ED_FM_ENGINE_1_RPM:
		return s_input.throttleNorm() * 3000;

	case ED_FM_ENGINE_1_TEMPERATURE:
		return 600.0;

	case ED_FM_ENGINE_1_OIL_PRESSURE:
		return 600.0;

	case ED_FM_ENGINE_1_FUEL_FLOW:
		return 5.0;

	case ED_FM_ENGINE_1_CORE_RELATED_THRUST:
	case ED_FM_ENGINE_1_RELATED_THRUST:
	case ED_FM_ENGINE_1_RELATED_RPM:
	case ED_FM_ENGINE_1_CORE_RELATED_RPM:
		return s_input.throttleNorm();

	case ED_FM_ENGINE_1_CORE_THRUST:
	case ED_FM_ENGINE_1_THRUST:
		return s_fm.thrust();
	case ED_FM_ENGINE_1_COMBUSTION:
		return 1.0;
	case ED_FM_SUSPENSION_1_RELATIVE_BRAKE_MOMENT:
		return s_input.normalise(s_input.brakeLeft());
	case ED_FM_SUSPENSION_2_RELATIVE_BRAKE_MOMENT:
		return s_input.normalise(s_input.brakeRight());
	}

	return 0;

}


void ed_fm_cold_start()
{
	s_fm.coldInit();
	s_airframe.coldInit();
}

void ed_fm_hot_start()
{
	s_fm.hotInit();
	s_airframe.hotInit();
}

void ed_fm_hot_start_in_air()
{
	s_fm.airbornInit();
	s_airframe.airborneInit();
}

bool ed_fm_add_local_force_component( double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z )
{
	return false;
}

bool ed_fm_add_global_force_component( double & x,double &y,double &z,double & pos_x,double & pos_y,double & pos_z )
{
	return false;
}

bool ed_fm_add_local_moment_component( double & x,double &y,double &z )
{
	return false;
}

bool ed_fm_add_global_moment_component( double & x,double &y,double &z )
{
	return false;
}

double ed_fm_get_shake_amplitude()
{
	return 0.0;
}

void ed_fm_suspension_feedback(int idx, const ed_fm_suspension_info* info)
{
	//printf("Force(%lf, %lf, %lf)\n", info->acting_force[0], info->acting_force[1], info->acting_force[2]);
	//printf("Position(%lf, %lf, %lf)\n", info->acting_force_point[0], info->acting_force_point[1], info->acting_force_point[2]);
	//printf("Struct Compression %d: %lf\n", idx, info->struct_compression);
	//printf("Integrity Factor: %lf", info->integrity_factor);
}
