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
  clockgen.setupPLL(SI5351_PLL_A, 24, 0, 1); // XTAL * (24 + 0/1) = 600 MHz (XTAL = 25 MHz)
  //clockgen.setupMultisynth(0, SI5351_PLL_A, 800, 275, 2); // PLLB/(800 + 275/2) = 600'000 / (937.5) = 640 kHz
  // по факту = 640.064 кГц, значит нужно убавить 64 Гц: 640'000 - 64 = 639'936
  clockgen.setupMultisynth(0, SI5351_PLL_A, 800, 275.187518, 2); // PLLB/(800 + 275.187518/2) = 600'000 / (937,593759) = 639'936 Hz
  // по факту = 640.062 кГц

  // нужно 1344 kHz
  clockgen.setupPLL(SI5351_PLL_B, 24, 0, 1); // XTAL * (24 + 0/1) = 600 MHz (XTAL = 25 MHz)
  //clockgen.setupMultisynth(1, SI5351_PLL_B, 445, 2.857142, 2); // PLLB/(445 + 2.857142/2) = 600 / (445 + 1.428571) = 1344 kHz
  // по факту = 1.34542 МГц, значит нужно убавить 1420 Гц: 1344000 - 1420 = 1'342'580
  clockgen.setupMultisynth(1, SI5351_PLL_B, 445, 3.8014866898, 2); // PLLB/(445 + 3.8014866898/2) = 600 / (445 + 1.900743) = 1'342'580 Hz
  // по факту = 1.34392 МГц

  /* Enable the clocks */
  clockgen.enableOutputs(true);
}

void loop(void)
{
}