#ifndef RES_HPP
#define RES_HPP
#include<stdint.h>
#include<map>
class resData{
public:
resData(uint8_t ptr[],uint32_t dataSize):p(ptr),size(dataSize){};
uint8_t* p;
uint32_t size;
};
class MResources{
public:
MResources();
std::map<std::string,resData*>resMap;
};
extern uint8_t res_fa_png[];extern uint32_t res_fa_png_size;
extern uint8_t res_so_png[];extern uint32_t res_so_png_size;
extern uint8_t res_re_png[];extern uint32_t res_re_png_size;
extern uint8_t res_la_png[];extern uint32_t res_la_png_size;
extern uint8_t res_do_png[];extern uint32_t res_do_png_size;
extern uint8_t res_mi_png[];extern uint32_t res_mi_png_size;
extern uint8_t res_ti_png[];extern uint32_t res_ti_png_size;
extern uint8_t res_cs_png[];extern uint32_t res_cs_png_size;
extern uint8_t res_cs_down_png[];extern uint32_t res_cs_down_png_size;
extern uint8_t res_h_png[];extern uint32_t res_h_png_size;
extern uint8_t res_g_png[];extern uint32_t res_g_png_size;
extern uint8_t res_21_png[];extern uint32_t res_21_png_size;
extern uint8_t res_2_png[];extern uint32_t res_2_png_size;
extern uint8_t res_1_png[];extern uint32_t res_1_png_size;
extern uint8_t res_donghua_png[];extern uint32_t res_donghua_png_size;
extern uint8_t res_U_wav[];extern uint32_t res_U_wav_size;
extern uint8_t res_T_wav[];extern uint32_t res_T_wav_size;
extern uint8_t res_Y_wav[];extern uint32_t res_Y_wav_size;
extern uint8_t res_W_wav[];extern uint32_t res_W_wav_size;
extern uint8_t res_R_wav[];extern uint32_t res_R_wav_size;
extern uint8_t res_bg_png[];extern uint32_t res_bg_png_size;
extern uint8_t res_J_wav[];extern uint32_t res_J_wav_size;
extern uint8_t res_S_wav[];extern uint32_t res_S_wav_size;
extern uint8_t res_X_wav[];extern uint32_t res_X_wav_size;
extern uint8_t res_Q_wav[];extern uint32_t res_Q_wav_size;
extern uint8_t res_E_wav[];extern uint32_t res_E_wav_size;
extern uint8_t res_H_wav[];extern uint32_t res_H_wav_size;
extern uint8_t res_G_wav[];extern uint32_t res_G_wav_size;
extern uint8_t res_V_wav[];extern uint32_t res_V_wav_size;
extern uint8_t res_N_wav[];extern uint32_t res_N_wav_size;
extern uint8_t res_F_wav[];extern uint32_t res_F_wav_size;
extern uint8_t res_M_wav[];extern uint32_t res_M_wav_size;
extern uint8_t res_D_wav[];extern uint32_t res_D_wav_size;
extern uint8_t res_A_wav[];extern uint32_t res_A_wav_size;
extern uint8_t res_B_wav[];extern uint32_t res_B_wav_size;
extern uint8_t res_C_wav[];extern uint32_t res_C_wav_size;
extern uint8_t res_Z_wav[];extern uint32_t res_Z_wav_size;
extern uint8_t res_ft_ttf[];extern uint32_t res_ft_ttf_size;
#endif
