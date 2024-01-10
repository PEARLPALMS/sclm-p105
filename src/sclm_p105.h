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

#ifndef SCLM_P105_h
#define SCLM_P105_h
#include <Arduino.h>

// バージョン番号
#define SCLM_P105_VERSION 1.2

// 色定義
#define LED_BLACK     0xE0 // 黒
#define LED_BLUE      0xC0 // 青
#define LED_RED       0x60 // 赤
#define LED_VIOLET    0x40 // 紫
#define LED_GREEN     0xA0 // 緑
#define LED_LIGHTBLUE 0x80 // 水色
#define LED_YELLOW    0x20 // 黄
#define LED_WHITE     0x00 // 白

class SCLM_P105
{
  public:
    byte data[27];
    SCLM_P105(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7);
    void begin(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7);
    void begin();
    void setFillZero(boolean b);
    void printUp(double d, int c);
    void printUp(float f, int c);
    void printUp(int i, int c);
    void printUp(String s, int c);
    void printUp(long l, int c);
    void printDown(double d, int c);
    void printDown(float f, int c);
    void printDown(int i, int c);
    void printDown(String s, int c);
    void printDown(long l, int c);
    void mark0(int c);
    void mark1(int c);
    void mark2(int c);
    void mark3(int c);
    void mark4(int c);
    void mark5(int c);
    void mark6(int c);
    void mark7(int c);
    void mark8(int c);
    void mark9(int c);
    void mark10(int c);
    void mark11(int c);
    void markColon(int c);
    void markUpDot(int c);
    void markDownDot(int c);
    void update();
    void clear();
  private:
    void inputMark(int mark, int c);
    void transferData(int dataSize);
    void waitBusy();
};
#endif // SCLM_P105_h
