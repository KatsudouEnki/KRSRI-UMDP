/* Keterangan singkatan
 * sp   = set_point
 * n    = normal
 * m    = mirror
 * sz   = safe zone
 * //
 * nomor di akhir variabel merupakan urutan kemunculan/pemakaian variabel apabila 
 *  terdapat lebih dari satu kali penggunaan setpoint yang berbeda pada misi yang sama
 * //
 */

/* 
 *  home BNO= 5
 *  home compass hp = 270
 *  
 *  puing BNO= 96
 *  puing Compass 10
 *  
 *  kelereng BNO = 255
 *  kelereng compss 167
 */

void heading_list(){
  /* */
  //Heading di Home (mengarah ke korban)
  sp_home_n = 32;
  sp_home_m = 212;
  //Heading sebelum mengambil korban (mengarah ke korban)
  sp_korban1_n = sp_home_n;
  sp_korban1_m = sp_home_m;
  //Heading mengarah ke puing
  sp_puing1_n = 284;
  sp_puing1_m = 122;
  //Heading mengarah di obstacle miring
  sp_miring_n = sp_puing1_n;
  sp_miring_m = sp_puing1_m;
  //Heading mengarah di obstacle batu
  sp_batu1_n = sp_puing1_n;
  sp_batu1_m = sp_puing1_m;
  //Heading mengarah di safe_zone
  sp_sz1_n = sp_puing1_n;
  sp_sz1_m = sp_puing1_m;
  //Heading mengarah di obstacle kelereng dan korban 2
  sp_kelereng_n = 104;
  sp_kelereng_m = 313;
  //heading mengarah safezone 2
  sp_sz2_n = 25;
  sp_sz2_m = 227;
  
  sp_transisi_n_1 = 9;//belum
  sp_transisi_n_2 = 54;//belum
  sp_transisi_m_1 = 265;
  sp_transisi_m_2 = 244;
  
  sp_puing2_n = 5;//belum
  sp_puing2_m = 221;
  
  sp_batu2_n = sp_puing2_n;//belum
  sp_batu2_m = sp_puing2_m;
  
  sp_tangga_n = sp_puing2_n;//belum
  sp_tangga_m = 38;
  
  sp_r10_n = 302;//belum
  sp_r10_m = 302;
  /* */

  /* Start of Area testing *
  //Heading di Home (mengarah ke korban)
  sp_home_n = 200;
  sp_home_m = 5;
  //Heading sebelum mengambil korban (mengarah ke korban)
  sp_korban1_n = sp_home_n;
  sp_korban1_m = sp_home_m;
  //Heading mengarah ke puing
  sp_puing1_n = 313;
  sp_puing1_m = 276;
  //Heading mengarah di obstacle miring
  sp_miring_n = sp_puing1_n;
  sp_miring_m = sp_puing1_m;
  //Heading mengarah ke obstacke batu dkn 
  sp_batu1_n = sp_puing1_n;
  sp_batu1_m = sp_puing1_m;
  
  sp_sz1_n = sp_puing1_n;
  sp_sz1_m = sp_puing1_m;
  
  sp_kelereng_n = 133;
  sp_kelereng_m = 106;
  
  sp_sz2_n = 223;
  sp_sz2_m = 5;
  
  sp_transisi_n_1 = 173;
  sp_transisi_n_2 = 218;
  sp_transisi_m_1 = 58;
  sp_transisi_m_2 = 99;
  
  sp_puing2_n = 218;
  sp_puing2_m = 5;
  
  sp_batu2_n = 206;
  sp_batu2_m = 8;
  
  sp_tangga_n = sp_batu2_n;
  sp_tangga_m = sp_batu2_m;
  
  sp_r10_n = 106;
  sp_r10_m = 99;
  /* End of Area Testing */
}
