<?php
 
 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/admin_app/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/admin_app/';		
	} 
    else{
	  $base_path = $server . '/admin_app/';	 
	}  
 }
 
 include_once $base_path.'db/tb_mhs.class.inc';
 

class dt_mhs
{
   var $tb;
   var $numrows;  
   
   var $ktp;
   var $prod; 
   var $Nama_mahasiswa;
   var $jenisKelamin;
   var $tanggalLahir;
   var $tahunMasuk;
   var $kelas;
   var $nim;
   var $status;
   var $status_awl;
   var $tempatLahir;
   var $alamat;
   var $kota;
   var $telepon;
   var $provinsi;
   var $hp;
   var $kodePos;
   var $tanggalLulus;
   var $tanggalMasuk;
   var $ipkAkhir;
   var $nomorSkYudisium;
   var $batasStudi;
   var $tanggalYudisium;
   var $nomorSeriIjazah;
   var $smaAsal;
   var $sksDiakui;
   var $namaTempatPekerjaan;
   var $kodePekerjaan;
   var $prodiAsal;
   var $universitasAsal;
   var $pass;
   var $optcdate;
   var $optcid; 
   var $optudate;
   var $optuid; 
   
   function dt_mhs(){
     $this->tb = new tb_mhs;
	 
   }
  
    function getJml($where)
    {	  
	  
	  $this->tb->sql_select ="*";
	  
	  $this->tb->tablename ="tmst_mahasiswa left join tmst_prodi on kode_program_studi = kd_prodi";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $this->numrows;		 
	  	  
	}

	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function KTPada($ktp)
	{
	  
	  $data = $this->getData("NO_KTP = '".$ktp."'");
	  
	  if(!empty($data)){
	    foreach($data as $row){
			  $this->prod = $row['Kode_program_studi']; 
			  $this->Nama_mahasiswa = $row['Nama_mahasiswa'];
			  $this->jenisKelamin  = $row['Jenis_kelamin'];
			  $this->tanggalLahir  = $row['Tanggal_lahir'];
			  $this->tahunMasuk  = $row['Tahun_masuk'];
			  $this->kelas = $row['Kelas'];
			  $this->nim  = $row['NIM'];
			  $this->status  = $row['Status_mahasiswa'];
			  $this->status_awl  = $row['Status_awal_mahasiswa'];
			  $this->tempatLahir  = $row['Tempat_lahir'];
			  $this->alamat  = $row['Alamat'];
			  $this->kota  = $row['Kode_kota'];
			  $this->telepon  = $row['Telepon'];
			  $this->provinsi  = $row['Kode_provinsi'];
			  $this->hp  = $row['HP'];
			  $this->kodePos  = $row['Kode_pos'];
			  $this->tanggalLulus  = $row['Tanggal_lulus'];
			  $this->tanggalMasuk  = $row['Tanggal_masuk'];
			  $this->ipkAkhir  = $row['IPK_akhir'];
			  $this->nomorSkYudisium  = $row['Nomor_SK_yudisium'];
			  $this->batasStudi  = $row['Batas_studi'];
			  $this->tanggalYudisium  = $row['Tanggal_SK_yudisium'];
			  $this->nomorSeriIjazah  = $row['Nomor_seri_ijazah'];
			  $this->smaAsal  = $row['Sma_Asal'];
			  $this->sksDiakui  = $row['SKS_diakui'];
			  $this->namaTempatPekerjaan  = $row['Nama_tempat_bekerja'];
			  $this->kodePekerjaan  = $row['Kode_pekerjaan'];
			  $this->prodiAsal  = $row['Kode_program_studi_asal'];
			  $this->universitasAsal  = $row['Kode_perguruan_tinggi_asal'];
		}	  
	  }
	  
	  return $this->numrows>0; 
	}
	
		
	function getDataEntri($where)
    {	  
	  
	  $this->tb->tablename ="tmst_mahasiswa left join tmst_prodi on kode_program_studi = kd_prodi";
	  
	  $this->tb->sql_orderby = "mhscdate desc";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}

	
	function getOrderedData($where)
    {	  
	  $this->tb->sql_select ="*";
	  $this->tb->tablename ="tmst_mahasiswa left join tmst_prodi on kode_program_studi = kd_prodi";	  
	  $this->tb->sql_orderby = "Nama_mahasiswa asc";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}	
	
	function update_verifikasi($no_ktp,$ver_flag,$optudate,$optuid)
    {
	  
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"verifikasi"=>$ver_flag,"optudate"=>$optudate ,"optuid"=>$optuid));
	  return 1;	 
	}
	
   function update_validasi($no_ktp,$valid)
    {
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"validasi"=>$valid));
	  return 1;	 
	}
	
	function update_tgl_msk($no_ktp,$tgl)
    {
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"Tanggal_masuk"=>$tgl));
	  return 1;	 
	}
	function getdataStat($where)
    {
	   
	  $this->tb->sql_select ="Tahun_masuk,
							  COUNT(`tmst_mahasiswa`.`NO_KTP`) AS `jmlttl`,
							  SUM(IF(kelas='R',1,0)) AS `jmlR`,
							  SUM(IF(kelas='N',1,0)) AS `jmlN`, 
							  SUM(IF(Status_awal_mahasiswa='B',1,0)) AS `jmlB`,
							  SUM(IF(Status_awal_mahasiswa='P',1,0)) AS `jmlP`, 
							  SUM(IF(((`tmst_mahasiswa`.`validasi` = 0) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlblmlyk`,
							  SUM(IF(((`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlval`,
							  SUM(IF(((`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`nm_file` <> '')),1,0)) AS `jmlsdver`,
							  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 1),1,0)) AS `jmlver`,
							  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 2),1,0)) AS `jmlnotver`";
	  $this->tb->sql_groupby ="Tahun_masuk";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="(tmst_mahasiswa INNER JOIN tmst_prodi ON kode_program_studi=tmst_prodi.kd_prodi)";
	  
	  $data = $this->tb->getData($where);  
	  
	  return $data;
	}
	
	function getdataStat1($where)
    {
	   
	  $this->tb->sql_select ="tmst_prodi.kd_fakultas,fakultas,tmst_prodi.kd_prodi,prodi,
							  COUNT(`tmst_mahasiswa`.`NO_KTP`) AS `jmlttl`,
							  SUM(IF(((`tmst_mahasiswa`.`validasi` = 0) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlblmlyk`,
							  SUM(IF(((`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlval`,
							  SUM(IF(((`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`nm_file` <> '')),1,0)) AS `jmlsdver`,
							  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 1),1,0)) AS `jmlver`,
							  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 2),1,0)) AS `jmlnotver`";
	  $this->tb->sql_groupby ="kd_fakultas,Kd_Prodi";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="(tmst_mahasiswa INNER JOIN tmst_prodi ON kode_program_studi=tmst_prodi.kd_prodi) INNER JOIN tmst_fakultas ON  tmst_fakultas.kd_fakultas=tmst_prodi.kd_fakultas";
	  
	  $data = $this->tb->getData($where);  
	  
	  return $data;
	}
	
	function getdataStat2($where)
    {
	   
	  $this->tb->sql_select ="   `tmst_prodi`.`kd_fakultas`     AS `kd_fakultas`,
	                             `tmst_fakultas`.`fakultas`     AS `fakultas`, 
								 `tmst_mahasiswa`.`Tahun_masuk` AS `Tahun_masuk`,
								  COUNT(`tmst_mahasiswa`.`NO_KTP`) AS `jmlttl`,
								  SUM(IF(((`tmst_mahasiswa`.`validasi` = 0) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlblmlyk`,  
								  SUM(IF(((`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlval`,
								  SUM(IF(((`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`nm_file` <> '')),1,0)) AS `jmlsdver`,
								  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 1),1,0)) AS `jmlver`,
								  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 2),1,0)) AS `jmlnotver`";
	  $this->tb->sql_groupby ="`tmst_prodi`.`kd_fakultas`,`tmst_mahasiswa`.`Tahun_masuk`";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="((`tmst_mahasiswa`
							   JOIN `tmst_prodi`
							   ON ((`tmst_prodi`.`kd_prodi` = `tmst_mahasiswa`.`Kode_program_studi`))) join tmst_fakultas on `tmst_prodi`.`kd_fakultas` =  `tmst_fakultas`.`kd_fakultas` )";
	  
	  $data = $this->tb->getData($where);  
	  
	  return $data;
	}
	
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 