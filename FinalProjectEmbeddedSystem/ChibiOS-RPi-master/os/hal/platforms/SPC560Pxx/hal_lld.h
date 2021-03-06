/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    SPC560Pxx/hal_lld.h
 * @brief   SPC560Pxx HAL subsystem low level driver header.
 * @pre     This module requires the following macros to be defined in the
 *          @p board.h file:
 *          - SPC5_XOSC_CLK.
 *          - SPC5_OSC_BYPASS (optionally).
 *          .
 *
 * @addtogroup HAL
 * @{
 */

#ifndef _HAL_LLD_H_
#define _HAL_LLD_H_

#include "xpc560p.h"
#include "spc560p_registry.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @brief   Defines the support for realtime counters in the HAL.
 */
#define HAL_IMPLEMENTS_COUNTERS FALSE

/**
 * @name    Platform identification
 * @{
 */
#define PLATFORM_NAME               "SPC560Pxx Chassis and Safety"
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Maximum XOSC clock frequency.
 */
#define SPC5_XOSC_CLK_MAX           40000000

/**
 * @brief   Minimum XOSC clock frequency.
 */
#define SPC5_XOSC_CLK_MIN           4000000

/**
 * @brief   Maximum FMPLLs input clock frequency.
 */
#define SPC5_FMPLLIN_MIN            4000000

/**
 * @brief   Maximum FMPLLs input clock frequency.
 */
#define SPC5_FMPLLIN_MAX            16000000

/**
 * @brief   Maximum FMPLLs VCO clock frequency.
 */
#define SPC5_FMPLLVCO_MAX           512000000

/**
 * @brief   Maximum FMPLLs VCO clock frequency.
 */
#define SPC5_FMPLLVCO_MIN           256000000

/**
 * @brief   Maximum FMPLL0 output clock frequency.
 */
#define SPC5_FMPLL0_CLK_MAX         64000000

/**
 * @brief   Maximum FMPLL1 output clock frequency.
 */
#define SPC5_FMPLL1_CLK_MAX         120000000

/**
 * @brief   Maximum FMPLL1 1D1 output clock frequency.
 */
#define SPC5_FMPLL1_1D1_CLK_MAX     80000000
/** @} */

/**
 * @name    Internal clock sources
 * @{
 */
#define SPC5_IRC_CLK                16000000    /**< Internal RC oscillator.*/
/** @} */

/**
 * @name    FMPLL_CR register bits definitions
 * @{
 */
#define SPC5_FMPLL_ODF_DIV2         (0U << 24)
#define SPC5_FMPLL_ODF_DIV4         (1U << 24)
#define SPC5_FMPLL_ODF_DIV8         (2U << 24)
#define SPC5_FMPLL_ODF_DIV16        (3U << 24)
/** @} */

/**
 * @name    ME_GS register bits definitions
 * @{
 */
#define SPC5_ME_GS_SYSCLK_MASK      (15U << 0)
#define SPC5_ME_GS_SYSCLK_IRC       (0U << 0)
#define SPC5_ME_GS_SYSCLK_XOSC      (2U << 0)
#define SPC5_ME_GS_SYSCLK_FMPLL0    (4U << 0)
#define SPC5_ME_GS_SYSCLK_FMPLL1    (5U << 0)
/** @} */

/**
 * @name    ME_ME register bits definitions
 * @{
 */
#define SPC5_ME_ME_RESET            (1U << 0)
#define SPC5_ME_ME_TEST             (2U << 0)
#define SPC5_ME_ME_SAFE             (4U << 0)
#define SPC5_ME_ME_DRUN             (8U << 0)
#define SPC5_ME_ME_RUN0             (16U << 0)
#define SPC5_ME_ME_RUN1             (32U << 0)
#define SPC5_ME_ME_RUN2             (64U << 0)
#define SPC5_ME_ME_RUN3             (128U << 0)
#define SPC5_ME_ME_HALT0            (256U << 0)
#define SPC5_ME_ME_STOP0            (1024U << 0)
/** @} */

/**
 * @name    ME_xxx_MC registers bits definitions
 * @{
 */
#define SPC5_ME_MC_SYSCLK_MASK      (15U << 0)
#define SPC5_ME_MC_SYSCLK(n)        ((n) << 0)
#define SPC5_ME_MC_SYSCLK_IRC               SPC5_ME_MC_SYSCLK(0)
#define SPC5_ME_MC_SYSCLK_XOSC              SPC5_ME_MC_SYSCLK(2)
#define SPC5_ME_MC_SYSCLK_FMPLL0            SPC5_ME_MC_SYSCLK(4)
#define SPC5_ME_MC_SYSCLK_FMPLL1            SPC5_ME_MC_SYSCLK(5)
#define SPC5_ME_MC_SYSCLK_DISABLED          SPC5_ME_MC_SYSCLK(15)
#define SPC5_ME_MC_IRCON            (1U << 4)
#define SPC5_ME_MC_XOSC0ON          (1U << 5)
#define SPC5_ME_MC_PLL0ON           (1U << 6)
#define SPC5_ME_MC_PLL1ON           (1U << 7)
#define SPC5_ME_MC_CFLAON_MASK      (3U << 16)
#define SPC5_ME_MC_CFLAON(n)        ((n) << 16)
#define SPC5_ME_MC_CFLAON_PD        (1U << 16)
#define SPC5_ME_MC_CFLAON_LP        (2U << 16)
#define SPC5_ME_MC_CFLAON_NORMAL    (3U << 16)
#define SPC5_ME_MC_DFLAON_MASK      (3U << 18)
#define SPC5_ME_MC_DFLAON(n)        ((n) << 18)
#define SPC5_ME_MC_DFLAON_PD        (1U << 18)
#define SPC5_ME_MC_DFLAON_LP        (2U << 18)
#define SPC5_ME_MC_DFLAON_NORMAL    (3U << 18)
#define SPC5_ME_MC_MVRON            (1U << 20)
#define SPC5_ME_MC_PDO              (1U << 23)
/** @} */

/**
 * @name    ME_MCTL register bits definitions
 * @{
 */
#define SPC5_ME_MCTL_KEY            0x5AF0U
#define SPC5_ME_MCTL_KEY_INV        0xA50FU
#define SPC5_ME_MCTL_MODE_MASK      (15U << 28)
#define SPC5_ME_MCTL_MODE(n)        ((n) << 28)
/** @} */

/**
 * @name    ME_RUN_PCx registers bits definitions
 * @{
 */
#define SPC5_ME_RUN_PC_TEST         (1U << 1)
#define SPC5_ME_RUN_PC_SAFE         (1U << 2)
#define SPC5_ME_RUN_PC_DRUN         (1U << 3)
#define SPC5_ME_RUN_PC_RUN0         (1U << 4)
#define SPC5_ME_RUN_PC_RUN1         (1U << 5)
#define SPC5_ME_RUN_PC_RUN2         (1U << 6)
#define SPC5_ME_RUN_PC_RUN3         (1U << 7)
/** @} */

/**
 * @name    ME_LP_PCx registers bits definitions
 * @{
 */
#define SPC5_ME_LP_PC_HALT0         (1U << 8)
#define SPC5_ME_LP_PC_STOP0         (1U << 10)
/** @} */

/**
 * @name    ME_PCTL registers bits definitions
 * @{
 */
#define SPC5_ME_PCTL_RUN_MASK       (7U << 0)
#define SPC5_ME_PCTL_RUN(n)         ((n) << 0)
#define SPC5_ME_PCTL_LP_MASK        (7U << 3)
#define SPC5_ME_PCTL_LP(n)          ((n) << 3)
#define SPC5_ME_PCTL_DBG            (1U << 6)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @brief   Disables the clocks initialization in the HAL.
 */
#if !defined(SPC5_NO_INIT) || defined(__DOXYGEN__)
#define SPC5_NO_INIT                FALSE
#endif

/**
 * @brief   Disables the overclock checks.
 */
#if !defined(SPC5_ALLOW_OVERCLOCK) || defined(__DOXYGEN__)
#define SPC5_ALLOW_OVERCLOCK        FALSE
#endif

/**
 * @brief   FMPLL0 IDF divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL0_IDF_VALUE) || defined(__DOXYGEN__)
#define SPC5_FMPLL0_IDF_VALUE       5
#endif

/**
 * @brief   FMPLL0 NDIV divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL0_NDIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_FMPLL0_NDIV_VALUE      32
#endif

/**
 * @brief   FMPLL0 ODF divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL0_ODF) || defined(__DOXYGEN__)
#define SPC5_FMPLL0_ODF             SPC5_FMPLL_ODF_DIV4
#endif

/**
 * @brief   FMPLL1 IDF divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL1_IDF_VALUE) || defined(__DOXYGEN__)
#define SPC5_FMPLL1_IDF_VALUE       5
#endif

/**
 * @brief   FMPLL1 NDIV divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL1_NDIV_VALUE) || defined(__DOXYGEN__)
#define SPC5_FMPLL1_NDIV_VALUE      60
#endif

/**
 * @brief   FMPLL1 ODF divider value.
 * @note    The default value is calculated for XOSC=40MHz and PHI=64MHz.
 */
#if !defined(SPC5_FMPLL1_ODF) || defined(__DOXYGEN__)
#define SPC5_FMPLL1_ODF             SPC5_FMPLL_ODF_DIV4
#endif

/**
 * @brief   Active run modes in ME_ME register.
 * @note    Modes RESET, SAFE, DRUN, and RUN0 modes are always enabled, there
 *          is no need to specify them.
 */
#if !defined(SPC5_ME_ME_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_ME_BITS                     (SPC5_ME_ME_RUN1 |              \
                                             SPC5_ME_ME_RUN2 |              \
                                             SPC5_ME_ME_RUN3 |              \
                                             SPC5_ME_ME_HALT0 |             \
                                             SPC5_ME_ME_STOP0)
#endif

/**
 * @brief   TEST mode settings.
 */
#if !defined(SPC5_ME_TEST_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_TEST_MC_BITS                (SPC5_ME_MC_SYSCLK_IRC |        \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   SAFE mode settings.
 */
#if !defined(SPC5_ME_SAFE_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_SAFE_MC_BITS                (SPC5_ME_MC_PDO)
#endif

/**
 * @brief   DRUN mode settings.
 */
#if !defined(SPC5_ME_DRUN_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_DRUN_MC_BITS                (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN0 mode settings.
 */
#if !defined(SPC5_ME_RUN0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN0_MC_BITS                (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN1 mode settings.
 */
#if !defined(SPC5_ME_RUN1_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN1_MC_BITS                (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN2 mode settings.
 */
#if !defined(SPC5_ME_RUN2_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN2_MC_BITS                (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   RUN3 mode settings.
 */
#if !defined(SPC5_ME_RUN3_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN3_MC_BITS                (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   HALT0 mode settings.
 */
#if !defined(SPC5_ME_HALT0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_HALT0_MC_BITS               (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   STOP0 mode settings.
 */
#if !defined(SPC5_ME_STOP0_MC_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_STOP0_MC_BITS               (SPC5_ME_MC_SYSCLK_FMPLL0 |     \
                                             SPC5_ME_MC_IRCON |             \
                                             SPC5_ME_MC_XOSC0ON |           \
                                             SPC5_ME_MC_PLL0ON |            \
                                             SPC5_ME_MC_PLL1ON |            \
                                             SPC5_ME_MC_CFLAON_NORMAL |     \
                                             SPC5_ME_MC_DFLAON_NORMAL |     \
                                             SPC5_ME_MC_MVRON)
#endif

/**
 * @brief   Peripheral mode 0 (run mode).
 * @note    Do not change this setting, it is expected to be the "never run"
 *          mode.
 */
#if !defined(SPC5_ME_RUN_PC0_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC0_BITS                0
#endif

/**
 * @brief   Peripheral mode 1 (run mode).
 * @note    Do not change this setting, it is expected to be the "always run"
 *          mode.
 */
#if !defined(SPC5_ME_RUN_PC1_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC1_BITS                (SPC5_ME_RUN_PC_TEST |          \
                                             SPC5_ME_RUN_PC_SAFE |          \
                                             SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 2 (run mode).
 * @note    Do not change this setting, it is expected to be the "only during
 *          normal run" mode.
 */
#if !defined(SPC5_ME_RUN_PC2_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC2_BITS                (SPC5_ME_RUN_PC_DRUN |          \
                                             SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 3 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC3_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC3_BITS                (SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 4 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC4_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC4_BITS                (SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 5 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC5_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC5_BITS                (SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 6 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC6_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC6_BITS                (SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 7 (run mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_RUN_PC7_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_RUN_PC7_BITS                (SPC5_ME_RUN_PC_RUN0 |          \
                                             SPC5_ME_RUN_PC_RUN1 |          \
                                             SPC5_ME_RUN_PC_RUN2 |          \
                                             SPC5_ME_RUN_PC_RUN3)
#endif

/**
 * @brief   Peripheral mode 0 (low power mode).
 * @note    Do not change this setting, it is expected to be the "never run"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC0_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC0_BITS                 0
#endif

/**
 * @brief   Peripheral mode 1 (low power mode).
 * @note    Do not change this setting, it is expected to be the "always run"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC1_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC1_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 2 (low power mode).
 * @note    Do not change this setting, it is expected to be the "halt only"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC2_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC2_BITS                 (SPC5_ME_LP_PC_HALT0)
#endif

/**
 * @brief   Peripheral mode 3 (low power mode).
 * @note    Do not change this setting, it is expected to be the "stop only"
 *          mode.
 */
#if !defined(SPC5_ME_LP_PC3_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC3_BITS                 (SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 4 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC4_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC4_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 5 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC5_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC5_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 6 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC6_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC6_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   Peripheral mode 7 (low power mode).
 * @note    Not defined, available to application-specific modes.
 */
#if !defined(SPC5_ME_LP_PC7_BITS) || defined(__DOXYGEN__)
#define SPC5_ME_LP_PC7_BITS                 (SPC5_ME_LP_PC_HALT0 |          \
                                             SPC5_ME_LP_PC_STOP0)
#endif

/**
 * @brief   PIT channel 3 IRQ priority.
 * @note    This PIT channel is allocated permanently for system tick
 *          generation.
 */
#if !defined(SPC5_PIT3_IRQ_PRIORITY) || defined(__DOXYGEN__)
#define SPC5_PIT3_IRQ_PRIORITY              4
#endif

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/* Check on the XOSC frequency.*/
#if (SPC5_XOSC_CLK < SPC5_XOSC_CLK_MIN) ||                                  \
    (SPC5_XOSC_CLK > SPC5_XOSC_CLK_MAX)
#error "invalid SPC5_XOSC_CLK value specified"
#endif

/* Check on SPC5_FMPLL0_IDF_VALUE.*/
#if (SPC5_FMPLL0_IDF_VALUE < 1) || (SPC5_FMPLL0_IDF_VALUE > 15)
#error "invalid SPC5_FMPLL0_IDF_VALUE value specified"
#endif

/* Check on SPC5_FMPLL0_NDIV_VALUE.*/
#if (SPC5_FMPLL0_NDIV_VALUE < 32) || (SPC5_FMPLL0_NDIV_VALUE > 96)
#error "invalid SPC5_FMPLL0_NDIV_VALUE value specified"
#endif

/* Check on SPC5_FMPLL0_ODF.*/
#if (SPC5_FMPLL0_ODF == SPC5_FMPLL_ODF_DIV2)
#define SPC5_FMPLL0_ODF_VALUE    2
#elif (SPC5_FMPLL0_ODF == SPC5_FMPLL_ODF_DIV4)
#define SPC5_FMPLL0_ODF_VALUE    4
#elif (SPC5_FMPLL0_ODF == SPC5_FMPLL_ODF_DIV8)
#define SPC5_FMPLL0_ODF_VALUE    8
#elif (SPC5_FMPLL0_ODF == SPC5_FMPLL_ODF_DIV16)
#define SPC5_FMPLL0_ODF_VALUE    16
#else
#error "invalid SPC5_FMPLL0_ODF value specified"
#endif

/**
 * @brief   SPC5_FMPLL0_VCO_CLK clock point.
 */
#define SPC5_FMPLL0_VCO_CLK                                                 \
  ((SPC5_XOSC_CLK / SPC5_FMPLL0_IDF_VALUE) * SPC5_FMPLL0_NDIV_VALUE)

/* Check on FMPLL0 VCO output.*/
#if (SPC5_FMPLL0_VCO_CLK < SPC5_FMPLLVCO_MIN) ||                            \
    (SPC5_FMPLL0_VCO_CLK > SPC5_FMPLLVCO_MAX)
#error "SPC5_FMPLL0_CLK outside acceptable range (SPC5_FMPLLVCO_MIN...SPC5_FMPLLVCO_MAX)"
#endif

/**
 * @brief   SPC5_FMPLL0_CLK clock point.
 */
#define SPC5_FMPLL0_CLK                                                     \
  (SPC5_FMPLL0_VCO_CLK / SPC5_FMPLL0_ODF_VALUE)

/* Check on SPC5_FMPLL0_CLK.*/
#if (SPC5_FMPLL0_CLK > SPC5_FMPLL0_CLK_MAX) && !SPC5_ALLOW_OVERCLOCK
#error "SPC5_FMPLL0_CLK outside acceptable range (0...SPC5_FMPLL0_CLK_MAX)"
#endif

/* Check on SPC5_FMPLL1_IDF_VALUE.*/
#if (SPC5_FMPLL1_IDF_VALUE < 1) || (SPC5_FMPLL1_IDF_VALUE > 15)
#error "invalid SPC5_FMPLL1_IDF_VALUE value specified"
#endif

/* Check on SPC5_FMPLL1_NDIV_VALUE.*/
#if (SPC5_FMPLL1_NDIV_VALUE < 32) || (SPC5_FMPLL1_NDIV_VALUE > 96)
#error "invalid SPC5_FMPLL1_NDIV_VALUE value specified"
#endif

/* Check on SPC5_FMPLL1_ODF.*/
#if (SPC5_FMPLL1_ODF == SPC5_FMPLL_ODF_DIV2)
#define SPC5_FMPLL1_ODF_VALUE    2
#elif (SPC5_FMPLL1_ODF == SPC5_FMPLL_ODF_DIV4)
#define SPC5_FMPLL1_ODF_VALUE    4
#elif (SPC5_FMPLL1_ODF == SPC5_FMPLL_ODF_DIV8)
#define SPC5_FMPLL1_ODF_VALUE    8
#elif (SPC5_FMPLL1_ODF == SPC5_FMPLL_ODF_DIV16)
#define SPC5_FMPLL1_ODF_VALUE    16
#else
#error "invalid SPC5_FMPLL1_ODF value specified"
#endif

/**
 * @brief   SPC5_FMPLL1_VCO_CLK clock point.
 */
#define SPC5_FMPLL1_VCO_CLK                                                 \
  ((SPC5_XOSC_CLK / SPC5_FMPLL1_IDF_VALUE) * SPC5_FMPLL1_NDIV_VALUE)

/* Check on FMPLL1 VCO output.*/
#if (SPC5_FMPLL1_VCO_CLK < SPC5_FMPLLVCO_MIN) ||                            \
    (SPC5_FMPLL1_VCO_CLK > SPC5_FMPLLVCO_MAX)
#error "SPC5_FMPLL1_CLK outside acceptable range (SPC5_FMPLLVCO_MIN...SPC5_FMPLLVCO_MAX)"
#endif

/**
 * @brief   SPC5_FMPLL1_CLK clock point.
 */
#define SPC5_FMPLL1_CLK                                                     \
  (SPC5_FMPLL1_VCO_CLK / SPC5_FMPLL1_ODF_VALUE)

/* Check on SPC5_FMPLL1_CLK.*/
#if (SPC5_FMPLL1_CLK > SPC5_FMPLL1_CLK_MAX) && !SPC5_ALLOW_OVERCLOCK
#error "SPC5_FMPLL1_CLK outside acceptable range (0...SPC5_FMPLL1_CLK_MAX)"
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

typedef enum {
  SPC5_RUNMODE_TEST  = 1,
  SPC5_RUNMODE_SAFE  = 2,
  SPC5_RUNMODE_DRUN  = 3,
  SPC5_RUNMODE_RUN0  = 4,
  SPC5_RUNMODE_RUN1  = 5,
  SPC5_RUNMODE_RUN2  = 6,
  SPC5_RUNMODE_RUN3  = 7,
  SPC5_RUNMODE_HALT0 = 8,
  SPC5_RUNMODE_STOP0 = 10
} spc560prunmode_t;

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void spc560p_clock_init(void);
  bool_t halSPC560PSetRunMode(spc560prunmode_t mode);
  void halSPC560PSetPeripheralClockMode(uint32_t n, uint32_t pctl);
#if !SPC5_NO_INIT
  uint32_t halSPC560PGetSystemClock(void);
#endif
#ifdef __cplusplus
}
#endif

#endif /* _HAL_LLD_H_ */

/** @} */
