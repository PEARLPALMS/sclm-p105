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

  // 文字列表示(コロン、ドット込み)
  String s = "123:4.5";
  sclm.printUp(s, LED_WHITE);
  String t = "1234.5";
  sclm.printDown(t, LED_WHITE);
  sclm.update();
  delay(500);

  // 文字列表示
  String u = "32767";
  sclm.printUp(u, LED_YELLOW);
  sclm.printDown(u, LED_YELLOW);
  sclm.update();
  delay(500);

  // int表示(0-32767)
  int i = 32767;
  sclm.printUp(i, LED_LIGHTBLUE);
  sclm.printDown(i, LED_LIGHTBLUE);
  sclm.update();
  delay(500);

  // long表示(0-99999)
  long l = 99999L;
  sclm.printUp(l, LED_GREEN);
  sclm.printDown(l, LED_GREEN);
  sclm.update();
  delay(500);

  // float表示(0-9999.9) 小数点以下3桁目を四捨五入
  float f = 9999.855;
  sclm.printUp(f, LED_VIOLET);
  sclm.printDown(f, LED_VIOLET);
  sclm.update();
  delay(500);

  // double表示(0-9999.9) 小数点以下3桁目を四捨五入
  double d = 9999.855;
  sclm.printUp(d, LED_RED);
  sclm.printDown(d, LED_RED);
  sclm.update();
  delay(500);
}
