#ifndef APT_COM_H_
#define APT_COM_H_


// Ref. Thorlabs APT Controllers Host-Controller Communications Protocol
// Caution: Not fully implemented!

// USB S/N    Type of product                          Thorlabs code
// 73xxxxxx   3-channel card slot brushless DC driver  BBD103 / BBD203

// RS232 Interface
// *** 115200 bps (bits per second)
// *** 8 data bits, 1 stop bit
// *** No parity
// *** RTS/CTS Handshake

// Communication Data Frame (header with data packet or not)
//   ------------------------------------------------------------
//  | byte 0 | byte 1 |   byte 2  |   byte 3   | byte 4 | byte 5 |
//  |------------------------------------------------------------
//  |   Message ID    |  param 1  |  param 2   |  dest  | source |   - Type 1
//  |------------------------------------------------------------
//  |   Message ID    |   data packet length   |  dest  | source |   - Type 2
//   ------------------------------------------------------------
// Description:
// Type 1 : Fixed Data Frame (6 bytes)
// Type 2 : Varibale Data Frame (6 bytess + data packet length)
// *** Type 2 is different from type 1 in byte 4:
// ***             dest in type 2: dest | 0x80
// dest   : the destination module
// source : the source of the message
// *** Source / dest code :
// ***             0x01   -    Host controller (i.e. PC, STM32 ...)
// ***             0x11   -    Motherboard (i.e. BBD203 Controller ...)
// ***             0x21   -    Bay 0 (i.e. X-asix ...)
// ***             0x22   -    Bay 1 (i.e. Y-axis ...)
// ***             etc.   -    ...
// ***             0x2A   -    Bay 9 
// ***             0x50   -    Generic USB hardware unit


// Another way to classify Data frame
// Type 1: Host       -> Controller
// Type 2: Controller -> Host




// Definition For Parameters 
// -------------------------
// Generic Variables
#define DEVICE_ID                     uint_8
#define HOST                          0x01
#define MotherBoard                   0x11
#define Bay_0                         0x21
#define Bay_1                         0x22
#define Bay_2                         0x23
#define Bay_3                         0x24
#define Bay_4                         0x25
#define Bay_5                         0x26
#define Bay_6                         0x27
#define Bay_7                         0x28
#define Bay_8                         0x29
#define Bay_9                         0x2A
#define Generic_USB                   0x50

#define CHANNEL_ID                    uint_8
#define CHANNEL_1                     0x01
#define CHANNEL_2                     0x02


// Message ID (no function related with a page_num behind)
#define MGMSG_MOD_IDENTIFY            0x0223

#define MGMSG_MOD_SET_CHANENABLESTATE 0x0220
#define MGMSG_MOD_REQ_CHANENABLESTATE 0x0221
#define MGMSG_MOD_GET_CHANEBABLESTATE 0x0212

#define MGMSG_HW_DISCONNECT           0x0002 // p.45
#define MGMSG_HW_RESPONSE             0x0080 // p.45
#define MGMSG_HW_RICHRESPONSE         0x0081 // p.46
#define MGMSG_HW_START_UPDATEMSGS     0x0011 // p.47
#define MGMSG_HW_STOP_UPDATEMSGS      0x0012 // p.47
#define MGMSG_HW_REQ_INFO             0x0005 // p.48
#define MGMSG_HW_GET_INFO             0x0006 // p.48

#define MGMSG_RACK_REQ_BAYUSED        0x0060 // p.50
#define MGMSG_RACK_GET_BAYUSED        0x0061 // p.50
#define MGMSG_HUB_REQ_BAYUSED         0x0065 // p.51
#define MGMSG_HUB_GET_BAYUSED         0x0066 // p.51

#define MGMSG_MOT_SET_VELPARAMS       0x0413
#define MGMSG_MOT_REQ_VELPARAMS       0x0414
#define MGMSG_MOT_GET_VELPARAMS       0x0415

#define MGMSG_MOT_SET_JOGPARAMS       0x0416
#define MGMSG_MOT_REQ_JOGPARAMS       0x0417
#define MGMSG_MOT_GET_JOGPARAMS       0x0418

#define MGMSG_MOT_ERQ_ADCINPUTS       0x042B  // p.65
#define MGMSG_MOT_GET_ADCINPUTS       0x042C  // p.65

#define MGMSG_MOT_SET_MOVERELPARAMS   0x0445  
#define MGMSG_MOT_REQ_MOVERELPARAMS   0x0446
#define MGMSG_MOT_GET_MOVERELPARAMS   0x0447

#define MGMSG_MOT_SET_MOVEABSPARAMS   0x0450
#define MGMSG_MOT_REQ_MOVEABSPARAMS   0x0451
#define MGMSG_MOT_GET_MOVEABSPARAMS   0x0452

#define MGMSG_MOT_SET_HOMEPARAMS      0x0440
#define MGMSG_MOT_REQ_HOMEPARAMS      0x0441
#define MGMSG_MOT_GET_HOMEPARAMS      0x0442

#define MGMSG_MOT_SET_LIMSWITCHPARAMS 0x0423
#define MGMSG_MOT_REQ_LIMSWITCHPARAMS 0x0424
#define MGMSG_MOT_GET_LIMSWITCHPARAMS 0x0425

#define MGMSG_MOT_MOVE_HOME           0x0443
#define MGMSG_MOT_MOVE_HOMED          0x0444

#define MGMSG_MOT_MOVE_RELATIVE       0x0448
#define MGMSG_MOT_MOVE_ABSOLUTE       0x0453 
#define MGMSG_MOT_MOVE_COMPLETED      0x0464

#define MGMSG_MOT_MOVE_JOG            0x046A
#define MGMSG_MOT_MOVE_VELOCITY       0x0457 // p.83
#define MGMSG_MOT_MOVE_STOP           0x0465 // p.84
#define MGMSG_MOT_MOVE_STOPPED        0x0466 // p.85



// Return State
#define APT_STATE                     uint_8
#define STATUS_OK                     0x00
#define STATUS_ERROR                  0x01




// Functions 
// 
void APT_IdentifyChannel(CHANNEL_ID ch);

APT_STATE APT_ChannelEnable(CHANNEL_ID ch);
chan_state APT_ChannelState(CHANNEL_ID ch);

APT_SET_VelParams();
APT_GET_VelParams();

APT_SET_JogParams();
APT_GET_JogParams();

APT_SET_MoveRelParams();
APT_GET_MoveRelParams();

APT_GET_ADCInputs();

APT_SET_MoveAbsParams();
APT_GET_MoveAbsParams();

APT_SET_HomeParams();
APT_GET_HomeParams();

APT_SET_LimSwitchParams();
APT_GET_LimSwitchParams();

APT_MOV_Home();
APT_MOV_Relative();
APT_MOV_Absolute();
APT_MOV_Jog();








// Functions 



#endif // APT_COM_H_