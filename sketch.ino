#include <mp3TF.h>
 
mp3TF mp3tf = mp3TF ();
unsigned int speed;
unsigned char prev_speed;
unsigned int speed_change_counter = 0;
boolean speed_changed = false;
 
void setup()
{
    mp3tf.init(&Serial);
    Serial.begin(9600);
}
 
unsigned int measureSpeed()
{
    return analogRead(A0);
}
 
void saySpeed()
{
    unsigned char pseudospeed = speed/40;
 
    if(pseudospeed == 0)
        mp3tf.stop();
    else if(pseudospeed > 6)
        mp3tf.play(7);
    else
        mp3tf.play(pseudospeed);
}
 
void loop()
{
    speed = measureSpeed();
 
    if (abs(speed-prev_speed) > 40 && speed/40 != prev_speed/40) {
        speed_change_counter = 0;
        speed_changed = true;
 
        prev_speed = speed;
    }
    else {
        if(speed_changed) {
            if(++speed_change_counter == 10) {
                speed_changed = false;
 
                saySpeed();
            }
        }
    }
 
    delay(100);
}
