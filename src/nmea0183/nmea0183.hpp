#if ! defined( NMEA_0183_CLASS_HEADER )
#define NMEA_0183_CLASS_HEADER

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/

/*
** General Purpose Classes
*/

#include "Sentence.hpp"
#include "Response.hpp"
#include "LatLong.hpp"
//#include "LoranTD.hpp"
//#include "Manufact.hpp"
//#include "MList.hpp"
//#include "OmegaPar.hpp"
//#include "DeccaLOP.hpp"
//#include "RatioPls.hpp"
//#include "RadarDat.hpp"
//#include "FreqMode.hpp"

/*
** Response Classes
*/

/*
#include "AAM.hpp"
#include "ALM.hpp"
#include "APB.hpp"
#include "ASD.hpp"
#include "BEC.hpp"
#include "BOD.hpp"
#include "BWC.hpp"
#include "BWR.hpp"
#include "BWW.hpp"
#include "DBT.hpp"
#include "DCN.hpp"
#include "DPT.hpp"
#include "FSI.hpp"
#include "GGA.hpp"
#include "GLC.hpp"
#include "GLL.hpp"
#include "GXA.hpp"
#include "HDG.hpp"
#include "HDT.hpp"
#include "HSC.hpp"
#include "LCD.hpp"
#include "MTW.hpp"
#include "MWV.hpp"
#include "OLN.hpp"
#include "OSD.hpp"
#include "P.hpp"
#include "RMA.hpp"
*/
#include "RMB.hpp"
#include "RMC.HPP"
/*
#include "ROT.hpp"
#include "RPM.hpp"
#include "RSA.hpp"
#include "RSD.hpp"
#include "RTE.hpp"
#include "SFI.hpp"
#include "STN.hpp"
#include "TRF.hpp"
#include "TTM.hpp"
#include "VBW.hpp"
#include "VDR.hpp"
#include "VHW.hpp"
#include "VLW.hpp"
#include "VPW.hpp"
#include "VTG.hpp"
#include "WCV.hpp"
#include "WNC.hpp"
#include "WPL.hpp"
#include "XDR.hpp"
#include "XTE.hpp"
#include "XTR.hpp"
#include "ZDA.hpp"
#include "ZFO.hpp"
#include "ZTG.hpp"
*/

WX_DECLARE_LIST(RESPONSE, MRL);

class NMEA0183
{

   private:

      SENTENCE sentence;

      void initialize( void );

   protected:

      MRL response_table;

      void set_container_pointers( void );
      void sort_response_table( void );

   public:

      NMEA0183();
      virtual ~NMEA0183();

      /*
      ** NMEA 0183 Sentences we understand
      */

/*
      AAM Aam;
      ALM Alm;
      APB Apb;
      ASD Asd;
      BEC Bec;
      BOD Bod;
      BWC Bwc;
      BWR Bwr;
      BWW Bww;
      DBT Dbt;
      DCN Dcn;
      DPT Dpt;
      FSI Fsi;
      GGA Gga;
      GLC Glc;
      GLL Gll;
      GXA Gxa;
      HDG Hdg;
      HDT Hdt;
      HSC Hsc;
      LCD Lcd;
      MTW Mtw;
      MWV Mwv;
      OLN Oln;
      OSD Osd;
      P   Proprietary;
      RMA Rma;
*/
       RMB Rmb;
        RMC Rmc;
/*
      ROT Rot;
      RPM Rpm;
      RSA Rsa;
      RSD Rsd;
      RTE Rte;
      SFI Sfi;
      STN Stn;
      TRF Trf;
      TTM Ttm;
      VBW Vbw;
      VDR Vdr;
      VHW Vhw;
      VLW Vlw;
      VPW Vpw;
      VTG Vtg;
      WCV Wcv;
      WNC Wnc;
      WPL Wpl;
      XDR Xdr;
      XTE Xte;
      XTR Xtr;
      ZDA Zda;
      ZFO Zfo;
      ZTG Ztg;
*/
      wxString ErrorMessage; // Filled when Parse returns FALSE
      wxString LastSentenceIDParsed; // ID of the lst sentence successfully parsed
      wxString LastSentenceIDReceived; // ID of the last sentence received, may not have parsed successfully

      wxString TalkerID;
      wxString ExpandedTalkerID;

//      MANUFACTURER_LIST Manufacturers;

      virtual bool IsGood( void ) const;
      virtual bool Parse( void );

      NMEA0183& operator << ( const char *source );
      NMEA0183& operator >> ( wxString& destination );
};

#endif // NMEA_0183_CLASS_HEADER
