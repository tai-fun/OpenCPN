#include "nmea0183.h"

/*
** Author: Samuel R. Blackburn
** CI$: 76300,326
** Internet: sammy@sed.csc.com
**
** You can use it any way you like.
*/


SENTENCE::SENTENCE()
{
   Sentence.Empty();
}

SENTENCE::~SENTENCE()
{
   Sentence.Empty();
}

NMEA0183_BOOLEAN SENTENCE::Boolean( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "A" )
   {
      return( NTrue );
   }
   else if ( field_data == "V" )
   {
      return( NFalse );
   }
   else
   {
      return( Unknown0183 );
   }
}

COMMUNICATIONS_MODE SENTENCE::CommunicationsMode( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "d" )
   {
      return( F3E_G3E_SimplexTelephone );
   }
   else if ( field_data == "e" )
   {
      return( F3E_G3E_DuplexTelephone );
   }
   else if ( field_data == "m" )
   {
      return( J3E_Telephone );
   }
   else if ( field_data == "o" )
   {
      return( H3E_Telephone );
   }
   else if ( field_data == "q" )
   {
      return( F1B_J2B_FEC_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "s" )
   {
      return( F1B_J2B_ARQ_NBDP_TelexTeleprinter );
   }
   else if ( field_data == "w" )
   {
      return( F1B_J2B_ReceiveOnlyTeleprinterDSC );
   }
   else if ( field_data == "x" )
   {
      return( A1A_MorseTapeRecorder );
   }
   else if ( field_data == "{" )
   {
      return( A1A_MorseKeyHeadset );
   }
   else if ( field_data == "|" )
   {
      return( F1C_F2C_F3C_FaxMachine );
   }
   else
   {
      return( CommunicationsModeUnknown );
   }
}

unsigned char SENTENCE::ComputeChecksum( void ) const
{
//   ASSERT_VALID( this );

   unsigned char checksum_value = 0;

   int string_length = Sentence.Len();
   int index = 1; // Skip over the $ at the begining of the sentence

   while( index < string_length    &&
          Sentence[ index ] != '*' &&
          Sentence[ index ] != CARRIAGE_RETURN &&
          Sentence[ index ] != LINE_FEED )
   {
      checksum_value ^= Sentence[ index ];
      index++;
   }

   return( checksum_value );
}

double SENTENCE::Double( int field_number ) const
{
 //  ASSERT_VALID( this );

   return( ::atof( Field( field_number ) ) );
}


EASTWEST SENTENCE::EastOrWest( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "E" )
   {
      return( East );
   }
   else if ( field_data == "W" )
   {
      return( West );
   }
   else
   {
      return( EW_Unknown );
   }
}

const wxString& SENTENCE::Field( int desired_field_number ) const
{
//   ASSERT_VALID( this );

   static wxString return_string;

   return_string.Empty();

   int index                = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;
   int string_length        = 0;

   string_length = Sentence.Len();

   while( current_field_number < desired_field_number && index < string_length )
   {
      if ( Sentence[ index ] == ',' || Sentence[ index ] == '*' )
      {
         current_field_number++;
      }

      index++;
   }

   if ( current_field_number == desired_field_number )
   {
      while( index < string_length    &&
             Sentence[ index ] != ',' &&
             Sentence[ index ] != '*' &&
             Sentence[ index ] != 0x00 )
      {
         return_string += Sentence[ index ];
         index++;
      }
   }

   return( return_string );
}

int SENTENCE::GetNumberOfDataFields( void ) const
{
//   ASSERT_VALID( this );

   int index                = 1; // Skip over the $ at the begining of the sentence
   int current_field_number = 0;
   int string_length        = 0;

   string_length = Sentence.Len();

   while( index < string_length )
   {
      if ( Sentence[ index ] == '*' )
      {
         return( (int) current_field_number );
      }

      if ( Sentence[ index ] == ',' )
      {
         current_field_number++;
      }

      index++;
   }

   return( (int) current_field_number );
}

void SENTENCE::Finish( void )
{
//   ASSERT_VALID( this );

   unsigned char checksum = ComputeChecksum();

   char temp_string[ 10 ];

   sprintf( temp_string, "*%02X%c%c", (int) checksum, CARRIAGE_RETURN, LINE_FEED );
   Sentence += temp_string;
}

int SENTENCE::Integer( int field_number ) const
{
//   ASSERT_VALID( this );

   return( ::atoi( Field( field_number ) ) );
}

NMEA0183_BOOLEAN SENTENCE::IsChecksumBad( int checksum_field_number ) const
{
//   ASSERT_VALID( this );

   /*
   ** Checksums are optional, return TRUE if an existing checksum is known to be bad
   */

   wxString checksum_in_sentence = Field( checksum_field_number );

   if ( checksum_in_sentence == "" )
   {
      return( Unknown0183 );
   }

   if ( ComputeChecksum() != HexValue( checksum_in_sentence ) )
   {
      return( NTrue );
   }

   return( NFalse );
}

LEFTRIGHT SENTENCE::LeftOrRight( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "L" )
   {
      return( Left );
   }
   else if ( field_data == "R" )
   {
      return( Right );
   }
   else
   {
      return( LR_Unknown );
   }
}

NORTHSOUTH SENTENCE::NorthOrSouth( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "N" )
   {
      return( North );
   }
   else if ( field_data == "S" )
   {
      return( South );
   }
   else
   {
      return( NS_Unknown );
   }
}

REFERENCE SENTENCE::Reference( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "B" )
   {
      return( BottomTrackingLog );
   }
   else if ( field_data == "M" )
   {
      return( ManuallyEntered );
   }
   else if ( field_data == "W" )
   {
      return( WaterReferenced );
   }
   else if ( field_data == "R" )
   {
      return( RadarTrackingOfFixedTarget );
   }
   else if ( field_data == "P" )
   {
      return( PositioningSystemGroundReference );
   }
   else
   {
      return( ReferenceUnknown );
   }
}

TRANSDUCER_TYPE SENTENCE::TransducerType( int field_number ) const
{
//   ASSERT_VALID( this );

   wxString field_data;

   field_data = Field( field_number );

   if ( field_data == "A" )
   {
      return( AngularDisplacementTransducer );
   }
   else if ( field_data == "D" )
   {
      return( LinearDisplacementTransducer );
   }
   else if ( field_data == "C" )
   {
      return( TemperatureTransducer );
   }
   else if ( field_data == "F" )
   {
      return( FrequencyTransducer );
   }
   else if ( field_data == "N" )
   {
      return( ForceTransducer );
   }
   else if ( field_data == "P" )
   {
      return( PressureTransducer );
   }
   else if ( field_data == "R" )
   {
      return( FlowRateTransducer );
   }
   else if ( field_data == "T" )
   {
      return( TachometerTransducer );
   }
   else if ( field_data == "H" )
   {
      return( HumidityTransducer );
   }
   else if ( field_data == "V" )
   {
      return( VolumeTransducer );
   }
   else
   {
      return( TransducerUnknown );
   }
}

/*
** Operators
*/

SENTENCE::operator wxString() const
{
//   ASSERT_VALID( this );

   return( Sentence );
}

const SENTENCE& SENTENCE::operator = ( const SENTENCE& source )
{
//   ASSERT_VALID( this );

   Sentence = source.Sentence;

   return( *this );
}

const SENTENCE& SENTENCE::operator = ( const wxString& source )
{
//   ASSERT_VALID( this );

   Sentence = source;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( const wxString& source )
{
//   ASSERT_VALID( this );

   Sentence += ",";
   Sentence += source;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( double value )
{
//   ASSERT_VALID( this );

   char temp_string[ 80 ];

   sprintf( temp_string, "%.3f", value );

   Sentence += ",";
   Sentence += temp_string;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( COMMUNICATIONS_MODE mode )
{
//   ASSERT_VALID( this );

   Sentence += ",";

   switch( mode )
   {
      case F3E_G3E_SimplexTelephone:

            Sentence += "d";
               break;

      case F3E_G3E_DuplexTelephone:

            Sentence += "e";
               break;

      case J3E_Telephone:

            Sentence += "m";
               break;

      case H3E_Telephone:

            Sentence += "o";
               break;

      case F1B_J2B_FEC_NBDP_TelexTeleprinter:

            Sentence += "q";
               break;

      case F1B_J2B_ARQ_NBDP_TelexTeleprinter:

            Sentence += "s";
               break;

      case F1B_J2B_ReceiveOnlyTeleprinterDSC:

            Sentence += "w";
               break;

      case A1A_MorseTapeRecorder:

            Sentence += "x";
               break;

      case A1A_MorseKeyHeadset:

            Sentence += "{";
               break;

       case F1C_F2C_F3C_FaxMachine:

           Sentence += "|";
           break;

       case CommunicationsModeUnknown:

           break;
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( TRANSDUCER_TYPE transducer )
{
//   ASSERT_VALID( this );

   Sentence += ",";

   switch( transducer )
   {
      case TemperatureTransducer:

            Sentence += "C";
               break;

      case AngularDisplacementTransducer:

            Sentence += "A";
               break;

      case LinearDisplacementTransducer:

            Sentence += "D";
               break;

      case FrequencyTransducer:

            Sentence += "F";
               break;

      case ForceTransducer:

            Sentence += "N";
               break;

      case PressureTransducer:

            Sentence += "P";
               break;

      case FlowRateTransducer:

            Sentence += "R";
               break;

      case TachometerTransducer:

            Sentence += "T";
               break;

      case HumidityTransducer:

            Sentence += "H";
               break;

      case VolumeTransducer:

            Sentence += "V";
               break;

      case TransducerUnknown:

            Sentence += "?";
               break;

   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( NORTHSOUTH northing )
{
//   ASSERT_VALID( this );

   Sentence += ",";

   if ( northing == North )
   {
      Sentence += "N";
   }
   else if ( northing == South )
   {
      Sentence += "S";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( int value )
{
//   ASSERT_VALID( this );

   char temp_string[ 80 ];

   sprintf( temp_string, "%d", value );

   Sentence += ",";
   Sentence += temp_string;

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( EASTWEST easting )
{
//   ASSERT_VALID( this );

   Sentence += ",";

   if ( easting == East )
   {
      Sentence += "E";
   }
   else if ( easting == West )
   {
      Sentence += "W";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( NMEA0183_BOOLEAN boolean )
{
//   ASSERT_VALID( this );

   Sentence += ",";

   if ( boolean == NTrue )
   {
      Sentence += "A";
   }
   else if ( boolean == NFalse )
   {
      Sentence += "V";
   }

   return( *this );
}

const SENTENCE& SENTENCE::operator += ( LATLONG& source )
{
//   ASSERT_VALID( this );

   source.Write( *this );

   return( *this );
}
