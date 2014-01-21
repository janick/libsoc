#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "libsoc_pwm.h"
#include "libsoc_debug.h"

/**
 *
 * This pwm_test is intended to be run on beaglebone white hardware
 * and uses pins P9_42(gpio7) and P9_27 (gpio115) connected together.
 *
 * The GPIO_OUTPUT and INPUT defines can be changed to support any board
 * all you need to do is ensure that the two pins are connected together
 *
 */

#define PWM_OUTPUT_CHIP 0
#define PWM_CHIP_OUTPUT 1

int main(void)
{
  int ret = EXIT_SUCCESS;

  libsoc_set_debug(1);

  pwm *pwm = libsoc_pwm_request(PWM_OUTPUT_CHIP, PWM_CHIP_OUTPUT, LS_SHARED);

  if (!pwm)
  {
    printf("Failed to get PWM\n");
    goto fail;
  }

  libsoc_pwm_set_enabled(pwm, ENABLED);

  int enabled = libsoc_pwm_get_enabled(pwm);

  if (!enabled)
  {
    printf("Failed enabling test\n");
    ret = EXIT_FAILURE;
    goto fail;
  }

  libsoc_pwm_set_enabled(pwm, DISABLED);

  enabled = libsoc_pwm_get_enabled(pwm);

  if (enabled)
  {
    printf("Failed disabling test\n");
    ret = EXIT_FAILURE;
    goto fail;
  }

  libsoc_pwm_set_period(pwm, 10);

  int current_period = libsoc_pwm_get_period(pwm);

  if (current_period != 10)
  {
    printf("Failed period test\n");
    goto fail;
  }

  libsoc_pwm_set_duty_cycle(pwm, 5);

  int current_duty = libsoc_pwm_get_duty_cycle(pwm);

  if (current_duty != 5)
  {
    printf("Failed duty test\n");
  }

  libsoc_pwm_set_polarity(pwm, INVERSED);

  int polarity = libsoc_pwm_get_polarity(pwm);

  if (polarity != INVERSED)
  {
    printf("Failed polarity test\n");
    goto fail;
  }

  libsoc_pwm_set_polarity(pwm, NORMAL);

  polarity = libsoc_pwm_get_polarity(pwm);

  if (polarity != NORMAL)
  {
    printf("Failed polarity test\n");
    goto fail;
  }

  fail:

  libsoc_pwm_free(pwm);

  return ret;
}
