<?php
require_once 'default_table.class.inc';
class tb_mhs extends Default_Table
{
    // additional class variables go here
    function tb_mhs ()
    {
        $this->tablename       = 'tmst_mahasiswa';
        
		$this->fieldlist       = array('NO_KTP','Kode_perguruan_tinggi','Kode_program_studi','Kelas','NIM','Nama_mahasiswa','Jenis_kelamin','Tempat_lahir','Tanggal_lahir','Alamat','Kode_kota','Kode_provinsi','Kode_pos','Status_mahasiswa','Tahun_masuk','Batas_studi','Tanggal_masuk','Tanggal_lulus','IPK_akhir','Nomor_SK_yudisium','Tanggal_SK_yudisium','Nomor_seri_ijazah','Kode_prov_asal_pendidikan','Status_awal_mahasiswa','Sma_Asal','Kode_perguruan_tinggi_asal','Kode_program_studi_asal','NIM_asal','SKS_diakui','Kode_beasiswa','Kode_jenjang_pendidikan _sblm','Kode_pekerjaan','Nama_tempat_bekerja','Jalur_skripsi','Judul_skripsi','Bulan_awal_bimbingan','Bulan_akhir_bimbingan', 'ID_log_audit','Tgl_Log','password','Telepon','HP','mhscdate','mhsudate','optcdate','optcid','optudate','optuid','verifikasi','nm_file','validasi');
        
		$this->sql_orderby     = "";
		
		$this->fieldlist['NO_KTP'] = array('pkey' => 'y');
		        
				
    } // end class constructor

} // end class
?>

