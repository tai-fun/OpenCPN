#if ! defined( NMEA_0183_HEADER )

#define NMEA_0183_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

//	Include wxWindows stuff
//#include "wx/wxprec.h"

//#ifndef  WX_PRECOMP
//  #include "wx/wx.h"
//#endif //precompiled headers
#include "wx/string.h"
#include "wx/list.h"

/*
** Include all the needed MFC stuff
*/

//#include <afx.h>
//#include <afxcoll.h>

/*
** Turn off the warning about precompiled headers, it is rather annoying
*/

#ifdef __WXMSW__
#pragma warning( disable : 4699 )
#endif

#define CARRIAGE_RETURN 0x0D
#define LINE_FEED       0x0A


typedef enum _NMEA0183_BOOLEAN
{
   Unknown0183 = 0,
   NTrue,
   NFalse
} NMEA0183_BOOLEAN;

typedef enum _leftright
{
   LR_Unknown = 0,
   Left,
   Right
} LEFTRIGHT;

typedef enum _eastwest
{
   EW_Unknown = 0,
   East,
   West
} EASTWEST;

typedef enum _northsouth
{
   NS_Unknown = 0,
   North,
   South
} NORTHSOUTH;

typedef enum _reference
{
   ReferenceUnknown = 0,
   BottomTrackingLog,
   ManuallyEntered,
   WaterReferenced,
   RadarTrackingOfFixedTarget,
   PositioningSystemGroundReference
} REFERENCE;

typedef enum _communicationsmode
{
   CommunicationsModeUnknown         = 0,
   F3E_G3E_SimplexTelephone          = 'd',
   F3E_G3E_DuplexTelephone           = 'e',
   J3E_Telephone                     = 'm',
   H3E_Telephone                     = 'o',
   F1B_J2B_FEC_NBDP_TelexTeleprinter = 'q',
   F1B_J2B_ARQ_NBDP_TelexTeleprinter = 's',
   F1B_J2B_ReceiveOnlyTeleprinterDSC = 'w',
   A1A_MorseTapeRecorder             = 'x',
   A1A_MorseKeyHeadset               = '{',
   F1C_F2C_F3C_FaxMachine            = '|'
} COMMUNICATIONS_MODE;

typedef enum _transducertype
{
   TransducerUnknown   = 0,
   AngularDisplacementTransducer = 'A',
   TemperatureTransducer         = 'C',
   LinearDisplacementTransducer  = 'D',
   FrequencyTransducer           = 'F',
   HumidityTransducer            = 'H',
   ForceTransducer               = 'N',
   PressureTransducer            = 'P',
   FlowRateTransducer            = 'R',
   TachometerTransducer          = 'T',
   VolumeTransducer              = 'V'
} TRANSDUCER_TYPE;

/*
** Misc Function Prototypes
*/

int HexValue( const char *hex_string );

wxString& expand_talker_id( const wxString & );
wxString& Hex( int value );
wxString& talker_id( const wxString& sentence );

#include "nmea0183.hpp"

#endif // NMEA0183_HEADER
