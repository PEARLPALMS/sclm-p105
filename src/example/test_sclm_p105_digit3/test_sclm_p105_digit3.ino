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

  sclm.clear();
  sclm.update();

  // 上段数字部分の表示
  sclm.data[17] = 0x00;
  sclm.data[18] = 0x01;
  sclm.data[19] = 0x02;
  sclm.data[20] = 0x03;
  sclm.data[21] = 0x04;
  // コロン表示
  sclm.markColon(LED_LIGHTBLUE);
  // ドット表示
  sclm.markUpDot(LED_VIOLET);
  sclm.update();
  delay(500);

  // 下段数字部分の表示
  sclm.clear();
  sclm.update();
  sclm.data[22] = 0x05;
  sclm.data[23] = 0x06;
  sclm.data[24] = 0x07;
  sclm.data[25] = 0x08;
  sclm.data[26] = 0x09;
  // ドット表示
  sclm.markDownDot(LED_VIOLET);
  sclm.update();
  delay(500);
}
