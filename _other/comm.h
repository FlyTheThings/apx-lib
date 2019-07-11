//=============================================================
#ifndef comm_H
#define comm_H
//=============================================================
#include <inttypes.h>
#include <sys/types.h>
#include <termios.h>
//=============================================================
class Comm
{
public:
  Comm();
  ~Comm();

  bool open(const char *portname="",int baudrate=0,const char *name="",int timeout=1,uint parity=0);
  void close();
  bool isOpen(void);
  int handle(void);
  bool isAvailable(const char *portname);

  void write(const uint8_t v);
  void write(const uint8_t *buf,uint cnt);
  void writeEscaped(const uint8_t *tbuf,uint dcnt);

  uint8_t read_char(void);
  uint read(uint8_t *buf,uint cnt);
  uint readEscaped(uint8_t *buf,uint max_len);

  uint8_t getCRC(const uint8_t *buf,uint cnt);
  unsigned int getRxCnt(void);
  unsigned int getTxCnt(void);
  uint isBusy(void);
  void flush(void);

  const char *name; //debug name
  uint brate; //baudrate
  const char *pname; //device name

private:
  int   fd;
  uint retry;
  uint8_t tmpBuf[4096];
  //ESC reader
  uint8_t esc_rx[4096];      //data from readEscaped()
  //uint8_t esc_tmp[16],esc_tmp_cnt;
  uint esc_state,esc_cnt,esc_crc,esc_pos_save;
  //uint esc_cnt_save;
};
//=============================================================
#endif