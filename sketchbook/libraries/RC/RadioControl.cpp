#include "RadioControl.h"

// Instantiates a default RCAxisChannel
RCAxisChannel* initRCAxisChannel( int pinIn, int highOffset, int lowOffset )
{
    RCAxisChannel* ch;

    ch = ( RCAxisChannel* )malloc( sizeof( RCAxisChannel ) );
    ch->pin = pinIn;

    ch->highOffset = highOffset;
    ch->lowOffset = lowOffset;

    //Sets the default output range
    ch->highOutput = STD_HIGH_OUTPUT;
    ch->lowOutput = STD_LOW_OUTPUT;

    ch->outputLevel = 0;

    return ch;
}

// Initiates a default RC Switch Channel
RCSwitchChannel* 
initRCSwitchChannel( int pinIn, int highOffset, int lowOffset )
{
    RCSwitchChannel* ch;

    ch = ( RCSwitchChannel* )malloc( sizeof( RCSwitchChannel ) );
    ch->pin = pinIn;

    ch->highOffset = highOffset;
    ch->lowOffset = lowOffset;

    ch->numberOfOptions = 2;
    ch->outputSelection = 0;


    return ch;
}

// Setups channels for testing
RC* initRC()
{
    RC* rc = ( RC* )malloc( sizeof( RC ) );

    if( rc == NULL ) return NULL;

    pinMode( rc->gearSwitch->pin, INPUT );

    rc->RSX = initRCAxisChannel( RSX_PIN, RSX_HIGH_OFFSET, RSX_LOW_OFFSET );
    pinMode( rc->RSX->pin, INPUT );

    rc->RSY = initRCAxisChannel( RSY_PIN, RSY_HIGH_OFFSET, RSY_LOW_OFFSET );
    pinMode( rc->RSY->pin, INPUT );

    rc->LSX = initRCAxisChannel( LSX_PIN, LSX_HIGH_OFFSET, LSX_LOW_OFFSET );
    pinMode( rc->LSX->pin, INPUT );

    rc->LSY = initRCAxisChannel( LSY_PIN, LSY_HIGH_OFFSET, LSY_LOW_OFFSET );
    pinMode( rc->LSY->pin, INPUT );

    rc->AUX = initRCAxisChannel( AUX_PIN, AUX_HIGH_OFFSET, AUX_LOW_OFFSET );
    setOutputRange( rc->AUX, 0, 1000 );
    pinMode( rc->AUX->pin, INPUT );

    rc->gearSwitch = initRCSwitchChannel(
                         GEAR_PIN,
                         GEAR_HIGH_OFFSET,
                         GEAR_LOW_OFFSET );

    return rc;
}


// Internal - Used to update all channels
void updateControllerValues( RC* rc )
{
    updateAxisPulse( rc->RSX );
    updateAxisPulse( rc->RSY );
    updateAxisPulse( rc->LSX );
    updateAxisPulse( rc->LSY );
    updateAxisPulse( rc->AUX );
    updateSwitchPulse( rc->gearSwitch );
}

// Sets a custom output range for axis/knob channels
void setOutputRange( RCAxisChannel* ch, int low, int high )
{
    ch->highOutput = high;
    ch->lowOutput = low;
}

/* Updates Channel from Pulses */
void updateAxisChannelOutput( RCAxisChannel* ch )
{
    updateAxisPulse( ch );
}

void updateSwitchChannelOutput( RCSwitchChannel* ch )
{
    updateSwitchPulse( ch );
}

/* Updates channel then returns channel output */
int getAxisOutput( RCAxisChannel* ch )
{
    updateAxisPulse( ch );
    return ch->outputLevel;
}

int getSwitchOutput( RCSwitchChannel* ch )
{
    updateSwitchPulse( ch );
    return ch->outputSelection;
}

/* Updates Channel and returns output,
 * But output is limited to the channel's range
 */
int getBoundedOutput( RCAxisChannel* ch )
{
    updateAxisPulse( ch );

    if( ch->outputLevel > ch->highOutput )
        return ch->highOutput;

    else if( ch->outputLevel < ch->lowOutput )
        return ch->lowOutput;

    else
        return ch->outputLevel;
}

/* Updates axis channel from pulse */
void updateAxisPulse( RCAxisChannel* ch )
{
    unsigned long pulseLength = pulseIn( ch->pin, HIGH, STD_TIMEOUT );
    ch->outputLevel = map( 
            pulseLength, ch->lowOffset, 
            ch->highOffset, ch->lowOutput, ch->highOutput );
}

/* Updates switch channel from pulse */
void updateSwitchPulse( RCSwitchChannel* ch )
{
    unsigned long pulseLength = pulseIn( ch->pin, HIGH, STD_TIMEOUT );
    ch->outputSelection = map( 
            pulseLength, ch->lowOffset, 
            ch->highOffset, 0, ch->numberOfOptions - 1 );
}

//void printAll(RC *rc){
  //printAll(rc->RSX,rc->RSY,rc->LSX,rc->LSY,rc->AUX,rc->gearSwitch);
//}

//void printAll(RCAxisChannel *RSX, RCAxisChannel *RSY, RCAxisChannel *LSX, RCAxisChannel *LSY, RCAxisChannel *AUX, RCSwitchChannel *gear){
  //Serial.print("(");
  //Serial.print(RSX->outputLevel);
  //Serial.print(", ");
  //Serial.print(RSY->outputLevel);
  //Serial.print(")       (");
  
  //Serial.print(LSX->outputLevel);
  //Serial.print(", ");
  //Serial.print(LSY->outputLevel);
  //Serial.print(")       (");
  
  //Serial.print(AUX->outputLevel);
  //Serial.print(")\t");
  
  //Serial.print("[");
  //Serial.print(gear->outputSelection);
  //Serial.print("]\n");
//}
