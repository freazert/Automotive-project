/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem0.h
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

#ifndef RTW_HEADER_Subsystem0_h_
#define RTW_HEADER_Subsystem0_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#ifndef Subsystem0_COMMON_INCLUDES_
# define Subsystem0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#endif                                 /* Subsystem0_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef SS_INT64
#define SS_INT64                       18
#endif

#ifndef SS_UINT64
#define SS_UINT64                      19
#endif

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  uint32_T UD_DSTATE;                  /* '<S4>/UD' */
  uint32_T DiscreteTimeIntegrator_DSTATE;/* '<S2>/Discrete-Time Integrator' */
  uint16_T Current;                    /* '<S3>/Current' */
  uint8_T is_c1_Subsystem0;            /* '<Root>/Chart' */
  boolean_T active;                    /* '<Root>/Chart' */
  boolean_T setSpeed;                  /* '<Root>/Chart' */
  boolean_T Controller_MODE;           /* '<Root>/Controller' */
} DW;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState TriggeredSubsystem_Trig_ZCE;/* '<Root>/Triggered Subsystem' */
  ZCSigState Chart_Trig_ZCE[4];        /* '<Root>/Chart' */
} PrevZCX;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  boolean_T activate1;                 /* '<Root>/activate1' */
  boolean_T deactivate1;               /* '<Root>/deactivate1' */
  boolean_T abrogate1;                 /* '<Root>/abrogate1' */
  boolean_T resume1;                   /* '<Root>/resume1' */
  uint16_T DesiredSpeed1;              /* '<Root>/DesiredSpeed1' */
  uint16_T ActualSpeed1;               /* '<Root>/ActualSpeed1' */
} ExtU;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint16_T Power1;                     /* '<Root>/Power1' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (auto storage) */
extern DW rtDW;

/* External inputs (root inport signals with auto storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void Subsystem0_initialize(void);
extern void Subsystem0_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S4>/Data Type Duplicate' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Subsystem0'
 * '<S1>'   : 'Subsystem0/Chart'
 * '<S2>'   : 'Subsystem0/Controller'
 * '<S3>'   : 'Subsystem0/Triggered Subsystem'
 * '<S4>'   : 'Subsystem0/Controller/Discrete Derivative'
 */
#endif                                 /* RTW_HEADER_Subsystem0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
