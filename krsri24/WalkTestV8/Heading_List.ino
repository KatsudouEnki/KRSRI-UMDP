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
void heading_list(){
  //Heading di Home (mengarah ke korban)
  sp_home_n = 335;
  sp_home_m = 120;
  //Heading sebelum mengambil korban (mengarah ke korban)
  sp_korban1_n = 335;
  sp_korban1_m = 120;
  //Heading mengarah ke puing
  sp_puing1_n = 64;
  sp_puing1_m = 40;
  //Heading mengarah di obstacle miring
  sp_miring_n = 60;
  sp_miring_m = 60;
  
  sp_batu1_n = 55;
  sp_batu1_m = 55;
  
  sp_sz1_n = 55;
  sp_sz1_m = 55;
  
  sp_kelereng_n = 213;
  sp_kelereng_m = 213;
  
  sp_sz2_n = 321;
  sp_sz2_m = 120;
  
  sp_transisi_n_1 = 250;
  sp_transisi_n_2 = 313;
  sp_transisi_m_1 = 180;
  sp_transisi_m_2 = 120;
  
  sp_puing2_n = 321;
  sp_puing2_m = 120;
  
  sp_batu2_n = 321;
  sp_batu2_m = 210;
  
  sp_tangga_n = 321;
  sp_tangga_m = 141;
  
  sp_r10_n = 210;
  sp_r10_m = 110;
}
