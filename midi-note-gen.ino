#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

static const unsigned ledPin = 6;      // midi shield LED
int note = 0;
int complete = 0;

void setup()
{
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin,LOW);
    Serial.begin(9600);
    MIDI.begin(1); //listen on channel 1
    MIDI.turnThruOff();
}

void BlinkLed(byte num)         
{
    for (byte i=0;i<num;i++)
    {
        digitalWrite(ledPin,HIGH);
        delay(50);
        digitalWrite(ledPin,LOW);
        delay(50);
    }
}

void loop()
{
    
   if (MIDI.read())              // If we have received a message    
    {
      switch(MIDI.getType())      // Get the type of the message we caught
        {
            case midi::NoteOn:       
                
                note = MIDI.getData1();
                //BlinkLed(complete);  // blink the LED a number of times
                //Serial.print("eggs");                        
                playnote(note,127,1);
                //scatter(note);              
                
                break;
                
            default:
                break;
        }

    }
}

void scatter(int x)
{
  int up_oct;
  int down_oct;
  int up_oct_2;
  int down_oct_2;
  up_oct = x+12;
  up_oct_2 = x+24;
  down_oct = x-12;
  down_oct_2 = x-24;
  delay(rnd);
  playnote(up_oct,127,1);
  delay(rnd);
  playnote(down_oct_2,127,1);
  delay(rnd);
  playnote(up_oct_2,20,1);
  delay(rnd);
  playnote(down_oct,20,1);
 
}

void playnote(int note,int vel, int channel)
{
  MIDI.sendNoteOn(note+12, 127, 1);    // Send a Note (pitch 22, velo 127 on channel 1)
  delay(10);                // Wait for a second
  MIDI.sendNoteOff(note+12, 0, 1); 
  delay(10);
  MIDI.sendNoteOn(note-12, 127, 1);    // Send a Note (pitch 22, velo 127 on channel 1)
  delay(10);                // Wait for a second
  MIDI.sendNoteOff(note-12, 0, 1); 
}

int rnd()
{
  random(50);
}


