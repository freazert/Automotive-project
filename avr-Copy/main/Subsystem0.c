/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem0.c
 *
 * Code generated for Simulink model 'Subsystem0'.
 *
 * Model version                  : 1.30
 * Simulink Coder version         : 8.13 (R2017b) 24-Jul-2017
 * C/C++ source code generated on : Wed May 16 08:14:37 2018
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR (8-bit)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "headers/Subsystem0.h"

/* Named constants for Chart: '<Root>/Chart' */
#define IN_Active                      ((uint8_T)1U)
#define IN_NotActive                   ((uint8_T)2U)
#define IN_Suspend                     ((uint8_T)3U)
#define event_abrogate                 (2L)
#define event_activate                 (0L)
#define event_deactivate               (1L)
#define event_resume                   (3L)
#ifndef PORTABLE_WORDSIZES
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFU) ) || ( INT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFUL) ) || ( LONG_MAX != (0x7FFFFFFFL) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if 0

/* Skip this size verification because of preprocessor limitation */
#if ( ULLONG_MAX != (0xFFFFFFFFFFFFFFFFULL) ) || ( LLONG_MAX != (0x7FFFFFFFFFFFFFFFLL) )
#error Code was generated for compiler with different sized ulong_long/long_long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif
#endif
#endif                                 /* PORTABLE_WORDSIZES */

/* Block signals and states (auto storage) */
DW rtDW;

/* Previous zero-crossings (trigger) states */
PrevZCX rtPrevZCX;

/* External inputs (root inport signals with auto storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Forward declaration for local functions */
static void chartstep_c1_Subsystem0(const int32_T *sfEvent);

/* Function for Chart: '<Root>/Chart' */
static void chartstep_c1_Subsystem0(const int32_T *sfEvent)
{
  switch (rtDW.is_c1_Subsystem0) {
   case IN_Active:
    rtDW.active = true;
    rtDW.setSpeed = true;
    switch (*sfEvent) {
     case event_deactivate:
      rtDW.is_c1_Subsystem0 = IN_NotActive;
      rtDW.active = false;
      rtDW.setSpeed = false;
      break;

     case event_abrogate:
      rtDW.is_c1_Subsystem0 = IN_Suspend;
      rtDW.active = false;
      rtDW.setSpeed = true;
      break;
    }
    break;

   case IN_NotActive:
    rtDW.active = false;
    rtDW.setSpeed = false;
    if (*sfEvent == event_activate) {
      rtDW.is_c1_Subsystem0 = IN_Active;
      rtDW.active = true;
      rtDW.setSpeed = true;
    }
    break;

   default:
    rtDW.active = false;
    rtDW.setSpeed = true;
    switch (*sfEvent) {
     case event_deactivate:
      rtDW.is_c1_Subsystem0 = IN_NotActive;
      rtDW.active = false;
      rtDW.setSpeed = false;
      break;

     case event_resume:
      rtDW.is_c1_Subsystem0 = IN_Active;
      rtDW.active = true;
      rtDW.setSpeed = true;
      break;
    }
    break;
  }
}

/* Model step function */
void Subsystem0_step(void)
{
  uint32_T rtb_Subtract;
  uint64_T rtb_Add;
  int32_T sfEvent;
  boolean_T zcEvent_idx_0;
  boolean_T zcEvent_idx_1;
  boolean_T zcEvent_idx_2;
  boolean_T zcEvent_idx_3;

  /* Chart: '<Root>/Chart' incorporates:
   *  TriggerPort: '<S1>/input events'
   */
  /* Inport: '<Root>/activate1' */
  zcEvent_idx_0 = (rtU.activate1 && (rtPrevZCX.Chart_Trig_ZCE[0] != POS_ZCSIG));

  /* Inport: '<Root>/deactivate1' */
  zcEvent_idx_1 = (rtU.deactivate1 && (rtPrevZCX.Chart_Trig_ZCE[1] != POS_ZCSIG));

  /* Inport: '<Root>/abrogate1' */
  zcEvent_idx_2 = (rtU.abrogate1 && (rtPrevZCX.Chart_Trig_ZCE[2] != POS_ZCSIG));

  /* Inport: '<Root>/resume1' */
  zcEvent_idx_3 = (rtU.resume1 && (rtPrevZCX.Chart_Trig_ZCE[3] != POS_ZCSIG));
  if (zcEvent_idx_0 || zcEvent_idx_1 || zcEvent_idx_2 || zcEvent_idx_3) {
    if (zcEvent_idx_0) {
      sfEvent = event_activate;
      chartstep_c1_Subsystem0(&sfEvent);
    }

    if (zcEvent_idx_1) {
      sfEvent = event_deactivate;
      chartstep_c1_Subsystem0(&sfEvent);
    }

    if (zcEvent_idx_2) {
      sfEvent = event_abrogate;
      chartstep_c1_Subsystem0(&sfEvent);
    }

    if (zcEvent_idx_3) {
      sfEvent = event_resume;
      chartstep_c1_Subsystem0(&sfEvent);
    }
  }

  /* Inport: '<Root>/activate1' */
  rtPrevZCX.Chart_Trig_ZCE[0] = (ZCSigState)rtU.activate1;

  /* Inport: '<Root>/deactivate1' */
  rtPrevZCX.Chart_Trig_ZCE[1] = (ZCSigState)rtU.deactivate1;

  /* Inport: '<Root>/abrogate1' */
  rtPrevZCX.Chart_Trig_ZCE[2] = (ZCSigState)rtU.abrogate1;

  /* Inport: '<Root>/resume1' */
  rtPrevZCX.Chart_Trig_ZCE[3] = (ZCSigState)rtU.resume1;

  /* Outputs for Triggered SubSystem: '<Root>/Triggered Subsystem' incorporates:
   *  TriggerPort: '<S3>/Trigger'
   */
  if (rtDW.setSpeed && (rtPrevZCX.TriggeredSubsystem_Trig_ZCE != POS_ZCSIG)) {
    /* Inport: '<S3>/Current' incorporates:
     *  Inport: '<Root>/DesiredSpeed1'
     */
    rtDW.Current = rtU.DesiredSpeed1;
  }

  rtPrevZCX.TriggeredSubsystem_Trig_ZCE = (ZCSigState)rtDW.setSpeed;

  /* End of Outputs for SubSystem: '<Root>/Triggered Subsystem' */

  /* Outputs for Enabled SubSystem: '<Root>/Controller' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  if (rtDW.active) {
    if (!rtDW.Controller_MODE) {
      /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
      rtDW.DiscreteTimeIntegrator_DSTATE = 0UL;

      /* InitializeConditions for UnitDelay: '<S4>/UD'
       *
       * Block description for '<S4>/UD':
       *
       *  Store in Global RAM
       */
      rtDW.UD_DSTATE = 0UL;
      rtDW.Controller_MODE = true;
    }

    /* Sum: '<S2>/Subtract' incorporates:
     *  Inport: '<Root>/ActualSpeed1'
     *  Product: '<S2>/Divide'
     *  Product: '<S2>/Divide1'
     */
    rtb_Subtract = (uint32_T)((uint32_T)(uint64_T)((uint64_T)((uint64_T)
      rtDW.Current << 19) / 1843ULL) - (uint32_T)(uint64_T)((uint64_T)((uint64_T)
      rtU.ActualSpeed1 << 19) / 1843ULL));

    /* Sum: '<S2>/Add' incorporates:
     *  Constant: '<S2>/Ki'
     *  Constant: '<S2>/Kp'
     *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator'
     *  Product: '<S2>/Product'
     *  Product: '<S2>/Product1'
     */
    rtb_Add = (uint64_T)((uint64_T)((uint64_T)((uint64_T)(uint32_T)(uint64_T)
      ((uint64_T)((uint64_T)rtDW.DiscreteTimeIntegrator_DSTATE * 4096000ULL) /
       204800ULL) << 7) / 25ULL) + (uint64_T)(768000ULL * (uint64_T)rtb_Subtract));

    /* Saturate: '<S2>/Saturation' */
    if (rtb_Add < 8388608000ULL) {
      rtb_Add >>= 20;
      if (rtb_Add > 65535ULL) {
        rtb_Add = 65535ULL;
      }

      /* Outport: '<Root>/Power1' */
      rtY.Power1 = (uint16_T)rtb_Add;
    } else {
      /* Outport: '<Root>/Power1' */
      rtY.Power1 = 8000U;
    }

    /* End of Saturate: '<S2>/Saturation' */

    /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
    rtDW.DiscreteTimeIntegrator_DSTATE += rtb_Subtract;

    /* Update for UnitDelay: '<S4>/UD' incorporates:
     *  SampleTimeMath: '<S4>/TSamp'
     *
     * About '<S4>/TSamp':
     *  y = u * K where K = 1 / ( w * Ts )
     *
     * Block description for '<S4>/UD':
     *
     *  Store in Global RAM
     */
    rtDW.UD_DSTATE = (uint32_T)(uint64_T)((uint64_T)rtb_Subtract * 200ULL);
  } else {
    if (rtDW.Controller_MODE) {
      /* Disable for Outport: '<Root>/Power1' incorporates:
       *  Outport: '<S2>/Power'
       */
      rtY.Power1 = 0U;
      rtDW.Controller_MODE = false;
    }
  }

  /* End of Outputs for SubSystem: '<Root>/Controller' */
}

/* Model initialize function */
void Subsystem0_initialize(void)
{
  rtPrevZCX.Chart_Trig_ZCE[0] = POS_ZCSIG;
  rtPrevZCX.Chart_Trig_ZCE[1] = POS_ZCSIG;
  rtPrevZCX.Chart_Trig_ZCE[2] = POS_ZCSIG;
  rtPrevZCX.Chart_Trig_ZCE[3] = POS_ZCSIG;
  rtPrevZCX.TriggeredSubsystem_Trig_ZCE = POS_ZCSIG;

  /* Chart: '<Root>/Chart' */
  rtDW.is_c1_Subsystem0 = IN_NotActive;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
