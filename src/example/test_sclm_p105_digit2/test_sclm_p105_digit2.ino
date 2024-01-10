 /**
 * SCLM-P105
 * 2021/03/09 Tue pearlpalms@gmail.com
 * $Id:$
 *
 * SCLM-P105 <-> Arduino
 *  (VSS)  1 <-> GND
 *  (VDD)  2 <-> +5V
 *   (NC)  3 <-> ---
 * (BUSY)  4 <-> D2
 *  (CLK)  5 <-> D3
 *  (/CS)  6 <-> D4
 *  (DB0)  7 <-> D5
 *  (DB1)  8 <-> D6
 *  (DB2)  9 <-> D7
 *  (DB3) 10 <-> D8
 *  (DB4) 11 <-> D9
 *  (DB5) 12 <-> D10
 *  (DB6) 13 <-> D11
 *  (DB7) 14 <-> D12
 */

// SCLM_P105ライブラリ
#include <sclm_p105.h>

// デバッグ
#define DEBUG
#undef DEBUG
#define DEBUG_BPS 115200

// ピン定義
#define BUSY 2
#define  CLK 3
#define   CS 4
#define  DB0 5
#define  DB1 6
#define  DB2 7
#define  DB3 8
#define  DB4 9
#define  DB5 10
#define  DB6 11
#define  DB7 12

// SCLM_P105クラス
SCLM_P105 sclm(BUSY, CLK, CS, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7);

void setup(){

  // シリアルポート初期化
#ifdef DEBUG
  Serial.begin(DEBUG_BPS);
  while(!Serial);
  Serial.sclm.println(F("SCLM-P105 Test $Id:$ " __FILE__));
#endif // DEBUG

  // SCLM初期化
  sclm.begin();
}

void loop(){

  // 全ての桁に0～Fを表示
  for(int i = 0; i <= 0x0F; i++){
    sclm.data[17] = sclm.data[18] = sclm.data[19] = sclm.data[20] = sclm.data[21] = i;
    sclm.data[22] = sclm.data[23] = sclm.data[24] = sclm.data[25] = sclm.data[26] = i;
    sclm.update();
    delay(500);
  }
}
