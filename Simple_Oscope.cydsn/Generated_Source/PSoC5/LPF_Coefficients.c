#include "LPF.h"
#include "LPF_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelAFirCoefficients LPF_ChannelAFirCoefficients

/* Number of FIR filter taps are: 16 */

const uint8 CYCODE LPF_ChannelAFirCoefficients[LPF_FIR_A_SIZE] = 
{
 0x9Au, 0xF3u, 0xFFu, 0x00u, /* Tap(0), -0.00037837028503418 */

 0x7Cu, 0x41u, 0x00u, 0x00u, /* Tap(1), 0.0019984245300293 */

 0x04u, 0x20u, 0xFFu, 0x00u, /* Tap(2), -0.0068354606628418 */

 0x1Au, 0x4Fu, 0x02u, 0x00u, /* Tap(3), 0.0180389881134033 */

 0xB8u, 0xC5u, 0xFAu, 0x00u, /* Tap(4), -0.0408411026000977 */

 0x59u, 0xEEu, 0x0Au, 0x00u, /* Tap(5), 0.08539879322052 */

 0x4Du, 0x6Du, 0xE8u, 0x00u, /* Tap(6), -0.18416440486908 */

 0x12u, 0x39u, 0x50u, 0x00u, /* Tap(7), 0.626741647720337 */

 0x12u, 0x39u, 0x50u, 0x00u, /* Tap(8), 0.626741647720337 */

 0x4Du, 0x6Du, 0xE8u, 0x00u, /* Tap(9), -0.18416440486908 */

 0x59u, 0xEEu, 0x0Au, 0x00u, /* Tap(10), 0.08539879322052 */

 0xB8u, 0xC5u, 0xFAu, 0x00u, /* Tap(11), -0.0408411026000977 */

 0x1Au, 0x4Fu, 0x02u, 0x00u, /* Tap(12), 0.0180389881134033 */

 0x04u, 0x20u, 0xFFu, 0x00u, /* Tap(13), -0.0068354606628418 */

 0x7Cu, 0x41u, 0x00u, 0x00u, /* Tap(14), 0.0019984245300293 */

 0x9Au, 0xF3u, 0xFFu, 0x00u, /* Tap(15), -0.00037837028503418 */
};

