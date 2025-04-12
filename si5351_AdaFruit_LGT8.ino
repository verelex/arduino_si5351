#include <Adafruit_SI5351.h>

Adafruit_SI5351 clockgen = Adafruit_SI5351();

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Si5351 Clockgen Test"); Serial.println("");

  /* Initialise the sensor */
  if (clockgen.begin() != ERROR_NONE)
  {
    /* There was a problem detecting the IC ... check your connections */
    Serial.print("Ooops, no Si5351 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  Serial.println("OK!");

  /* FRACTIONAL MODE --> More flexible but introduce clock jitter */

  // нужно 640 kHz
  clockgen.setupPLL(SI5351_PLL_A, 35, 553, 625); // XTAL * (35 + 553/625) = 897.12 MHz ... (XTAL = 25 MHz)
  clockgen.setupMultisynth(0, SI5351_PLL_A, 1401, 3, 4); // PLLA/(1401 + 3/4) = 897.12 / 1401.75 = 0.64 MHz
  // по факту = 

  // нужно 1344 kHz
  clockgen.setupMultisynth(1, SI5351_PLL_A, 667, 1, 2); // PLLA/(667 + 1/2) = 897.12 / 667.5 = 1.344 MHz
  // по факту = 

  /* Enable the clocks */
  clockgen.enableOutputs(true);
}

void loop(void)
{
}
