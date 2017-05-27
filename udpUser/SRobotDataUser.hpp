/*
 * SRobotDataUser.hpp
 *
 *  Created on: May 27, 2017
 *      Author: Robert
 */

#ifndef SROBOTDATAUSER_HPP_
#define SROBOTDATAUSER_HPP_

#include <string>
#include "orx_def_user.hpp"
#include "TunedParameters.hpp"


namespace orobotix {

  class SRobotDataUser {
  public:
    SRobotDataUser() {
      config_id_ = 1;

      // initialize imu
      for (int i = 0; i < 6; i++)
        imu_[i] = 0;

      // initialize commended Eular angle
      for (int i = 0; i < 3; i++)
        c_EularAngle_[i] = 0;

      // initialize goal posture [yaw, pitch, roll] : unit:degree */
      for (int i = 0; i < 3; i++)
        goal_Eular_[i] = 0;

      // user input - forces and moments
      for (int i = 0; i < 6; i++)
        c_forces_moments_[i] = 0;

      // control gain
      for (int i = 0; i < 6; i++) {
        ctr_kp_[i] = 0;
        cur_ctr_kp_[i] = 0;
        ctr_kv_[i] = 0;
        cur_ctr_kv_[i] = 0;
        ctr_ki_[i] = 0;
        cur_ctr_ki_[i] = 0;
      }

      sampling_rate_control_ = 0;
      sampling_rate_imu_ = 0;
      sampling_rate_ps_ = 0;

      temperature_in_ = 0;
      temperature_out_ = 0;

      batteryVolt_ = 0;
      total_current_ = 0;
      led_brightness_top_ = 0;
      led_brightness_bot_ = 0;
      depth_ = 0;
      goal_depth_ = 0;
      depth_vel_ = 0;
      gimbal_Pitch_ = 0;//gimbal camera pitch unit:rad

      cur_max_thruster_acc_ = 20000;
      max_thruster_acc_ = 20000;
      for (int i = 0; i < 6; i++) {
        maxSpeed_fraction[i] = MAX_SPEED_DEFAULT_FRACTION[i];
      }
      depthLimit = DEPTH_LIMIT_DEFAULT;

      flag_enable_camera_[0] = 0;
      flag_enable_camera_[1] = 0;
      flag_enable_camera_[2] = 0;

      flag_enable_thruster_ = false;
      flag_enable_individual_control_ = false;
      flag_change_control_gain_ = false;
      flag_resetProgram_ = false;


    }

    ~SRobotDataUser() {}


    /** initialize the thruster information */
    void initThrusterInfo(int arg_thruster_N) {
      thrusterN_ = arg_thruster_N;
      //NSLog(@"initializing %d thrusters",thrusterN_);

      for (int i = 0; i < thrusterN_; i++) {
        c_rpm_[i] = 0;
        m_rpm_[i] = 0;
        t_rpm_[i] = 0;
      }

      // initialize alarmIndex
      for (int i = 0; i < thrusterN_; i++)
        alarmIndex_[i] = 0x00;
    }

    /** calculate the rotation matrix of the robot from imu data*/
    void updateOrientationMatrix() {
//		Eigen::AngleAxisd yawAngle(imu_[0]/180.0*3.14159, Eigen::Vector3d::UnitZ());
//		Eigen::AngleAxisd pitchAngle(imu_[1]/180.0*3.14159, Eigen::Vector3d::UnitY());
//		Eigen::AngleAxisd rollAngle(imu_[2]/180.0*3.14159, Eigen::Vector3d::UnitX());
//
//		Eigen::Quaternion<double> q = yawAngle * pitchAngle* rollAngle;
//		m_robot_R_ = q.matrix();
    }

    /** drone ip address */
    std::string droneIP_;

    /** drone port */
    int dronePort_;

    /** thruster number */
    int thrusterN_;

    /** robot configuration id. 1="inspector", 2="developer". */
    int config_id_;

    /** max speed in 6-axis [Vx; Vy; Vz; Wx; Wy; Wz] */
    float maxSpeed_fraction[6];

    // sensor
    //================================
    /** imu [yaw pitch roll; yaw_vel; pitch_vel; roll_vel]: unit:degree, degree/s*/
    float imu_[6];

    /** commanded rpm that was transmitted */
    int c_rpm_[6];

    /** measured rpm, coming from the motor controller */
    int m_rpm_[6];

    /** goal posture [yaw, pitch, roll] : unit:degree */
    float goal_Eular_[3];

    /** desired goal (unit:meter) */
    double goal_depth_;

    /** depth sensor (unit: meter) */
    double depth_;

    /** depth velocity (unit: m/s) */
    double depth_vel_;

    /** gimbal pitch (unit:rad) */
    float gimbal_Pitch_;

    // control loop rate (Hz)
    float sampling_rate_control_;

    // imu sampling rate (Hz)
    float sampling_rate_imu_;

    /** sampling rate of the pressure sensor (Hz) */
    float sampling_rate_ps_;

    /** temperature inside dome, which is measured from MPU9150. unit:degree */
    float temperature_in_;

    /** temperature outside dome, which is measured from the pressure sensor. unit:degree */
    float temperature_out_;

    /** input voltage */
    float batteryVolt_;

    /** total current (amp) */
    float total_current_;

    /** alarm index */
    unsigned char alarmIndex_[6];

    /** led brightness 0~100 */
    int led_brightness_top_;

    /** led brightness 0~100 */
    int led_brightness_bot_;

    // actuator
    //================================
    /** thruster rpm commanded by the UI. (Not necessarily transmitted yet) */
    int t_rpm_[6];

    /** user input - forces and moments */
    float c_forces_moments_[6];

    /** current max thruster acceleration (rpm/s^2) */
    int cur_max_thruster_acc_;

    /** max thruster acceleration (rpm/s^2) */
    int max_thruster_acc_;

    /** desired control gain - kp */
    float ctr_kp_[6];

    /** desired control gain - kv */
    float ctr_kv_[6];

    /** desired control gain - ki */
    float ctr_ki_[6];

    /** current control gain - kp */
    float cur_ctr_kp_[6];

    /** current control gain - kv */
    float cur_ctr_kv_[6];

    /** current control gain - ki */
    float cur_ctr_ki_[6];

    /** depth limit command */
    float depthLimit;

    // user command
    //================================
    /** commanded Eular angle [yaw pitch roll] */
    float c_EularAngle_[3];

    /** commanded robot pose;
     * rotation matrix for the orientation of the robot */
    //Eigen::MatrixXd c_robot_R_;

    /** flag for enabling the camera
        * 0:disabling camera.  1:low resolution camera. 2:high resolution camera */
    int flag_enable_camera_[3];

    /** flag for enabling thruster */
    bool flag_enable_thruster_;

    /** flag - enable slider control */
    bool flag_enable_individual_control_;

    /** flag - change control gain */
    bool flag_change_control_gain_;

    /** flag - reset program */
    bool flag_resetProgram_;

    /** true if drone should be on. Gets set false again after it's transmitted */
    bool drone_please_power_off;

    // robot status
    //================================
    /** measured robot pose
     * rotation matrix for the orientation of the robot */
    //Eigen::MatrixXd m_robot_R_;
  };

} // end of namespace

#endif /* SROBOTDATAUSER_HPP_ */